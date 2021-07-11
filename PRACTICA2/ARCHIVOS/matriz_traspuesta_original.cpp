/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO DIVIDE Y VECENRAS DEL PROBLEMA COMUN: TRASPUESTA DE MATRIZ CUADRADA*****************************

Compilacion: g++ dyv.cpp -o ejecutable
Ejecucion: ./ejecutable [nº_filas] [nº_columnas]


EJEMPLO:
Matriz original                                   Matriz Traspuesta
1 2 3 4                                           1 1 1 1
1 2 3 4                                           2 2 2 2
1 2 3 4                                           3 3 3 3
1 2 3 4                                           4 4 4 4

*/


#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

using namespace std;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Muestra por pantalla la matriz en un formato correcto de filas y columnas
 * @param matriz Matriz a mostrar
 * @param fila_inicio tamaño de la matriz cuadrada
 * @param columna_inicio columna de la matriz de la que parte 
 * @param dimension tamaño de la matriz cuadrada a mostrar
*/
void MostrarPantalla(int **matriz, int fila_inicio, int columna_inicio, int dimension); 

//Implementacion de funcion que muestra por pantalla la matriz en un formato correcto de filas y columnas
void MostrarPantalla(int **matriz, int fila_inicio, int columna_inicio, int dimension){
	
	for(int i = 0; i < dimension; i++, fila_inicio++){   			//Bucle que recurre las filas
		int columna = columna_inicio;          			//para reiniciar el valor de la columna cada vez que termine una fila
		for(int j = 0; j < dimension; j++, columna++){			 //Bucle que recurre las columnas
			
			cout << matriz[fila_inicio][columna] << " ";          //muestra el contenido con un espacio detras para ver la separacion entre numeros
			
		}
		
		cout<<endl;              //Salto de linea tras cada fila que le da formato de matriz
		
	}
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Cambia valores de posicion en la matriz
 * @param matriz Matriz de la que y en la que se van a intercambiar elementos
 * @param fila_partida fila en la que se encuentra el primer elemento de los que se va a intercambiar
 * @param columna_partida columna en la que se encuentra el primer elemento de los que se va a intercambiar
 * @param fila_llegada fila en la que se encuentra el segundo elemento por el que se va a intercambiar
 * @param columna_llegada columna en la que se encuentra el segundo elemento de los que se va a intercambiar
 * @param tamanio numero de columnas/filas que mide la porcion de la matriz a intercambiar (nº de filas y columnas que tiene que avanzar )
 */
void intercambiar (int **matriz, int fila_partida, int columna_partida, int fila_llegada, int columna_llegada, int tamanio); 

//Implementacion de funcion que cambia valores de posicion en la matriz
void intercambiar(int **matriz, int fila_partida, int columna_partida, int fila_llegada, int columna_llegada, int tamanio){
	
    for (int i=0; i<tamanio; i++){  //Bucle para avanzar en las filas que hace tantas iteraciones como numero de filas tenga la seccion a intercambiar
    	
        for (int j=0; j<tamanio; j++) {  //Bucle para avanzar en las columnas que hace tantas iteraciones como numero de columnas tenga la seccion a intercambiar
        	
            int aux = matriz[fila_partida+i][columna_partida+j];   //Guarda en una auxiliar el valor de una casilla de salida
            matriz[fila_partida+i][columna_partida+j] = matriz[fila_llegada+i][columna_llegada+j];		//Modifica el valor de la casilla de salida con la casilla de llegada
            matriz[fila_llegada+i][columna_llegada+j] = aux;		//Modifica el valor de la casilla de llegada con la de la casilla de salida (guardada en auxiliar)
            
        }
        
    }
    
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Divide la matriz en 4 matrices cuadradas iguales recursivamente y traspone cada porcion
 * @param matriz Matriz que se va a partir en 4 partes iguales
 * @param primera_fila numero de la fila superior que acota la porcion de matriz que llama a esta funcion
 * @param ultima_fila numero de la fila inferior que acota la porcion de matriz que llama a esta funcion
 * @param primera_columna numero de la columna izquiera que acota la porcion de matriz que llama a esta funcion
 * @param ultima_columna numero de la columna derecha que acota la porcion de matriz que llama a esta funcion
 */
void traspuesta(int **matriz, int dimension, int primera_fila, int ultima_fila, int primera_columna, int ultima_columna); 
																																
//Implementacion de funcion que divide la matriz en 4 matrices cuadradas iguales recursivamente hasta no poder mas
void traspuesta(int **matriz, int dimension, int primera_fila, int ultima_fila, int primera_columna, int ultima_columna){
    
	if( primera_fila < ultima_fila )       //Dentro de este "if" se divide la matriz en unidades más pequeñas 
						//y se hace la traspuesta, por ello si la fila en la que empieza la 
						//sub-matriz que se comprueba no es menor que la ultima, es porque 
						//empieza y termina en la misma, por lo que la matriz solamente tiene 
						//una fila y ya es indivisible (la ultima divisible es una 2x2)
	{
		
        int fila_del_medio, columna_del_medio;	//Para dividir en 4 partes iguales hay que conocer la mitad vertical y la mitad horizontal
        
		fila_del_medio = (primera_fila+ultima_fila)/2;	//Se calcula la fila central de la matriz que estamos evaluando en este caso
        columna_del_medio = (primera_columna+ultima_columna)/2;	//Se calcula la columna central de la matriz que estamos evaluando en este caso


        traspuesta(matriz, dimension, primera_fila, fila_del_medio, primera_columna, columna_del_medio); //Recursiva del primer cuarto de la matriz (arriba izquierda)
        traspuesta(matriz, dimension, primera_fila, fila_del_medio, columna_del_medio+1, ultima_columna); //Recursiva del segundo cuarto de la matriz (arriba derecha)
        traspuesta(matriz, dimension, fila_del_medio+1, ultima_fila, primera_columna, columna_del_medio); //Recursiva del tercer cuarto de la matriz (abajo izquierda)
        traspuesta(matriz, dimension, fila_del_medio+1, ultima_fila, columna_del_medio+1, ultima_columna); //Recursiva del cuarto cuarto de la matriz (abajo derecha)


	//Parte del codigo valida para los ejemplos (descomentar para ver la ejecucion paso por paso)
	/*
	if((ultima_fila-primera_fila+1)%2==0){

		cout<<"Porcion de la matriz a intercambiar: "<<endl;
		MostrarPantalla(matriz,primera_fila, primera_columna, ultima_fila-primera_fila+1);
		cout<<endl;
		cout<<"-----------------------------------------------------------------------------"<<endl;

	}*/
	

        intercambiar(matriz, fila_del_medio+1, primera_columna, primera_fila, columna_del_medio+1, ultima_fila-fila_del_medio); //se hace la traspuesta de cada cuarta parte
	


	//Parte del codigo valida para los ejemplos (descomentar para ver la ejecucion paso por paso)
	/*
	if((ultima_fila-primera_fila+1)%2==0){

		cout<<"Porcion de la matriz intercambiada: "<<endl;
		MostrarPantalla(matriz,primera_fila, primera_columna, ultima_fila-primera_fila+1);
		cout<<endl;
		cout<<"-----------------------------------------------------------------------------"<<endl;
		cout<<"Asi queda la original por ahora: "<<endl;
		MostrarPantalla(matriz,0, 0, dimension);
		cout<<endl;
		cout<<"-----------------------------------------------------------------------------"<<endl;

	}*/

    }
    
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



int main(int argc, char * argv[]){

  if (argc != 3) //Comprueba que se le pasen dos parámetros con el numero de filas y el numero de columnas
    { 
      cerr << "Debes introducir: " << argv[0] << " [nº filas] " << " [nº columnas]" << endl;     //Mensaje de error que indica al usuario la correcta ejecucion del programa
      return -1;
    }


	//Elementos para el calculo del tiempo de ejecucion
	unsigned long tiempo_total;
	clock_t tiempo1, tiempo2;


	int numero_filas, numero_columnas, mayor_fila_columna;   //declaracion de variables relacionadas con los elementos de la matriz
	
	
	numero_filas = atoi(argv[1]);      //El primer argumento introducido se asigna al numero de filas
	numero_columnas = atoi(argv[2]);	//El segundo argumento introducido se asigna al numero de columnas
	
	
	//Como debe ser cuadrada, vemos cual de las dimensiones es mayor y es la cantidad de memoria que se reserva para columnas y filas. 
	//Los huecos en blanco se rellenan con 0. Mejor reservar de mas que eliminar numeros de la matriz
	if( numero_columnas >= numero_filas ) mayor_fila_columna = numero_columnas;
	else mayor_fila_columna = numero_filas;
	
	
	//Reserva de memoria
	int **matriz; 	//Declara la matriz
	matriz = new int *[mayor_fila_columna];  //Reserva memoria para un vector del tamaño del numero de filas
	for(int i = 0; i < mayor_fila_columna; i++){
		
	  matriz[i] = new int[mayor_fila_columna]; //Reserva un vector del tamaño del numero de columnas para cada casilla del vector (para cada fila), creando una matriz de axa
	  
	}
	
	
	//Rellenar la matriz con numeros aleatorios
	for(int i=0; i<numero_filas; i++){
		
	  for(int j=0; j<numero_columnas; j++){
	  	
	    matriz[i][j] = rand()%10;
	    
	  }
	  
	}
	
	//Rellena con 0 las filas o columnas adicionales introducidas para que sea cuadrada
	if( numero_filas < numero_columnas ){      //si hay que rellenar filas
		
	  for(int i=numero_filas; i<numero_columnas; i++){
	  	
	    for(int j=numero_filas; j<numero_columnas; j++){
	    	
	      matriz[i][j] = 0;
	      
	    }
	    
	  }
	  
	}else if(numero_filas > numero_columnas){       //si hay que rellenar columnas
		
	  for(int i=numero_columnas; i<numero_filas; i++){
	  	
	    for(int j=numero_columnas; j<numero_filas; j++){
	    	
	      matriz[i][j] = 0;
	      
	    }
	    
	  }
	  
	}
	
	cout<<"------------------------------------------------------------"<<endl;
	cout<< "ORIGINAL:"<<endl;
	MostrarPantalla(matriz,0,0,mayor_fila_columna);		//Se muestra la matriz original
	
	cout<<endl;	
	cout<<"------------------------------------------------------------"<<endl;
	
	
	cout<<endl;	
	
	tiempo1 = clock(); //Se calcula el tiempo antes de ejecutar la funcion de trasponer
	traspuesta(matriz,mayor_fila_columna, 0, mayor_fila_columna-1, 0, mayor_fila_columna-1);
	tiempo2 = clock(); //Se calcula el tiempo despues de ejecutar la funcion de trasponer
	
	cout << "Una vez traspuesta:\n"; 
	MostrarPantalla(matriz, 0,0,mayor_fila_columna);    //Se muestra la matriz traspuesta
	
	tiempo_total = tiempo2 - tiempo1;    //Calulo del tiempo total tardado en la ejecucion
	
	cout<<endl;	
	
	cout<<"La ejecucion tarda " << tiempo_total << " us " << endl;

	for(int i = 0 ; i < mayor_fila_columna ;i++){

		delete[] matriz[i];
	
	}

	delete [] matriz;

}
