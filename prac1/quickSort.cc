//Marcos Cerdán Amat 20518142-A

/*
ADA 2019-20
Pràctica 1: Empirical analysis of Quicksort average-time complexity.
*/

//--------------------------------------------------------------
// Middle QuickSort

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

void 
middle_QuickSort(int * v, long left, long right){

    long i,j;
    int pivot,aux; 
    if (left<right)
    {
        i=left; j=right;
        pivot=v[(i+j)/2];
        do
        {
            while (v[i]<pivot) i++;
            while (v[j]>pivot) j--;
            if (i<=j)
            {
                aux=v[i]; v[i]=v[j]; v[j]=aux;
                i++; j--;
            }
       } while (i<=j);
       if (left<j)  middle_QuickSort(v,left,j);
       if (i<right) middle_QuickSort(v,i,right);
    }
}

int
main(void){

    double suma = 0.0;
    double tiempos = 0.0;

//    srand(getpid());
    srand(0);

    cout << "# QuickSort CPU times in milliseconds:"
        << endl
        << "# Size \t Average CPU time (ms.)"
        << endl
        << "# -------------------------------"
        << endl;

    for (int exp = 15; exp <= 22; exp++){
        size_t size = size_t( pow(2,exp) );
        int* v = new int [size];
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t\t" << flush;
        for(size_t x = 0; x<30; x++){
            for (size_t j = 0; j < size; j++){
                v[j] = rand();
            }
            auto start = clock();
            middle_QuickSort(v, 0, size-1);
            auto end = clock();
            tiempos = 1000.0 * (end-start) / CLOCKS_PER_SEC;
            suma += tiempos;
        }
        cout << suma/30 << endl;

        for (size_t i = 1; i < size; i++)
            if (v[i] < v[i-1]){ 
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE);            
            }

        delete[] v; 
    }
}

