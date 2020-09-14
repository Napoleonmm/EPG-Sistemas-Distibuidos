/*
 ============================================================================
 Name        : Trabajo002_openMP_EPSILON.c
 Author      : Napoleon
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"

int main(void) {



    int n=10;
    double factorial[n];
    factorial[1] = 1;
    double ValEpsilon = 0;
    double ValorEpsilon =0;
    double EPSILON = 2.718281828459045235360;
    double ErrorEpsilon;


    #pragma omp parallel
    {
        int ithread = omp_get_thread_num();
        int  nthreads = omp_get_num_threads();

        double prod = 1;

        #pragma omp for schedule(static,8) nowait
        for (int i=1; i<=n; i++) {
            prod *= i;

            factorial[i] = 1/prod;

            ValEpsilon += 1/prod;
            //
        }


    }

    ValorEpsilon = ValEpsilon +1;
    ErrorEpsilon = EPSILON-ValorEpsilon;

    for(int i=1; i<=n; i++){printf("%.20f\n", factorial[i]); }

    printf("El valor aproximado de Epsilon es: ");
    printf("%.20f", ValorEpsilon);
    printf(" con un error de:");
    printf("%.20f\n",ErrorEpsilon);putchar('\n');
}


