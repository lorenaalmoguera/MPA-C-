#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <climits>

using namespace std;

// codigo realizado por:
// Lorena Almoguera Romero
// Maria Isabel Salinas Perez

int minimo(int a, int b) {
    return (a < b) ? a : b;
}

int elegir_vertice_coste_min(int *vCiudades, int* S, int n) {
    int eleccion = -1;
    int auxiliar = INT_MAX;

    for (int i = 1; i <= n; i++) {
        if (vCiudades[i] != 0 && S[i] < auxiliar) {
            auxiliar = S[i];
            eleccion = i;
        }
    }
    return eleccion;
}

void dijkstra(int n, int *vCiudades, int **matriz, int* S, int ciudad_inicial) {
    for(int i = 1; i <= n; i++) {
        vCiudades[i] = 1; 
    }

    for(int i = 1; i <= n; i++) {
        if (i == ciudad_inicial) {
            S[i] = 0; 
        } else if (matriz[ciudad_inicial][i] != 0) {
            S[i] = matriz[ciudad_inicial][i];
        } else {
            S[i] = INT_MAX; 
        }
    }

    for(int i = 1; i < n; i++) {
        int x = elegir_vertice_coste_min(vCiudades, S, n);
        if(x == -1) break; 
        vCiudades[x] = 0; 
        for(int j = 1; j <= n; j++) {
            if(vCiudades[j] != 0 && matriz[x][j] != 0 && S[x] != INT_MAX) {
                S[j] = minimo(S[j], S[x] + matriz[x][j]);
            }
        }
    }
}
void imprimirRuta(int *ruta, int destino, string* sCiudades) {
    if (ruta[destino] == 0) {
        cout << sCiudades[destino];
        return;
    }
    imprimirRuta(ruta, ruta[destino], sCiudades);
    cout << " -> " << sCiudades[destino];
}

void dijkstra_v2(int n, int* vCiudades, int **matriz, int *S, int origen, string* sCiudades){
    int i,j,x;
    int* ruta = new int[n];
    for(i = 1 ; i <= n ; i++){
        ruta[i] = 0;
    }
    i=j=x=0;

    for(int i = 1; i <= n; i++) {
        vCiudades[i] = 1; // Reiniciamos ciudades a no visitadas
    }

    int* P = new int[n+1];
    for(i = 1; i <= n; i++){
        if (i == origen) {
            S[i] = 0; // dist ciudad inicial = 0
        } else if (matriz[origen][i] != 0) {
            S[i] = matriz[origen][i]; // si hay una conex dir, usar ese costo
        } else {
            S[i] = INT_MAX; // si no hay conex dir, establecer inf
        }
    }

    for(int i = 1; i < n; i++) {
        int x = elegir_vertice_coste_min(vCiudades, S, n);
        if(x == -1) break;
        vCiudades[x] = 0;
        for(int j = 1; j <= n; j++) {
            if(vCiudades[j] != 0 && matriz[x][j] != 0 && S[x] != INT_MAX) {
                S[j] = minimo(S[j], S[x] + matriz[x][j]);
                if(S[j] == S[x] + matriz[x][j]){
                    ruta[j] = x;
                }
            }
        }
    } 

    cout << "Destino\tPrecio\tRuta" << endl;
    cout << "-------\t------\t-----" << endl;
    for (int i = 1; i <= n; i++) {
        if(i != origen){
            cout << sCiudades[i] << "\t" << S[i] << "\t";
            imprimirRuta(ruta, i, sCiudades);
            cout << endl;
        }
    }
    cout << endl <<endl;

    delete[] P; // liberar memoria
}

int main() {
    bool func_prog = false;
    int n, ciudad_origen, seleccion_int, i, j;
    string seleccion, nombrearchivo;

    cout << "Por favor, introduce el fichero con las ciudades y los vuelos" << endl;
    cin >> nombrearchivo;
    ifstream archivo(nombrearchivo);
    if (!archivo) {
        cout << "Ese fichero no existe" << endl;
        return -1;
    }

    archivo >> n;
    string* vCiudades = new string[n+1];
    int* iCiudades = new int[n+1];

    for(int i = 1; i <= n; i++) {
        archivo >> vCiudades[i];
    }

    int** matriz = new int*[n+1];
    for(int i = 1; i <= n; i++) {
        matriz[i] = new int[n+1];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            archivo >> matriz[i][j];
        }
    }

    int* S = new int[n+1];
    archivo.close();

    while(!func_prog) {
        cout << "Por favor, elige una de las siguientes opciones: " << endl 
             << "Opcion 1: Vuelos" << endl 
             << "Opcion 2: Precios vuelos más baratos" << endl 
             << "Opcion 3: Precios y rutas de los vuelos más baratos" << endl 
             << "Opcion 4: Salir." << endl;

        do {
            cout << "Solo se permiten números positivos: ";
            cin >> seleccion;
        } while (!regex_match(seleccion, regex("^[0-9]*[1-9][0-9]*$")));

        seleccion_int = atoi(seleccion.c_str());

        switch(seleccion_int) {
            case 1:
                cout << "**** Opcion seleccionada 1: Vuelos ****" << endl << endl;
                cout << "Destinos disponibles: " << n << endl;
                cout << "Ciudades disponibles: " << endl;

                for(i = 1 ; i <= n ; i++){
                    cout << vCiudades[i] << "   ";
                }
                cout << endl;

                cout << "Precios de los vuelos " << endl;
                cout << endl;

                cout << "\t";
                for(i = 1 ; i <= n ; i++){
                    cout << vCiudades[i] << "    ";
                }
                cout << endl;
                for (i = 1; i <= n; i++) {
                    cout << vCiudades[i]  << "\t";
                    for (j = 1; j <= n; j++) {
                        cout << matriz[i][j] << "\t";
                    }
                    cout << endl;
                }
                break;
            case 2:
                cout << "**** Opcion seleccionada 2: Precios vuelos mas baratos ****" << endl << endl;
                cout << "Por favor, indique la ciudad inicial (1-" << n << "): " << endl;
                cin >> ciudad_origen;

                if (ciudad_origen < 1 || ciudad_origen > n) {
                    cout << "Ciudad origen inválida. Intente nuevamente." << endl;
                    continue;
                }

                dijkstra(n, iCiudades, matriz, S, ciudad_origen);
                for(i = 1 ; i <= n ; i++){
                    if(i != ciudad_origen){
                        cout << vCiudades[i] << " - - - - - - - - - - - " << S[i] << endl;
                    }
                }
                break;
            case 3:
                cout << "**** Opcion seleccionada 3: Precios y rutas de los vuelos mas baratos ****" << endl << endl;
                cout << "Por favor, indique la ciudad inicial (1-" << n << "): " << endl;
                cin >> ciudad_origen;

                if (ciudad_origen < 1 || ciudad_origen > n) {
                    cout << "Ciudad origen inválida. Intente nuevamente." << endl;
                    continue;
                }

                dijkstra_v2(n, iCiudades, matriz, S, ciudad_origen, vCiudades);
                break;
            case 4:
                cout << "Saliendo del programa" << endl << endl;
                func_prog = true;
                break;
            default:
                cout << "**** OPCION NO VALIDA ****" << endl << endl;
                break;
        }
    }

    //liberar memoria
    delete[] S;
    delete[] iCiudades;
    for(int i = 1; i <= n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete[] vCiudades;

    return 0;
}
