#ifndef AUDIO_LPF_H_
#define AUDIO_LPF_H_

#define PROJECT_NAME	"AudioLPF"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <stdbool.h>
#include <malloc/malloc.h>
#include <math.h>

#define DEBUG_MODULE

#define NUM_OF_FIR_COEF 511

#define LOW_PASS_FILTER

#define CUT_FREQ        200
#define CUT_FREQ1       2800
#define CUT_FREQ2       3100


// Структура, описывающая заголовок WAV файла.
typedef struct WAVHEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    char chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    int32_t chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    char format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:
    
    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    char subchunk1Id[4];

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    uint32_t subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    uint16_t audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    uint16_t numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    int32_t sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    uint32_t byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    uint16_t blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    uint16_t bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    // char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    // uint32_t subchunk2Size;
    // char subchunk3Id[4];
    // char subchunk4Id[4];

    // Далее следуют непосредственно Wav данные.
}wavhdr_t;

typedef struct DataChunk_s
{
    char        chunkId[4];
    int32_t     chunkSize;
}DataChunk_t;

void    aud_print_wav_hdr(wavhdr_t *hdr);
double  *aud_fir_calc(double *data, uint32_t numData, double *coef, uint32_t numFirCoef);
double  *aud_lpf_calc_coef(int inbufflen, int fcutL, int fdiskret);
double  *aud_bsf_calc_coef(int inbufflen, int Fp1, int Fp2, int fdiskret);
int16_t *aud_fir_coef_float2int16(int inbufflen, double *coef);
int16_t *aud_fir_calc_int16(int16_t *data, uint32_t numData, int16_t *coef, uint32_t numFirCoef);

#endif
