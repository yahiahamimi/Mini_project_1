#ifndef MINI_PROJECT_1_H
#define MINI_PROJECT_1_H

#define WITH_ENGINE_TEMP_CONTROLLER 1

char main_menu();
char sensors_set_menu();
void trafic_light();
void Show_vechile_states();
#if WITH_ENGINE_TEMP_CONTROLLER
void engine_temperature();
#endif
void room_temperature();

enum states
{
    OFF,
    ON
};

#endif /* MINI_PROJECT_1_H */
