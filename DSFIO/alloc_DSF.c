/* alloc_DSD.c */

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

/* DSD struct allocation */
DSF *alloc_DSF(void){
    /* Memory Allocation */
    DSF *dsf = (DSF *)malloc(sizeof(DSF));

    /* DSD data point to NULL */
    dsf->data.data = NULL;

    /* Return Allocated DSD struct */
    return dsf;
}

