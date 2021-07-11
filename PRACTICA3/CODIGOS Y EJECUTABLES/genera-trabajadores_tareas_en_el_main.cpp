using namespace std;
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_tareas>" << " <num_trabajadores>" << endl;
      return -1;
    }

  int tareas = atoi(argv[1]);
  int trabajadores =atoi(argv[2]);
int total = trabajadores * tareas, mayor_fila_columna; 		//Calculo del total de elementos en la matriz (trabajadores x tareas) y declaracion del valor mas grande de estos


//Como debe ser cuadrada, vemos cual de las dimensiones es mayor y es la cantidad de memoria que se reserva para columnas y filas. 
	if( tareas >= trabajadores )
		mayor_fila_columna = tareas;
	else 
		mayor_fila_columna = trabajadores;


	//se reserva memoria para la matriz con tamaño mayor_fila_columna
  	int **T;
	T =  new int * [mayor_fila_columna];
 	assert(T);

	for (int i = 0; i < mayor_fila_columna ; i++)
    	T[i]= new int [mayor_fila_columna];

	//se reserva memoria para un vector auxiliar con tamaño total (trabajadores*tareas)
	int * aux = new int[total];
	assert(aux);
	
	//inicializar la semilla 
	srand(time(0)); 

	//genero todos los enteros entre 0 y mayor_fila_columna-1
	for (int j=0; j<mayor_fila_columna; j++) aux[j]=j;

	//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
	for (int i=0; i<mayor_fila_columna; i++) {
		int t=0;
		int m=0;

		while (m<tareas) {
		    double u=uniforme();
    		if ((mayor_fila_columna-t)*u >= (tareas-m))
				t++;
    		else {
        		T[i][m]=aux[t];
    			t++;
    			m++;
    		}
  		}
	}
	
	
for(int i=0; i<mayor_fila_columna; i++)
		for(int j=0; j<mayor_fila_columna; j++)   
			T[i][j] = 1 + rand()%9;




cout<<"-----------------------------------------------------------------------"<<endl;
	cout<< "TABLA DE COSTES:"<<endl;
	cout<<"              ";     //Hueco en blanco de adaptacion del formato
	
	for(int j = 0; j < mayor_fila_columna; j++){	//Bucle que pinta sobre la matriz una fila con los indices de cada columna especificando la tarea a la que referencia
			
			cout << "Tarea "<<j+1<< "    " ;         
			
	}
	
	cout<<endl;
	
	for(int i = 0; i < mayor_fila_columna; i++){   	
	 
		cout << "Trabajador "<< i+1 <<":     "   ;    //Escribe antes de cada fila el trabajador al que se refiere (El trabajador 1 equivale a la fila 0)
		 			
		for(int j = 0; j < mayor_fila_columna; j++){			
			
			cout << T[i][j] << "          ";         
			
		}
		
		cout<<endl;             
		
	}
	
	cout<<"-----------------------------------------------------------------------"<<endl;
}
