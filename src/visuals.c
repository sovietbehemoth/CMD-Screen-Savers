#include "../include/visuals.h"


//This file is occupied by functions which create visuals that do not require escape sequences
//thus they are generally more likely to work on other compilers or environments. These functions
//are less likely to have unexpected behavior and are more likely to work under alternative 
//terminal conditions as they implement simple stdout calls and not usage of escape sequences that could
//cause issues.


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
    double speed =        _speed == -1 ? 10000: _speed * 1000000;

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

    //Tracks total characters printed. 
    int i = 0;

    //Tracks total iterations.
    int j = 0;

    while (1) {

        //Reached maximum width.
        if (i == max) {
            inc = false; dec = true;
        //Reached zero, return to width max.
        } else if (i == 0) {
            inc = true; dec = false;
        }

        //Position in buffer.
        for (int j = 0; j < i; j++) {
            putchar(' ');
        } putchar(d);
        putchar('\n');
        
        //Every N iterations.
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




//Represents a singular binary string.
typedef struct matrix_area {

    //Is the string actively printing?
    bool active;

    //Position in iteration.
    int J;

    //Amount of binary to generate.
    int length;

    int position;
} matrix_t;


//Count matrixes that are active.
static int matrixes_complete(matrix_t *matrix, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (matrix[i].active == true) {
            count++;
        }
    } 
    return count;
}

/**
 * Create a visual of falling binary.
 * @param width Maximum width of the terminal to be occupied by falling binary. Prevents line wrapping.
 * @param max_strings Maximum amount of strings of binary to be displayed at once. This is restricted to prevent crowding and maintain the matrix style.
 * @param max_strlen Maximum height of the binary strings.
 * @param speed Speed of the falling binary. Should be lower than other visuals.
 */
void matrix_theme(int width, int max_strings, int max_strlen, double speed) {

    int length =  width == -1 ? 160: width;
    int inhabited_areas = 0;
    int max_at_once = max_strings == -1 ? 50: max_strings;
    int max_bin_length = max_strlen == -1 ? 120: max_strlen;
    double delay = speed == -1 ? 10000: speed * 1000000;

    //This pointer keeps record of all strings of binary and tracks when they are finished iterating.
    matrix_t *areas = (matrix_t*) calloc(length, sizeof(matrix_t));

    
    //Set all binary strings to inactive.
    for (int i = 0; i < length; i++) {
        areas[i].active = false;
    }


    while (1) {
        int complete = matrixes_complete(areas, length);
        
        //Initialize new strings if needed.
        if (complete < max_at_once) {

            for (int i = 0; i < max_at_once; i++) {
                


                retry:;
            
                //Random position in array.
                int randpos = rand() % length;
                
                bool available;

                //The random should never be out of index.
                assert(randpos <= length && randpos >= 0);


                for (int l = 0; l < length; l++) {
                    if (l == randpos) {
                        available = false;
                    }
                } available = true;


                if (available == true) {

                    //Random length between zero and the user set max.
                    areas[randpos].length = rand() % max_bin_length;
                    areas[randpos].position = randpos;

                    //Iteration in binary.
                    areas[randpos].J = 0;

                    //Set active.
                    areas[randpos].active = true;


                } else goto retry;

                    

                    
                  
            }
        }



        //Display binary.
        for (int i = 0; i < length; i++) {

            //Must be an active binary string.
            if (areas[i].active == true) {

                //String has completed iteration and should be de-activated.
                if (areas[i].J > areas[i].length) {
                    areas[i].active = false;
                    areas[i].J = 0;
                    putchar(' ');
                    continue;
                }

                //Random (1 or 0)
                int rbin = rand() % 2;

                printf("%d", rbin);

                //Increment iterator.
                areas[i].J += 1;
            } else {
                putchar(' ');
            }
        } putchar('\n');

        //Speed.
        usleep(delay);
    }
}