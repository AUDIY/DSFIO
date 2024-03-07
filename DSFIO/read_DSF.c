/* read_DSD.c */

/*----------------------------------------------------
  Copyright (c) 2024 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* Include Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include dsfio.h */
#include "dsfio.h"

void read_DSF(DSF *dsf, char *filename){
    FILE *fp;
    uint8_t *data_ptr;
    uint8_t LSBdata[256];

    /* Make LSB data table */
    for (int i = 0; i < 256; i++) {

        LSBdata[i] = 0;

        for (int j = 0; j < 8; j++) {
            LSBdata[i] |= ((i >> j) & 1) << (7-j);
        }
    }

    /* Open the DSF File */
    fp = fopen(filename, "rb");

    fread(dsf->dsd.chunkID, 1, 4, fp);

    if (strncmp(dsf->dsd.chunkID, "DSD ", 4) != 0) {
        /* Throw the Error. */
        printf("Error!: This File is NOT DSF.\n");
    } else {
        fread(&dsf->dsd.chunkSize, 8, 1, fp);     /* 28 */
        fread(&dsf->dsd.fileSize, 8, 1, fp);      /* Total File Size */
        fread(&dsf->dsd.metaPoint, 8, 1, fp);     /* Pointer to Metadata Chunk */
        fread(dsf->fmt.chunkID, 1, 4, fp);        /* "fmt " */
        fread(&dsf->fmt.chunkSize, 8, 1, fp);     /* Usually, 52 */
        fread(&dsf->fmt.formatVersion, 4, 1, fp); /* 1 */
        fread(&dsf->fmt.formatID, 4, 1, fp);      /* 0: DSD RAW */
        fread(&dsf->fmt.channelType, 4, 1, fp);   /* 1 - 7, See Format Specification. */
        fread(&dsf->fmt.channelNum, 4, 1, fp);    /* 1 - 6, See Format Specification. */
        fread(&dsf->fmt.samplesPerSec, 4, 1, fp); /* Sampling Frequency */
        fread(&dsf->fmt.bitsPerSample, 4, 1, fp); /* Quantization Bits */
        fread(&dsf->fmt.sampleCount, 8, 1, fp);   /* samplesPerSec * [Playback time (sec)] (Little Endian) */
        fread(&dsf->fmt.blockSize, 4, 1, fp);     /* 4096 */
        fseek(fp, 4, SEEK_CUR);                   /* RESERVED (0x00, 0x00, 0x00, 0x00) */
        fread(dsf->data.chunkID, 1, 4, fp);       /* "data" */
        fread(&dsf->data.chunkSize, 8, 1, fp);    /* (data byte)+12 */
        
        /* For debug */
        //printf("%s\n", dsf->dsd.chunkID);
        //printf("%lld\n", dsf->dsd.chunkSize);
        //printf("%lld\n", dsf->dsd.fileSize);
        //printf("%lld\n", dsf->dsd.metaPoint);
        //printf("%s\n", dsf->fmt.chunkID);
        //printf("%lld\n", dsf->fmt.chunkSize);
        //printf("%d\n", dsf->fmt.formatVersion);
        //printf("%d\n", dsf->fmt.formatID);
        //printf("%d\n", dsf->fmt.channelType);
        //printf("%d\n", dsf->fmt.channelNum);
        //printf("%d\n", dsf->fmt.samplesPerSec);
        //printf("%d\n", dsf->fmt.bitsPerSample);
        //printf("%lld\n", dsf->fmt.sampleCount);
        //printf("%d\n", dsf->fmt.blockSize);
        //printf("%s\n", dsf->data.chunkID);
        //printf("%lld\n", dsf->data.chunkSize);
        //printf("\n");
       
       /* Calcurate Data Byte */
       uint64_t data_size = dsf->data.chunkSize - 12;
       
       /* Allocate data byte memory */
       dsf->data.data = (uint8_t *)calloc(data_size, sizeof(uint8_t));
       data_ptr = dsf->data.data; /* Head Pointer */
       
       for (uint64_t i = 0; i < data_size; i++) {
            /* Store 8 samples */
            fread(dsf->data.data, 1, 1, fp);

            switch (dsf->fmt.bitsPerSample) {
                case 1:
                    /* Store the data as LSB first. */
                    *dsf->data.data = LSBdata[*dsf->data.data];
                    break;

                case 8:
                    /* Store the data as MSB first. */
                    break;

                default:
                    printf("Error!: Invalid Bits per sample.\n");
                    printf("Program ends forcibly.\n");
                    free_DSF(dsf);
                    exit(1);
                    break;
            }

            /* For Debug. */
            //printf("%lld: %x\n", i, *dsd->data.data);
            dsf->data.data++;
       }
       
       /* Move data address to head. */
       dsf->data.data = data_ptr;
    }
    

    /* Close the file */
    fclose(fp);
}
