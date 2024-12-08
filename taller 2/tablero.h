#pragma once
#define TABLERO_H

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();
const int NEG_INF = numeric_limits<int>::min();

class Tablero {
private:
    vector<vector<char>> tablero;

public:
    Tablero();

    void imprimir() const;

    bool estaLleno() const;

    int evaluar() const;

    bool esEstadoTerminal() const;

    void colocar(int fila, int columna, char jugador);

    void deshacer(int fila, int columna);

    vector<pair<int, int>> movimientosDisponibles() const;
};
