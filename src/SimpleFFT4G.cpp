//
//  SimpleFFT4G.cpp
//  SimpleFFT4G
//
//  Created by Andrew Robertson on 06/03/2015.
//  Copyright (c) 2015 Andrew Robertson. All rights reserved.
//

#include "SimpleFFT4G.h"

#include "FFT4G.c"

#include <Math.h>



void realMagDFT(int n, int isgn, float *a, int *ip, float *w) {
    
}

void SimpleFFT4G::realdft(int n, int isgn, float *a, int *ip, float *w){
    //printf("w %i\n", ip[0]); all fine
    float real[1+n/2];
    float imag[1+n/2];
    ip[0] = 0;
    printf("SimpleFFT4G: require nyquist length: %i\n", 1+n/2);
    rdft(n, isgn, a, ip, w);
    
    for (int i = 0; i < n; i++)
        printf("realdft a[%i] %f\n", i, a[i]);
    
    
    
    getComplexResult(n, a, &real[0], &imag[0]);
    
    for (int i = 0; i < n; i++)
        printf("buffer_after_processing[%i] %f\n", i, a[i]);
    
    for (int i = 0; i <= n/2; i++)
        printf("real fft[%i]: %.4f + %.4f i\n", i, real[i], imag[i]);
    
    
}

void SimpleFFT4G::getComplexResult(int n, float* a, float* real, float* imag) {
    real[0] = a[0];
    real[n/2] = a[1];
    imag[0] = 0;
    imag[n/2] = 0;
    
    for (int i = 1; i < n/2; i++) {
        real[i] = a[2*i];
        imag[i] = -1*a[(2*i)+1];
    }
}

void SimpleFFT4G::getMagnitude(int n, float* a, float* mag){
    mag[0] = fabs(a[0]);
    mag[n/2] = fabs(a[1]);
    for (int i = 1; i < n/2; i++) {
        mag[i] = sqrt((a[2*i] * a[2*i]) + (a[(2*i)+1]*a[(2*i)+1]));
    }
}



void SimpleFFT4G::complexdft(int n, int isgn, float *a) {
    /*
    <case1>
    ip[0] = 0; // first time only
    cdft(2*n, 1, a, ip, w);
    <case2>
    ip[0] = 0; // first time only
    cdft(2*n, -1, a, ip, w);
    [parameters]
    2*n            :data length (int)
    n >= 1, n = power of 2
    a[0...2*n-1]   :input/output data (float *)
    input data
    a[2*j] = Re(x[j]),
    a[2*j+1] = Im(x[j]), 0<=j<n
    output data
    a[2*k] = Re(X[k]),
    a[2*k+1] = Im(X[k]), 0<=k<n
    */
    
    float *w;// = (float *)malloc(n+2, sizeof(float));//calloc zeros out memory
    int *ip;// = (int *)malloc(n+2, sizeof(int));
    
    
    
    w = new float[n+2];
    ip = new int[n+2];
    ip[0] = 0;
    cdft(2*n, isgn, a, ip, w);//nb the 2*n in the call here
    
    //for (int i = 0; i < 2*n; i++)
    //    printf("cdft a[%i] %f\n", i, a[i]);
    
    float real[n/2];
    float imag[n/2];
    
    for (int i = 0; i < n; i++) {
        real[i] = a[(2*i)+n];
        imag[i] = a[(2*i)+n+1];
    }
    
    for (int i = 0; i < n/2; i++)
        printf("complex_fft[%i]: %f + %fj\n", i, real[i], imag[i]);
    
    printf("nyquist is %f\n", a[0]);
}

void SimpleFFT4G::inverseComplexDFT(int n, float *a) {
    /*
     Inverse of
     ddct(n, -1, a, ip, w);
     is
     a[0] *= 0.5;
     ddct(n, 1, a, ip, w);
     for (j = 0; j <= n - 1; j++) {
     a[j] *= 2.0 / n;
    */
    float *w;
    int *ip;
    w = new float[n+2];
    ip = new int[n+2];
    cdft(2*n, 1, a, ip, w);
    for (int j = 0; j <= 2 * n - 1; j++) {
        a[j] *= 1.0 / n;
    }
    
    float real[n/2];
    float imag[n/2];
    
    for (int i = 0; i < n; i++) {
        real[i] = a[(2*i)+n];
        imag[i] = a[(2*i)+n+1];
    }
    
    for (int i = 0; i < n; i++)
        printf("inv_complex_fft[%i]: %f + %fj\n", i, real[i], imag[i]);
    
}
