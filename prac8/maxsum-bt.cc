//Marcos Cerdán Amat 20518142-A
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <chrono>
using namespace std;

bool error = false;
vector <unsigned>  tabla;

int Nodos_E, Nodos_D = 0;



void fallo(){
    cout << "Usage:" << endl <<"$maxsum [-t] [--ignore_naive] -f file \n";
}

string leerArgumentos(int argc, char *argv[]){
    string nombre_fichero;
    string argumento = "";

    if (argc < 2){
        error = true;
        cout << "Error, necesitas mínimo 2 argumentos" << endl;
    }
    for(int i = 1; i < argc ; i++){
        
        argumento = argv[i];

        if(argumento == "-f"){
            if(i+1 < argc){
                nombre_fichero = argv[i+1];
                i++;
            }
        }
        else{
            error = true;
            cout << "ERROR: unknown option " << argumento << ". \n";  
        }
    }
    return nombre_fichero;
}

vector<string> leerFichero(string nombre){
    string linea;
    vector<string> lineas;

    ifstream fichero(nombre.c_str());

    if(!fichero.is_open()){
        error = true;
        cout << "ERROR: can’t open file: " << nombre << ". \n";
    }
    else{
        getline(fichero,linea);
        lineas.push_back(linea);
            
        getline(fichero,linea);
        lineas.push_back(linea);
    
    }
    return lineas;
}

int add_rest( const vector<int> &v, size_t k ){
    int r = 0;
    for( size_t i = k; i < v.size(); i++) r += v[i];
    return r;
}

void knapsack(const vector<int> &v, int V, size_t k, vector<unsigned> &x, int acc_v, int &best_v){
    if( k == x.size() || best_v >= V) {
        best_v = max(best_v,acc_v);

        if(k == x.size()){
            tabla = x;
        }
        return;
    }
    
    for (unsigned j = 0; j < 2; j++ ) {
        x[k]=j;
        int present_v = acc_v + x[k] * v[k];

        if( present_v <= V && present_v + add_rest(v, k+1) > best_v){
            Nodos_E++;
            knapsack(v, V, k+1, x, present_v, best_v);
            
        }
        else{
            Nodos_D++;
        }
    }
}

int knapsack( const vector<int> &v, int V ){

    vector<unsigned> x(v.size());
    
    int best_v = -1.0;
    knapsack( v, V, 0, x, 0, best_v );
    return best_v;
}

void asignarDatos (vector<string> lineas, int &num, int &tam, vector<int> &componentes){
    
    string token;
    stringstream ss1 (lineas[0]);
    stringstream ss2 (lineas[1]);

    int i = 0;
    while (ss1 >> token){
        if(i == 0){
            num = stoi(token);
            i++;
        }
        if(i == 1){
            tam = stoi(token);
        }
    }
    while (ss2 >> token){
        componentes.push_back(stoi(token));
    }
}

int main(int argc, char *argv[]){

    int num, tam;
    vector<int> componentes;
    string nombre_fichero = leerArgumentos(argc, argv);

    if(!error){
        vector<string> lineas = leerFichero(nombre_fichero);

        if(!error){
            cout << "Backtracking: ";
            asignarDatos(lineas, num, tam, componentes);

            vector<int> aux (componentes.size());

            for(size_t i = 0; i< aux.size(); i++){
                aux[i] = componentes[i];
            }

            sort(aux.begin(), aux.end());

            auto start = clock();
            cout << knapsack(aux,tam) << endl;
            auto end = clock();
            cout << "Selection: ";
            for( unsigned i = 0; i < aux.size(); i++){
                if(tabla[i] == 1){
                    cout << aux[i] << " ";
                }
            }
            cout << endl;
            cout << "Expanded nodes: " << Nodos_E << endl;
            cout << "Discarded nodes: " << Nodos_D << endl;
            double time = (double(end-start)*1000/CLOCKS_PER_SEC);
            cout << "CPU time (ms): " << time << endl;
        } 
        else fallo();
    }
    else fallo();   
    return 0;
}