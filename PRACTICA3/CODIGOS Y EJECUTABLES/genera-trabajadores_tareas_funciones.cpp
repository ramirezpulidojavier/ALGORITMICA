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


double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
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
* @brief Funcion para asignar de forma aleatoria una caracteristica a un coche (1..n) de la que depende el tiempo de atencion de ese coche
* @param coches vector que contiene el tiempo de cada coche (por ejemplo, el coche 5 tarda coches[4])
* @param numCoches numero de coches a los que asignar un tipo
*/
void generadorTiempos(vector<int>&coches, int numCoches){
	
	//Inicializar semilla random
	srand (time(NULL));
	
	for(int i=0; i<numCoches; i++)
		coches.push_back((rand() % numCoches) + 1);  //Genera un numero aleatorio entre [0..numCoches]
	
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
* @brief Funcion para mostrar por pantalla los coches con sus costes
* @param coches vector que contiene el tiempo de cada coche (por ejemplo, el coche 5 tarda coches[4])
* @param lineasCoches numero de lineas que hay para la atencion de coches
*/
void MuestroCoches(vector<int> coches, int lineasCoches){
	
	cout <<"*******************************************"<<endl;
	cout <<"        COCHES CON SUS TIEMPOS            " << endl;
	cout <<"*******************************************"<<endl;
	cout <<endl;
	
	
	//Muestra la matriz por pantalla
	if(coches.size() % 2 == 0){        //Adaptar el formato a que el numero de coches sea par para mostrarlo en columnas (para ahorrar espacio en la salida por pantalla)
		
		for (int i = 0; i < coches.size()/2; i++){
		
			cout<<"Coche "<< i+1 << ":  " << coches[i] << "\tCoche "<< (coches.size()/2) + i+ 1 << ":  " << coches[(coches.size()/2) + i] << endl;
				
		}
		
	}else{
		
		for (int i = 0; i <= coches.size()/2 ; i++){  //Adaptar el formato a que el numero de coches sea impar para mostrarlo en columnas 
		
			if(i != coches.size()/2)
				cout<<"Coche "<< i+1 << ":  " << coches[i] << "\tCoche "<< (coches.size()/2) + i+ 2 << ":  " << coches[(coches.size()/2) + i +1] << endl;
			else   //al ser impar, la ultima iteracion solamente muestra una columna
				cout<<"Coche "<< i+1 << ":  " << coches[i] <<  endl;
		
		}
		
	}

	cout <<"\n*******************************************"<<endl;
	cout <<"\nNUMERO DE LINEAS: " << lineasCoches <<endl ;
	cout <<"\n*******************************************"<<endl;
	
	
}


int main(int argc, char * argv[])
{

  	//Comprobacion de que el numero de argumentos pasado sea el correcto (en este caso 3)
	bool sigue = comprobar_argumentos(argc, argv);
  	if(!sigue) return -1;

	vector<int>coches;     				//Vector que contendra para cada coche i, su tiempo de atencion segun sus caracteristicas (el coche 1 tarda coches[0] unidades de tiempo)
  	int numCoches = atoi(argv[1]);		//Numero de coches a asignar pasados como parametros
	int lineasCoches= atoi(argv[2]);	//Numero de lineas en las que repatir
		
	//Generar tiempos segun las caracteristicas de los coches (aleatorio)
	generadorTiempos(coches, numCoches);
	
	//Muestra por pantalla cada coche con el tiempo que necesita (segun sus caracteristicas)
	MuestroCoches(coches, lineasCoches);		
	
}
