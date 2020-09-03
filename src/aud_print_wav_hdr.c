#include "audiolpf.h"

void aud_print_wav_hdr(wavhdr_t *hdr){
    printf("ChunkID \t%c%c%c%c\n", hdr->chunkId[0], hdr->chunkId[1], hdr->chunkId[2], hdr->chunkId[3]);
    printf("ChunkSize \t%d\n", hdr->chunkSize);
    printf("Format \t\t%c%c%c%c\n", hdr->format[0], hdr->format[1], hdr->format[2], hdr->format[3]);
    
    printf("\n");
    
    printf("Subchunk1ID \t%c%c%c%c\n", hdr->subchunk1Id[0],hdr->subchunk1Id[1], hdr->subchunk1Id[2], hdr->subchunk1Id[3]);
    printf("Subchunk1Size \t%u\n", hdr->subchunk1Size);
    printf("AudioFormat \t%d\n",  hdr->audioFormat);
    printf("NumChannels \t%d\n", hdr->numChannels);
    printf("SampleRate \t%d\n", hdr->sampleRate);
    printf("ByteRate \t%u\n", hdr->byteRate);
    printf("BlockAlign \t%d\n", hdr->blockAlign);
    printf("BitsPerSample \t%d\n", hdr->bitsPerSample);
    
    printf("\n");
}
