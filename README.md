Pablo López Saavedra
21.518.678-4
pablo.lopez01@alumnos.ucn.cl
Paralelo C2

Javier Pizarro Fleming
21.213.249-7
javier.pizarro@alumnos.ucn.cl
Paralelo C2

	Algoritmo minimax sin poda:
- Lo que hace este algoritmo es tomar en cuenta todos los casos posibles en un juego de información perfecta (todos los jugadores saben toda la información del juego, como el ajedrez, o el gato),
cada escenario final tiene una puntuación, y cada decisión que es tomada se hace pensando que tu oponente también elegirá su mejor movimiento. De esta forma cada caso tendrá una "puntuación", y al comparar
y considerar que tu oponente hara su mejor movimiento, obtendremos el camino que es mejor elegir para tener un buen futuro.

	Algoritmo minimax con poda alfa-beta:
- Este algoritmo es una optimización del primero, ya que evita la comparación de ponerse en todos los casos posibles, utilizando un intervalo basado en los valores; alfa para el max, y beta para el min.
Estos valores parten en un intervalo de -infinito para alfa y al +infinito para beta, y son actualizados a medida que se van comparando con valores que son mejores que los que ya se encuentran
(en un nodo max, valores mayores a -infinito para alfa, y en un nodo min, valores menores a + infinito para beta), si llega el momento en el que alfa es mayor o igual a beta, se deja de comparar los hijos que aún no se han visto de ese nodo,
ya que no hay forma de que los resultados mejoren en ese camino. Cuando esto sucede en un nodo max, se le llama poda alfa, y cuando sucede en un nodo min, se llama poda beta.

	Complejidad algoritmica:
- Cuando no hay poda, la complejidad es de O(nˣ), n siendo la cantidad de ramas iniciales y ˣ el nivel de profundidad, y cuando si hay poda, el caso general es cuando se elimina aproximadamente la mitad de ramas,
por lo que la complejidad final sería de O(n^(x/2)), aunque podría darse el (peor) caso de que finalmente la complejidad no cambie y siga siendo O(nˣ), esto debido a un mal orden de los nodos en el árbol.

Primero tenemos que compilar los archivos, escribiendo por consola: g++ main.cpp Tablero.cpp -o gato 
Para iniciar el programa escribimos por la consola: ./gato
(gato puede ser reemplazado por el nombre que desees que tenga el .exe)

Luego empieza el programa y la partida de Tic-tac-toe, creándose un tablero que siempre sera de tamaño 3.
Hay 3 opciones, jugar 2 personas, una persona contra la IA siendo manejada por el algoritmo minimax, y una tercera opción de persona contra la IA siendo manejada por el algoritmo minimax con poda alfa beta.


