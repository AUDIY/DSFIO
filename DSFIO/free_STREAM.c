/* free_STREAM.c */

/*----------------------------------------------------
  Copyright (c) 2024 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Include dsfio.h */
#include "dsfio.h"

void free_STREAM(DSD_STREAM *stream){
    free(stream->DSDL);
    free(stream->DSDR);

    free(stream);
}