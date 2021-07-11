//Compilación: g++ -g -std=c++11 matriz_traspuesta.cpp -o matriz_traspuesta

#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <cmath>
#include <time.h>


using namespace std;

void liberar(int **& matriz, int n){
	for(int i=0; i<n; i++){
		delete [] matriz[i];
	}
	delete [] matriz;
}

int ** reservar(int n){
	int **matriz;
	matriz = new int *[n];
	for(int i = 0; i<n; i++){ matriz[i] = new int[n]; }
	return matriz;
}

int ** trasponer(int**& matriz, int n){
	int ** traspuesta = reservar(n);
	for( int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			traspuesta[i][j] = matriz[j][i];
		}
	}
	liberar(matriz, n);
	matriz = traspuesta;

	return matriz;
}

void imprimir(int **& matriz, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char * argv[]){

	if (argc != 3){
		cerr << "Formato: " << argv[0] << " <nº filas>" << " <nº columnas>" << endl;
		return -1;
	}

	int aux;
	int num_filas, num_columnas;
	unsigned long t_total;            //Almacenará el tiempo total de ejecucion del programa
	clock_t t_antes, t_despues;

	num_filas = atoi(argv[1]);
	num_columnas = atoi(argv[2]);

	srand(time(NULL));

	if( num_filas <= num_columnas ){ aux = num_columnas; }
	else{ aux = num_filas; }

	int **matriz = reservar(aux);  //Reservamos memoria para la matriz

	//Primero rellenamos la matriz con valores aleatorios
	for(int i=0; i<num_filas; i++){
		for(int j=0; j<num_columnas; j++){
			matriz[i][j] = rand()%10 + 1;
		}
	}


	//Luego rellenamos la matriz con ceros
	if( num_filas < num_columnas ){
		for(int i=num_filas; i<num_columnas; i++){
			for(int j=num_filas; j<num_columnas; j++){
				matriz[i][j] = 0;
			}
		}
	}
	else{ //Si el numero de filas no es menor que el numero de columnas...
		for(int i=num_columnas; i<num_filas; i++){
			for(int j=num_columnas; j<num_filas; j++){
				matriz[i][j] = 0;
			}
		}
	}

 	if( aux<=12 ){
		cout << "\n----------------[MATRIZ ORIGINAL]-------------------\n";
		imprimir(matriz,aux);
	}

	t_antes = clock();
	trasponer(matriz,aux);
	t_despues = clock();

	if( aux<=12 ){
		cout << "\n----------------[MATRIZ TRASPUESTA]------------------\n";
		imprimir(matriz,aux);
	}

	t_total = t_despues - t_antes;
	cout << "Tamanio: " << aux << "     Tiempo total: " << t_total << endl;

	liberar(matriz,aux);

}
