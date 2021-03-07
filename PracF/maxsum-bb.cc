//Marcos Cerdán Amat 20518142-A
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <queue>
#include <tuple>
using namespace std;

bool error = false;

int Nodos_Expandidos = 0;
int Nodos_vivos = 0;
int Nodos_No_Factibles = 0;
int Nodos_No_Prometedores = 0;
int Nodos_Casi_Prometedores = 0;
int Nodos_Completados = 0;
int Actualizaciones_Nodo_Completado = 0;
int Actualizaciones_Nodo_No_Completado = 0;



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

int cota_pesimista(const vector<int> v, size_t k, int V){

    int acc_v = 0;
    
    for ( unsigned i = k; i < v.size() ; i++){
        if( v[i] < V ) {
            acc_v += v[i];
            V -= v[i];
        }
    }
    return acc_v;
}

int cota_optimista(const vector<int> &v, size_t k, int V){

    int acc_v = 0.0;

    for( unsigned i = k; i < v.size() ; i++){
        if( v[i] > V ) {
            acc_v += V;
            break;
        }
        acc_v += v[i];
        V -= v[i];
    }
    return acc_v;
}

int knapsack( const vector<int> &v, int V){

    typedef vector <short> Sol;
    typedef tuple <int, int, Sol, unsigned> Node;
    priority_queue <Node> pq;

    int best_val = cota_pesimista(v, 0, V);
    int opt_bound = cota_optimista(v, 0, V);

    pq.emplace( opt_bound, 0, Sol(v.size()), 0);

    while(!pq.empty()){

        unsigned k = 0;
        int value = 0;
        Sol x;
        tie(ignore,value,x,k) = pq.top();
        pq.pop();
        
        if(value == V){ //si el valor actual que tenemos es el óptimo, dejamos de buscar
            continue;
        }

        if(opt_bound <= best_val){ //comprobamos si el valor optimista llega a ser mejor que el valor actual
            Nodos_Casi_Prometedores++;
        }

        if( k == v.size()){
            Nodos_Completados++; 
            
            if(value >= best_val){ //Seleccionamos el mejor resultado posible
                Actualizaciones_Nodo_Completado++;
                best_val = value;
            }
            continue;
        }

        Nodos_Expandidos++;

        for (unsigned j = 0; j<2; j++){ //Expandimos los hijos de un nodo
            x[k] = j;
            int new_value = value + x[k] * v[k]; //Calculamos los valores de los nodos

            if(new_value <= V){ //Tiene que cumplir la restricción de que el nuevo valor no desborde la mochila

                Actualizaciones_Nodo_No_Completado++;

                best_val = max(best_val, new_value + cota_pesimista(v, k+1, V- new_value));
               
                int opt_bound = new_value + cota_optimista(v, k+1, V- new_value); 

                if(opt_bound > best_val){ //Si el valor óptimo es mayor que la cota pesimista
                    Nodos_vivos++;
                    pq.emplace( opt_bound, new_value, x, k+1); //Añadimos el nodo a la cola de prioridad
                }
                else Nodos_No_Prometedores++;
            }
            else Nodos_No_Factibles++;
        }
    }
    return best_val;
}


int main(int argc, char *argv[]){

    int num, tam;
    vector<int> componentes;
    string nombre_fichero = leerArgumentos(argc, argv);

    if(!error){
        vector<string> lineas = leerFichero(nombre_fichero);

        if(!error){

            asignarDatos(lineas, num, tam, componentes);


            auto comienzo = clock();
            cout << knapsack(componentes, tam) << endl;
            auto final = clock();

            cout 
            << Nodos_Expandidos << " "
            << Nodos_vivos << " "
            << Nodos_No_Factibles << " "
            << Nodos_No_Prometedores << " "
            << Nodos_Casi_Prometedores << " "
            << Nodos_Completados << " "
            << Actualizaciones_Nodo_Completado << " "
            << Actualizaciones_Nodo_No_Completado << endl;

            cout << (double) 1000*(final-comienzo)/CLOCKS_PER_SEC << endl;


        } 
        else fallo();
    }
    else fallo();   
    return 0;
}




