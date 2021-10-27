#include "../include/visuals.h"

//This file contains the programs main function as well as the parser for command line arguments.




/**
 * Assert such that index never goes out of bounds due to an unprovided value.
 * @param expr Argc expression.
 * @param field Error unprovided field for.
 */ 
void lenassert(bool expr, char *field) {
    if (!expr) {
        printf("Expected field for %s.\n", field);
        exit(1);
    }
}

/**
 * Unrecognized option exception.
 * @param flag Target flag.
 * @returns Never.
 */ 
_No_return_ void unrec(char *flag) {
    printf("Unrecognized option '%s', run '-h' for a list of options.\n", flag);
    exit(1);
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

                for (int j = i+1; j < argc; j++) {

                    



                    if (!strcmp(argv[j], "-width")) {

                        lenassert(argc >= j + 2, "width");
                        width = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-maxstr")) {

                        lenassert(argc >= j + 2, "maxstr");
                        max_strings = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-maxheight")) {

                        lenassert(argc >= j + 2, "maxheight");
                        max_height = atoi(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-speed")) {
    
                        lenassert(argc >= j + 2, "speed");
                        speed = atof(argv[j+1]); j++;

                    } else if (!strcmp(argv[j], "-h")) {

                        printf("--matrix: Creates a visual of binary digits falling, similar to that of the movie. Note that all units pertaining to measurement are in characters.\n");
                        printf("\t-width: Width of the terminal to be occupied by falling digits, this prevents digits wrapping onto the next line.\n");
                        printf("\t-maxstr: The maximum number of lines of falling digits to be displayed at once, ensures that digits are spaced apart, preserving the effect.\n");
                        printf("\t-maxheight: The maximum length of a single line of falling digits.\n");
                        printf("\t-speed: The speed at which the digits will fall.\n");
                        exit(0);

                    } else unrec(argv[j]);

                    


                } matrix_theme(width, max_strings, max_height, speed); exit(0);
            } else if (!strcmp(argv[i], "--wave")) {

                int amplitude = -1;
                int speed = -1;
                int lw = -1;
                int rw = -1;
                int ia = -1;
                int da = -1;
                char *set = NULL;

                for (int j = i+1; j < argc; j++) {

                    

                    if (!strcmp(argv[j], "-amp")) {
                        lenassert(argc >= j + 2, "amplitude");
                        amplitude = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-speed")) {
                        lenassert(argc >= j + 2, "speed");
                        speed = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-lw")) {
                        lenassert(argc >= j + 2, "left width");
                        lw = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-rw")) {
                        lenassert(argc >= j + 2, "right width");
                        rw = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-ia")) {
                        lenassert(argc >= j + 2, "increment amount");
                        ia = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-da")) {
                        lenassert(argc >= j + 2, "decrement amount");
                        da = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-set")) {
                        lenassert(argc >= j + 2, "char set");
                        set = (char*) malloc(sizeof (char*) * argc); 

                        for (int n = j+1; n < argc; n++) {
                            if (strlen(argv[n]) * sizeof(char) > sizeof(char*) * argc) {
                                set = realloc(set, sizeof (char*) * argc + (strlen(argv[n]) * sizeof(char)));
                            } strcat(set, argv[n]); 
                            
                            if (n != argc - 1) strcat(set, " ");
                        } break;
                        
                    } else if (!strcmp(argv[j], "-h")) {
                        
                        
                        printf("--wave: Creates a filled wave effect.\n");
                        printf("\t-amp: The amplitude of the wave, controls the height of each wave.\n");
                        printf("\t-speed: The speed at which the wave will rise and fall.\n");
                        printf("\t-lw: The slant at which the wave rises.\n");
                        printf("\t-rw: The slant at which the wave falls.\n");
                        printf("\t-ia: Controls how steep the wave rises.\n");
                        printf("\t-da: Controls how steep the wave falls.\n");
                        printf("\t-set: The set of characters that the wave will be composed of. This should be the last argument. The string may be truncated if it surpasses the amplitude.\n");
                        exit(0);
                    
                    } else unrec(argv[j]);

                }

                wave_pattern(amplitude, speed, lw, rw, ia, da, set); exit(0);

            } else if (!strcmp(argv[i], "--circle")) { 
                
                char *item = "x";
                int length = -1;
                int width = -1;
                double speed = -1;
                
                for (int j = i+1; j < argc; j++) {
                    if (!strcmp(argv[j], "-item")) {
                        lenassert(argc >= j + 2, "item");
                        item = (char*) malloc(sizeof (char*) * argc);

                        for (int n = j+1; n < argc; n++) {
                            if (strlen(argv[n]) * sizeof(char) > sizeof(char*) * argc) {
                                item = realloc(item, sizeof (char*) * argc + (strlen(argv[n]) * sizeof(char)));
                            } strcat(item, argv[n]); 
                                
                            if (n != argc - 1) strcat(item, " ");
                        } break;
                    } else if (!strcmp(argv[j], "-len")) {
                        lenassert(argc >= j + 2, "length");
                        length = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-width")) {
                        lenassert(argc >= j + 2, "width");
                        width = atoi(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-speed")) {
                        lenassert(argc >= j + 2, "speed");
                        speed = atof(argv[j+1]); j++;
                    } else if (!strcmp(argv[j], "-h")) {
                        printf("--circle: Render text constantly moving around a set rectangle.\n");
                        printf("\t-item: Text to render. Should be last argument.\n");
                        printf("\t-len: Amount to descend in circle.\n");
                        printf("\t-width: Amount to go forward in circle.\n");
                        printf("\t-speed: Speed of circle render.\n");
                        exit(0);
                    } else unrec(argv[j]);
                }


                circle_item(item, length, width, speed); exit(0);
            } else if (!strcmp(argv[i], "-h")) {
                help_index:;
                printf("Display command line visuals. Run any of the following with '-h' to list their respective flags.\n");
                printf("\t--matrix: Creates a visual of binary digits falling, similar to that of the movie.\n");
                printf("\t--wave: Creates a filled wave effect.\n");
                printf("\t--circle: Render text constantly moving around a set rectangle.\n");
            } else if (i > 0) unrec(argv[i]);
        }
    } else goto help_index;
}