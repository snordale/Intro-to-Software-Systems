/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
  // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
        
        // Open a binary bmp file
        FILE *bmpfile = fopen( bmp_filename, "rb" );
        if (bmpfile == NULL) {
            printf("Bad File: file not found\n");
            return -1;
        }
        
        // Read the B and M characters into chars
        char b, m;
        fread (&b,1,1,bmpfile);
        fread (&m,1,1,bmpfile);
    
        if (b != 'B' || m != 'M') {
            printf("Bad File: requires bitmap file\n");
            return -1;
        }
        
        // Read the overall file size
        fread(data_size, 1, sizeof(unsigned int), bmpfile);
        
        // Close the file, re-open it to be at the beginning, and read the entire contents
        fclose(bmpfile);
        bmpfile = fopen(bmp_filename, "rb");
    
        //reserve memory in heap
        *img_data = (unsigned char *)malloc(*data_size * 1);
        fread(*img_data, 1, *data_size, bmpfile);

        *width = *(unsigned int*)(*img_data+18);
    
        *height = *(unsigned int*)(*img_data+22);

        *bits_per_pixel = *(unsigned int*)(*img_data+28);

        *padding = (4 - ((*width) * (*bits_per_pixel) / 8) % 4) % 4;
        *padding = (4 - ((*width)*(*bits_per_pixel)/8)%4)%4;
    
        unsigned int* op = (unsigned int*)(*img_data+10);
        *data_offset = *op;
    
        fclose(bmpfile);

  // TO HERE
  
  return 0;  
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
  // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
    
    //reserve memory for final img
    unsigned char * img = (unsigned char *)malloc(data_size * 1);
    
    //copy img data to img
    memcpy(img, img_data, data_size);
    
    //byts = bytes per pixel
    int byts = bits_per_pixel/8;
    
    //mask specified region
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            img[data_offset + (img_width * byts + padding) * y + (x * byts)] = blue;
            img[data_offset + (img_width * byts + padding) * y + (x * byts) + 1] = green;
            img[data_offset + (img_width * byts + padding) * y + (x * byts) + 2] = red;
        }
    }
    
    //create final file and write data into it
    FILE * sol = fopen(output_bmp_filename, "wb");
    fwrite(img, 1, data_size, sol);
    free(img);
    
    fclose(sol);
    
  // TO HERE!
  
  bmp_close( &img_data );
  
  return 0;
}         

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
    
    unsigned int newWidth, newHeight;
    
    //sets width for new img
    if (x_offset < 0) {
        if (img_width1 > img_height2 - x_offset) {
            newWidth = img_width1;
        }
        else {
            newWidth = img_height2 - x_offset;
        }
    }
    else {
        if (img_width1 > img_height2 + x_offset) {
            newWidth = img_width1;
        }
        else {
            newWidth = img_height2 + x_offset;
        }
    }
    
    //sets height for new img
    if (y_offset < 0) {
        if (img_height1 > img_height2 - y_offset) {
            newHeight = img_height1;
        }
        else {
            newHeight = img_height2 - y_offset;
        }
    }
    else {
        if (img_height1 > img_height2 + y_offset) {
            newHeight = img_height1;
        }
        else {
            newHeight = img_height2 + y_offset;
        }
    }
    
    //need dimensions to make new img
    unsigned int minx1, maxx1, miny1, maxy1, minx2, maxx2, miny2, maxy2;
    
    //if offset positive, img2 will be offset
    if (x_offset >= 0) {
        minx2 = x_offset;
    }
    //else, img1 is offset
    else {
        minx2 = 0;
        minx1 = -x_offset;
    }
    //y offset calculations
    if (y_offset >= 0) {
        miny2 = y_offset;
    }
    else {
        miny2 = 0;;
        miny1 = -y_offset;
    }
    
    //setting bmp info for new img
    unsigned int data_offset, bits_per_pixel, byts, padding, data_size;
    
    if (data_offset1 > data_offset2) {
        data_offset = data_offset1;
    }
    else {
        data_offset = data_offset2;
    }
    
    if (bits_per_pixel1 > bits_per_pixel2) {
        bits_per_pixel = bits_per_pixel1;
    }
    else {
        bits_per_pixel = bits_per_pixel2;
    }
    
    byts = bits_per_pixel / 8;
    
    padding = (4 - (newWidth * bits_per_pixel) % 4) % 4;
    
    data_size = (data_offset + (newWidth * byts + padding)) * newHeight;
    
    //reserve memory for final img
    char * sol = (char *)malloc((data_offset + data_size));

    //copies first img if its offset was greater
    if (data_offset == data_offset1) {
        memcpy(sol, img_data1, data_offset1);
    }
    else {
        memcpy(sol, img_data2, data_offset2);
    }
    
    //copy bmp info into final img data
    memcpy(sol + 2, &data_size, sizeof(unsigned int));
    memcpy(sol + 18, &newWidth, sizeof(unsigned int));
    memcpy(sol + 22, &newHeight, sizeof(unsigned int));
    memcpy(sol + 28, &bits_per_pixel, sizeof(unsigned int));
    
    //index to run through and transfer bmp data
    unsigned int i, j;
    
    //transfer img1 to final
    for (int y = miny1; y < maxy1; y++) {
        for(int x = minx1; x < maxx1; x++) {
            i = data_offset + (newWidth * byts + padding) * y + x * byts;
            j = data_offset1 + (img_width1 * bits_per_pixel1 / 8 + padding1) * (y - miny1) + (bits_per_pixel1 / 8) * (x - minx1);
            
            sol[i] = img_data1[j];
            sol[i + 1] = img_data1[j + 1];
            sol[i + 2] = img_data1[j + 2];
        }
    }
    
    //transfer img2 to final
    for (int y = miny2; y < maxy2; y++) {
        for(int x = minx2; x < maxx2; x++) {
            i = data_offset + (newWidth * byts + padding) * y + x * byts;
            j = data_offset2 + (img_width2 * bits_per_pixel2 / 8 + padding2) * (y - miny2) + (bits_per_pixel2 / 8) * (x - minx2);
            
            sol[i] = img_data2[j];
            sol[i + 1] = img_data2[j + 1];
            sol[i + 2] = img_data2[j + 2];
        }
    }
    
    FILE * solFile = fopen(bmp_result, "wb");
    if (solFile == NULL) {
        return -1;
    }
    
    //write final data into file
    fwrite(sol, 1, data_size, solFile);
    
    free(sol);
    fclose(solFile);
    
    bmp_close(&img_data1);
    bmp_close(&img_data2);
    
    return 0;

    
  // TO HERE!
      
  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
