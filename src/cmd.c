#include "./visuals.h"

void lenassert(bool expr, char *field) {
    if (!expr) {
        printf("Expected field for %s.\n", field);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            if (!strcmp(argv[i], "--matrix")) {
                
                int width = -1;
                int max_strings = -1;
                int max_height = -1;
                double speed = -1;

                for (int j = i; j < argc; j++) {

                    



                    if (!strcmp(argv[j], "-width")) {

                        lenassert(argc >= j + 1, "width");
                        width = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-maxstr")) {

                        lenassert(argc >= j + 1, "maxstr");
                        max_strings = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-maxheight")) {

                        lenassert(argc >= j + 1, "maxheight");
                        max_height = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-speed")) {
    
                        lenassert(argc >= j + 1, "speed");
                        speed = atof(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-h")) {

                        printf("--matrix: Creates a visual of binary digits falling, similar to that of the movie. Note that all units pertaining to measurement are in characters.\n");
                        printf("\t-width: Width of the terminal to be occupied by falling digits, this prevents digits wrapping onto the next line.\n");
                        printf("\t-maxstr: The maximum number of lines of falling digits to be displayed at once, ensures that digits are spaced apart, preserving the effect.\n");
                        printf("\t-maxheight: The maximum length of a single line of falling digits.\n");
                        printf("\t-speed: The speed at which the digits will fall.\n");
                        exit(0);

                    }

                    


                } matrix_theme(width, max_strings, max_height, speed);
            }
        }
    }
}