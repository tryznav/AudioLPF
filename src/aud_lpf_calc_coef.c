#include "audiolpf.h"

/**
* eth_cmdcnt() : calculation of coefficients for a low pass filter filter by with appropriate parameters.
* 
* @numFirCoef:  Number of FIR filter coefficients
* @Fp1:         The lower cutoff frequency.
* @Fp2:         The upper cutoff frequency.
* Return:       The pointer to the memory in HEAP which stores the band-stop filter coefficients.
*/

double* aud_lpf_calc_coef(int numFirCoef, int fcutL, int sampleRate){
    double *hzB = (double *)malloc(sizeof(double) * numFirCoef);
    int nm = numFirCoef / 2;                                 //номера значений для коэфф фильтра симметричны
    int j= nm;                                              //отсчет от середины фильтра

    for (int i = 0; i < nm; i++) {
        if (i == 0)
        {
            hzB[j] = 2.0 * fcutL / sampleRate;
        }
        else
        {
            hzB[j + i] = (sin(2.0 * M_PI * i * fcutL / sampleRate))  / (M_PI * i);
            hzB[j - i] = hzB[j + i];
        }
    }
    return hzB;
}
