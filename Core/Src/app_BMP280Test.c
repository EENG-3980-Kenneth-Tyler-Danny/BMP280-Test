/*
 * app_LCDTest.c
 *
 *  Created on: Nov 15, 2024
 *      Author: tylermiller
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "stm32l4xx_hal.h"
#include "app.h"
#include "lcd.h"
#include "bmp280.h"

extern I2C_HandleTypeDef hi2c1;
extern BMP280_HandleTypedef bmp280;

char message[16];
char PresStr[16];
float temperature, pressure, humidity;

void App_Init(void) {

	initLCD();

	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = &hi2c1;

	while (!bmp280_init(&bmp280, &bmp280.params)) {

		sprintf(message,"BMP Init");
		clearLCD();
		writeLCD(message);
		setCursor(0,1);
		sprintf(message,"Failed");
		HAL_Delay(2000);

	}

	bool bme280p = bmp280.id == BME280_CHIP_ID;

	if (bme280p){

		sprintf(message,"BMP280 Found");
		clearLCD();
		writeLCD(message);
		HAL_Delay(2000);

	}

}

void App_MainLoop(void) {

	HAL_Delay(100);

	while (!bmp280_read_float(&bmp280, &temperature, &pressure, &humidity)) {

		sprintf(message,"BMP Reading");
		clearLCD();
		writeLCD(message);
		setCursor(0,1);
		sprintf(message,"Failed");
		HAL_Delay(2000);

	}

	sprintf(PresStr,"Pres: %.2f",pressure);
	clearLCD();
	writeLCD(PresStr);

	HAL_Delay(2000);

}
