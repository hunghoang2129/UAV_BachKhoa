/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mpu9255.h"
#include "IMU.h"
#include <math.h>
//#include "PWM_to_F.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define 	SAFETY_START 					1
#define		TX_CONTROLLER					1
#define		RUNNING_TIME					4000
#define 	AUTO_RUN							0
#define		YAW_CONTROLLER				1

//#define		KP_ROLL_PITCH					2.8f
//#define		KP_ROLL_PITCH_OMEGA		2.5f
//#define		KI_ROLL_PITCH_OMEGA		0.0122f
//#define		KD_ROLL_PITCH_OMEGA		12.3f
//#define		PID_MAX								450.0f
//#define		PID_MAX_INTEGRAL			300.0f

#define		KP_ROLL_PITCH					1.3f
#define		KP_ROLL_PITCH_OMEGA		1.2f
#define		KI_ROLL_PITCH_OMEGA		0.0062f
#define		KD_ROLL_PITCH_OMEGA		3.0f
#define		PID_MAX_ROLL_PITCH		450.0f
#define		PID_MAX_RP_INTEGRAL		300.0f

#define 	KP_YAW_OMEGA					0.0f
#define 	KI_YAW_OMEGA					0.0f
#define		KD_YAW_OMEGA					0.0f
#define 	PID_MAX_YAW_INTEGRAL	80.0f
#define		PID_MAX_YAW						100.0f

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
uint32_t count = 0, ii= 0 ,ga = 0, iii = 0, start = 0;
float channel_3 = 0, channel_1 = 0, channel_5;
volatile uint16_t esc1 = 1000, esc2 = 1000 , esc3 = 1000, esc4 = 1000; // Cap PWM cho dong co : 1000-2000 
volatile float esc1_f = 0, esc2_f = 0, esc3_f =0, esc4_f =0, ga_f = 0;
extern uint8_t buffer3[21];
extern float roll, pitch, yaw;
extern float gyro_that[3];

/////////////////PID CONSTANTS/////////////////
double kp_roll = KP_ROLL_PITCH;//2.75
double ki_roll = 0.0f;//0.01
double kd_roll = 0.0f;//1.5
float pid_output_roll = 0, pid_error_temp_roll = 0, pid_i_mem_roll = 0, pid_last_roll_d_error =0 ;
float pid_max_roll = 50.0f ;

float pid_output_roll_omega = 0, pid_error_temp_roll_omega = 0, pid_i_mem_roll_omega = 0, pid_last_roll_d_error_omega = 0 ;
double kp_roll_omega = KP_ROLL_PITCH_OMEGA;//2.75
double ki_roll_omega = KI_ROLL_PITCH_OMEGA;//0.01
double kd_roll_omega = KD_ROLL_PITCH_OMEGA;//1.5

float pid_max_roll_omega_integral = PID_MAX_RP_INTEGRAL;
float pid_max_roll_omega = PID_MAX_ROLL_PITCH;

///////////////////////////////////////////////
double kp_pitch = KP_ROLL_PITCH;     //0.02
double ki_pitch = 0.0f;  //0.00004
double kd_pitch = 0.0f;   //0.01
float pid_output_pitch = 0, pid_error_temp_pitch = 0, pid_i_mem_pitch = 0, pid_last_pitch_d_error =0 ;
float pid_max_pitch = 50.0f ;

double kp_pitch_omega = KP_ROLL_PITCH_OMEGA;     //0.02
double ki_pitch_omega = KI_ROLL_PITCH_OMEGA;  //0.00004
double kd_pitch_omega = KD_ROLL_PITCH_OMEGA;   //0.01
float pid_output_pitch_omega = 0, pid_error_temp_pitch_omega = 0, pid_i_mem_pitch_omega = 0, pid_last_pitch_d_error_omega =0 ;

float pid_max_pitch_omega_integral = PID_MAX_RP_INTEGRAL;
float pid_max_pitch_omega = PID_MAX_ROLL_PITCH ;

////////////////////////////////////////////////
float yaw_offset = 0, yaw_offset_tmp = 0;
uint8_t i_yaw = 0;
double kp_yaw = 0.5;
double ki_yaw = 0;
double kd_yaw = 0;
float pid_output_yaw = 0, pid_error_temp_yaw = 0, pid_i_mem_yaw = 0, pid_last_yaw_d_error = 0;
float pid_max_yaw = 100;

double kp_yaw_omega = KP_YAW_OMEGA;
double ki_yaw_omega = KI_YAW_OMEGA;
double kd_yaw_omega = KD_YAW_OMEGA;
float pid_output_yaw_omega = 0, pid_error_temp_yaw_omega = 0, pid_i_mem_yaw_omega = 0, pid_last_yaw_d_error_omega = 0;
float pid_max_yaw_omega = PID_MAX_YAW;
float pid_max_yaw_omega_integral = PID_MAX_YAW_INTEGRAL;

//----------------------
//extern TM_MPU6050_t	MPU6050_Data0;
//extern TM_HMC_t			HMC_Data;

uint16_t 	Gyroscope_X_offset=0,Gyroscope_Y_offset=0,Gyroscope_Z_offset=0,Accelerometer_X_offset=0,Accelerometer_Y_offset=0,Accelerometer_Z_offset=0;

uint8_t read_channel_1 = 0;
uint8_t read_channel_2 = 0;
uint8_t read_channel_3 = 0;
uint8_t read_channel_4 = 0;
uint8_t read_channel_5 = 0;
uint8_t read_channel_6 = 0;

uint8_t controller_start = 0;
uint32_t running_timer = 0, running_timer_counter = 0, start_running = 0;
uint8_t start_button = 0;
uint32_t start_button_counter = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
		{
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
			{
				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9) == 1)
				{
					__HAL_TIM_SetCounter(&htim1, 0);
				}
				else
				{	
					channel_3 = __HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_1);
				}
			}
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
			{
				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_11) == 1)
				{	
					__HAL_TIM_SetCounter(&htim1, 0);
				}
				else
				{
					channel_1 = __HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_2);
				}
			}
			if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
			{
        if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)==1)
				{
					
					__HAL_TIM_SetCounter(&htim1,0);
				}
				else
				{
					channel_5 = __HAL_TIM_GetCompare(&htim1,TIM_CHANNEL_3);
				}
			}

		}
}
/* PID CONTROLLER */
void PID_Controller_Angles(void)
{
	
	//Roll calculations///////////////////////////////////////////
	pid_error_temp_roll = 0.0f - roll ;
			
	pid_i_mem_roll += ki_roll * pid_error_temp_roll;
	
	if (pid_i_mem_roll > pid_max_roll) pid_i_mem_roll = pid_max_roll;
	else 
			if (pid_i_mem_roll < pid_max_roll * -1) pid_i_mem_roll = pid_max_roll * -1;
	
	pid_output_roll = kp_roll * pid_error_temp_roll + pid_i_mem_roll + (-kd_roll)*(pid_error_temp_roll - pid_last_roll_d_error);
			
	if( pid_output_roll > pid_max_roll) pid_output_roll = pid_max_roll;
	else 
			if (pid_output_roll < pid_max_roll * -1) pid_output_roll = pid_max_roll * -1;
	
	pid_last_roll_d_error = pid_error_temp_roll;
	
	//Pitch calculations///////////////////////////////////////////
	pid_error_temp_pitch = 0.0f - pitch ;
	
	pid_i_mem_pitch += ki_pitch * pid_error_temp_pitch;
	
	if (pid_i_mem_pitch > pid_max_pitch) pid_i_mem_pitch = pid_max_pitch;
	else 
			if (pid_i_mem_pitch < pid_max_pitch*-1) pid_i_mem_pitch = pid_max_pitch*-1;
		
	pid_output_pitch = kp_roll * pid_error_temp_pitch + pid_i_mem_pitch + (-kd_pitch)*(pid_error_temp_pitch - pid_last_pitch_d_error);
	
	if (pid_output_pitch > pid_max_pitch) pid_output_pitch = pid_max_pitch;
	else
			if (pid_output_pitch < pid_max_pitch*-1) pid_output_pitch = pid_max_pitch * -1;
	
	pid_last_pitch_d_error = pid_error_temp_pitch;
	
	//Yaw calculations/////////////////////////////////////////////
	pid_error_temp_yaw = 0.0f - yaw;
	
	pid_i_mem_yaw += ki_yaw*pid_error_temp_yaw;
	
	if (pid_i_mem_yaw > pid_max_yaw) pid_i_mem_yaw = pid_max_yaw;
	else if (pid_i_mem_yaw < pid_max_yaw*(-1)) pid_i_mem_yaw = pid_max_yaw*(-1);
	
	pid_output_yaw = kp_yaw*pid_error_temp_yaw + pid_i_mem_yaw + (-kd_yaw)*(pid_error_temp_yaw - pid_last_yaw_d_error);
	
	if (pid_output_yaw > pid_max_yaw) pid_output_yaw = pid_max_yaw;
	else if (pid_output_yaw < pid_max_yaw*(-1)) pid_output_yaw = pid_max_yaw*(-1);
	
	pid_last_yaw_d_error = pid_error_temp_yaw;

	count++;

}

int sign_output_roll, pre_sign_output_roll = 1;
int sign_output_pitch, pre_sign_output_pitch = 1;
int sign_output_yaw, pre_sign_output_yaw = 1;

void PID_Controller_Omega(float dt)
{
	//Omega roll calculation//////////////////////////////////////////
	pid_error_temp_roll_omega = pid_output_roll - gyro_that[0] ;
	
	pid_i_mem_roll_omega += ki_roll_omega * pid_error_temp_roll_omega;
	
	if (pid_i_mem_roll_omega > pid_max_roll_omega_integral) pid_i_mem_roll_omega = pid_max_roll_omega_integral;
	else if (pid_i_mem_roll_omega < pid_max_roll_omega_integral * (-1)) pid_i_mem_roll_omega = pid_max_roll_omega_integral * (-1);
	
	pid_output_roll_omega = kp_roll_omega*pid_error_temp_roll_omega + pid_i_mem_roll_omega + kd_roll_omega * (pid_error_temp_roll_omega - pid_last_roll_d_error_omega);
	
	if (pid_output_roll_omega > pid_max_roll_omega) pid_output_roll_omega = pid_max_roll_omega;
	else if (pid_output_roll_omega < pid_max_roll_omega * (-1)) pid_output_roll_omega = pid_max_roll_omega * (-1);
	
	pid_last_roll_d_error_omega = pid_error_temp_roll_omega;
	
	//Omega pitch calculation//////////////////////////////////////////
	pid_error_temp_pitch_omega = pid_output_pitch - gyro_that[1] ;
	
	pid_i_mem_pitch_omega += ki_pitch_omega * pid_error_temp_pitch_omega;
	
	if (pid_i_mem_pitch_omega > pid_max_pitch_omega_integral) pid_i_mem_pitch_omega = pid_max_pitch_omega_integral;
	else if (pid_i_mem_pitch_omega < pid_max_pitch_omega_integral * (-1)) pid_i_mem_pitch_omega = pid_max_pitch_omega_integral * (-1);
	
	pid_output_pitch_omega = kp_pitch_omega * pid_error_temp_pitch_omega + pid_i_mem_pitch_omega + kd_pitch_omega * (pid_error_temp_pitch_omega - pid_last_pitch_d_error_omega);
	
	if (pid_output_pitch_omega > pid_max_pitch_omega) pid_output_pitch_omega = pid_max_pitch_omega;
	else if (pid_output_pitch_omega < pid_max_pitch_omega * (-1)) pid_output_pitch_omega = pid_max_pitch_omega * (-1);
	
	pid_last_pitch_d_error_omega = pid_error_temp_pitch_omega;

	//Omega yaw calculation//////////////////////////////////////////
	pid_error_temp_yaw_omega = pid_output_yaw - gyro_that[2];
	
	pid_i_mem_yaw_omega += ki_yaw_omega * pid_error_temp_yaw_omega;

	if (pid_i_mem_yaw_omega > pid_max_yaw_omega_integral) pid_i_mem_yaw_omega = pid_max_yaw_omega_integral;
	else if (pid_i_mem_yaw_omega < pid_max_yaw_omega_integral * (-1)) pid_i_mem_yaw_omega = pid_max_yaw_omega_integral * (-1);
	
	pid_output_yaw_omega = kp_yaw_omega * pid_error_temp_yaw_omega + pid_i_mem_yaw_omega + kd_yaw_omega * (pid_error_temp_yaw_omega - pid_last_yaw_d_error_omega);
	
	if (pid_output_yaw_omega > pid_max_yaw_omega) pid_output_yaw_omega = pid_max_yaw_omega;
	else if (pid_output_yaw_omega < pid_max_yaw_omega * (-1)) pid_output_yaw_omega = pid_max_yaw_omega * (-1);
	
	pid_last_yaw_d_error_omega = pid_error_temp_yaw_omega;

}
		
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t control_delay;
uint32_t w_control_timer, w_control_timer_raw, w_control_timer_pre;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		controller_start = 1;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	Init_button_and_led();

	MPU9255_Init();
	InitGyrOffset();
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	
	/*----Xuat PWM ra dong co -----*/
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1 , 1000 ); //PA0
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2 , 1000 ); //PA1
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3 , 1000 ); //PA2
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4 , 1000 ); //PA3
	HAL_Delay(2500);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

	
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
	
	control_delay = TIM1->CNT;
	while ((TIM1->CNT - control_delay) < 500) {};
	HAL_TIM_Base_Start_IT(&htim3);
		
	start = 1;
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if (controller_start == 1){
			controller();
			controller_start = 0;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 83;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 29999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();  
	}

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 83;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 83;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
uint32_t channel_1_buffer[2] = {0, 0};
uint32_t channel_3_buffer[2] = {0, 0};
float channel_1_raw, channel_1_pre;
float channel_3_raw, channel_3_pre;

void Init_button_and_led(void){
		GPIO_InitTypeDef GPIO_Init;
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_Init.Pin = GPIO_PIN_12;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_Init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOD, &GPIO_Init);
	
	GPIO_Init.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD, &GPIO_Init);
	
	GPIO_Init.Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOD, &GPIO_Init);

	GPIO_Init.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &GPIO_Init);

}

void read_channel_1_handler(void){

}

void read_channel_2_handler(void){
  
}

void read_channel_3_handler(void){
	
}

void read_channel_4_handler(void){
  
}

void read_channel_5_handler(void){
  
}

void read_channel_6_handler(void){
  
}

static int controller_counter = 0;
static uint32_t dt_pre, dt_raw;
static float dt = 0.002f;

void controller(void)
{
#if SAFETY_START		
	if (start == 0) {
		
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 1000);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 1000);
		
	}
	else if (start == 1) 
	{
#endif
		MPU9255_Get_Data();
		IMU_GetYawPitchRoll();
		
#if AUTO_RUN
		running_timer_counter++;
		controller_counter++;
		if (running_timer_counter == 500){
			running_timer++;
			running_timer_counter = 0;
		}
		if (running_timer == RUNNING_TIME){
			start = 0;
		}
#endif

		ii++;
		if (ii == 10)
		{
			ii = 0;
			iii++;
			if ( iii == 5 )
			{
				iii = 0;
				PID_Controller_Angles();
			}
			dt_raw = TIM3->CNT;
			dt = 0.002f + dt_raw * 0.000001f - dt_pre * 0.000001f;
			dt_pre = dt_raw;

			PID_Controller_Omega(dt);
			
#if TX_CONTROLLER
			if (channel_5 > 1500)
			{
#endif
				
				ga = channel_3 ;
				if (ga >= 1500) ga = 1500;
				//ga = 1350;	
				
#if YAW_CONTROLLER		
				esc1 = ga - pid_output_roll_omega - pid_output_pitch_omega - pid_output_yaw_omega;   //MPU dat giua 2 truc
				esc2 = ga - pid_output_roll_omega + pid_output_pitch_omega + pid_output_yaw_omega;
				esc3 = ga + pid_output_roll_omega + pid_output_pitch_omega - pid_output_yaw_omega;
				esc4 = ga + pid_output_roll_omega - pid_output_pitch_omega + pid_output_yaw_omega;
#else
				esc1 = ga - pid_output_roll_omega - pid_output_pitch_omega;
				esc2 = ga - pid_output_roll_omega + pid_output_pitch_omega;
				esc3 = ga + pid_output_roll_omega + pid_output_pitch_omega;
				esc4 = ga + pid_output_roll_omega - pid_output_pitch_omega;
#endif
				
				if (esc1 < 1100) esc1 = 1100;                                                //Keep the motors running.
				if (esc2 < 1100) esc2 = 1100;                                                //Keep the motors running.
				if (esc3 < 1100) esc3 = 1100;                                                //Keep the motors running.
				if (esc4 < 1100) esc4 = 1100;                                                //Keep the motors running.
                             
				if (esc1 > 1900) esc1 = 1900;                                                 //Limit the esc-1 pulse to 2000us.
				if (esc2 > 1900) esc2 = 1900;                                                 //Limit the esc-2 pulse to 2000us.
				if (esc3 > 1900) esc3 = 1900;                                                 //Limit the esc-3 pulse to 2000us.
				if (esc4 > 1900) esc4 = 1900;                                                 //Limit the esc-4 pulse to 2000us.
#if TX_CONTROLLER			
			}
			else 
			{
				
				esc1 = 1000;
				esc2 = 1000;
				esc3 = 1000;
				esc4 = 1000;
				
			}
#endif
		/*----Xuat PWM ra dong co -----*/
				
		esc1 = esc3 = 1000;
		//esc2 = esc4 = 1000;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1 , esc3 ); //PA0
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2 , esc1 ); //PA1
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3 , esc2 ); //PA2
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4 , esc4 ); //PA3
		}
	}

}

int getsign(float c){
	if (c >= 0) return 1;
	else return -1;
}

float wrap_to_range_f(const float low, const float high, float x)
{
  /* Wrap x into interval [low, high) */
  /* Assumes high > low */

  const float range = high - low;

  if (range > 0.0f) {
    while (x >= high) {
      x -= range;
    }

    while (x < low) {
      x += range;
    }
  } else {
    x = low;
  }

  return x;
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
