//Marcos Cerdán Amat 20518142-A
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

bool error = false;
vector <int>  tabla;

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

int mochilaVoraz(const vector<int> &v, int n, int V){
    
    vector<size_t> idx(v.size());
    vector<int> aux(n);

    for(size_t i = 0; i< idx.size(); i++) idx[i] = i;

    sort (idx.begin(), idx.end(), [&v] (size_t x, size_t y){
        return v[x] > v[y];
    });

    int acc_v = 0;

    for(auto i : idx){

        if(v[i] < V){
            acc_v += v[i];
            V -= v[i];
            if(v[i] != 0){
                aux[i] = v[i];
            }
        }
    }
    tabla = aux;
    return acc_v;
}

int main(int argc, char *argv[]){

    int resultado_selection = 0;
    int num, tam;
    vector<int> componentes;
    string nombre_fichero = leerArgumentos(argc, argv);

    if(!error){
        vector<string> lineas = leerFichero(nombre_fichero);

        if(!error){
            asignarDatos(lineas, num, tam, componentes);

            cout << "Greedy: " << mochilaVoraz(componentes, num, tam) << endl;
            cout << "Selection: ";
            for( unsigned i = 0; i<componentes.size(); i++){
                if(tabla[i] != 0){
                    cout << tabla[i] << " ";
                    resultado_selection += tabla[i];
                }
            }
            cout << endl <<  "Selection value: " << resultado_selection << endl;

        } 
        else fallo();
    }
    else fallo();   
    return 0;
}