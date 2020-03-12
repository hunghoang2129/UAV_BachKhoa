#include "PWM_to_F.h"
#include <math.h>
#include "stm32f4xx_hal.h"

float PWM_to_F_1(int PWM){
	float F;
	if (PWM <= 1100) {F = 0.0033*PWM - 3.3;}
	else if ((PWM > 1100) && (PWM <= 1150)) {F = 0.0068*PWM - 7.15;}
	else if ((PWM > 1150) && (PWM <= 1200)) {F = 0.0068*PWM - 7.15;}
	else if ((PWM > 1200) && (PWM <= 1250)) {F = 0.0088*PWM - 9.55;}
	else if ((PWM > 1250) && (PWM <= 1300)) {F = 0.0078*PWM - 8.3;}
	else if ((PWM > 1300) && (PWM <= 1350)) {F = 0.008*PWM - 8.56;}
	else if ((PWM > 1350) && (PWM <= 1400)) {F = 0.0078*PWM - 8.29;}
	else if ((PWM > 1400) && (PWM <= 1450)) {F = 0.0102*PWM - 11.65;}
	else if ((PWM > 1450) && (PWM <= 1500)) {F = 0.01*PWM - 11.36;}
	else if ((PWM > 1500) && (PWM <= 1550)) {F = 0.0104*PWM - 11.96;}
	else if ((PWM > 1550) && (PWM <= 1600)) {F = 0.0116*PWM - 13.82;}
	else if ((PWM > 1600) && (PWM <= 1650)) {F = 0.0066*PWM - 5.82;}
	else if ((PWM > 1650) && (PWM <= 1700)) {F = 0.0124*PWM - 15.39;}
	else if ((PWM > 1700) && (PWM <= 1750)) {F = 0.012*PWM - 14.71;}
	else if ((PWM > 1750) && (PWM <= 1800)) {F = 0.0054*PWM - 3.16;}
	else if (PWM > 1800) {F = 0.0118*PWM - 14.68;}
	return F;
}

float PWM_to_F_2(int PWM){
	float F;
	if (PWM <= 1100) {F = 0.0035*PWM - 3.5;}
	else if ((PWM > 1100) && (PWM <= 1150)) {F = 0.0062*PWM - 6.47;}
	else if ((PWM > 1150) && (PWM <= 1200)) {F = 0.0066*PWM - 6.93;}
	else if ((PWM > 1200) && (PWM <= 1250)) {F = 0.0074*PWM - 7.89;}
	else if ((PWM > 1250) && (PWM <= 1300)) {F = 0.0076*PWM - 8.14;}
	else if ((PWM > 1300) && (PWM <= 1350)) {F = 0.0074*PWM - 7.88;}
	else if ((PWM > 1350) && (PWM <= 1400)) {F = 0.0026*PWM - 1.4;}
	else if ((PWM > 1400) && (PWM <= 1450)) {F = 0.0078*PWM - 8.68;}
	else if ((PWM > 1450) && (PWM <= 1500)) {F = 0.01*PWM - 11.87;}
	else if ((PWM > 1500) && (PWM <= 1550)) {F = 0.0092*PWM - 10.67;}
	else if ((PWM > 1550) && (PWM <= 1600)) {F = 0.007*PWM - 7.26;}
	else if ((PWM > 1600) && (PWM <= 1650)) {F = 0.008*PWM - 8.86;}
	else if ((PWM > 1650) && (PWM <= 1700)) {F = 0.0102*PWM - 12.49;}
	else if ((PWM > 1700) && (PWM <= 1750)) {F = 0.0162*PWM - 22.69;}
	else if ((PWM > 1750) && (PWM <= 1800)) {F = 0.0126*PWM - 13.39;}
	else if (PWM > 1800) {F = 0.0088*PWM - 9.55;}
	return F;
}

float PWM_to_F_3(int PWM){
	float F;
	if (PWM <= 1100) {F = 0.0038*PWM - 3.8;}
	else if ((PWM > 1100) && (PWM <= 1150)) {F = 0.0084*PWM - 8.86;}
	else if ((PWM > 1150) && (PWM <= 1200)) {F = 0.008*PWM - 8.4;}
	else if ((PWM > 1200) && (PWM <= 1250)) {F = 0.0094*PWM - 10.08;}
	else if ((PWM > 1250) && (PWM <= 1300)) {F = 0.0092*PWM - 9.83;}
	else if ((PWM > 1300) && (PWM <= 1350)) {F = 0.0124*PWM - 13.99;}
	else if ((PWM > 1350) && (PWM <= 1400)) {F = 0.0064*PWM - 5.89;}
	else if ((PWM > 1400) && (PWM <= 1450)) {F = 0.0068*PWM - 6.45;}
	else if ((PWM > 1450) && (PWM <= 1500)) {F = 0.0078*PWM - 7.9;}
	else if ((PWM > 1500) && (PWM <= 1550)) {F = 0.0112*PWM - 13;}
	else if ((PWM > 1550) && (PWM <= 1600)) {F = 0.0116*PWM - 13.62;}
	else if ((PWM > 1600) && (PWM <= 1650)) {F = 0.0128*PWM - 15.54;}
	else if ((PWM > 1650) && (PWM <= 1700)) {F = 0.0104*PWM - 11.58;}
	else if ((PWM > 1700) && (PWM <= 1750)) {F = 0.008*PWM - 7.5;}
	else if ((PWM > 1750) && (PWM <= 1800)) {F = 0.0102*PWM - 11.35;}
	else if (PWM > 1800) {F = 0.0118*PWM - 14.23;}
	return F;
}

float PWM_to_F_4(int PWM){
	float F;
	if (PWM <= 1100) {F = 0.0026*PWM - 2.6;}
	else if ((PWM > 1100) && (PWM <= 1150)) {F = 0.0062*PWM - 6.56;}
	else if ((PWM > 1150) && (PWM <= 1200)) {F = 0.0068*PWM - 7.25;}
	else if ((PWM > 1200) && (PWM <= 1250)) {F = 0.0076*PWM - 8.21;}
	else if ((PWM > 1250) && (PWM <= 1300)) {F = 0.0074*PWM - 7.96;}
	else if ((PWM > 1300) && (PWM <= 1350)) {F = 0.008*PWM - 8.74;}
	else if ((PWM > 1350) && (PWM <= 1400)) {F = 0.0074*PWM - 7.93;}
	else if ((PWM > 1400) && (PWM <= 1450)) {F = 0.0092*PWM - 10.45;}
	else if ((PWM > 1450) && (PWM <= 1500)) {F = 0.0082*PWM - 9;}
	else if ((PWM > 1500) && (PWM <= 1550)) {F = 0.0124*PWM - 15.3;}
	else if ((PWM > 1550) && (PWM <= 1600)) {F = 0.0084*PWM - 9.1;}
	else if ((PWM > 1600) && (PWM <= 1650)) {F = 0.0118*PWM - 14.54;}
	else if ((PWM > 1650) && (PWM <= 1700)) {F = 0.0086*PWM - 9.26;}
	else if ((PWM > 1700) && (PWM <= 1750)) {F = 0.0044*PWM - 2.12;}
	else if ((PWM > 1750) && (PWM <= 1800)) {F = 0.0076*PWM - 7.72;}
	else if (PWM > 1800) {F = 0.0078*PWM - 8.08;}
	return F;
}

int F_to_PWM_1(float F){
	int PWM;
	if (F <= 0.33) {PWM = (int)((F + 3.3)/0.0033);}
	else if ((F > 0.33) && (F <= 0.67)) {PWM = (int)((F + 7.15)/0.0068);}
	else if ((F > 0.67) && (F <= 1.01)) { PWM = (int)((F + 7.15) / 0.0068); }
	else if ((F > 1.01) && (F <= 1.45)) { PWM = (int)((F + 9.55) / 0.0088); }
	else if ((F > 1.45) && (F <= 1.84)) { PWM = (int)((F + 8.3) / 0.0078); }
	else if ((F > 1.84) && (F <= 2.24)) { PWM = (int)((F + 8.56) / 0.008); }
	else if ((F > 2.24) && (F <= 2.63)) { PWM = (int)((F + 8.29) / 0.0078); }
	else if ((F > 2.63) && (F <= 3.14)) { PWM = (int)((F + 11.65) / 0.0102); }
	else if ((F > 3.14) && (F <= 3.64)) { PWM = (int)((F + 11.36) / 0.01); }
	else if ((F > 3.64) && (F <= 4.16)) { PWM = (int)((F + 11.96) / 0.0104); }
	else if ((F > 4.16) && (F <= 4.74)) { PWM = (int)((F + 13.82) / 0.0116); }
	else if ((F > 4.74) && (F <= 5.07)) { PWM = (int)((F + 5.82) / 0.0066); }
	else if ((F > 5.07) && (F <= 5.69)) { PWM = (int)((F + 15.39) / 0.0124); }
	else if ((F > 5.69) && (F <= 6.29)) { PWM = (int)((F + 14.71) / 0.012); }
	else if ((F > 6.29) && (F <= 6.56)) { PWM = (int)((F + 3.16) / 0.0054); }
	else if (F > 6.56) { PWM = (int)((F + 14.68) / 0.0118); }
	return PWM;
}

int F_to_PWM_2(float F) {
	int PWM;
	if (F <= 0.35) { PWM = (int)((F + 3.5) / 0.0035); }
	else if ((F > 0.35) && (F <= 0.66)) { PWM = (int)((F + 6.47) / 0.0062); }
	else if ((F > 0.66) && (F <= 0.99)) { PWM = (int)((F + 6.93) / 0.0066); }
	else if ((F > 0.99) && (F <= 1.36)) { PWM = (int)((F + 7.89) / 0.0074); }
	else if ((F > 1.36) && (F <= 1.74)) { PWM = (int)((F + 8.14) / 0.0076); }
	else if ((F > 1.74) && (F <= 2.11)) { PWM = (int)((F + 7.88) / 0.0074); }
	else if ((F > 2.11) && (F <= 2.24)) { PWM = (int)((F + 1.4) / 0.0026); }
	else if ((F > 2.24) && (F <= 2.63)) { PWM = (int)((F + 8.68) / 0.0078); }
	else if ((F > 2.63) && (F <= 3.13)) { PWM = (int)((F + 11.87) / 0.01); }
	else if ((F > 3.13) && (F <= 3.59)) { PWM = (int)((F + 10.67) / 0.0092); }
	else if ((F > 3.59) && (F <= 3.94)) { PWM = (int)((F + 7.26) / 0.007); }
	else if ((F > 3.94) && (F <= 4.34)) { PWM = (int)((F + 8.86) / 0.008); }
	else if ((F > 4.34) && (F <= 4.85)) { PWM = (int)((F + 12.49) / 0.0102); }
	else if ((F > 4.85) && (F <= 5.66)) { PWM = (int)((F + 22.69) / 0.0162); }
	else if ((F > 5.66) && (F <= 6.29)) { PWM = (int)((F + 13.39) / 0.0126); }
	else if (F > 6.29) { PWM = (int)((F + 9.55) / 0.0088); }
	return PWM;
}

int F_to_PWM_3(float F) {
	int PWM;
	if (F <= 0.38) { PWM = (int)((F + 3.8) / 0.0038); }
	else if ((F > 0.38) && (F <= 0.8)) { PWM = (int)((F + 8.86) / 0.0084); }
	else if ((F > 0.8) && (F <= 1.2)) { PWM = (int)((F + 8.4) / 0.008); }
	else if ((F > 1.2) && (F <= 1.67)) { PWM = (int)((F + 10.08) / 0.0094); }
	else if ((F > 1.67) && (F <= 2.13)) { PWM = (int)((F + 9.83) / 0.0092); }
	else if ((F > 2.13) && (F <= 2.75)) { PWM = (int)((F + 13.99) / 0.0124); }
	else if ((F > 2.75) && (F <= 3.07)) { PWM = (int)((F + 5.89) / 0.0064); }
	else if ((F > 3.07) && (F <= 3.41)) { PWM = (int)((F + 6.45) / 0.0068); }
	else if ((F > 3.41) && (F <= 3.8)) { PWM = (int)((F + 7.9) / 0.0078); }
	else if ((F > 3.8) && (F <= 4.36)) { PWM = (int)((F + 13) / 0.0112); }
	else if ((F > 4.36) && (F <= 4.94)) { PWM = (int)((F + 13.62) / 0.0116); }
	else if ((F > 4.94) && (F <= 5.58)) { PWM = (int)((F + 15.54) / 0.0128); }
	else if ((F > 5.58) && (F <= 6.1)) { PWM = (int)((F + 11.58) / 0.0104); }
	else if ((F > 6.1) && (F <= 6.5)) { PWM = (int)((F + 7.5) / 0.008); }
	else if ((F > 6.5) && (F <= 7.01)) { PWM = (int)((F + 11.35) / 0.0102); }
	else if (F > 7.01) { PWM = (int)((F + 14.23) / 0.0118); }
	return PWM;
}

int F_to_PWM_4(float F) {
	int PWM;
	if (F <= 0.26) { PWM = (int)((F + 2.6) / 0.0026); }
	else if ((F > 0.26) && (F <= 0.57)) { PWM = (int)((F + 6.56) / 0.0062); }
	else if ((F > 0.57) && (F <= 0.91)) { PWM = (int)((F + 7.25) / 0.0068); }
	else if ((F > 0.91) && (F <= 1.29)) { PWM = (int)((F + 8.21) / 0.0076); }
	else if ((F > 1.29) && (F <= 1.66)) { PWM = (int)((F + 7.96) / 0.0074); }
	else if ((F > 1.66) && (F <= 2.06)) { PWM = (int)((F + 8.74) / 0.008); }
	else if ((F > 2.06) && (F <= 2.43)) { PWM = (int)((F + 7.93) / 0.0074); }
	else if ((F > 2.43) && (F <= 2.89)) { PWM = (int)((F + 10.45) / 0.0092); }
	else if ((F > 2.89) && (F <= 3.3)) { PWM = (int)((F + 9) / 0.0082); }
	else if ((F > 3.3) && (F <= 3.92)) { PWM = (int)((F + 15.3) / 0.0124); }
	else if ((F > 3.92) && (F <= 4.34)) { PWM = (int)((F + 9.1) / 0.0084); }
	else if ((F > 4.34) && (F <= 4.93)) { PWM = (int)((F + 14.54) / 0.0118); }
	else if ((F > 4.93) && (F <= 5.36)) { PWM = (int)((F + 9.26) / 0.0086); }
	else if ((F > 5.36) && (F <= 5.58)) { PWM = (int)((F + 2.12) / 0.0044); }
	else if ((F > 5.58) && (F <= 5.96)) { PWM = (int)((F + 7.72) / 0.0076); }
	else if (F > 5.96) { PWM = (int)((F + 8.08) / 0.0078); }
	return PWM;
}
