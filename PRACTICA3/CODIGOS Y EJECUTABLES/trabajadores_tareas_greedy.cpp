/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO GREEDY DEL PROBLEMA ASIGNADO 3.3: ASIGNAR N TAREAS A N TRABAJADORES*****************************

Compilacion: g++ trabajadores_tareas_greedy.cpp -o ejecutable

Ejecucion: ./ejecutable [nº_tareas] [nº_trabajadores]


*/


#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

//Defino el valor máximo que puede contener un entero para luego poder buscar valores por debajo de este
#define MAX 2147483647

using namespace std;

//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//                       F              U              N              C              I              O              N              E              S
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************



//generador de ejemplos aleatorios para el problema asignado 3.3

double uniforme(){ //Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores disponibles en C.

	int t = rand();
	double f = ((double)RAND_MAX+1.0);
	return (double)t/f;
 
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comprueba que el numero de argumentos pasados como parametros es el correcto (en nuestro caso 3)
 * @param argc Numero de elementos que tiene el vector de parametros pasado a la funcion
 * @param argv Vector en el que van los valores de los parametros pasados como argumento 
 * @return Devuelve un booleano que indica si es valido (true) o no (false) el numero de argumentos utilizado
*/
bool comprobar_argumentos(int argc, char * argv[]);

//Implementacion
bool comprobar_argumentos(int argc, char * argv[]){
	
	if (argc != 3){ //Deben ser 3 argumentos por: el nombre del ejecutable, el numero de tareas y el numero de trabajadores
		
    	cerr << "Formato " << argv[0] << " <num_tareas>" << " <num_trabajadores>" << endl;     //Si no lo has introducido bien, te dice como hacerlo
    	return false;
    }
    
    return true;
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Genera los numeros entre 0 y mayor_fila_columna-1 y luego se aplica el algoritmo S de Knuth para la asignacion de valores aleatorios
 * @param T matriz a modificar 
 * @param aux Vector auxiliar al que se le introducen los datos del 0 al mayor_fila_columna-1 para luego ser usado en el algoritmo 
 * @param tareas Numero de tareas que será util como número de columnas
 * @param mayor_fila_columan Variable que en caso de no ser una matriz cuadrada contiene el valor de la variable mas grande (en una 3x4 contendria 4)
*/
void algoritmo_sampling(int **T, int *aux,  int tareas, int mayor_fila_columna); 

//Implementacion
void algoritmo_sampling(int **T, int *aux, int tareas, int mayor_fila_columna){
	
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
	
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Muestra por pantalla la matriz, pero en este caso lo hace con un formato que facilita la visualizacion de la tabla con el indice de tarea y trabajador
 * (a partir del tamaño 10 u 11 puede que muestre desajustes por no caber en pantalla, pero ocurre lo mismo sin el formato, a raiz de ciertas dimensiones
 * se mancha la salida por pantalla de los datos) 
 * @param matriz matriz a mostrar
 * @param dimension Variable que contiene cual es la dimension de la matriz cuadrada (coincide con el valor de mayor_fila_columna)
*/
void MostrarPantalla(int **matriz, int dimension); 

//Implementacion
void MostrarPantalla(int **matriz, int dimension){
	
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<< "TABLA DE COSTES:"<<endl;
	cout<<"              ";     //Hueco en blanco de adaptacion del formato
	
	for(int j = 0; j < dimension; j++){	//Bucle que pinta sobre la matriz una fila con los indices de cada columna especificando la tarea a la que referencia
			
			cout << "Tarea "<<j+1<< "    " ;         
			
	}
	
	cout<<endl;
	
	for(int i = 0; i < dimension; i++){   	
	 
		cout << "Trabajador "<< i+1 <<":     "   ;    //Escribe antes de cada fila el trabajador al que se refiere (El trabajador 1 equivale a la fila 0)
		 			
		for(int j = 0; j < dimension; j++){			
			
			cout << matriz[i][j] << "          ";         
			
		}
		
		cout<<endl;             
		
	}
	
	cout<<"-----------------------------------------------------------------------"<<endl;
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comprueba qué tarea de las restantes es la menos costosa para el trabajador 1, luego para el 2, para el 3, y así asigna las tareas con menor 
 * coste a los trabajadores por orden
 * @param matriz Matriz que contiene los costes 
 * @param trabajadores Numero de trabajadores entre los que repartir las tareas
 * @param tareas Numero de tareas a repartir entre los trabajadores
 * @param tareas_asignadas Vector en el que se almacenan las tareas asignadas (en la posicion 0, se almacena el indice de la tarea que hace el 1º trabajador, 
 * en la 1 la tarea que hace el segundo, etc)
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 * @return Devuelve el coste total de haber asignado las tareas a los trabajadores
*/
int AsignarTareasATrabajadores(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas, int mayor_fila_columna); 

//Implementacion
int AsignarTareasATrabajadores(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas, int mayor_fila_columna){
	
	int menor, coste_total = 0; 
	bool ignorar;   //booleano que dirá si la tarea que estamos revisando ya ha sido asignada a un trabajor o no para saber si hay que comprobarla o ignorarla
	
	for(int i = 0; i < mayor_fila_columna; i++){   //Se mueve por los trabajadores (filas)
	
		menor = MAX; //Cada vez que se evaluan las tareas para un nuevo trabajador, se asigna el maximo valor posible de un entero para que desde la primera  
					//tarea a comparar se quede con el valor mas pequeño 
		
		for(int j = 0; j < mayor_fila_columna; j++){  //Se mueve por las tareas (columnas)
			
			ignorar = false;  //inicialmente no hay que ignorar ninguna tarea a evaluar
			
			for(int k = 0 ; k < mayor_fila_columna ; k++){  //Comprueba los indices de las tareas ya asignadas para ver si la que estamos evaluando ya lo ha sido
				
				if(j == tareas_asignadas[k]){  //Condicion de haber encontrado la tarea actual en el vector de los asignados ya
					
					ignorar= true; //Si se cumple la condicion, si que se ignora esa tarea porque ya ha sido asignada
					
				}
				
			}
			
			if(!ignorar){ //Si la tarea no ha sido asignada, se comprueba su coste y se compara con el coste de la tarea que por ahora iba a ser asignada 
						  //al trabajador i 
				
				if(matriz[i][j] < menor){ //Si el coste de esa tarea con ese trabajador es menor que la que ibamos a asignar, esta pasa a ser la asignada
										  //(en la primera iteracion compara con el mayor valor posible de un entero, por lo que la primera tarea que evalue
										  //para cada trabajador, sera asignada)
					
					tareas_asignadas[i] = j;   //Se guarda en la matriz el indice de la tarea que se ha asignado al trabajador i
					menor = matriz[i][j];      //Se actualiza el valor del menor, siendo ahora el coste de la tarea asignada j al trabajador i
					
					
				}
				
			}
			
		}
		
		coste_total += matriz[i][tareas_asignadas[i]]; //Cada vez que se hace definitiva la asignacion, suma el coste de esta a la total que llevamos.
		
		
	}
	
	return coste_total;
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comprueba qué tarea de las restantes es la menos costosa para el trabajador 1, luego para el 2, para el 3, y así asigna las tareas con menor 
 * coste a los trabajadores por orden, pero teniendo en cuenta que en caso de empate, se asigne la tarea que genere más costes para el resto de trabajadores y así quitarla de posibilidades. 
 * @param matriz Matriz que contiene los costes 
 * @param trabajadores Numero de trabajadores entre los que repartir las tareas
 * @param tareas Numero de tareas a repartir entre los trabajadores
 * @param tareas_asignadas_suma Vector en el que se almacenan las tareas asignadas teniendo en cuenta la suma (en la posicion 0, se almacena el indice de la tarea que hace el 1º trabajador, 
 * en la 1 la tarea que hace el segundo, etc)
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 * @return Devuelve el coste total de haber asignado las tareas a los trabajadores teniendo en cuenta la suma 
*/
int AsignarTareasATrabajadoresConSuma(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas_suma, int mayor_fila_columna); 

//Implementacion
int AsignarTareasATrabajadoresConSuma(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas_suma, int mayor_fila_columna){
	
	int menor, coste_total = 0, suma; 
	bool ignorar;   //booleano que dirá si la tarea que estamos revisando ya ha sido asignada a un trabajor o no para saber si hay que comprobarla o ignorarla
	int * aux = new int[mayor_fila_columna];
	
	//Bucle que calcula y almacena en un vector la suma que genera cada tarea para los trabajadores
	for(int i = 0 ; i < mayor_fila_columna ; i++){
		suma = 0;
		for(int j = 0 ; j < mayor_fila_columna ; j++){
			
			suma+=matriz[j][i];
			
		}
		
		aux[i]=suma;
		
	}
	
	for(int i = 0; i < mayor_fila_columna; i++){   //Se mueve por los trabajadores (filas)
	
		menor = MAX; //Cada vez que se evaluan las tareas para un nuevo trabajador, se asigna el maximo valor posible de un entero para que desde la primera  
					//tarea a comparar se quede con el valor mas pequeño 
		
		for(int j = 0; j < mayor_fila_columna; j++){  //Se mueve por las tareas (columnas)
			
			ignorar = false;  //inicialmente no hay que ignorar ninguna tarea a evaluar
			
			for(int k = 0 ; k < mayor_fila_columna ; k++){  //Comprueba los indices de las tareas ya asignadas para ver si la que estamos evaluando ya lo ha sido
				
				if(j == tareas_asignadas_suma[k]){  //Condicion de haber encontrado la tarea actual en el vector de los asignados ya
					
					ignorar= true; //Si se cumple la condicion, si que se ignora esa tarea porque ya ha sido asignada
					
				}
				
			}
			
			if(!ignorar){ //Si la tarea no ha sido asignada, se comprueba su coste y se compara con el coste de la tarea que por ahora iba a ser asignada 
						  //al trabajador i 
				
				if(matriz[i][j] < menor){ //Si el coste de esa tarea con ese trabajador es menor que la que ibamos a asignar, esta pasa a ser la asignada
										  //(en la primera iteracion compara con el mayor valor posible de un entero, por lo que la primera tarea que evalue
										  //para cada trabajador, sera asignada)
					
					tareas_asignadas_suma[i] = j;   //Se guarda en la matriz el indice de la tarea que se ha asignado al trabajador i
					menor = matriz[i][j];      //Se actualiza el valor del menor, siendo ahora el coste de la tarea asignada j al trabajador i
					
					
				}else if(matriz[i][j] == menor){ //En caso de que el valor sea el mismo, es decir, que haya un empate....
					
					if(aux[j] > aux[tareas_asignadas_suma[i]] ){ //... se comprueba que la suma sea mayor para quedarnos con esta.
						
						tareas_asignadas_suma[i] = j;   //Se guarda en la matriz el indice de la tarea que se ha asignado al trabajador i
						menor = matriz[i][j]; 	//Se actualiza el valor del menor, siendo ahora el coste de la tarea asignada j al trabajador i
						
					}
					
				}
				
			}
			
		}
		
		coste_total += matriz[i][tareas_asignadas_suma[i]]; //Cada vez que se hace definitiva la asignacion, suma el coste de esta a la total que llevamos.
		
		
	}
	
	return coste_total;
	
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comprueba qué trabajador de los restantes es el que menos coste tiene realizando la tarea 1, luego la 2, la 3, y así asigna los trabajadores que 
 * que producen el menor coste a cada tarea por orden
 * @param matriz Matriz que contiene los costes 
 * @param trabajadores Numero de trabajadores entre los que repartir las tareas
 * @param tareas Numero de tareas a repartir entre los trabajadores
 * @param trabajadores_asignados Vector en el que se almacenan los trabajadores asignadas (en la posicion 0, se almacena el indice del trabajador que hace 
 * la 1º tarea, en la 1 el trabajador que hace la segunda, etc)
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 * @return Devuelve el coste total de haber asignado los trabajadores a las tareas 
*/
int AsignarTrabajadoresATareas(int **matriz, int trabajadores, int tareas, int *&trabajadores_asignados, int mayor_fila_columna); 

//Implementacion
int AsignarTrabajadoresATareas(int **matriz, int trabajadores, int tareas, int *&trabajadores_asignados, int mayor_fila_columna){
	
	
	int menor, coste_total = 0;
	bool ignorar;  //booleano que dirá si el trabajador que estamos revisando ya tiene asignada una tarea o no para saber si hay que compararlo o ignorarlo
	
	
	for(int i = 0; i < mayor_fila_columna; i++){   	//Se mueve por las tareas (columnas)
	
		menor = MAX;  //Cada vez que se evaluan los trabajadores para una nueva tarea, se asigna el maximo valor posible de un entero para que desde el primer trabajador  
					  //a comparar se quede con el valor mas pequeño
		
		for(int j = 0; j < mayor_fila_columna; j++){ //Se mueve por los trabajadores (filas)
			
			ignorar = false;   //inicialmente no hay que ignorar ningun trabajador a evaluar
			
			for(int k = 0 ; k < mayor_fila_columna ; k++){  //Comprueba los indices de los trabajadores ya asignadas para ver si el que estamos evaluando ya tiene una tarea
				
				if(j == trabajadores_asignados[k]){ //Condicion de haber encontrado el trabajador actual en el vector de los que tienen una tarea asignada ya
					
					ignorar= true;  //Si eso ocurre, no se le puede asignar otra ya y por eso se activa el bool de ignorar
					
				}
				
			}
			
			if(!ignorar){  //Si el trabajador aun no tiene tarea asignada, se comprueba el coste de asignarle la actual (i) y se compara con el coste que producia asignar esa tarea 
						   //al trabajador que la tuviese asignada previamente
				
				if(matriz[j][i] < menor){  //Se cumple si el coste con este trabajador es menor que el coste con el trabajador anterior al que se le ha asignado temporalmente 
					
					trabajadores_asignados[i] = j;  //Se guarda para la tarea i (en la posicion i) el indice del trabajador que realizara esa tarea
					menor = matriz[j][i];   //Se actualiza el valor del menor coste de asignar la tarea i al este trabajador, para futuras comprobaciones
					
				}
				
			}
			
		}
		
		coste_total += matriz[trabajadores_asignados[i]][i];  //Cuando la asignacion es definitiva se suma el coste de esta al coste total
		
	}
	
	return coste_total;  //Devuelve el coste total de haber asignado los trabajadores correctos a cada tarea
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Comprueba qué trabajador de los restantes es el que menos coste tiene realizando la tarea 1, luego la 2, la 3, y así asigna los trabajadores que 
 * que producen el menor coste a cada tarea por orden, pero teniendo en cuenta que en caso de empate, se asigne la tarea que genere más costes para el resto de trabajadores y así quitarla de posibilidades. 
 * @param matriz Matriz que contiene los costes 
 * @param trabajadores Numero de trabajadores entre los que repartir las tareas
 * @param tareas Numero de tareas a repartir entre los trabajadores
 * @param trabajadores_asignados_suma Vector en el que se almacenan los trabajadores asignadas pero teniendo en cuenta la suma (en la posicion 0, se almacena el indice del trabajador que hace 
 * la 1º tarea, en la 1 el trabajador que hace la segunda, etc)
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 * @return Devuelve el coste total de haber asignado los trabajadores a las tareas teniendo en cuenta la suma
*/
int AsignarTrabajadoresATareasConSuma(int **matriz, int trabajadores, int tareas, int *&trabajadores_asignados_suma, int mayor_fila_columna); 

//Implementacion
int AsignarTrabajadoresATareasConSuma(int **matriz, int trabajadores, int tareas, int *&trabajadores_asignados_suma, int mayor_fila_columna){
	
	
	int menor, coste_total = 0, suma;
	bool ignorar;  //booleano que dirá si el trabajador que estamos revisando ya tiene asignada una tarea o no para saber si hay que compararlo o ignorarlo
	int * aux = new int[mayor_fila_columna];
	
	//Bucle que calcula y almacena en un vector la suma que genera cada trabajador para todas las tareas
	for(int i = 0 ; i < mayor_fila_columna ; i++){
		suma = 0;
		for(int j = 0 ; j < mayor_fila_columna ; j++){
			
			suma+=matriz[i][j];
			
		}
		
		aux[i]=suma;
		
	}
	
	
	for(int i = 0; i < mayor_fila_columna; i++){   	//Se mueve por las tareas (columnas)
	
		menor = MAX;  //Cada vez que se evaluan los trabajadores para una nueva tarea, se asigna el maximo valor posible de un entero para que desde el primer trabajador  
					  //a comparar se quede con el valor mas pequeño
		
		for(int j = 0; j < mayor_fila_columna; j++){ //Se mueve por los trabajadores (filas)
			
			ignorar = false;   //inicialmente no hay que ignorar ningun trabajador a evaluar
			
			for(int k = 0 ; k < mayor_fila_columna ; k++){  //Comprueba los indices de los trabajadores ya asignadas para ver si el que estamos evaluando ya tiene una tarea
				
				if(j == trabajadores_asignados_suma[k]){ //Condicion de haber encontrado el trabajador actual en el vector de los que tienen una tarea asignada ya
					
					ignorar= true;  //Si eso ocurre, no se le puede asignar otra ya y por eso se activa el bool de ignorar
					
				}
				
			}
			
			if(!ignorar){  //Si el trabajador aun no tiene tarea asignada, se comprueba el coste de asignarle la actual (i) y se compara con el coste que producia asignar esa tarea 
						   //al trabajador que la tuviese asignada previamente
				
				if(matriz[j][i] < menor){  //Se cumple si el coste con este trabajador es menor que el coste con el trabajador anterior al que se le ha asignado temporalmente 
					
					trabajadores_asignados_suma[i] = j;  //Se guarda para la tarea i (en la posicion i) el indice del trabajador que realizara esa tarea
					menor = matriz[j][i];   //Se actualiza el valor del menor coste de asignar la tarea i al este trabajador, para futuras comprobaciones
					
				}else if(matriz[j][i] == menor){
					
					if(aux[j] > aux[trabajadores_asignados_suma[i]] ){
						
						trabajadores_asignados_suma[i] = j;   //Se guarda en la matriz el indice de la tarea que se ha asignado al trabajador i
						menor = matriz[i][j]; 
						
					}
					
				}
				
			}
			
		}
		
		coste_total += matriz[trabajadores_asignados_suma[i]][i];  //Cuando la asignacion es definitiva se suma el coste de esta al coste total
		
	}
	
	return coste_total;  //Devuelve el coste total de haber asignado los trabajadores correctos a cada tarea
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Realiza las asignaciones de las dos maneras, tareas-trabajadores y trabajadores-tareas y almacena los costes en sus respectivas variables para luego poder compararlas. Esta
 * es la funcion de la que se miden los tiempos porque se hace cada una de las asignaciones y almacena los datos en sus vectores y costes respectivos, la decision de cual es mejor es una
 * comprobacion aparte. 
 * @param matriz Matriz que contiene los costes de asignacion
 * @param trabajadores numero de trabajadores entre los que repartir las tareas
 * @param tareas numero de tareas a repartir entre los trabajadores
 * @param tareas_asignadas Vector que contiene las tareas asignadas (tareas_asignadas[0] -> tarea que realiza el primer trabajador)
 * @param trabajadores_asignados Vector que contiene los trabajadores que realizan cada tarea (trabajadores_asignados[0] -> trabajador que realiza la primera tarea)
 * @param tareas_asignadas_suma Vector que contiene las tareas asignadas a los trabajadores teniendo en cuenta la suma
 * @param trabajadores_asignados_suma Vector que contiene los trabajadores asignados a las tareas teniendo en cuenta la suma
 * @param coste_asignar_tareas Coste total que se produce cuando se asignan las tareas a los trabajadores
 * @param coste_asignar_trabajadores Coste total que se produce cuando se asignan los trabajadores a las tareas
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 * @param coste_asignar_tareas_con_suma Coste total que se produce cuando se asignan las tareas a los trabajadores teniendo en cuenta la suma
 * @param coste_asignar_trabajadores_con_suma Coste total que se produce cuando se asignan los trabajadores a las tareas
 */
void asignacion(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas, int *&trabajadores_asignados, int *&tareas_asignadas_suma, int *&trabajadores_asignados_suma, int &coste_asignar_tareas, int &coste_asignar_trabajadores, int mayor_fila_columna, int &coste_asignar_tareas_con_suma, int &coste_asignar_trabajadores_con_suma); 
																																
//Implementacion
void asignacion(int **matriz, int trabajadores, int tareas, int *&tareas_asignadas, int *&trabajadores_asignados, int *&tareas_asignadas_suma, int *&trabajadores_asignados_suma, int &coste_asignar_tareas, int &coste_asignar_trabajadores, int mayor_fila_columna, int &coste_asignar_tareas_con_suma, int &coste_asignar_trabajadores_con_suma){
	
	coste_asignar_tareas = AsignarTareasATrabajadores(matriz, trabajadores, tareas, tareas_asignadas, mayor_fila_columna); //Se asignan tareas a trabajadores
	coste_asignar_trabajadores = AsignarTrabajadoresATareas(matriz, trabajadores, tareas, trabajadores_asignados, mayor_fila_columna); //Se asignan trabajadores a tareas
	coste_asignar_tareas_con_suma = AsignarTareasATrabajadoresConSuma(matriz, trabajadores, tareas, tareas_asignadas_suma, mayor_fila_columna); //Se asignan tareas a trabajadores teniendo en cuenta la suma
	coste_asignar_trabajadores_con_suma = AsignarTrabajadoresATareasConSuma(matriz, trabajadores, tareas, trabajadores_asignados_suma, mayor_fila_columna); //Se asignan trabajadores a tareas teniendo en cuenta la suma
    
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Una vez realizado cada enfoque de forma independiente, habiendo hecho el reparto respectivo en cada caso, se comparan los resultados y se escoge el que menos coste proporcione
 * @param T Matriz que contiene los costes de asignacion
 * @param tareas_asignadas Vector que contiene las tareas asignadas (tareas_asignadas[0] -> tarea que realiza el primer trabajador)
 * @param trabajadores numero de trabajadores entre los que repartir las tareas
 * @param tareas numero de tareas a repartir entre los trabajadores
 * @param trabajadores_asignados Vector que contiene los trabajadores que realizan cada tarea (trabajadores_asignados[0] -> trabajador que realiza la primera tarea)
 * @param tareas_asignadas_suma Vector que contiene las tareas asignadas teniendo en cuenta la suma (tareas_asignadas[0] -> tarea que realiza el primer trabajador)
 * @param trabajadores_asignados_suma Vector que contiene los trabajadores que realizan cada tarea teniendo en cuenta la suma (trabajadores_asignados[0] -> trabajador que realiza la primera tarea)
 * @param coste_asignar_tareas Coste total que se produce cuando se asignan las tareas a los trabajadores
 * @param coste_asignar_trabajadores Coste total que se produce cuando se asignan los trabajadores a las tareas
 * @param coste_asignar_tareas_con_suma Coste total que se produce cuando se asignan las tareas a los trabajadores teniendo en cuenta la suma
 * @param coste_asignar_trabajadores_suma Coste total que se produce cuando se asignan los trabajadores a las tareas teniendo en cuenta la suma
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
 */
void decision(int **T, int *tareas_asignadas, int trabajadores, int tareas, int *trabajadores_asignados, int *tareas_asignadas_suma, int *trabajadores_asignados_suma, int coste_asignar_tareas, int coste_asignar_trabajadores, int coste_asignar_tareas_con_suma, int coste_asignar_trabajadores_suma, int mayor_fila_columna ); 
																																
//Implementacion
void decision(int **T, int *tareas_asignadas, int trabajadores, int tareas, int *trabajadores_asignados, int *tareas_asignadas_suma, int *trabajadores_asignados_suma, int coste_asignar_tareas, int coste_asignar_trabajadores, int coste_asignar_tareas_con_suma, int coste_asignar_trabajadores_suma, int mayor_fila_columna ){
	
	//Crea una variable "menor" que contendra el coste minimo para poder comparar y decidir cuál es el mejor reparto. "cont" no es más que un contador para rellenar un vector controladamente
    int menor = coste_asignar_tareas, cont = 0;
    
    //Vector que va a contener el indice de aquel/los algoritmo/s que den el coste minimo. Se crea con tamaño 4 porque es el maximo de algoritmos que puede mostrar a la vez (son todos los que hay). Por cada -1 que haya dentro, será un algoritmo que no se muestra
    int *mostrar = new int[4];
	
	//Inicializa a -1 cada posicion porque inicialmente no sabe cual mostrar.
	for(int i = 0; i < 4 ; i++){
		
		mostrar[i]=-1;
		
	}	

    //Muestra los resultados de haber asignado las tareas a los trabajadores
    cout << "\nTareas que hace cada trabajador:\n";

    for(int i = 0 ; i< mayor_fila_columna; i++)
        cout <<"El trabajador "<< i+1 << " hace la tarea " <<tareas_asignadas[i]+1 << " que tiene un coste de: "<< T[i][tareas_asignadas[i]]<<endl;

    cout<<"El coste total asignando tareas es: "<< coste_asignar_tareas<<endl;  //Coste total de esta opcion

	//Muestra los resultados de haber asignado los trabajadores a las tareas
    cout << "\nTrabajador para cada tarea:\n";

    for(int i = 0 ; i< mayor_fila_columna; i++)
        cout <<"La tarea "<< i+1 << " es hecha por el trabajador " <<trabajadores_asignados[i]+1 << " que tiene un coste de: "<< T[trabajadores_asignados[i]][i]<<endl;

    cout<<"El coste total asignando trabajadores es: "<< coste_asignar_trabajadores<<endl;  //Coste total de esta opcion


	//Muestra los resultados de haber asignado las tareas a los trabajadores con suma
    cout << "\nTareas que hace cada trabajador teniendo en cuenta el coste del resto:\n";

    for(int i = 0 ; i< mayor_fila_columna; i++)
        cout <<"El trabajador "<< i+1 << " hace la tarea " <<tareas_asignadas_suma[i]+1 << " que tiene un coste de: "<< T[i][tareas_asignadas_suma[i]]<<endl;

    cout<<"El coste total asignando tareas es: "<< coste_asignar_tareas_con_suma<<endl;  //Coste total de esta opcion


	//Muestra los resultados de haber asignado los trabajadores a las tareas con suma
    cout << "\nTrabajador para cada tarea teniendo en cuenta el coste del resto:\n";

    for(int i = 0 ; i< mayor_fila_columna; i++)
        cout <<"La tarea "<< i+1 << " es hecha por el trabajador " <<trabajadores_asignados_suma[i]+1 << " que tiene un coste de: "<< T[trabajadores_asignados_suma[i]][i]<<endl;

    cout<<"El coste total asignando trabajadores es: "<< coste_asignar_trabajadores_suma<<endl;  //Coste total de esta opcion


    //Comparacion y seleccion del que produzca menor coste
   	mostrar[cont] = 0; //El primer algoritmo se mete si o si. Alguno obligatoriamente es mejor o igual que el resto, por lo que no se da el caso en el que ningun algoritmo sea añadido al vector de los que se van a mostar. 
   					   //por lo que a continuación lo que se hace es comprobar si este algoritmo se deja o se sustituye por otro, pero que hay uno dentro originalmente es inevitable
	cont++;	
   	
	if(coste_asignar_trabajadores < menor){ //Si el coste es menor que los que he dicho que voy a mostrar entro aqui
		
		for(int i = 0; i < 4 ; i++){ //Al ser menor, no voy a mostrar los que decia que iba a mostrar y paso a mostrar solamente este (que es el mejor) por lo que borro todos los que he dicho que iba a enseñar hasta ahora
		
			mostrar[i]=-1;
		
		}
		cont = 0;
		mostrar[cont]=1; //Añado el indice de este algoritmo (en este caso 1, por lo que luego al mirar en la matriz de mostrar, si en alguna de las posiciones hay un 1 mostrare este reparto concreto)
		cont++;
		menor = coste_asignar_trabajadores;
		
	}else if(coste_asignar_trabajadores==menor){ //Si el valor es igual al minimo, no borro lo que iba a mostar, simplemente lo muestro tambien por si fuese una alternativa nueva de reparto, contar con varias opciones que den el mismo coste
		
		mostrar[cont]=1;
		cont++;
		
	}
	if(coste_asignar_tareas_con_suma < menor){
		
		for(int i = 0; i < 4 ; i++){
		
			mostrar[i]=-1;
		
		}
		cont = 0;
		mostrar[cont]=2;
		cont++;
		menor = coste_asignar_tareas_con_suma;
		
	}else if(coste_asignar_tareas_con_suma==menor){
		
		mostrar[cont]=2;
		cont++;
		
	}
	if(coste_asignar_trabajadores_suma < menor){
		
		for(int i = 0; i < 4 ; i++){
		
			mostrar[i]=-1;
		
		}
		cont = 0;
		mostrar[cont]=3;
		cont++;
		menor = coste_asignar_trabajadores_suma;
		
	}else if(coste_asignar_trabajadores_suma==menor){
		
		mostrar[cont]=3;
		cont++;
		
	}
	
	cout<<"\nEl coste mas bajo se ha obtenido tras asignar de la siguiente forma: ";
	
	for(int i = 0 ; i < 4 ; i++){ //Comprobamos y mostramos los resultados que han resultado ser los menores. Puede mostrar un algoritmo, dos, tres o cuatro. Plantea todas las opciones.
		
		if(mostrar[i] == 0){
			
			cout<< "\n    Asignando tareas a trabajadores, lo cual da un coste de "<< coste_asignar_tareas << " y un reparto (trabajador-tarea): "<<endl;
			for(int i = 0 ; i< mayor_fila_columna; i++)
        		cout << i+1 << " - " <<tareas_asignadas[i]+1 << " / ";
        		
        	cout<<endl;
		
		}
		if(mostrar[i] == 1){
			
			cout<< "\n    Asignando trabajadores a tareas, lo cual da un coste de "<< coste_asignar_trabajadores << " y un reparto (trabajador-tarea): "<<endl;
			for(int i = 0 ; i< mayor_fila_columna; i++)
        		cout << trabajadores_asignados[i]+1 << " - " <<i+1 << " / ";
        		
		}
		if(mostrar[i] == 2){
			
			cout<< "\n    Asignando tareas a trabajadores teniendo en cuenta el coste de esas tareas para otros trabajadores, lo cual da un coste de "<< coste_asignar_tareas_con_suma << " y un reparto (trabajador-tarea): "<<endl;
			for(int i = 0 ; i< mayor_fila_columna; i++)
        		cout << i+1 << " - " <<tareas_asignadas_suma[i]+1 << " / ";
        		
		}
		if(mostrar[i] == 3){
			
			cout<< "\n    Asignando trabajadores a tareas teniendo en cuenta el coste de esos trabajadores para otras tareas, lo cual da un coste de "<< coste_asignar_trabajadores_suma << " y un reparto (trabajador-tarea): "<<endl;
			for(int i = 0 ; i< mayor_fila_columna; i++)
        		cout << trabajadores_asignados_suma[i]+1 << " - " <<i+1 << " / ";
        		
		}
		
		cout<<endl;
	}

}
    

 
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Calcula el tiempo que tardado el ejecutarse la parte del codigo en la que se realizan todas las asignaciones por el metodo greedy
 * @param tiempo2 Tiempo registrado antes de la ejecucion de la funcion que realiza la parte greedy
 * @param tiempo1 Tiempo registrado despues de la ejecucion de la funcion que realiza la parte greedy
*/
void tiempo_total(clock_t tiempo2, clock_t tiempo1 ); 
																																
//Implementacion
void tiempo_total(clock_t tiempo2, clock_t tiempo1 ){
	
	unsigned long  tiempo_total = tiempo2 - tiempo1;    //Calulo del tiempo total tardado en la ejecucion
	
	cout<<"\nLa ejecucion tarda " << (double)tiempo_total/1000  << " segundos " << endl;
    
}
 
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Introduce un -1 en todas las posiciones de tareas_asignadas y trabajadores_asignados para cuando se compare el contenido de estos con el indice del trabajador/tarea 
 * correspondiente, solo de true con valore reales
 * @param trabajadores numero de trabajadores entre los que repartir las tareas
 * @param tareas numero de tareas a repartir entre los trabajadores
 * @param tareas_asignadas Vector que contiene las tareas asignadas (tareas_asignadas[0] -> tarea que realiza el primer trabajador)
 * @param trabajadores_asignados Vector que contiene los trabajadores que realizan cada tarea (trabajadores_asignados[0] -> trabajador que realiza la primera tarea)
 * @param mayor_fila_columna dimension real de la matriz cuadrada que contiene los trabajadores y tareas (inluidos los insertados extras para que sea cuadrada)
*/
void inicializa_vectores(int trabajadores, int tareas, int *&tareas_asignadas , int *&trabajadores_asignados, int *&tareas_asignadas_suma,int *&trabajadores_asignados_suma , int mayor_fila_columna); 
																																
//Implementacion
void inicializa_vectores(int trabajadores, int tareas, int *&tareas_asignadas , int *&trabajadores_asignados, int *&tareas_asignadas_suma, int *&trabajadores_asignados_suma ,int mayor_fila_columna){
	
	for (int j=0; j<mayor_fila_columna; j++){
	
		tareas_asignadas[j]=-1;    //Inicializa cada posicion con el valor -1 para no generar conflictos con ninguna tarea aun no asignada
		trabajadores_asignados[j]=-1;   //Inicializa cada posicion con el valor -1 para no generar conflictos con ningun trabajador aun no asignado
		tareas_asignadas_suma[j]=-1; 
		trabajadores_asignados_suma[j]=-1;
	
	} 
    
   
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Rellena con valores aleatorios la matriz 
 * @param T matriz a rellenar
 * @param mayor_fila_columna dimension, contiene cuantas tareas/trabajadores tiene
*/
void rellenar_con_aleatorio(int **T, int mayor_fila_columna);

//Implementacion
void rellenar_con_aleatorio(int **T, int mayor_fila_columna){

	for(int i=0; i<mayor_fila_columna; i++)
		for(int j=0; j<mayor_fila_columna; j++)   
			T[i][j] = 1 + rand()%9;
		  

}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//                                                              M              A              I              N 
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************
//**************************************************************************************************************************************************************************************

int main(int argc, char * argv[]){

	
	//Comprobacion de que el numero de argumentos pasado sea el correcto (en este caso 3)
	bool sigue = comprobar_argumentos(argc, argv);
  	if(!sigue) return -1;
    
    //Declaracion de variables
    int tareas = atoi(argv[1]), trabajadores = atoi(argv[2]);  	//Asigna los valores de los parametros a las variables de trabajadores y tareas
	int total = trabajadores * tareas, mayor_fila_columna; 		//Calculo del total de elementos en la matriz (trabajadores x tareas) y declaracion del valor mas grande de estos
    clock_t tiempo1, tiempo2;  									//elementos para la medicion del tiempo
	int coste_asignar_tareas, coste_asignar_trabajadores, coste_asignar_tareas_suma, coste_asignar_trabajadores_suma;   	//Costes dependiendo de la forma en la que asignemos las tareas
	
	
	
    //Como debe ser cuadrada, vemos cual de las dimensiones es mayor y es la cantidad de memoria que se reserva para columnas y filas. 
	if( tareas >= trabajadores )
		mayor_fila_columna = tareas;
	else 
		mayor_fila_columna = trabajadores;

	int *tareas_asignadas = new int[mayor_fila_columna];				//Vectores en los que se almacenaran las tareas que son asignadas a cada trabajador (tareas_asignadas[0] contiene por ejemplo la tarea que realiza el primer trabajador)
	int *trabajadores_asignados = new int[mayor_fila_columna];				//Vectores en los que se almacenaran los trabajadores que se han asignado a cada tarea (trabajadores_asignados[0] contiene por ejemplo el trabajador que realiza la primera tarea)
	int *tareas_asignadas_suma = new int[mayor_fila_columna];				//Vectores en los que se almacenaran los trabajadores que se han asignado a cada tarea (trabajadores_asignados[0] contiene por ejemplo el trabajador que realiza la primera tarea)
	int *trabajadores_asignados_suma = new int[mayor_fila_columna];				//Vectores en los que se almacenaran los trabajadores que se han asignado a cada tarea (trabajadores_asignados[0] contiene por ejemplo el trabajador que realiza la primera tarea)


	//se reserva memoria para la matriz con tamaño mayor_fila_columna
  	int **T;
	T =  new int * [mayor_fila_columna];
 	assert(T);

	for (int i = 0; i < mayor_fila_columna ; i++)
    	T[i]= new int [mayor_fila_columna];

	//se reserva memoria para un vector auxiliar con tamaño total (trabajadores*tareas)
	int * aux = new int[total];
	assert(aux);

	//algoritmo sampling para los numeros aleatorios
	algoritmo_sampling(T, aux,  tareas, mayor_fila_columna);
		
	//Rellenar la matriz con numeros aleatorios
	rellenar_con_aleatorio(T, mayor_fila_columna);
	
	//Muestra por pantalla la matriz que contiene los costes por cada pareja trabajador-tarea	
	MostrarPantalla(T,mayor_fila_columna);		
	
	//Inicializa los vectores de tareas asignadas y trabajadores asignados con valores que no sean conflictivos con los que vamos a añadir (-1)
	inicializa_vectores(trabajadores, tareas, tareas_asignadas, trabajadores_asignados, tareas_asignadas_suma, trabajadores_asignados_suma, mayor_fila_columna);
	
	//Se calcula el tiempo de ejecucion del algoritmo
	tiempo1 = clock(); 				//Se calcula el tiempo antes de ejecutar la funcion de trasponer
	asignacion(T, trabajadores, tareas, tareas_asignadas, trabajadores_asignados, tareas_asignadas_suma,trabajadores_asignados_suma, coste_asignar_tareas, coste_asignar_trabajadores,mayor_fila_columna, coste_asignar_tareas_suma, coste_asignar_trabajadores_suma);
	tiempo2 = clock(); 				//Se calcula el tiempo despues de ejecutar la funcion de trasponer
	
	//Una vez calculado cada coste, los muestra y dice cual es mejor de ambos
	decision(T, tareas_asignadas, trabajadores, tareas, trabajadores_asignados, tareas_asignadas_suma, trabajadores_asignados_suma,  coste_asignar_tareas, coste_asignar_trabajadores, coste_asignar_tareas_suma, coste_asignar_trabajadores_suma,  mayor_fila_columna );
	
	//Esto muestra la diferencia de tiempo entre el final y el inicial de la ejecucion del algoritmo
	tiempo_total(tiempo2, tiempo1);   						
	
	//libera memoria de la matriz
	for(int i = 0 ; i < mayor_fila_columna ;i++){

		delete[] T[i];
	
	}

	delete [] T;
}
 
