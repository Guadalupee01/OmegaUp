#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int N, M_Caballos,ColorActual,Color ;

// Poner el caballo en la casilla. Esto es para comprobar el color y verificar si se puede resolver el problema
void PosicionCaballos(int CantidadCaballos, vector<pair<int, int>>& NPosicionCaballos) {
    int x, y;
    for(int i = 0; i < CantidadCaballos; i++) {
        cin >> x >> y;
        // -1 es por que estamos iniciando desde 0 pero el usuario empiesa a contar desde el 1
        NPosicionCaballos[i].first = x - 1;
        NPosicionCaballos[i].second = y - 1;
    }
}

// Actualiza el tablero principal que indica el menor número de movimientos de los caballos
// Este se actualiza con el máximo del tablero donde el caballo [i] está haciendo el recorrido
void ActualisacionTableroDeTodosLosCaballos(int tamano, vector<vector<int>>& tableroGeneral, vector<vector<int>>& tableroCaballoActual) {
    for(int y = 0; y < tamano; y++) {
        for(int x = 0; x < tamano; x++) {
            if (tableroGeneral[y][x] == -1 || tableroCaballoActual[y][x] == -1) {
                tableroGeneral[y][x] = -1;
            } else {
                tableroGeneral[y][x] = max(tableroGeneral[y][x], tableroCaballoActual[y][x]);
            }        }
    }
}

//retorna el valor minimo del tablero final (donde estan los minimos moviimientos de todos los caballos juntos )
int RetornoDevalorMinimo(int tamano, vector<vector<int>>& tablero) {
    int minimo = 999999;
    bool existeSolucion = false; 
    for(int y = 0; y < tamano; y++) {
        for(int x = 0; x < tamano; x++) {
            if(tablero[y][x] != -1) { 
                if(tablero[y][x] < minimo) {
                    minimo = tablero[y][x];
                    existeSolucion = true;
                }
            }
        }
    }
    return existeSolucion ? minimo : -1;
}

void RecursividadCaballos(int contador, int tamanoTablero, int iCaballo, vector<pair<int, int>>& NPosicionCaballos, vector<vector<int>>& tableroCaballo) {
   // X y Y estan manejados como Coordenadas cartesianas
    int x = NPosicionCaballos[iCaballo].first; 
    int y = NPosicionCaballos[iCaballo].second; 

    //Verifica que no se salga de los limites 
    if (x < 0 || x >= tamanoTablero || y < 0 || y >= tamanoTablero) return;

    // MEMO (si ya llegamos y es mayor o igual no seguir calculando)
    if (tableroCaballo[y][x] != -1 && contador >= tableroCaballo[y][x]) return;

    tableroCaballo[y][x] = contador;

    int areglo_movimientos_x[] = {1, -1, -1, 1, -2, 2, -2, 2}; // Movimientos del caballo. Para no manejarlos en muchos if distintos, estos movimientos se pueden ver en la captura de pantalla (Movimiientos Caballoo.png)
    int areglo_movimientos_y[] = {2, 2, -2, -2, -1, -1, 1, 1}; // Movimientos del caballo. Para no manejarlos en muchos if distintos, estos movimientos se pueden ver en la captura de pantalla (Movimiientos Caballoo.png)

    
    for (int i = 0; i < 8; i++) {
        int posicon_actual_x = x + areglo_movimientos_x[i];
        int posicon_actual_y = y + areglo_movimientos_y[i];

        //Validacion de movimientos
        if (posicon_actual_x >= 0 && posicon_actual_x < tamanoTablero && posicon_actual_y >= 0 && posicon_actual_y < tamanoTablero) {
            NPosicionCaballos[iCaballo].first = posicon_actual_x;
            NPosicionCaballos[iCaballo].second = posicon_actual_y;
            
            RecursividadCaballos(contador + 1, tamanoTablero, iCaballo, NPosicionCaballos, tableroCaballo);
        //Posicion Sin movimiento, retrocedemos un movimieto para checar mas movientos
            NPosicionCaballos[iCaballo].first = x;
            NPosicionCaballos[iCaballo].second = y;
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M_Caballos;

    //Vector donde se encuentran las posiciones de los caballos 
        vector<pair<int, int>> NPosicionCaballos(M_Caballos);
        PosicionCaballos(M_Caballos, NPosicionCaballos);
    //Tablero que contendra los movimientos minimos para llegar a todas las casillas de todos los caballos 
        vector<vector<int>> tableroGeneral(N, vector<int>(N, -1));

    //Checar que exista solucion (es para checar que todos los caballos esten en el mismo color)
         Color = (NPosicionCaballos[0].first + NPosicionCaballos[0].second)%2;
        for (int i = 1; i < M_Caballos; i++) {
             ColorActual = (NPosicionCaballos[i].first + NPosicionCaballos[i].second)%2;
            
            if (ColorActual != Color) {
                cout << -1 ;
                return 0;
            }
        }
    
    // Primer caballo 
    RecursividadCaballos(0, N, 0, NPosicionCaballos, tableroGeneral);

    for(int i = 1; i < M_Caballos; i++) {
        vector<vector<int>> tableroCaballoActual(N, vector<int>(N, -1));
        RecursividadCaballos(0, N, i, NPosicionCaballos, tableroCaballoActual);
        // Actualisamos el tablero para que tenga la mayor cantidad de movimientos que tarda en llegar todos los caballos a esa casilla 
        ActualisacionTableroDeTodosLosCaballos(N, tableroGeneral, tableroCaballoActual);
    }

    cout << RetornoDevalorMinimo(N, tableroGeneral); 

    return 0;
}