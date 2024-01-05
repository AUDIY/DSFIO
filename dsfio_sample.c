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

int main(void) {

    DSF *dsf;
    DSD_STREAM *stream;
    char *filename = "01_LR_997Hz_0dB_60s.dsf";
    uint64_t i;
    uint64_t j;
    uint8_t left, right;

    dsf = alloc_DSF();
    stream = alloc_STREAM();

    read_DSF(dsf, filename);
    shape_STREAM(dsf, stream);

    for (i = 0; i < (dsf->data.chunkSize - 12)/2; i++){
        //printf("%lld: 0x%2x, 0x%2x\n", i, *stream->DSDL, *stream->DSDR);
        //printf("%lld: 0b", i);
        for (j = 8; j > 0; j--) {
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
        
        stream->DSDL++;
        stream->DSDR++;
    }

    free_DSF(dsf);
    free_STREAM(stream);

    return 0;
}
