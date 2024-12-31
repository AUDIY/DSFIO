/* dsfio_sample.c */
// Print DSD stream by 8bit.

/*----------------------------------------------------
  Copyright (c) 2024 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

/* Include prototype header file */
#include "dsfio.h"

/* Prototype Definition */
void printb(uint8_t v);
void putb(uint8_t v);

int main(void) {

    DSF *dsf;
    DSD_STREAM *stream;
    
    char *filename = "Sine_1kHz_0dB_LR_DSD64.dsf"; // Change the file name to read.
    uint8_t left, right;

    /* Allocate the structs. */
    dsf = alloc_DSF();
    stream = alloc_STREAM();

    read_DSF(dsf, filename);   // Read DSF file
    shape_STREAM(dsf, stream); // shape DSF File to stream

    for (uint64_t i = 0; i < (dsf->data.chunkSize - 12)/2; i++){
        
        /* Print DSD stream by 1bit. */
        for (uint64_t j = 8; j > 0; j--) {
            left = *stream->DSDL / (int)(pow(2, j-1));
            right = *stream->DSDR / (int)(pow(2, j-1));
            printf("%1d, %1d\n", left, right);
            if (left == 1) {
                *stream->DSDL -= (int)pow(2, j-1);
            }
            if (right == 1) {
                *stream->DSDR -= (int)pow(2, j-1);
            }
        }
        
        /* Increment the pointer */
        stream->DSDL++;
        stream->DSDR++;
    }

    /* Free the structs. */
    free_DSF(dsf);
    free_STREAM(stream);

    return 0;
}

