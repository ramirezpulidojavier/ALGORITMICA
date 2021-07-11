/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO DIVIDE Y VECENRAS DEL PROBLEMA 3.2: VECTOR ORDENADO*****************************

Compilacion: g++ dyv.cpp -o ejecutable
Ejecucion: ./ejecutable [nº_elementos] [nº_vectores]


EJEMPLO:
Matriz original                                   Vector unido
1 2 4 6                                           
2 6 7 11                                          1 1 2 2 2 3 3 4 4 5 6 6 7 7 9 11 
1 2 3 4                                           
3 5 7 9                                           

*/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;


//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}


/**
 * @brief Funcion para ordenar los vectores procedentes de la union recursiva en uno final con todos los valores que ordena a la vez
 * @param array1 vector1 en el que se almacenara la union final  
 * @param array2 vector2 en el que se alamacenara la union final
 * @param start inicio del vector
 * @param end tamaño del array1
 * @param end2 tamaño del array2
*/

void unionFinal (int *&array1, int *&array2, int start, int end, int end2){

    int tam = end+end2; //el tamaño sera la suma del tamaño de cada vector
    int *array = new int [tam]; // se reserva memoria para un array con dimension tam
	int contadorarray = 0 ;
    int contador1 = 0 ; // se inicializa un contador
	int contador2 = 0 ; // se inicializa otro contador

	while( (contador1 + contador2) < tam){ //mientras que la suma de los contadores sea menos que el tamaño del array final 
		if(contador1!=end && contador2!=end2){ //comprueba que los contadores sean distintos de sus respectivos tamaños
			
			if(array1[contador1] > array2[contador2]){ //si el elemento del array1 es mayor que el del array2
			
			array[contadorarray] = array2[contador2]; //metemos en el array final el contenido del array2
			contador2++; //incrementamos contador de array2
			contadorarray++; //incrementamos contador del array final
			
			}
			else{
				if(array1[contador1] <= array2[contador2]){ //si el elemento del array2 es mayor que el del array1
					
					array[contadorarray] = array1[contador1]; //metemos en array final el contenido de array1
					contador1++; //incrementamos el contador del array1
					contadorarray++; //incrementamos el contador del array final
					
				}
				
			}	
			
		}
		else if(contador1 == end){ //si el contador1 ya ha llegado a su fin, es decir si se ha copiado el array1 ya
			array[contadorarray] = array2[contador2]; //se copia el array2 en el array final
			contador2++; //incrementamos el contador del array2
			contadorarray++; //incrementamos el contador del array final
		}
		else{ //si es al contario, es decir, si el contador2 ha llegado a su fin
			
			array[contadorarray] = array1[contador1]; //se copia el array1 en el array final
			contador1++; //se incrementa el contador del array1
			contadorarray++; //se incrementa el contador del array2
			
		}
		
	}

    array1 = array2 = array; //se igualan los punteros de array1 y array2 con array para que tengan ambos el vector final unido

}

/**
 * @brief Funcion para unir los vectores ordenador recursivamente
 * @param matriz es la matriz que tiene los vectores ordenados en filas  
 * @param primerafila es la primera fila de la matriz como el nombre indica
 * @param ultimafila es la fila que señala donde queremos cortar la matriz
 * @param tamanios es el tamaño de la matriz, que sera el numero de vectores de la misma
 * @param util es el util de la matriz dinamica, es decir, su tamaño 
*/

void uneVectores(int **matriz, int primerafila, int ultimafila, int *&tamanios, int &util){

  if(primerafila < ultimafila){ //si la fila final es mayor que la inicial

		int filadelmedio = (primerafila + ultimafila)/2; //se calcula la fila del medio

	  	uneVectores(matriz,primerafila,filadelmedio, tamanios, util); //se une de forma recursiva la primera mitad de la matriz

    	uneVectores(matriz,filadelmedio+1, ultimafila, tamanios, util); //se une de forma recursiva la segunda mitad de la matriz


	//DESCOMENTAR PARA VER PASOS INTERMEDIOS
	/*
	cout << "Se va a combinar la fila " << primerafila << " con la fila " << ultimafila << endl;

		for(int i=0; i<util; i++){
	
	    	int aux = tamanios[i] ;
	
	    	for(int j=0; j<aux; j++){
	
	        	cout << matriz[i][j] << " " ;
	    
			}
	    
		cout << endl ;
	  
	  	}
	
	    cout << endl ;
	
	*/

	  	unionFinal(matriz[primerafila],matriz[ultimafila],0,tamanios[primerafila],tamanios[ultimafila]); //se llama a unionFinal con los vectores restantes de realizar la union recursiva

  		tamanios[primerafila] += tamanios[ultimafila]; //se actualiza el valor de tamaños en primerafila como la suma de el mismo
  		tamanios[ultimafila] = tamanios[primerafila]; //se actualiza el valor de tamños en ultimafila como el tamaño de primerafila


	//DESCOMENTAR PARA VER PASOS INTERMEDIOS
	/*
	cout << "Resultado de combinar la fila " << primerafila << " con la fila " << ultimafila << endl;

	for(int i=0; i<util; i++){
	
	    int aux = tamanios[i];
	
	    for(int j=0; j<aux; j++){
	
	        cout << matriz[i][j] << " " ;
	    }
	    
		cout << endl ;
	  
	}
	
	cout << endl ;
	*/
	
	} //cierre del if
	
}


int main(int argc, char * argv[])
{

	if (argc != 3)
	{
    	cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
    	return -1;
    }

	int n = atoi(argv[1]); //n es el numero de elementos que se pasara como primer argumento
	int k=atoi(argv[2]); //k es el numero de vectores que se pasara como segundo argumento
	int N=k*n; //N es el tamaño del vector que tendra k*n elementos

	//se reserva memoria para la matriz con tamaño k
  	int **T;
	T =  new int * [k];
 	assert(T);

	for (int i = 0; i < k; i++)
    	T[i]= new int [N];

	//se reserva memoria para un vector auxiliar con tamaño N (k*n)
	int * aux = new int[N];
	assert(aux);

	srand(time(0)); //inicializar la semilla 

	//genero todos los enteros entre 0 y k*n-1
	for (int j=0; j<N; j++) aux[j]=j;

	//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
	for (int i=0; i<k; i++) {
		int t=0;
		int m=0;

		while (m<n) {
		    double u=uniforme();
    		if ((N-t)*u >= (n-m))
				t++;
    		else {
        		T[i][m]=aux[t];
    			t++;
    			m++;
    		}
  		}
	}


	//se crea un vector tamaños con memoria k que sera el vector de tamaños de la matriz
	int *tamanios = new int [k];
	int util = 0;
	
	for(util  = 0 ; util < k ; util++)
    	tamanios[util] = n ;



	cout <<"---------------------------------------"<<endl;
	cout << "***********MATRIZ ORIGINAL***********"  << endl ;
	cout <<"---------------------------------------"<<endl;
	
		for(int i=0; i<k;i++){
	        
			cout<<"El vector "<< i+1<< " es: | ";
	        
			for(int j=0; j<n; j++){
	            
				cout << T[i][j] << " | " ;
	
	        }
	        
			cout<< endl ;
	        
		}
	cout <<"---------------------------------------"<<endl;
	
	cout << endl ;

	
	uneVectores(T, 0, k-1, tamanios, util); //se llama a la funcion uneVectores para unir los vectores ordenados que tiene matriz 


	delete [] aux; //se libera memoria del vector aux 

	//DESCOMENTAR PARA PROBAR PASOS INTERMEDIOS
	/*
	cout << endl;
	cout << "La matriz finalmente por filas ha quedado asi: " << endl;
	
	
	for (int i=0; i<k; i++) {
	
	    n=tamanios[i];
	    cout << "La fila " << i << " ha quedado con " << n << " elementos que son: " ;
	
	for (int j=0; j<n; j++)

	   cout << T[i][j] << " ";

	cout << " " << endl;

	}
	
	cout << endl ;
	*/

	cout <<"---------------------------------------"<<endl;
	cout << "***********RESULTADO FINAL***********"  << endl ;
	cout <<"---------------------------------------"<<endl;
	cout<<"La mezcla final y ordenada es: ";

	for (int i=0; i<N; i++)
	    cout << T[0][i] << " ";
	
	cout << endl ;
	
	
	delete [] tamanios; //liberamos la memoria del vector de tamanios

}
