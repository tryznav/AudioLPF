#include "audiolpf.h"

/**
* aud_fir_coef_float2int16() : convert from fir coefficients from double to   
*
* @bufflen:     The coefficient buffer length.
* @coef:        The pointer to the coefficient buffer to convert.
*
* Return:       The pointer to coefficient buffer after conversion with signed 16 bit int type.
*/

int16_t *aud_fir_coef_float2int16(int inbufflen, double *coef){
    int16_t *coef_int16 = (int16_t *)malloc(sizeof(int16_t) * inbufflen);
    
    for(int i = 0; i < inbufflen; i++){
        coef_int16[i] = INT16_MAX * coef[i];
    }
    return coef_int16;
}
