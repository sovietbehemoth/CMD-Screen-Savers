#include "visuals.h"

void throw_solid_item(char _c, int _length, int _width, int _distance, int _speed) {
    printf("\n\n\n\n\n\n\n\n\n");

    char c = _c == -1 ? '0': _c;
    int length = _length == -1 ? 2: _length;
    int width = _width == -1 ? 2: _width;
    int speed = _speed == -1 ? 10000: _speed * 1000000;
    int distance = _distance == -1 ? 60: _distance;

    bool clear = true;
    bool decr = false;

    int i = 0;

    while (1) {
        if (i > distance) {
            decr = true;
        }

        if (i == 0) {
            decr = false;
        }


        for (int j = 0; j < length; j++) {
            for (int n = 0; n < i; n++) {
                putchar(' ');
            } 
            for (int n = 0; n < width; n++) {
                putchar(c);
            } putchar('\n');
        }
        printf("\033[2J"); printf("\033[1;1H");
        usleep(speed);
        
        //putchar('');
        if (!decr) {
            i++;
        } else i--;
    }
}


void throw_item(char *item, int _distance, double _speed) {
    int speed = _speed == -1 ? 10000: _speed * 1000000;
    int distance = _distance == -1 ? 10: _distance;

    bool clear = true;
    bool decr = false;

    int i = 0;
    int n;
    int newlines = 0;

    while (1) {
        //printf("%d\n",i);
        if (i > distance) {
            decr = true;
        }

        if (i == 0) {
            decr = false;
        }

        int save = 0;
        int n = 0;



        for (int l = 0; l < i; l++) {
            putchar(' ');
        }
        
        

        for (n = 0; n < i+strlen(item)+1; n++) {


            if (n >= strlen(item)) {
                puts("\n\n\n\n");
                break;
            }

            

            if (item[n] == '\n') {
                putchar('\n');
                for (int x = 0; x < i; x++) {
                    putchar(' ');
                }
                
                continue;
            }

            putchar(item[n]);
        } 
        printf("\033[2J"); printf("\033[1;1H");
        usleep(speed);
        //putchar('');
        if (!decr) {
            i++;
        } else i--;
    }
}

void circle_item(char *item, int length, int width, double _speed) {
    int speed = _speed == -1 ? 10000: _speed * 1000000;
    int distance = width == -1 ? 10: width;
    int downfor = width == -1 ? 10: length;

    bool clear = true;
    bool decr = false;
    bool stay_down = true;
    bool go_up = false;

    int i = 0;
    int n;
    int nline_dec = downfor;
    int nline_inc = 0;

    while (1) {
        if ((i > distance*2 && stay_down == true)) {
            go_up = true;
            stay_down = false;
        }

        if (i == 0 && decr == true) {
            decr = false;
            stay_down = true;
            go_up = false;
            nline_inc = 0;
            nline_dec = downfor;
        }

        int save = 0;
        int n = 0;


        //puts("\n\n\n");

        if (nline_inc == -1) {
            for (int l = 0; l < i; l++) {
                putchar(' ');
            }
        }
        
        

        for (n = 0; n < i+strlen(item)+1; n++) {


            if (n >= strlen(item)) {
                putchar('\n');
                break;
            }

            

            if (item[n] == '\n') {
                putchar('\n');

                if (nline_inc == -1) {
                    for (int x = 0; x < i; x++) {
                        putchar(' ');
                    }
                }
                
                continue;
            }

            putchar(item[n]);
        } 
        printf("\033[2J"); printf("\033[1;1H");
        // usleep(speed);


        if (stay_down == true) {
            if (nline_inc == downfor) {
                nline_inc = -1;
            }

            if (nline_inc > -1) {
                for (int j = 0; j < nline_inc; j++) {
                    putchar('\n');
                } nline_inc++;
            } else {
                for (int j = 0; j < downfor; j++) {
                    putchar('\n');
                } 
            }
        }

        if (go_up == true) {
            if (nline_dec == 0) {
                go_up = false;
                decr = true;
                stay_down = false;
            }

            for (int j = 0; j < nline_dec; j++) {
                putchar('\n');
            } nline_dec--;
        }

        usleep(speed);
        if ((nline_inc == -1 && go_up == false)) {
            if (!decr) {
                i++;
            } else i--;
        }
    }
}