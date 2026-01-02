/* dsfio.h */

/*----------------------------------------------------
  Copyright (c) 2024 - 2026 AUDIY
  Released under the MIT license
  https://opensource.org/licenses/mit-license.php
----------------------------------------------------*/

/* include guard */
#ifndef INCLUDED_DSFIO
#define INCLUDED_DSFIO

#include <stdint.h>

/* extern C */
#ifdef __cplusplus
extern "C"
{
#endif

/* DSD chunk */
typedef struct {
    char chunkID[4];    /* "DSD " */
    uint64_t chunkSize; /* 28 (Little Endian) */
    uint64_t fileSize;  /* Total File Size (Little Endian) */
    uint64_t metaPoint; /* Pointer to Metadata chunk (Little Endian) */
} DSD;

/* Format chunk */
typedef struct {
    char chunkID[4];        /* "fmt " */
    uint64_t chunkSize;     /* Usually, 52 (Little Endian) */
    uint32_t formatVersion; /* 1 (Little Endian) */
    uint32_t formatID;      /* 0: DSD RAW (Little Endian) */
    uint32_t channelType;   /* 1 - 7 (Little Endian), See Format Specification. */
    uint32_t channelNum;    /* 1 - 6 (Little Endian), See Format Specification. */
    uint32_t samplesPerSec; /* Sampling Frequency (Little Endian) */
    uint32_t bitsPerSample; /* Quantization Bits (Little Endian) */
    uint64_t sampleCount;   /* samplesPerSec * [Playback time (sec)] (Little Endian) */
    uint32_t blockSize;     /* 4096 */
    //uint32_t RSVD;         /* Fill Zero(0x00, 0x00, 0x00, 0x00) */
} FMT;

/* DATA chunk */
typedef struct {
    char chunkID[4];    /* "data" */
    uint64_t chunkSize; /* (data byte)+12 */
    uint8_t *data;      /* DSD data */
} DATA;

/* DSF struct */
typedef struct {
    DSD dsd;           /* DSD Chunk */
    FMT fmt;           /* Format chunk */
    DATA data;         /* Data chunk */
} DSF;

/* DSD stream */
typedef struct {
    uint8_t *DSDL; /* Left Data (8 samples in 1 index) */
    uint8_t *DSDR; /* Right Data (8 samples in 1 index) */
} DSD_STREAM;

/* Prototype Declaration */
DSF *alloc_DSF(void);                    /* alloc_DSD.c */
void free_DSF(DSF *dsf);                 /* free_DSD.c */
void read_DSF(DSF *dsf, char *filename); /* read_DSD.c */

DSD_STREAM *alloc_STREAM(void);                  /* alloc_STREAM.c */
void free_STREAM(DSD_STREAM *stream);            /* free_STREAM.c */
void shape_STREAM(DSF *dsf, DSD_STREAM *stream); /* shape_STREAM.c */


#ifdef __cplusplus
}
#endif

/* Close include guard */
#endif

