#include "audiolpf.h"

/**
* eth_cmdcnt() : calculation of coefficients for a band stop filter filter by with appropriate parameters.
* 
* @numFirCoef:  Number of FIR filter coefficients
* @Fp1:         The lower cutoff frequency.
* @Fp2:         The upper cutoff frequency.
* Return:       The pointer to the memory in HEAP which stores the band-stop filter coefficients.
*/

double* aud_bsf_calc_coef(int numFirCoef, int Fp1, int Fp2, int sampleRate){
    double *hzB = (double *)malloc(sizeof(double) * numFirCoef);
    int nm = numFirCoef / 2;
    int j= nm;

    for (int i = 0; i < nm; i++) {
        if (i == 0)
        {
            hzB[j] = 1 - 2.0 * (Fp2-Fp1)/sampleRate;
        }
        else
        {
            hzB[j + i] = (sin(2.0 * Fp1 * M_PI * i / sampleRate) - sin(2.0 * Fp2 * M_PI * i / sampleRate)) / (M_PI * i);
            hzB[j - i] = hzB[j + i];
        }
    }
    return hzB;
}
