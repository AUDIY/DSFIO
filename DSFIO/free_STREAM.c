/* free_STREAM.c */

/*----------------------------------------------------
  Copyright (c) 2024 - 2026 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Include dsfio.h */
#include "dsfio.h"

/* free DSD_STREAM struct */
void free_STREAM(DSD_STREAM *stream){
    /* free DSD stream Data */
    free(stream->DSDL);
    free(stream->DSDR);

    /* free struct */
    free(stream);
}

