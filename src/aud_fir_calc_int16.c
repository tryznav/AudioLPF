#include "audiolpf.h"

/**
* aud_fir_calc() : Implementation of an algorithm for filtering using FIR filter coefficients by 16-bit int type.
*
* @data:        The filtering data
* @dataLen:     The data buffer length.
* @coef:        FIR filter coefficients.
* @numFirCoef:  Number of coefficients @coef
* Return:       The pointer to the memory in HEAP which stores the filtered signal.
*/

int16_t *aud_fir_calc_int16(int16_t *data, uint32_t dataLen, int16_t *coef, uint32_t numFirCoef){
    int16_t *firHist = (int16_t *)malloc(sizeof(int16_t) * numFirCoef);
    int16_t *fir = (int16_t *)malloc(sizeof(int16_t) * dataLen);
    uint32_t OfsetFirBuff = 0;

    for(uint32_t i = 0; i < dataLen; i++){
        int64_t tmpVal = 0;

        firHist[OfsetFirBuff] = data[i];
        for(int coefIndex = (numFirCoef - 1), OfsetFir = OfsetFirBuff; coefIndex > -1; coefIndex--){
            tmpVal += coef[coefIndex] * firHist[OfsetFir];
            OfsetFir = ((OfsetFir - 1) < 0) ?  (numFirCoef - 1) : OfsetFir - 1;
        }
        fir[i] = tmpVal/INT16_MAX;
        OfsetFirBuff = (OfsetFirBuff == numFirCoef) ? 0 : OfsetFirBuff+1;
    }
    return fir;
}
