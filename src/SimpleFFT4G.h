//
//  SimpleFFT4G.h
//  SimpleFFT4G
//
//  Created by Andrew Robertson on 06/03/2015.
//  Copyright (c) 2015 Andrew Robertson. All rights reserved.
//

#ifndef __SimpleFFT4G__SimpleFFT4G__
#define __SimpleFFT4G__SimpleFFT4G__

#include <stdio.h>


class SimpleFFT4G{
public:
    SimpleFFT4G(){
    }
    
    int fftSize;
    //int* ip;
   //float* w;
    
    
    void realdft(int n, int isgn, float *a, int *ip, float *w);
    /**
     * a[0...n-1]     :input/output data (float *)
     * <case1>
     * output data
     * a[2*k] = R[k], 0<=k<n/2
     * a[2*k+1] = I[k], 0<k<n/2
     * a[1] = R[n/2]
    */
    
    void getComplexResult(int n, float* a, float* real, float* imag);
    
    void getMagnitude(int n, float* a, float* mag);
    
    void complexdft(int n, int isgn, float *a);
    
    void inverseComplexDFT(int n, float *a);
};

#endif /* defined(__SimpleFFT4G__SimpleFFT4G__) */
