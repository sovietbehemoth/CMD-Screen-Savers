#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#if defined(WIN32) || defined(_WIN32)
    #include <Windows.h>
    #define usleep(ms) _sleep(ms*1000)
#else     
    #include <unistd.h>
#endif

#define V_BASIC_SQUARE "____________\n|          |\n|          |\n|          |\n|          |\n------------\n"

#define ZIGZAG_EXAMPLE -1, -1, -1, -1
#define WAVE_EXAMPLE -1, -1, -1, -1, -1, -1, NULL

void wave_pattern(int amplitude, double speed, int lwidth, int rwidth, int lexp, int rexp, char *set);
void zigzag_v(int width, int zag_length, char put, double speed);
void throw_solid_item(char c, int length, int width, int distance, int speed);
void throw_item(char *item, int _distance, double _speed);
void circle_item(char *item, int length, int width, double _speed);
void matrix_theme(void);

#define zigzag(width, zag) zigzag_v(width, zag, -1, -1)
