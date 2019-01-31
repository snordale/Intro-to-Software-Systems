//
//  q2_calender.c
//  
//
//  Created by Sam Nordale on 2/8/18.
//  260730745
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSep(int lineLength);
void printMonth(char * name, int lineLength);
void printDays(int daysize, int lineLength);
int printNumbers(int firstday, int max, int lineLength, int daysize);

main(int argc, char* argv[]) {
    int daysize, firstday, lineLength;
    
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Error: Bad Input");
    }
    
    daysize = atoi(argv[1]);
    firstday = atoi(argv[2]);
    
    if (daysize < 2) {
        printf("Must print at least 2 characters for labels.");
        return -1;
    }
    
    if (firstday < 1 || firstday > 7) {
        printf("First day must be between 1 and 7.");
        return -1;
    }
    
    lineLength = ((daysize + 3) * 7) + 1;
    
    printMonth("January", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("February", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("March", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("April", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("May", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("June", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("July", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("August", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("September", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("October", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("November", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printMonth("December", lineLength);
    printDays(daysize, lineLength);
    firstday = printNumbers(firstday, 30, lineLength, daysize);
    
    printSep(lineLength);
}

void printSep(int lineLength) {
    printf("|");
    for (int i = 0; i < lineLength - 2; i++) {
        printf("-");
    }
    printf("|\n");
}

void printMonth(char * name, int lineLength) {
    printSep(lineLength);
    printf("|");
    int nameLength = strlen(name);
    int half = (lineLength - 2 - nameLength) / 2;
    for (int i = 0; i < lineLength - 1; i++) {
        
        if (i < half) {
            printf(" ");
        }
        else if (i == half) {
            printf("%s", name);
            i += nameLength;
        }
        else {
            printf(" ");
        }
    }
    printf("|\n");
    printSep(lineLength);
}

void printDays(int daysize, int lineLength) {
    char days[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int supp;
    
    printf("|");
    for (int i = 0;  i < 7; i++) {
        supp = daysize - strlen(days[i]) - 1;
        printf(" ");
        for (int j = 0; j < daysize && j < strlen(days[i]); j++) {
            printf("%c", days[i][j]);
        }
        while (supp >= 0) {
            printf(" ");
            supp--;
        }
        printf(" |");
    }
    printf("\n");
    printSep(lineLength);
}

int printNumbers(int firstday, int max, int lineLength, int daysize) {
    int array[43];
    
    for (int j = 0; j < 43; j++) {
        if (j < firstday) {
            array[j] = 0;
        }
        else if (j >= firstday && j < max + firstday){
            array[j] = j + 1 - firstday;
        }
        else {
            array[j] = 0;
        }
    }
    
    for (int i = 1; i <= 42; i++) {
        if (array[i] == 0) {
            printf("|   ");
        }
        else {
            printf("| %d ", array[i]);
        }
        if (array[i] < 10) {
            for (int k = 1; k < daysize; k++) {
                printf(" ");
            }
        }
        //else if (i > firstday + max) {
//            for (int k = 1; k < daysize; k++) {
//                printf(" ");
//            }
 //       }
        else {
            for (int k = 2; k < daysize; k++) {
                printf(" ");
            }
        }
        
        if (i == 7 || i == 14 || i == 21 || i == 28 || i == 35 || i == 42) {
            printf("|");
            printf("\n");
        }
        if (i == 35 && (array[i] == 0 || array[i+1] == 0)) {
            break;
        }
    }

    firstday = firstday + (max % 7);
    if (firstday > 7) {
        firstday -= 7;
    }
    return firstday;
}
