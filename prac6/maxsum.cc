//Marcos Cerdán Amat 20518142-A
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

bool mostrar_matriz = false;
bool ignore_naive = false;
bool error = false;
const int Sentinel = -1;
vector <vector<int> > tabla;

void fallo(){
    cout << "Usage:" << endl <<"$maxsum [-t] [--ignore_naive] -f file \n";
}

void imprimir_tabla(int n, int V){
    for(int i = 0; i<= n; i++){
        for(int j = 0; j<=V ; j++){
            cout << tabla[i][j] << " ";
        }
        cout << endl;
    }
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
        if(argumento == "-t"){
            mostrar_matriz = true;
        }
        else if(argumento == "--ignore_naive"){
            ignore_naive = true;
        }
        else if(argumento == "-f"){
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

int Naive(const vector<int> v, int n, int V){
    if (n == 0){
        return 0;
    }

    int S1 = Naive(v, n-1, V);

    int S2 = numeric_limits<int>::lowest();

    if(v[n-1] <= V){
        S2 = v[n-1] + Naive(v, n-1, V-v[n-1]);
    }

    return max(S1,S2);
}

int Memoization(vector <vector<int> > &M, const vector<int> &v, int n, int V ){
    if( M[n][V] != Sentinel){
        return M[n][V];
    }
    if(n == 0){
        return M[n][V] = 0;
    }

    int S1 = Memoization(M, v, n-1, V);
    int S2 = numeric_limits<int>::lowest();

    if( v[n-1] <= V){
        S2 = v[n-1] + Memoization(M, v, n-1, V - v[n-1]);
    }

    return M[n][V] = max(S1, S2);
}

int Memoization(const vector <int> &v, int n, int V){
    vector< vector<int> > M(n+1, vector<int>(V+1, Sentinel));
    return Memoization(M, v, n, V);
}

int Iterative_table (const vector<int> &v, int last_n, int last_V){
    vector <vector <int>> M (last_n+1, vector<int> (last_V+1));

    for(int V = 0; V <= last_V; V++) M[0][V] = 0;

    for(int n = 1; n <= last_n; n++){
        for(int V = 1; V<= last_V; V++){
            int S1 = M[n-1][V];
            int S2 = numeric_limits<int>::lowest();

            if(V >=  v[n-1]) S2 = v[n-1] + M[n-1][V-v[n-1]];
            M[n][V] = max(S1, S2);
        }
    }
    tabla = M;
    return M[last_n][last_V];
}

int Iterative_vector (const vector <int> &v, int last_n, int last_V){

    vector<int> v0 (last_V+1);
    vector<int> v1 (last_V+1);

    for(int V = 0; V <= last_V; V++) v0[V] = 0;

    for(int n = 1; n <= last_n; n++){
        for(int V = 1; V <= last_V; V++){
            int S1 = v0[V];
            int S2 = numeric_limits<int>::lowest();

            if(V >= v[n-1]) S2 = v[n-1] + v0[V-v[n-1]];

            v1[V] = max(S1, S2);
        }

        swap(v0,v1);
    }

    return v0[last_V];
}

int Selection_value (const vector <int> &v, int last_n, int last_V, vector< vector<bool> > &trace){

    vector< vector<int> > M(last_n+1, vector<int> (last_V+1));
    trace = vector< vector<bool> >(last_n+1, vector<bool> (last_V+1));

    for(int V = 0; V <= last_V; V++){
        M[0][V] = 0;
        trace[0][V] = false;
    }

    for(int n = 1; n <= last_n; n++) {
        for (int V = 1; V<= last_V; V++){

            int S1 = M[n-1][V];
            int S2 = numeric_limits<int>::lowest();

            if(V >= v[n-1]) S2 = v[n-1] + M[n-1][V-v[n-1]];

            M[n][V] = max(S1,S2);
            trace[n][V] = S2 > S1;
        }
    }
    return M[last_n][last_V];
}

void parse(const vector<int> &v, const vector< vector<bool> > &trace, vector<bool>&sol){
    
    int last_n = trace.size()-1;
    int V = trace[0].size()-1;


    for(int n = last_n; n > 0; n--){
        if( trace[n][V]){
            sol[n-1] = true;
            V -= v[n-1];
        }
        else{
            sol[n-1] = false;
        }
    }   
}

int main(int argc, char *argv[]){

    int resultado_selection;
    int num, tam;
    vector<int> componentes;
    string nombre_fichero = leerArgumentos(argc, argv);

    if(!error){
        vector<string> lineas = leerFichero(nombre_fichero);
        if(!error){
            asignarDatos(lineas, num, tam, componentes);

            if(!ignore_naive){
                cout << "Naive: " << Naive(componentes, num, tam) << endl;
            }
            cout << "Memoization: " << Memoization(componentes, num, tam) << endl;

            cout << "Iterative (table): " << Iterative_table(componentes, num, tam) << endl;

            cout << "Iterative (vector): " << Iterative_vector(componentes, num, tam) << endl;

            vector < vector<bool>> trace;
            vector < bool> sol(tam);

            resultado_selection = Selection_value(componentes,num,tam,trace);

            cout << "Selection: ";
            parse(componentes, trace, sol);

            for(unsigned i = 0; i< sol.size(); i++){
                if( sol[i]){
                    cout << componentes[i] << " ";
                }
            }
            cout << endl;

            cout << "Selection value: " << resultado_selection << endl;

            if(mostrar_matriz){
                cout << "Iterative table: " << endl;
                imprimir_tabla(num, tam);
            }
        }
        else{
            fallo();
        }
    }
    else{
        fallo();
    }    
    return 0;
}