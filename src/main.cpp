//
//  main.cpp
//  SimpleFFT4G
//
//  Created by Andrew Robertson on 06/03/2015.
//  Copyright (c) 2015 Andrew Robertson. All rights reserved.
//

#include <iostream>

#include "SimpleFFT4G.h"
#include <math.h>


#ifndef NMAX
#define NMAX 8192
#define NMAXSQRT 64
#endif

#define MAX(x,y) ((x) > (y) ? (x) : (y))


/* random number generator, 0 <= RND < 1 */
#define RND(p) ((*(p) = (*(p) * 7141 + 54773) % 259200) * (1.0 / 259200.0))


void putdata(int nini, int nend, float *a)
{
    int j, seed = 0;
    for (j = nini; j <= nend; j++) {
        a[j] = RND(&seed);
        printf("a[%i] : %f\n", j, a[j]);
    }
}

double errorcheck(int nini, int nend, double scale, float *a);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Simple use FFT4G fpr FFT\n";
    
    SimpleFFT4G fft;
    if (true) {
        const int n = 4;
        
        float buffer[n] = {8,4,8,0};
        //2,3,-1,1};//expect {5 + 0j, 3+2j, -3+0j, 3 - 2j}
        
//        float buffer[n] = {1.f, 0.5f, 0.f, 0.1f, .0f, 0.5f, 0.0f, 0.0f};
    
        
        float complexBuffer[2*n];
        for (int i = 0; i < n; i++) {
            complexBuffer[2*i] = buffer[i];
            complexBuffer[2*i+1] = 0.f;
        }
        
        
        
        int isgn = 1;
        
        int ip[n];
        float w[n];
        
        ip[0] = 0;
        
        for (int i = 0; i < n; i++) {
            printf("buffer[%i] %f\n", i, buffer[i]);
        }
        
        fft.realdft(n, isgn, &buffer[0], &ip[0], &w[0]);
        
        
        fft.complexdft(n, isgn, &complexBuffer[0]);
        
        
        if (false) {
            float magnitude[1+n/2];
            
            fft.getMagnitude(n, &buffer[0], &magnitude[0]);
            
            for (int i = 0; i <= n/2; i++) {
                printf("mag[%i] %f\n", i, magnitude[i]);
            }
        
        }
        
    } else {
        
        int n, ip[NMAXSQRT + 2];
        float a[NMAX + 1], w[NMAX * 5 / 4], t[NMAX / 2 + 1], err;
        printf("data length n=? (must be 2^m)\n");
        scanf("%d", &n);
        ip[0] = 0;
        /* check of CDFT
        putdata(0, n - 1, a);
        cdft(n, 1, a, ip, w);
        cdft(n, -1, a, ip, w);
        err = errorcheck(0, n - 1, 2.0 / n, a);
        printf("cdft err= %g \n", err);
        */
        /* check of RDFT */
        putdata(0, n - 1, a);
        fft.realdft(n, 1, a, ip, w);
        fft.realdft(n, -1, a, ip, w);
        err = errorcheck(0, n - 1, 2.0 / n, a);
        printf("rdft err= %g \n", err);
    }
    return 0;
}


double errorcheck(int nini, int nend, double scale, float *a)
{
    int j, seed = 0;
    double err = 0, e;
    for (j = nini; j <= nend; j++) {
        e = RND(&seed) - a[j] * scale;
        err = MAX(err, fabs(e));
    }
    return err;
}
