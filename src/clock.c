#include "../include/visuals.h"


//This file stores functions to generate displays which display various types of
//time tracking interfaces such as stopwatches, digital watches, etc.




//A verbose stopwatch tracking from nanoseconds to days.
void time_counter() {

  
    time_t rtime;
    time(&rtime);
    struct tm *info = localtime(&rtime);
    
    long i = 0;

    while (1) {
        usleep(1);
        
        long double nanoseconds = i * 1000;
        double milliseconds = i / 100;
        double seconds = i / 1e+6;
        double minutes = i / 6e+7;
        double hour = i / 3.6e+9;
        long double day = i / 86400000000;
        

        printf("Nanoseconds: %ld\n", (long) nanoseconds);
        printf("Microseconds: %ld\n", (long) i);
        printf("Milliseconds: %f\n", milliseconds);
        printf("Seconds: %f\n", seconds * 1000);
        printf("Minutes: %f\n", minutes * 1000);
        printf("Hours: %f\n", hour * 1000);

        clrscr();

     
        i++;
    }
}

/**
 * Set a whitespace offset.
 * @param width N of offset.
 */ 
static void offset_c(int width) {
  for (int i = 0; i < width / 2; i++) {
    putchar(' ');
  }
}

/**
 * Dependent function to create visual of slider tracking time.
 * @param unit Unit to create cap for and possible modulus to fit width.
 * @param time_offset Offset the raw time calculated.
 * @param inc_offset Offset the raw incremented value.
 * @param time Raw time value to generate slider based off of.
 * @param width Max width of screen.
 */ 
static void draw_counter(int unit, int time_offset, int inc_offset, int time, int width) {
    //Calculate max of slider to fit width.
    int units = UNIT(unit);


    for (int i = 0; i < RANGE(unit); i++) {

        //Head of slider.
        if (units != 1 && __pure_iterator == __pure_time ) {
            putchar('>');
            continue;
        }

        //Body of slider.
        if (__pure_iterator < __pure_time && __pure_iterator % units == 0) {
            putchar('=');

        //Exception.
        } else if (__pure_iterator == __pure_time && __pure_iterator % units == 0) {
            if (units == 1 || (units != 1 && __pure_iterator == 0)) putchar('>');

        //Fit offset.
        } else if (__pure_iterator % units == 0) {
            putchar(' ');
        } 
    } putchar('\n');
}

/**
 * Display a digital clock interface detailing the percentage complete of (seconds, minutes, hours, days out of week, days out of month, and months out of year).
 * @param format Military or twelve hour (todo implement twelve hour).
 * @param width Width to occupy screen (60 is most stable).
 */ 
void draw_clock(int format, int width) {
  

    while (1) {

        //Delay. The clock is dependent on seconds for precision. As a result, the seconds is the 
        //only unit which is independent.
        usleep(100000);

        //Retrieve current time every iteration.
        time_t rtime;
        time(&rtime);
        struct tm *info = localtime(&rtime);
        
        
        //Create initial whitespace offset.
        offset_c(width);

        //Main digital clock interface.
        printf("%s%d:%s%d:%s%d\n", 
            info->tm_hour < 10 ? "0": "",                                                                               //All regions of clock should be 2 digits.
            format == MILITARY ? info->tm_hour: (info->tm_hour >= 12 ? info->tm_hour - 12 : info->tm_hour),             //Adjust for military and 12 hour time accordingly.
            info->tm_min < 10 ? "0": "",                                                                                //All regions of clock should be 2 digits.
            info->tm_min, 
            info->tm_sec < 10 ? "0" : "",                                                                               //All regions of clock should be 2 digits.
            info->tm_sec
        );

        offset_c(width);



        //Print day of week.
        switch (info->tm_wday) {
            case 1: printf("Monday"); break;
            case 2: printf("Tuesday"); break;
            case 3: printf("Wednesday"); break;
            case 4: printf("Thursday"); break;
            case 5: printf("Friday"); break;
            case 6: printf("Saturday"); break; 
            case 7: printf("Sunday"); break;
        } putchar('\n');



        offset_c(width);


        //Print month.
        switch (info->tm_mon) {
            case 0: printf("January"); break;
            case 1: printf("February"); break;
            case 2: printf("March"); break;
            case 3: printf("April"); break;
            case 4: printf("May"); break;
            case 5: printf("June"); break;
            case 6: printf("July"); break;
            case 7: printf("August"); break;
            case 8: printf("September"); break;
            case 9: printf("October"); break;
            case 10: printf("November"); break;
            case 11: printf("December"); break;
        } putchar(' ');

        //Print day in month.
        printf("%d\n", info->tm_mday);
        offset_c(width);

        //Print year, tm_year is formatted in years since 1900.
        printf("%d\n", info->tm_year + 1900);


            
        //Second counter.
        printf("(%f%%) ", ((double)info->tm_sec / 60) * 100);
        draw_counter(60, 1, 0, info->tm_sec, width);


        //Minute counter.
        printf("(%f%%) ", ((double)info->tm_min / 60) * 100);
        draw_counter(60, 1, 0, info->tm_min, width);


        //Hour counter.
        printf("(%f%%) ", ((double)info->tm_hour / 24) * 100);
        draw_counter(24, 1, 0, info->tm_hour, width);


        //Day of week has a unique exception that makes it incompatible with draw_counter().
        printf("(%f%%) ", ((double)info->tm_wday / 7) * 100);
        int units = UNIT(7);
        for (int i = 0; i < RANGE(7); i++) {
            if (i-1 == info->tm_wday) {
                putchar('>');
            } 

            if (i-1 < info->tm_wday && i-1 % units == 0) {
                putchar('=');
            } else if (i-1 % units == 0) {
                putchar(' ');
            }
        } putchar('\n');

            
        //Day of month counter.
        printf("(%f%%) ", ((double)info->tm_mday / 31) * 100);
        draw_counter(31, 0, 0, info->tm_mday, width);


        //Month out of year counter.
        printf("(%f%%) ", (((double)info->tm_mon + 1) / 12) * 100);
        draw_counter(11, 1, 0, info->tm_mon, width);


        clrscr();
    }
}