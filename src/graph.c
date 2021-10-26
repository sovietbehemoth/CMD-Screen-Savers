#include "visuals.h"


#define RIGHT 0
#define FORWARD 1
#define LEFT 2


void rpath_maker(int _width, int _every, double _speed) {
    
    int width = _width == -1 ? 20: _width;
    int every = _every == -1 ? 1: _every;
    double speed = _speed == -1 ? 10000 : _speed * 1000000;


    int i = 0;

    int previous_turn = -1;
    int offset = width / 2;

    while (1) {

        for (int i = 0; i < offset; i++) {
            putchar(' ');
        }

        if (offset <= 0) {
            goto right;
        } else if (offset >= width) {
            goto left;
        }


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