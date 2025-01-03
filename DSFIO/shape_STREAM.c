/* shape_STREAM.c */

/*----------------------------------------------------
  Copyright (c) 2024 - 2025 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Include dsfio.h */
#include "dsfio.h"

void shape_STREAM(DSF *dsf, DSD_STREAM *stream){
    uint64_t numarea;
    uint64_t data_size;
    uint64_t i;
    uint64_t j;
    uint8_t *dsdl_ptr, *dsdr_ptr;
    uint8_t *data_ptr;

    /* Calcurate data_size & numarea */
    data_size = dsf->data.chunkSize - 12;
    numarea = data_size / dsf->fmt.blockSize;

    /* Allocate stream data memory */
    stream->DSDL = (uint8_t *)calloc((uint64_t)(data_size/2), sizeof(uint8_t));
    stream->DSDR = (uint8_t *)calloc((uint64_t)(data_size/2), sizeof(uint8_t));
    
    /* Store the head of memory. */
    dsdl_ptr = stream->DSDL;
    dsdr_ptr = stream->DSDR;
    data_ptr = dsf->data.data;

    /* Split the interleaved data */
    for (i = 0; i < numarea; i++) {
        for (j = 0; j < dsf->fmt.blockSize; j++) {
            if (i % 2 == 0) {
                /* Left Format */
                *stream->DSDL = *dsf->data.data;
                stream->DSDL++;
            } else {
                /* Right Format */
                *stream->DSDR = *dsf->data.data;
                stream->DSDR++;
            }

            dsf->data.data++;
        }
    }

    /* Move pointer to Head */
    stream->DSDL = dsdl_ptr;
    stream->DSDR = dsdr_ptr;
    dsf->data.data = data_ptr;
}
