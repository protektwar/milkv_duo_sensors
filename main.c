#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include <wiringx.h>

#include <dht22.h>
#include <bmp180.h>
#include <display.h>
#include <display_st7735.h>
#include <ugui.h>


unsigned long __stack_chk_guard;

void __stack_chk_guard_setup(void)
{
     __stack_chk_guard = 0xBAAAAAAD;//provide some magic numbers
}

void __stack_chk_fail(void)
{
	printf("variable corrupted");

}// will be called when guard variable is corrupted

int bmp180_i2c;
struct bmp180_calib_param bmp180_calib_params;

int setup()
{
    // wiringx setup to duo
    printf("wiringXSetup duo\n");
    if (wiringXSetup("duo", NULL) == -1)
    {
        wiringXGC();
	return -1;
    }

    // DHT22 setup
    printf("dht22 setup\n");
    dht22_setup();
    printf("dht22 setup completed\n");
 
    // bmp180 setup
    printf("bmp180_setup\n");
    bmp180_i2c = bmp180_setup(BMP180_ULTRALOWPOWER);
    if (bmp180_i2c == -1)
	    exit(-1);
    printf("bmp180 setup completed\n");

    printf("reading bmp180 calibration parameters...\n");
    bmp180_get_calib_params(bmp180_i2c, &bmp180_calib_params);

}

void loop()
{
//	printf("reading from dht22...\n");
	read_dht22_dat();

//        int32_t b5 = bmp180_get_B5(bmp180_i2c, bmp180_calib_params);

//	int32_t temp = bmp180_get_temperature(bmp180_i2c, bmp180_calib_params); 
	float temp = (float) bmp180_get_temperature(bmp180_i2c, bmp180_calib_params); 
	float pressure = (float) bmp180_get_pressure(bmp180_i2c, bmp180_calib_params);

	int32_t altitude_meters = 0; // altitude at sea level
        int32_t sea_level_pressure = (int32_t)(pressure / pow(1.0 - altitude_meters / 44330, 5.255));
	//sea_level_pressure = 101325;
	sea_level_pressure = 101500;
	//printf("pressure: %f\n", pressure);
	//printf("sea_level_pressure: %d\n", sea_level_pressure);
	//printf("pressure / sea_level_pressure: %f\n", pressure / sea_level_pressure);
	//printf("pow(pressure / sea_level_pressure, 0.1903): %f\n", pow((float)(pressure / sea_level_pressure), 0.1903));
	float pressure_div = pressure / (float)sea_level_pressure;
	//printf("pow(pressure / sea_level_pressure, 0.1903): %f\n", pow(pressure_div, 1/5.255));
	//printf("pressure_div: %f\n", pressure_div);
	float altitude = 44330 * (1.0 - pow(pressure_div, 0.1903));

	printf("Temperature: %.2fC | ", temp / 10);
        printf("Pressure: %.2fmilibar | ", pressure / 100);
	printf("Altitude: %.2fm", altitude);
	printf("\n");
}

int main()
{
	if (setup() == -1)
	{
		printf("Setup failed\n");	
		return 0;
	}

	while(1)
	{
		loop();
		delayMicroseconds(1500000);
	}

}


