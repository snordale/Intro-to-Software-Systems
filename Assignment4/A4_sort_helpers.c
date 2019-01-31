#include "A4_sort_helpers.h"

// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words() {
    int j,i;
    
    for (i = 1; (int) text_array[i][0]!= 0; i++) {
        
        j = i;

            while (j > 0 && strcmp(text_array[j - 1], text_array[j]) > 0) {
                
                char word[MAX_LINE_LENGTH];
                
                strcpy(word, text_array[j - 1]);
                
                word[sizeof(word) - 1] = '\0';

                strcpy(text_array[j - 1], text_array[j]);
                
                text_array[j - 1][sizeof(text_array[j - 1]) - 1] = '\0';

                strcpy(text_array[j], word);
                
                text_array[j][sizeof(text_array[j]) - 1] = '\0';

                --j;
            }

        }
    
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.

    sem_t * semArray[27];
    char buf[200];
    
    FILE * fp;

int initialize( ){

    fp = fopen("out_multi_short.txt", "rw");
    
    for (int i = 0; i < 27; i++) {
        
        char c = (char) ((int) 'a' + i);
        
        sprintf(buf, "semaphore_%c", c);
        sem_unlink(buf);
        if (i == 0) {
            semArray[i] = sem_open(buf, O_CREAT, 0666, 1);
        }
        else {
            semArray[i] = sem_open(buf, O_CREAT, 0666, 0);
        }       
    }    
    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   


int process_by_letter( char* input_filename, char first_letter ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "This process will sort..." lines
    // are printed in the right order (alphabetical).
    
    int x = first_letter-'a';
    if(x == 0){
        int value = 0;
        sem_getvalue(semArray[0], &value);
	    fflush(stdout);
    }
    if (x == 25) {
        sem_wait(semArray[25]);
        read_by_letter(input_filename, first_letter);
        sort_words();
        int i =0;
        //char giant_buf[10000];
        while (text_array[i] != '\0' && i < 500) {
            //sprintf(giant_buf, "%s\n", text_array[i]);
            //sprintf(buf, "%s", text_array[i]);
            //fwrite(buf, 1, strlen(buf), fp);
            i++;
        }
        // printf("%s", giant_buf);
        // fflush(stdout);
        char c = (char) ((int) 'a' + x);
        printf("This process will sort the letter %c\n", c);
        fflush(stdout);
        sem_post(semArray[26]);
    }
    else {
        sem_wait(semArray[x]);
        read_by_letter(input_filename, first_letter);
        sort_words();
        int i = 0;
        int size = 0;
        char giant_buf[10000];
        while (text_array[i] != '\0' && i < 500) {
            text_array[i][199] = '\0';            
            sprintf(giant_buf + size , "%s", text_array[i]);
            //fflush(stdout);
            size += strlen(text_array[i]);
            i++;
            // printf("Infinite Lop %d\n", i);
            // fflush(stdout);
        }
        giant_buf[9999] = "\0";
        char c = (char) ((int) 'a' + x);
        printf("This process will sort the letter %c\n%s\n", c, giant_buf);
        fflush(stdout);
        sem_post(semArray[x + 1]);
    }

    // For Q3, uncomment the following 2 lines and integrate them with your overall solution.
    // read_by_letter( input_filename, first_letter );
    // sort_words( );

    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "Sorting complete!" line
    // is printed at the very end, after all letter lines.
    int value = 0;
    sem_wait(semArray[26]);
    sem_getvalue(semArray[26], &value);

    sprintf( buf, "Sorting complete!\n");
    write(1, buf, strlen(buf));
    sem_post(semArray[26]);

    // For Q3, come up with a way to accumulate the sorted results from each
    // letter process and print the overal sorted values to standard out.
    // You are not allowed to read from the input file, or call sort_words
    // directly from this function.


    return 0;
}

