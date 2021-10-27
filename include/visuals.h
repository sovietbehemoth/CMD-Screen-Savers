#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#if defined(WIN32) || defined(_WIN32)
    #include <Windows.h>
    #define usleep(ms) Sleep(ms/1000)
#else     
    #include <unistd.h>
#endif


#define clrscr() \
    printf("\033[2J"); printf("\033[1;1H"); 


#define _No_return_ __attribute__((noreturn))

#define V_BASIC_SQUARE "____________\n|          |\n|          |\n|          |\n|          |\n------------\n"

#define ZIGZAG_EXAMPLE -1, -1, -1, -1
#define WAVE_EXAMPLE -1, -1, -1, -1, -1, -1, NULL
#define MATRIX_EXAMPLE 160, 50, 120, .08

#define MILITARY 0
#define _12HOUR 1

#define RANGE(n) (width >= n ? n: width*units)
#define UNIT(n) ((n / width) < 1 ? 1 : n / width)

#define __pure_iterator (i + inc_offset)
#define __pure_time (time + time_offset)

void wave_pattern(int amplitude, double speed, int lwidth, int rwidth, int lexp, int rexp, char *set);
void zigzag_v(int width, int zag_length, char put, double speed);
void throw_solid_item(char c, int length, int width, int distance, int speed);
void throw_item(char *item, int _distance, double _speed);
void circle_item(char *item, int length, int width, double _speed);
void matrix_theme(int width, int max_strings, int max_strlen, double speed);

void rpath_maker(int _width, int _every, double _speed);

void time_counter();
void draw_clock(int format, int width);

#define zigzag(width, zag) zigzag_v(width, zag, -1, -1)
