#include "audiolpf.h"

int main(int argc, char* argv[])
{   
    FILE *file = NULL;
    char * buffer = 0;
    long length;

    if(argc > 1){
        file = fopen(argv[1], "rb");
    } else {
        file = fopen("pisk-mikrofona-mikrofon-fonit-32184.wav", "rb");
    }
    if (!file) {
        printf("can't open audio file\n");
        exit(EXIT_FAILURE);
    }
    fseek (file, 0, SEEK_END);
    length = ftell (file);
    fseek (file, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, file);
    }
    fclose (file);

    if(((wavhdr_t *)(buffer))->audioFormat != 1){
        fprintf(stderr, "Error: Not supported Audio format");
        exit(EXIT_FAILURE);
    }

    aud_print_wav_hdr((wavhdr_t *)(buffer));
    char c[4];
    memcpy(c, buffer, sizeof(c));
    DataChunk_t *DataChunk = NULL;
    for(int i = 0; i < (length - 3); i++){
        memcpy(c, &(buffer[i]), sizeof(c));
        if(c[0] == 'd' && c[1] == 'a' && c[2] == 't' && c[3] == 'a'){
            printf("blockID 3 t%c%c%c%c\n",c[0], c[1], c[2], c[3]);
            DataChunk = (DataChunk_t *)&(buffer[i]);
        }   
    }

    //DSP 
    int16_t *data = (int16_t *)(DataChunk + sizeof(DataChunk_t));
#ifdef LOW_PASS_FILTER
    double *coef = aud_lpf_calc_coef(NUM_OF_FIR_COEF, CUT_FREQ, (int)((wavhdr_t *)(buffer))->sampleRate);
#else
    double *coef = aud_bsf_calc_coef(NUM_OF_FIR_COEF, CUT_FREQ1, CUT_FREQ2, (int)((wavhdr_t *)(buffer))->sampleRate);
#endif
    int16_t *coef_int16 = aud_fir_coef_float2int16(NUM_OF_FIR_COEF, coef);
    int16_t *data_f = aud_fir_calc_int16(data, DataChunk->chunkSize/2, coef_int16, NUM_OF_FIR_COEF);
    DataChunk->chunkSize = DataChunk->chunkSize - (NUM_OF_FIR_COEF * sizeof(int16_t));
    ((wavhdr_t *)(buffer))->chunkSize = DataChunk->chunkSize + sizeof(wavhdr_t) + sizeof(DataChunk_t) - 8;
    //Write new file
    FILE *fp = fopen("test.wav", "w+");
    fwrite(buffer, 1, sizeof(wavhdr_t), fp);
    fwrite(DataChunk, 1, sizeof(DataChunk_t), fp);
    fwrite(&(data_f[NUM_OF_FIR_COEF - 1]), 1, DataChunk->chunkSize, fp);
    fclose(fp);

    free(coef_int16);
    free(data_f);
    free(coef);
}
