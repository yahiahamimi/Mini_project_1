/******************************************************************************
 *
 * File Name: Mini_project_1.c
 *
 * Description: source file for Mini_project_1
 *
 * Author: Yahia Hamimi
 ******************************************************************************/

#include <stdio.h>
#include "Mini_project_1.h"

struct vechile
{
	int engine;
	int AC;
	int Speed;
#if WITH_ENGINE_TEMP_CONTROLLER
	int Engine_temp_controller;
	float Engine_temp;
#endif
	float room_temp;
} v1;

/**
 * @brief Main function of the program
 *
 * @details This function is the entry point of the program. It initializes the vehicle
 * with default values and enters a loop where it displays a menu and waits for
 * user input. Depending on the user's input it either turns on or off the
 * vehicle's engine, sets the traffic light color, sets the room temperature, or
 * sets the engine temperature. It also displays the current state of the
 * vehicle.
 *
 * @return 0 if the user chooses to quit the system
 */
int main(void)
{
	v1.engine = ON;
	v1.AC = OFF;
	v1.Speed = 0;
	v1.room_temp = 25;
#if WITH_ENGINE_TEMP_CONTROLLER
	v1.Engine_temp_controller = OFF;
	v1.Engine_temp = 100;
#endif
	char sensors_menu_option;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while (1)
	{
		char option = main_menu();
		if (option == 'c')
			return 0;
		if (option == 'a')
		{
			printf("Vehicle engine is turned on\n");
			while (1)
			{

				sensors_menu_option = sensors_set_menu();
				switch (sensors_menu_option)
				{
				case 'a':
				{
					printf("Vehicle engine is turned off\n");
					break;
				}
				case 'b':
				{
					trafic_light();
					if (v1.Speed == 30)
					{
						if (v1.AC == OFF)
							v1.AC = ON;
						v1.room_temp = (v1.room_temp * 5 / 4) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER
						if (v1.Engine_temp_controller == OFF)
							v1.Engine_temp_controller = ON;
						v1.Engine_temp = (v1.Engine_temp * 5 / 4) + 1;
#endif
					}
					Show_vechile_states();
					break;
				}
				case 'c':
				{
					room_temperature();
					Show_vechile_states();
					break;
				}
#if WITH_ENGINE_TEMP_CONTROLLER
				case 'd':
				{

					engine_temperature();
					Show_vechile_states();
					break;
				}
#endif
				}
				if (sensors_menu_option == 'a')
					break;
			}
			if (option == 'b')
				printf("Vehicle engine is turned off\n");
		}
	}
}
/**
 * @name main_menu
 *
 * @brief Prints the main menu and gets the user option
 *
 * @details This function prints the main menu options and gets the user's
 *          choice. It returns the user's choice in the form of a character.
 *
 * @return The user's choice in the form of a character (a, b or c)
 */
char main_menu()
{
	char input_chr;
	printf("This is the main menu what option do you want\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	scanf(" %c", &input_chr);
	return input_chr;
}
/**
 * @name sensors_set_menu
 *
 * @brief Prints the sensors set menu and gets the user option
 *
 * @details This function prints the sensors set menu options and gets the user's
 *          choice. It returns the user's choice in the form of a character.
 *
 * @return The user's choice in the form of a character (a, b, c or d)
 */
char sensors_set_menu()
{
	char input_chr;
	printf("\na. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature\n");
#endif
	scanf(" %c", &input_chr);
	return input_chr;
}
/**
 * @name trafic_light
 *
 * @brief This function sets the traffic light color and the corresponding
 *        vehicle speed
 *
 * @details This function prints a prompt asking the user to enter the
 *          required color and gets the user's choice. Depending on the user's
 *          choice it sets the vehicle speed to 0, 30 or 100.
 */
void trafic_light()
{
	char input_chr;
	printf("Enter the required color(r/o/g):\n");
	scanf(" %c", &input_chr);

	switch (input_chr)
	{
	case 'g':
	{
		v1.Speed = 100;
		break;
	}
	case 'o':
	{
		v1.Speed = 30;
		break;
	}
	case 'r':
	{
		v1.Speed = 0;
		break;
	}
	}
}
/**
 * @name room_temperature
 *
 * @brief Sets the room temperature and the air conditioning status
 *
 * @details This function prompts the user to enter the desired room temperature.
 *          Depending on the user's input, it sets the room temperature to the
 *          input value and sets the air conditioning status to ON or OFF.
 */
void room_temperature()
{
	int input_data;
	printf("Enter the required degree:\n");
	scanf("%d", &input_data);

	if (input_data <= 10)
	{
		v1.AC = ON;
		v1.room_temp = 20;
	}
	else if (input_data >= 30)
	{
		v1.AC = ON;
		v1.room_temp = 20;
	}
	else
	{
		v1.AC = OFF;
		v1.room_temp = input_data;
	}
}
#if WITH_ENGINE_TEMP_CONTROLLER
/**
 * @name engine_temperature
 *
 * @brief Sets the engine temperature and the engine temperature controller status
 *
 * @details This function prompts the user to enter the desired engine temperature.
 *          Depending on the user's input, it sets the engine temperature to the
 *          input value and sets the engine temperature controller status to ON or
 *          OFF.
 */
void engine_temperature()
{
	int input_data;
	printf("Enter the required degree:\n");
	scanf("%d", &input_data);
	if (input_data <= 100)
	{

		v1.Engine_temp_controller = ON;
		v1.Engine_temp = 125;
	}
	else if (input_data >= 150)
	{
		v1.Engine_temp_controller = ON;
		v1.Engine_temp = 125;
	}
	else
	{
		v1.Engine_temp_controller = OFF;
		v1.Engine_temp = input_data;
	}
}
#endif

/**
 * @name Show_vechile_states
 *
 * @brief Displays the current state of the vehicle
 *
 * @details This function prints the current state of the vehicle, including the
 *          status of the engine, air conditioning, traffic light, room temperature,
 *          and engine temperature (if the engine temperature controller is on).
 */
void Show_vechile_states()
{
	printf("Engine is ON\n");
	if (v1.AC == OFF)
		printf("AC is OFF\n");
	else
		printf("AC is ON\n");
	printf("Engine speed is: %d Km/H\n", v1.Speed);
	printf("Room temperature is: %.1f C\n", v1.room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER
	if (v1.Engine_temp_controller == OFF)
	{
		printf("Engine Temp Controller is OFF\n");
	}
	else
		printf("Engine Temp Controller is ON\n");
	printf("Engine temperature is: %.1f C\n", v1.Engine_temp);
#endif
}
