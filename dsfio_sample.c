/* dsfio_sample.c */

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

/* Include prototype header file */
#include "dsfio.h"

void printb(uint8_t v);
void putb(uint8_t v);

int main(void) {

    DSF *dsf;
    DSD_STREAM *stream;
    char *filename = "Sine_1kHz_0dB_LR_DSD64_swap.dsf";
    //char *filename = "Sine_1kHz_0dB_LR_DSD64.dsf";
    uint64_t i;
    uint64_t j;
    uint8_t left, right;

    dsf = alloc_DSF();
    stream = alloc_STREAM();

    /* Prototype Definition */
    read_DSF(dsf, filename);
    shape_STREAM(dsf, stream);

    for (i = 0; i < (dsf->data.chunkSize - 12)/2; i++){
        //printf("%lld: 0x%2x, 0x%2x\n", i, *stream->DSDL, *stream->DSDR);
        printf("%lld: ", i);
        putb(*stream->DSDL);
        printf(", ");
        putb(*stream->DSDL);
        printf("\n");

        /*
        for (j = 8; j > 0; j--) {
            left = *stream->DSDL / (int)(pow(2, j-1));
            right = *stream->DSDR / (int)(pow(2, j-1));
            //printf("%1d, %1d\n", left, right);
            if (left == 1) {
                *stream->DSDL -= (int)pow(2, j-1);
            }
            if (right == 1) {
                *stream->DSDR -= (int)pow(2, j-1);
            }
        }
        */
        
        stream->DSDL++;
        stream->DSDR++;
    }

    free_DSF(dsf);
    free_STREAM(stream);

    return 0;
}

void printb(uint8_t v) {
  unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);
  do putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

void putb(uint8_t v) {
  //putchar('0'), putchar('b'), printb(v), putchar('\n');
  putchar('0'), putchar('b'), printb(v);
}
