#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LED0_trigger "/sys/class/leds/beaglebone:green:usr0/trigger"
#define LED1_trigger "/sys/class/leds/beaglebone:green:usr1/trigger"
#define LED2_trigger "/sys/class/leds/beaglebone:green:usr2/trigger"
#define LED3_trigger "/sys/class/leds/beaglebone:green:usr3/trigger"
#define LED0_brightness "/sys/class/leds/beaglebone:green:usr0/brightness"
#define LED3_brightness "/sys/class/leds/beaglebone:green:usr3/brightness"
#define JSUP "/sys/class/gpio/gpio26/value"
#define JSRT "/sys/class/gpio/gpio47/value"
#define JSDW "/sys/class/gpio/gpio46/value"	
#define JSLFT "/sys/class/gpio/gpio65/value"

void LED_initialize();
_Bool exit_game();

int main()
{
	//int current_score = 0;
	//int max_score = 10;
	long seconds = 3;
	long nanoseconds = 500000000;
	struct timespec reqDelay = {seconds, nanoseconds};


	LED_initialize();
	
	printf("Hello embedded world, from Zian Jiang!\n");
	printf("Press the Zen cape's Joystick in the direction of the LED.\n");
	printf("UP for LED 0 (top)\n");
	printf("DOWN for LED 3 (bottom)\n");
	printf("LEFT/RIGHT for exit app.\n");

	srand(time(NULL));
	int number = rand()%2;
	if(number == 0)
	{
		FILE *LED0_on;
		LED0_on = fopen(LED0_brightness,"w");
		fprintf(LED0_on,"1");
		fclose(LED0_on);

		nanosleep(&reqDelay, (struct timespec *) NULL); //suspend the process for 3.5s

		//printf("times up.\n");

		if(exit_game())
		{
			printf("Exiting...\n");
			return 1;
		}

		LED0_on = fopen(LED0_brightness,"w");
		fprintf(LED0_on,"0");
		fclose(LED0_on);


		
	}
	else
	{
		FILE *LED3_on;
		LED3_on = fopen(LED3_brightness,"w");
		fprintf(LED3_on,"1");
		fclose(LED3_on);

		nanosleep(&reqDelay, (struct timespec *) NULL); //suspend the process for 3.5s


		if(exit_game())
		{
			printf("Exiting...\n");
			return 2;
		}

		LED3_on = fopen(LED3_brightness,"w");
		fprintf(LED3_on,"0");
		fclose(LED3_on);
	}

	return 0;
}

_Bool exit_game()
{
	FILE *ljoystick = fopen(JSLFT,"r");
	FILE *rjoystick = fopen(JSRT,"r");

	if(ljoystick == 0)
	{
		printf("Error opening %s.", JSLFT);
		exit(-1);
	}

	if(rjoystick == 0)
	{
		printf("Error opening %s.", JSRT);
		exit(-1);
	}

	const int max_length = 1024;
	char buff1[max_length];
	char buff2[max_length];
	fgets(buff1, max_length, ljoystick);
	fgets(buff2, max_length, rjoystick);

	

	fclose(ljoystick);
	fclose(rjoystick);

	//printf("%s\n", buff1);
	//printf("Read: '%c' \n", buff1[0]);
	//printf("%s\n", buff2);
	//printf("Read: '%c' \n", buff2[0]);

	if(buff1[0] == '0' || buff2[0] == '0' )
	{
		return 1;
	}

	return 0;

}

/*_Bool is_pushed()
{
	
}*/

void LED_initialize()
{
	FILE *LED0 = fopen(LED0_trigger, "w");
	FILE *LED1 = fopen(LED1_trigger, "w");
	FILE *LED2 = fopen(LED2_trigger, "w");
	FILE *LED3 = fopen(LED3_trigger, "w");

	if(LED0 == 0)
	{
		printf("Error opening %s.", LED0_trigger);
	}

	if(LED1 == 0)
	{
		printf("Error opening %s.", LED1_trigger);
	}

	if(LED2 == 0)
	{
		printf("Error opening %s.", LED2_trigger);
	}

	if(LED3 == 0)
	{
		printf("Error opening %s.", LED3_trigger);
	}	
	
	int write_LED0 = fprintf(LED0, "none");
	int write_LED1 = fprintf(LED1, "none");
	int write_LED2 = fprintf(LED2, "none");
	int write_LED3 = fprintf(LED3, "none");

	if(write_LED0 <= 0)
	{
		printf("Errors writing to %s.", LED0_trigger);
	}

	if(write_LED1 <= 0)
	{
		printf("Errors writing to %s.", LED1_trigger);
	}

	if(write_LED2 <= 0)
	{
		printf("Errors writing to %s.", LED2_trigger);
	}

	if(write_LED3 <= 0)
	{
		printf("Errors writing to %s.", LED3_trigger);
	}
	
	fclose(LED0);
	fclose(LED2);
	fclose(LED3);
	fclose(LED1);
}






