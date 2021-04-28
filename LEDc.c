// Code to control LED3 usr by arguments
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LED3 "/sys/class/leds/beaglebone:green:usr3" //path

// Prototypes functions
void WriteLED(char filename[], char value[]);
void RemoveTrigger();

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		// Checks if number of arguments are right
		printf("Error wrong number of arguments! \n");
		return 2;
	}
	printf("Starting the script...\n");
	// Comparing argument
	if(strcmp(argv[1], "on") == 0)
	{
		// Turns on LED3
		printf("LED on \n");
		RemoveTrigger();
		WriteLED("/brightness","1");
	}
	else
	{
		// Turns off LED3
		if(strcmp(argv[1], "off") == 0)
		{
			printf("LED off \n");
			RemoveTrigger();
			WriteLED("/brightness", "0");
		}
		else
		{
			if(strcmp(argv[1], "flash") == 0)
			{
				// LED3 starts flashing 50ms on, 50ms off (needs sudo)
				printf("LED Flashing \n");
				WriteLED("/trigger","timer");
				WriteLED("/delay_on","50");
				WriteLED("/delay_off","50");
			}
			else
				printf("Wrong arguments \n");

		}
	}
	printf("Script Done \n");

	return 0;
}

// Complete functions
void WriteLED(char filename[], char value[])
{
	// Writes to the passed value to the file in the path
	FILE* fp;//
	char fullFile[100];
	sprintf(fullFile,LED3 "%s", filename);
	fp = fopen(fullFile, "w+");
	fprintf(fp, "%s", value);
	fclose(fp);
}

void RemoveTrigger()
{
	// Writes "none" in trigger
	WriteLED("/trigger", "none");
}
