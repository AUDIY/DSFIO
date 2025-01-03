/* alloc_STREAM.c */

/*----------------------------------------------------
  Copyright (c) 2024 - 2025 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Include dsfio.h */
#include "dsfio.h"

DSD_STREAM *alloc_STREAM(void){
    /* Allocate memory for DSD_STREAM */
    DSD_STREAM *stream = (DSD_STREAM *)malloc(sizeof(DSD_STREAM));

    /* Point to NULL. */
    stream->DSDL = NULL;
    stream->DSDR = NULL;

    /* Return Allocated struct pointer. */
    return stream;
}
