#include "Tablero.h"

Tablero::Tablero() : tablero(3, vector<char>(3, '_')) {}

void Tablero::imprimir() const {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            if (celda == '_') {
                cout << ". ";  
            } else {
                cout << celda << " ";  
            }
        }
        cout << endl;  
    }
    cout << endl;  

}



bool Tablero::estaLleno() const {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            if (celda == '_') {
                return false;  
            }
        }
    }
    return true;  
}


int Tablero::evaluar() const {
    // Verificar filas
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != '_') {
            return tablero[i][0] == 'X' ? 10 : -10;
        }
    }

    // Verificar columnas
    for (int j = 0; j < 3; ++j) {
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j] && tablero[0][j] != '_') {
            return tablero[0][j] == 'X' ? 10 : -10;
        }
    }

    // Verificar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != '_') {
        return tablero[0][0] == 'X' ? 10 : -10;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != '_') {
        return tablero[0][2] == 'X' ? 10 : -10;
    }

    return 0;
}

bool Tablero::esEstadoTerminal() const {
    return evaluar() != 0 || estaLleno();
}

void Tablero::colocar(int fila, int columna, char jugador) {
    while (true) {
        if (tablero[fila][columna] == '_') {
            tablero[fila][columna] = jugador;
            break;  
        } else {
            cout << "La celda (" << fila << ", " << columna << ") esta ocupada. Ingrese otros datos." << endl;
            cout << "Ingresa tu movimiento (fila y columna, de 0 a 2): " << endl;
            cin >> fila >> columna;
        }
    }
}

void Tablero::deshacer(int fila, int columna) {
    tablero[fila][columna] = '_';
}

vector<pair<int, int>> Tablero::movimientosDisponibles() const {
    vector<pair<int, int>> movimientos;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] == '_') {
                movimientos.emplace_back(i, j);
            }
        }
    }
    return movimientos;
}