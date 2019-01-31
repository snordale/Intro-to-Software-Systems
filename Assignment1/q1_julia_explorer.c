#include<stdio.h>
#include<stdlib.h>

//Sam Nordale
//260730745

main(int argc, char* argv[]) {
    
    if (argc != 4) {
        printf("Program requires 3 arguments.\n");
        exit(-1);
    }
    
    FILE * f = fopen(argv[1], "r");
    
    if (f == NULL) {
        printf("Error: Bad File");
        exit(-1);
    }
    
    if (((int) *argv[2] < 48 || (int) *argv[2] > 57) || ((int) *argv[3] < 48 || (int) *argv[3] > 57)) {
        printf("Second and third arguments must be numbers.\n");
        exit(-1);
    }
    
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    
    char * fileName = "tempFile.txt";
    FILE * n = fopen(fileName, "w");
    
    if (n == NULL) {
        printf("Error: Bad File");
        exit(-1);
    }
    
    char view[3] = "aaa";
    char aString[3] = "#A#";
    int aFound = 0;
    char bString[3] = "#B#";
    int bFound = 0;
    char curr;
    char second;
    char third;
    
    curr = fgetc(f);
    while (curr != EOF) {

        if (curr == aString[0] || curr == bString[0]) {
            
            view[0] = curr;
            second = fgetc(f);
            
            if (second == aString[1]) {
                view[1] = second;
                third = fgetc(f);
                
                if (third == aString[2]) {
                    fprintf(n, "%.6f", a);
                    printf("%.6f", a);
                    curr = fgetc(f);
                    aFound = 1;
                }
                else {
                    fputc(curr, n);
                    fputc(second, n);
                    printf("%c", curr);
                    printf("%c", second);
                    curr = third;
                }
            }
            
            else if (second == bString[1]) {
                view[1] = second;
                third = fgetc(f);
                
                if (third == bString[2]) {
                    fprintf(n, "%.6f", b);
                    printf("%.6f", b);
                    curr = fgetc(f);
                    bFound = 1;
                }
                else {
                    fputc(curr, n);
                    fputc(second, n);
                    printf("%c", curr);
                    printf("%c", second);
                    curr = second;
                }
                
            }
            
            else {
                curr = second;
                fputc(curr, n);
                printf("%c", curr);
            }
            
        }
        else {
            fputc(curr, n);
            printf("%c", curr);
            curr = fgetc(f);
        }
    }
    
    if (aFound == 0 || bFound == 0) {
        fclose(f);
        fclose(n);
        remove(fileName);
        printf("Error: No value tags found\n");
        return -1;
        
    }
    
    fclose(f);
    fclose(n);
    
    remove(fileName);
//    rename(fileName, argv[1]);
    return 0;

}
