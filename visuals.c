#include "./visuals.h"

//Generate psuedo random string.
static char *random_str(unsigned int max) {

    //Initial allocation.
    char *str = malloc(sizeof(char) * max);


    for (int i = 0; i < max; i++) {
        retry:;

        //Random char from basic unicode range (0-127).
        int c = rand() % 127;

        //Char must be printable.
        if (isprint(c) && c != 0) {
            str[i] = c;
        } else goto retry;

    } return str;
}

//Print n of str until in is chars.
static void printu(char *str, int chars) {
    for (int i = 0; i < strlen(str); i++) {
        if (i == chars) {
            return;
        } else putchar(str[i]);
    }
}

/**
 * Create a simple vertical dynamic wave pattern.
 * @param amplitude The height of the waves (in characters).
 * @param _speed The speed of the wave going up and down (in seconds).
 * @param lwidth Controls the slant at which the wave rises (in characters).
 * @param rwidth Controls the slant at which the wave falls (in characters).
 * @param lexp Controls how steep the wave's rise is (in characters).
 * @param rexp Controls how steep the wave's fall is (in characters).
 * @param set Set of characters to iterate through in wave (set to NULL for random set).
 */ 
void wave_pattern(int amplitude, double _speed, int lwidth, int rwidth, int lexp, int rexp, char *set) {
    //Default values.
    int max =           amplitude == -1 ? 30 : amplitude; //30
    int dec_every =     lwidth == -1 ? 5: lwidth; //3
    int inc_every =     rwidth == -1 ? 5: rwidth; //5
    int inc_amt =       rexp == -1 ? 1: rexp; //1
    int dec_amt =       lexp == -1 ? 1: lexp; //1
    int speed =        _speed == -1 ? 10000: _speed * 1000000;

    //Random seed.
    srand(time(NULL));
    
    //Tracks the amount of characters to generate a string for.
    int i = 0;
    
    //Tracks the amount of characters put.
    int j = 0;

    //Whether to increment or decrement i.
    bool dec = false;
    bool inc = true;

    while (1) {
        if (set == NULL) {
            //Generate psuedo random string.
            char *str = random_str(i);
            puts(str); 
        } else {

            //Custom char set.

            int n = 0;
            while (1) {
                if (n >= i) {
                    break;
                }

                printu(set, (i - n));
                n += strlen(set);
            } putchar('\n');
        }

        usleep(speed);

        //If i is max, we've reached our wave height.
        if (i >= max) {
            dec = true;
            inc = false;
        //Starting a new wave.
        } else if (i == 0) {
            inc = true;
            dec = false;
        }

        //Increment/decrement character every N chars.
        if (inc && j % inc_every == 0) {
            i += inc_amt;
        } else if (dec && j % dec_every == 0) {
            i -= dec_amt;
        }

        j++;
    }
}

/**
 * Generate zig-zag line which 'bounces'.
 * @param width Point at which the zig zag line will bounce back.
 * @param zag_length Slant of line.
 * @param put Character to encode line in.
 * @param _speed Speed of the line.
 */ 
void zigzag_v(int width, int zag_length, char put, double _speed) {
    //Default values.
    char d = put == -1 ? '0': put;
    int max = width == -1 ? 40: width;
    int amt = zag_length == -1 ? 5: zag_length;
    double speed = _speed == -1 ? 100000: _speed * 1000000;

    bool dec = false;
    bool inc = true;

    int i = 0;
    int j = 0;

    while (1) {
        if (i == max) {
            inc = false; dec = true;
        } else if (i == 0) {
            inc = true; dec = false;
        }

        for (int j = 0; j < i; j++) {
            putchar(' ');
        } putchar(d);
        putchar('\n');
        
        
        if (inc && j % amt == 0) {
            i++;
            usleep(speed);
        } else if (dec && j % amt == 0) {
            i--;
            usleep(speed);
        }

        j++;
    }

}





typedef struct matrix_area {
    bool active;

    int J;
    int length;
    int position;
} matrix_t;

static int matrixes_complete(matrix_t *matrix, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (matrix[i].active == true) {
            count++;
        }
    } 
    return count;
}

void matrix_theme(void) {
    int length = 160;
    int inhabited_areas = 0;
    int max_at_once = 50;
    int max_bin_length = 120;
    int delay = 10000;

    matrix_t *areas = (matrix_t*) calloc(length, sizeof(matrix_t));

    

    for (int i = 0; i < length; i++) {
        areas[i].active = false;
    }


    while (1) {
        int complete = matrixes_complete(areas, length);
        
        if (complete < max_at_once) {

            for (int i = 0; i < max_at_once; i++) {
                


                retry:;
            
                int randpos = rand() % length;
                
                bool available;



                assert(randpos <= length && randpos >= 0);
                for (int l = 0; l < length; l++) {
                    if (l == randpos) {
                        available = false;
                    }
                } available = true;


                if (available == true) {
                    areas[randpos].length = rand() % max_bin_length;
                    areas[randpos].position = randpos;
                    areas[randpos].J = 0;
                    areas[randpos].active = true;


                } else goto retry;

                    

                    
                  
            }
        }

        for (int i = 0; i < length; i++) {
            if (areas[i].active == true) {
                if (areas[i].J > areas[i].length) {
                    areas[i].active = false;
                    areas[i].J = 0;
                    putchar(' ');
                    continue;
                }

                int rbin = rand() % 2;

                printf("%d", rbin);

                areas[i].J += 1;
            } else {
                putchar(' ');
            }
        } putchar('\n');
        usleep(delay);
    }
}