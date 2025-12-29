/* dsfio_sample2.c */
// Print DSD stream by 1bit.

/*----------------------------------------------------
  Copyright (c) 2024 - 2026 AUDIY
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
      /* Print DSD stream by 8bit. */
      printf("%lu: ", i);
      putb(*stream->DSDL);
      printf(", ");
      putb(*stream->DSDL);
      printf("\n");

      /* Increment the pointer */
      stream->DSDL++;
      stream->DSDR++;
    }

    /* Free the structs. */
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
  putchar('0'), putchar('b'), printb(v);
}

