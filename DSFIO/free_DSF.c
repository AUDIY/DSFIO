/* free_DSD.c */

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

/* Free DSD struct */
void free_DSF(DSF *dsf){
    /* Free DSD data */
    free(dsf->data.data);

    /* Free DSD struct */
    free(dsf);
}

