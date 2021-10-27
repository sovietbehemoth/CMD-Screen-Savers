#include "../include/visuals.h"


#define RIGHT 0
#define FORWARD 1
#define LEFT 2

/**
 * Generate a line which changes direction randomly.
 * @param _width Maximum length that the line will travel.
 * @param _every Amount traveled in one movement.
 * @param _speed Speed to travel.
 */
void rpath_maker(int _width, int _every, double _speed) {
    
    int width = _width == -1 ? 20: _width;
    int every = _every == -1 ? 1: _every;
    double speed = _speed == -1 ? 10000 : _speed * 1000000;


    int i = 0;

    int previous_turn = -1;
    int offset = width / 2;

    while (1) {

        //Offset from 0.
        for (int i = 0; i < offset; i++) {
            putchar(' ');
        }

        //Do not go past maximum width or before zero. Prevent line wrapping.
        if (offset <= 0) {
            goto right;
        } else if (offset >= width) {
            goto left;
        }



        //Random turn.
        int turn = rand() % 4;



        if (turn == RIGHT) {
            right:;
            offset += every;
        } else if (turn == LEFT) {
            left:;
            offset -= every;
        } 

        printf("*\n");
        usleep(speed);
    }
}