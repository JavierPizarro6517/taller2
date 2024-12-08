#include "Tablero.h"

// Función para obtener las coordenadas del jugador
pair<int, int> obtenerMovimientoJugador(const Tablero& tablero) {
    int fila, columna;
    while (true) {
        cout << "Ingresa tu movimiento (fila y columna, de 0 a 2): ";
        cin >> fila >> columna;

        // Verificar si la posición es válida
        if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero.movimientosDisponibles().end() !=
            find(tablero.movimientosDisponibles().begin(), tablero.movimientosDisponibles().end(), make_pair(fila, columna))) {
            return {fila, columna};
        } else {
            cout << "Movimiento invalido. Intenta de nuevo." << endl;
        }
    }
}

// Función de Minimax (IA)
int minimax(Tablero& tablero, int profundidad, bool esMaximizador) {
    int puntaje = tablero.evaluar();

    // Si el juego ha terminado, retornar el puntaje
    if (puntaje != 0 || tablero.esEstadoTerminal()) {
        return puntaje;
    }

    if (esMaximizador) {
        int mejorPuntaje = NEG_INF;
        for (const auto& movimiento : tablero.movimientosDisponibles()) {
            tablero.colocar(movimiento.first, movimiento.second, 'X');
            mejorPuntaje = max(mejorPuntaje, minimax(tablero, profundidad + 1, false));
            tablero.deshacer(movimiento.first, movimiento.second);
        }
        return mejorPuntaje;
    } else {
        int mejorPuntaje = INF;
        for (const auto& movimiento : tablero.movimientosDisponibles()) {
            tablero.colocar(movimiento.first, movimiento.second, 'O');
            mejorPuntaje = min(mejorPuntaje, minimax(tablero, profundidad + 1, true));
            tablero.deshacer(movimiento.first, movimiento.second);
        }
        return mejorPuntaje;
    }
}

int minimaxConPoda(Tablero& tablero, bool esMaximizador, int alfa, int beta) {
    int puntaje = tablero.evaluar();

    // Si el juego ha terminado, retornar el puntaje
    if (puntaje != 0 || tablero.esEstadoTerminal()) {
        return puntaje;
    }

    if (esMaximizador) {
        int mejorPuntaje = NEG_INF;
        for (const auto& movimiento : tablero.movimientosDisponibles()) {
            tablero.colocar(movimiento.first, movimiento.second, 'X');
            mejorPuntaje = max(mejorPuntaje, minimaxConPoda(tablero, false, alfa, beta));
            tablero.deshacer(movimiento.first, movimiento.second);
            alfa = max(alfa, mejorPuntaje);
            if (beta <= alfa) {
                break;  // Poda beta
            }
        }
        return mejorPuntaje;
    } else {
        int mejorPuntaje = INF;
        for (const auto& movimiento : tablero.movimientosDisponibles()) {
            tablero.colocar(movimiento.first, movimiento.second, 'O');
            mejorPuntaje = min(mejorPuntaje, minimaxConPoda(tablero, true, alfa, beta));
            tablero.deshacer(movimiento.first, movimiento.second);
            beta = min(beta, mejorPuntaje);
            if (beta <= alfa) {
                break;  // Poda alfa
            }
        }
        return mejorPuntaje;
    }
}

// Función para calcular el mejor movimiento de la IA
pair<int, int> mejorMovimiento(Tablero& tablero) {
    int mejorPuntaje = NEG_INF;
    pair<int, int> movimiento = {-1, -1};

    for (const auto& pos : tablero.movimientosDisponibles()) {
        tablero.colocar(pos.first, pos.second, 'X');
        int puntaje = minimax(tablero, 0, false);
        tablero.deshacer(pos.first, pos.second);

        if (puntaje > mejorPuntaje) {
            mejorPuntaje = puntaje;
            movimiento = pos;
        }
    }

    return movimiento;
}

// Función para calcular el mejor movimiento de la IA con PODA
pair<int, int> mejorMovimientoConPoda(Tablero& tablero) {
    int mejorPuntaje = NEG_INF;
    pair<int, int> movimiento = {-1, -1};

    for (const auto& pos : tablero.movimientosDisponibles()) {
        tablero.colocar(pos.first, pos.second, 'X');
        int puntaje = minimaxConPoda(tablero, NEG_INF, INF, false);
        tablero.deshacer(pos.first, pos.second);

        if (puntaje > mejorPuntaje) {
            mejorPuntaje = puntaje;
            movimiento = pos;
        }
    }

    return movimiento;
}

int main() {
    Tablero tablero;
    char turno = 'O'; // 'O' para jugador, 'X' para IA

    cout << "¡Bienvenido al juego de Tic-Tac-Toe!" << endl;
    cout << "Las reglas son: No puedes ocupar una celda que ya está ocupada y el primero en lograr tener una linea de 3 celdas ocupada con su figura gana." << endl;
    cout << "" << endl;
    cout << "1.- Partida P1 vs P2" << endl;
    cout << "2.- Partida P1 vs IA" << endl;
    cout << "3.- Partida P1 vs IA con PODA" << endl;

    int opcion;
    cout << "Selecciona una opción (1 o 2): ";
    cin >> opcion;

    // Validación de entrada
    while (opcion != 1 && opcion != 2 && opcion != 3) {
        cout << "Opción inválida, ingresar nuevamente: ";
        cin >> opcion;}

    if (opcion == 1){
        while (!tablero.esEstadoTerminal()) {
        cout << "Estado actual del tablero:" << endl;
        cout << "" << endl;
        tablero.imprimir();

        if (turno == 'O') {
            // Turno del P1
            cout << "Tu turno (O):" << endl;
            auto movimientoJugador = obtenerMovimientoJugador(tablero);
            tablero.colocar(movimientoJugador.first, movimientoJugador.second, 'O');
            turno = 'X';
        } else {
            // Turno del P2
            cout << "Tu turno (O):" << endl;
            auto movimientoJugador = obtenerMovimientoJugador(tablero);
            tablero.colocar(movimientoJugador.first, movimientoJugador.second, 'X');
            turno = 'O';
        }
        }

        cout << "Estado final del tablero:" << endl;
        tablero.imprimir();

        int resultado = tablero.evaluar();
        if (resultado == 10) {
            cout << "El P2 gana. Felicidades!" << endl;
        } else if (resultado == -10) {
            cout << "El P1 gana Felicidades!." << endl;
        } else {
            cout << "Es un empate." << endl;
        }

    }

    if (opcion == 2){
        while (!tablero.esEstadoTerminal()) {
        cout << "Estado actual del tablero:" << endl;
        cout << "" << endl;
        tablero.imprimir();

        if (turno == 'O') {
            // Turno del jugador
            cout << "Tu turno (O):" << endl;
            auto movimientoJugador = obtenerMovimientoJugador(tablero);
            tablero.colocar(movimientoJugador.first, movimientoJugador.second, 'O');
            turno = 'X';
        } else {
            // Turno de la IA
            cout << "Turno de la IA (X):" << endl;
            auto movimientoIA = mejorMovimiento(tablero);
            tablero.colocar(movimientoIA.first, movimientoIA.second, 'X');
            cout << "La IA jugo en: (" << movimientoIA.first << ", " << movimientoIA.second << ")" << endl;
            turno = 'O';
        }
     }

        cout << "Estado final del tablero:" << endl;
        tablero.imprimir();

        int resultado = tablero.evaluar();
        if (resultado == 10) {
            cout << "La IA (X) gana. ¡Mejor suerte la proxima vez!" << endl;
        } else if (resultado == -10) {
            cout << "Felicidades! Ganaste." << endl;
        } else {
            cout << "Es un empate." << endl;
        }

    }

    if (opcion == 3){ // Por alguna razón la IA juega muy mal con la poda
        while (!tablero.esEstadoTerminal()) {
        cout << "Estado actual del tablero:" << endl;
        cout << "" << endl;
        tablero.imprimir();

        if (turno == 'O') {
            // Turno del jugador
            cout << "Tu turno (O):" << endl;
            auto movimientoJugador = obtenerMovimientoJugador(tablero);
            tablero.colocar(movimientoJugador.first, movimientoJugador.second, 'O');
            turno = 'X';
        } else {
            // Turno de la IA
            cout << "Turno de la IA (X):" << endl;
            auto movimientoIA = mejorMovimientoConPoda(tablero);
            tablero.colocar(movimientoIA.first, movimientoIA.second, 'X');
            cout << "La IA jugo en: (" << movimientoIA.first << ", " << movimientoIA.second << ")" << endl;
            turno = 'O';
        }
     }

        cout << "Estado final del tablero:" << endl;
        tablero.imprimir();

        int resultado = tablero.evaluar();
        if (resultado == 10) {
            cout << "La IA (X) gana. Mejor suerte la proxima vez!" << endl;
        } else if (resultado == -10) {
            cout << "Felicidades! Ganaste." << endl;
        } else {
            cout << "Es un empate." << endl;
        }

    }

        return 0;
}