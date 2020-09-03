#include "audiolpf.h"

/**
* aud_fir_calc() : Implementation of an algorithm for filtering using FIR filter coefficients by double type.
*
* @data:        The filtering data
* @dataLen:     The data buffer length.
* @coef:        FIR filter coefficients.
* @numFirCoef:  Number of FIR filter coefficients
*
* Return:       The pointer to the memory in HEAP which stores the filtered signal.
*/

double *aud_fir_calc(double *data, uint32_t dataLen, double *coef, uint32_t numFirCoef){
    double *firHist = (double *)malloc(sizeof(double) * numFirCoef);
    double *fir = (double *)malloc(sizeof(double) * dataLen);
    
    for(uint32_t i = 0; i < dataLen; i++){
        uint32_t OfsetFirBuff = 0;
        double tmpVal = 0;

        firHist[OfsetFirBuff] = data[i];
        for(int coefIndex = (numFirCoef - 1), OfsetFir = OfsetFirBuff; coefIndex > -1; coefIndex--){
            tmpVal += coef[coefIndex] * firHist[OfsetFir];
            OfsetFir = ((OfsetFir - 1) < 0) ?  (numFirCoef - 1) : OfsetFir - 1;
        }
        fir[i] = tmpVal;
        OfsetFirBuff = (OfsetFirBuff > numFirCoef) ? 0 : OfsetFirBuff++;
    }
    return firHist;
}
