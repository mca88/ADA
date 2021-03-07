//Marcos Cerdán Amat 20518142-A
#include <iostream>
#include <math.h>
using namespace std;

unsigned long pasos1;
unsigned long pasos2;
unsigned long pasos3;

//n
unsigned long pow2_1(unsigned n){
    pasos1++;
    long x = 2;
    for(unsigned i = 1; i<n ;i++) {
        pasos1++;
        x *= 2;
    }
    return x;
}

//2^n
unsigned long pow2_2(unsigned n){
    pasos2++;

    unsigned long x;
    if(n != 0){ 
        if(n%2 == 0){
            x = pow2_2(n/2) * pow2_2(n/2);
       }
       else{
            x = 2 * pow2_2(n/2) * pow2_2(n/2);
       }
    }
    else{ //caso base
        x=1;
    }
    return x;
}

//log(n)
unsigned long pow2_3(unsigned n){
    pasos3++;
    unsigned long x;
    unsigned long y;


    if(n != 0){
        if (n>0){
            if(n%2 == 0){
                x = pow2_3(n/2);
                y = pow(x,2);
            }
            else{
                x = pow2_3(n/2);
                y = 2* pow(x,2);
            }
        }
    }

    else{ //caso base
        y=1;
    }
    return y;
}


int main(){
   cout 
    << "          Análisis complejidad          " << endl
    << "----------------------------------------" << endl
    << "n \tø(n)\tø(2^n)\tø(log(n))" << endl;
    for(int i = 1 ; i<=100 ; i++){
        cout << i << "\t ";

        pow2_1(i);
        cout << pasos1 << "\t";
        pasos1 = 0;

        pow2_2(i);
        cout << pasos2 << "\t";
        pasos2 = 0;

        pow2_3(i);
        cout << pasos3 << "\t" << endl;
        pasos3 = 0;
    }
    return 0;
}