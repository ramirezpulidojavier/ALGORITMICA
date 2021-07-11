/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO BACKTRACKING. PROBLEMA ITV. PRACTICA 5**********************************

Compilacion: 
		g++ -std=c++11 ITV.cpp -o ejecutable

Alternativa de compilacion: 
		make
		
Limpieza de todos los ejecutables tras el make: 

		make clean

Ejecucion: 
		./ejecutable [nº coches a repartir] [lineas de servicio]


*/
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


/**
 * @brief Comprueba que el numero de argumentos pasados como parametros es el correcto (en nuestro caso 3)
 * @param argc Numero de elementos que tiene el vector de parametros pasado a la funcion
 * @param argv Vector en el que van los valores de los parametros pasados como argumento 
 * @return Devuelve un booleano que indica si es valido (true) o no (false) el numero de argumentos utilizado
*/
bool comprobar_argumentos(int argc, char * argv[]){
	
	if (argc != 3){ //Deben ser 3 argumentos por: el nombre del ejecutable, el numero de coches y el numero de lineas
		
    	cerr << "Formato " << argv[0] << " <NUM_COCHES>" << " <NUM_LINEAS>" << endl;     //Si no lo has introducido bien, te dice como hacerlo
    	return false;
    }
    
    return true;
	
}

/**
* @brief Funcion para asignar de forma aleatoria una caracteristica a un coche (1..n) de la que depende el tiempo de atencion de ese coche
* @param coches vector que contiene el tiempo de cada coche (por ejemplo, el coche 5 tarda coches[4])
* @param numCoches numero de coches a los que asignar un tipo
*/
void generadorTiempos(vector<int>&coches, int numCoches){
	
	for(int i=0; i<numCoches; i++)
		coches.push_back((rand() % numCoches) + 1);  //Genera un numero aleatorio entre [0..numCoches]
	
}


/**
* @brief Funcion para comprobar que el camino que llevamos hasta ahora no es ya más lento que cualquier otro camino completo, por lo que este se descartaria y no se compararia mas
* @param tiempos_coches vector que contiene el tiempo de cada coche (por ejemplo, el coche 5 tarda coches[4])
* @param tiempoParcial tiempo tiempos_lineasiliar que tardan los coches en ser atendidos en la alternativa que estamos tomando (caminos parciales, sin todos los coches)
* @param numLineas numero de lineas de atencion a coches que hay
* @param menorTiempo tiempo más pequeño obtenido hasta ahora en algun camino completo (haber ordenado todos los coches )
* @param tiempos_lineas Vector con "lineasCoches" posiciones que servirá para el calculo del tiempo completo y de la asignacion de fila para cada coche (no guardado)
* @param nuevoCoche indice del nuevo coche a comprobar (este se introduce en la linea que tenga la ocupacion durante menor tiempo (la que primero se vaya a quedar libre))
* @param etapa nivel del arbol de caminos posibles en la que estamos (nivel 0 -> decidimos el primer coche en pasar, nivel 1 -> segundo, etc...)
* @return booleano que devuelve true si el tiempo de este camino es menor que la cota con la que comparamos y false si ya nos hemos pasado de esta
*/
bool comprobacionEtapa(vector<int> tiempos_coches, int &tiempoParcial, int numLineas, int menorTiempo, vector<int>&tiempos_lineas, int nuevoCoche, int etapa){
	
	int posInsercion = 0;  	 //La posicion (linea de servicio) en la que el coche que estamos comprobando ahora entraria cuando sea posible
	int menor = INT_MAX; 	 //Mayor valor que puede tener un entero para usarrlo como cota incialmente( el primer camino va a ser mas pequeño seguro y esta sera la nueva cota)
	int mayor = -1;		  	 //Variable que contendra el tiempo de la linea en la que se tarda mas(coincide con el tiempo que tardarian los coches en ser atendidos con esa combinacion)
	vector<int>tiempos_lineas_aux = tiempos_lineas; //Vector auxiliar que sera utilizado para almacenar temporalmente los tiempos_lineas y luego volver a versiones anteriores de este (para pasos atras y caminos nuevos)
	bool salir = false;		 //Condicion de parada para poder parar el for cuanto antes y hacer el programa mas rapido


	//bucle para asignar los coches a una linea(a la que tenga almacenado un tiempo menor porque significara que termina antes y lo mas rapido seria que esta sirva al siguiente coche)
	for(int i=0; i<tiempos_lineas_aux.size() && !salir; i++){  
		
		if(etapa < numLineas && tiempos_lineas_aux[i]==-1){   //Si hay mas lineas que coche se estan repartiendo, se mete el coche en la primera que vea vacia y salimos del for
			
			tiempos_lineas_aux[i] = tiempos_coches[nuevoCoche]; //Introduce el tiempo que tarda el coche que estamos comprobando (aux es lo que contiene, el tiempo que estara ocupada cada linea en total)
			salir = true;
			
		}else if(tiempos_lineas_aux[i] < menor){  //Si hay menos lineas que coches, la linea asignada sera la que menos tiempo ocupada le quede (por eso busca el valor mas pequeño)
			
			menor = tiempos_lineas_aux[i];
			posInsercion = i; //Guarda la linea en la que el coche entrara por ser la que menos tiempo estara ocupada
		
		}
		
	}

	if(etapa >= numLineas)      //Si se estaban metiendo mas coches que lineas, que se inserte en la posicion obtenida cuando se recorran todas las lineas disponibles
		tiempos_lineas_aux[posInsercion] += tiempos_coches[nuevoCoche];    //Inserta el tiempo que tarda este realmente, es lo que nos interesa saber y comparar
	

	for(int w=0; w<tiempos_lineas_aux.size(); w++){  //Se busca entre todas las lineas el tiempo mayor (sera el que tarden todos los coches en ser atendidos)
		
		if(tiempos_lineas_aux[w] > mayor){   //Si el valor que hemos encontrado es mayor que el mayor hasta ahora
			
			mayor = tiempos_lineas_aux[w];   //Se actualiza el valor del que es ahora el mayor
			if (mayor > menorTiempo)   return false;  //Si ese tiempo ya es mayor que el tiempo mas corto que hemos obtenido hasta ahora con todos los coches, ya se devuelve false
					     							   //lo cual significa que no es valida esa asignacion porque ya hay al menos una linea sola que tarda mas que otra asignacion 
		}
	
	}
	
	tiempoParcial = mayor; //Si no hemos devuelto false, ninguno de los valores ha sido mayor que la cota, por lo que es valido y se guarda como tiempo parcial correcto
	tiempos_lineas = tiempos_lineas_aux;  //Se pasa a tiempos_lineas el vector auxiliar en el que se han hecho todas las comprobaciones para devolverlo como referencia
	
	return true; //Devuelve que el camino que llevamos por ahora es valido

}



/**
* @brief Funcion que utiliza backtracking para obtener el orden en el que los coches deben ser atendidos para que ocupen el menor tiempo posible
* @param numLineas numero de lineas que hay para la atencion de coches
* @param tiempos_coches vector que contiene el tiempo de cada coche (por ejemplo, el coche 5 tarda coches[4])
* @param etapa nivel del arbol de caminos posibles en la que estamos (nivel 0 -> decidimos el primer coche en pasar, nivel 1 -> segundo, etc...)
* @param nRestantes Vector que contendra los indices de los coches que aun quedan por ser asignados a un orden concreto (al principio todos (= coches))
* @param tiempoSolucion Tiempo cota para descartar combinaciones hasta encontrar uno que ocupe menos tiempo que este original (se inicializa al maximo)
* @param tiempoParcial Tiempo parcial de cada camino para comparar con el tiempo total y ver si se desestima el camino
* @param solucion Auxiliar que tendra versiones temporales del orden en el que los coches pasan a las lineas (desestimado si se descarta esa combinacion)
* @param solucion_def Vector que contiene el orden en el que los coches pasaran a las lineas cuando las vean libres (el 4º coche en ser atendido sera solucion[3])
* @param tiempos_lineas Vector con "lineasCoches" posiciones que servirá para el calculo del tiempo completo y de la asignacion de fila para cada coche (no guardado)	
* @return booleano que devuelve false si ha llegado al caso base y dependiendo de la recurrencia devuelve una cosa u otra. Sirve como condicion de parada a la comprobacion de caminos
*/
bool ITV(int numLineas, vector<int> tiempos_coches, int etapa, vector<int>nRestantes, int &tiempoSolucion, int &tiempoParcial, vector<int>&solucion, vector<int>&solucion_def, vector<int>&tiempos_lineas){
	
	int elementoBorrado;  		//Almacenara un elemento borrado del vector para poder reinsertarlo y poder hacer el resto de comprobaciones
	bool correcto = false;		//Condicion de para que para el for cuando la combinacion que se esta probando es peor opcion y se descarta
	vector <int> tiempos_lineas_mod = tiempos_lineas;	//Auxiliar para hacer comprobaciones sin perder el vector que proporciona la recursividad de la etapa anterior
	int tiempo_parcial_aux;
	
	//caso base
	if(etapa == tiempos_coches.size()){	
	
		if(tiempoParcial < tiempoSolucion){   //Si el tiempo obtenido al llegar al final del camino (reparto completo) es menor que el que habia ya
			
			solucion_def = solucion;		  //Se actualiza el vector con el orden de acceso de los coches que contiene la solucion
			tiempoSolucion = tiempoParcial;	  //El nuevo mejor tiempo se guarda como cota para posibles comprobaciones futuras
		
		}
		
		return false;					
	
	}
	
	//No es el caso base
	for(int i=0; i<nRestantes.size() && !correcto; i++){  //para probar con todas las opciones de los coches restantes que aun no han sido ordenados
	
		tiempos_lineas_mod = tiempos_lineas;   //Se recupera el valor del vector pasado como parametro para que todas las comprobaciones partan de los mismos datos, pues en cada iteracion este vector se modifica
		solucion[etapa] = nRestantes[i];  //Se añade el coche siguiente a comprobar en el vector de soluciones (este contiene indices de coches segun el orden con el que se atienden)
		
		tiempo_parcial_aux = tiempoParcial;	
		if(comprobacionEtapa(tiempos_coches, tiempoParcial, numLineas, tiempoSolucion, tiempos_lineas_mod, nRestantes[i], etapa)){ //si la comprobacion es valida para solucion
			
			if(etapa != tiempos_coches.size()){
								
				elementoBorrado = nRestantes[i];    	//Se guarda el elemento a borrar
				nRestantes.erase(nRestantes.begin()+i); //Se borra el coche que se introduce en la solucion como uno restante (pues ya no esta por asignar)
					
				correcto = ITV(numLineas, tiempos_coches,etapa+1,nRestantes,tiempoSolucion, tiempoParcial, solucion, solucion_def, tiempos_lineas_mod); //Se llama a recursividad con la siguiente etapa
				tiempoParcial = tiempo_parcial_aux;
				for(int j=etapa; j<solucion.size(); j++) //Tras ese camino comprobado se restaura solucion para que en la siguiente iteracion tenga los valores originales
					solucion[j] =- 1;
					
				nRestantes.insert(nRestantes.begin()+i, elementoBorrado);   //Reinserta el coche probado como uno de los restantes y pasa a comprobar otro coche
				
			}else{
				
				correcto = true;
				
			}
			
		}				
	
	}
	
	return correcto;
	
}



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


/**
* @brief Funcion para comprobar que el camino que llevamos hasta ahora no es ya más lento que cualquier otro camino completo, por lo que este se descartaria y no se compararia mas
* @param cochesRestantes Vector que contendra los indices de los coches que aun quedan por ser asignados a un orden concreto (al principio todos (= coches))
* @param solucion Auxiliar que tendra versiones temporales del orden en el que los coches pasan a las lineas (desestimado si se descarta esa combinacion)
* @param solucion_def Vector que contiene el orden en el que los coches pasaran a las lineas cuando las vean libres (el 4º coche en ser atendido sera solucion[3])
* @param tiempos_lineas Vector con "lineasCoches" posiciones que servirá para el calculo del tiempo completo y de la asignacion de fila para cada coche (no guardado)
* @param numCoches Numero de coches que hay
* @param lineasCoches numero de lineas que hay para la atencion de coches
*/
void InicializaVectores(vector<int> &cochesRestantes, vector<int> &solucion, vector<int> &solucion_def, vector<int> &tiempos_lineas, int numCoches, int lineasCoches){
	
	for(int i=0; i<numCoches ;i++){
		
		cochesRestantes.push_back(i);     //Inicializa el vector de coches restantes con los indices de los coches(el coche 0 estará en la posicion 0, inicialmente)
		solucion.push_back(-1);			  //Inicializa con -1 el vector de solucion auxiliar
		solucion_def.push_back(-1);		  //Inicializa con -1 el vector de solucion definitivo que contendra el orden en el que pasan los coches
		
	}

	for(int i=0; i<lineasCoches; i++)
		tiempos_lineas.push_back(-1);				 //Inicializa el vector que contendra los tiempos que cada linea este ocupada con valores -1 (representa estar vacio)
	
}



/**
* @brief Funcion para mostrar por pantalla el indice de los coches ordenados tal y como deberian ir entrando en las filas libres 
* @param solucion_def Vector que contiene el orden en el que los coches pasaran a las lineas cuando las vean libres (el 4º coche en ser atendido sera solucion[3])
* @param tiempoSolucion Tiempo cota para descartar combinaciones hasta encontrar uno que ocupe menos tiempo que este original (se inicializa al maximo)
*/
void MuestroCochesOrdenados(vector<int> solucion_def, int tiempoSolucion){
	
	cout << "\nCOCHES POR ORDEN DE ACCESO A LAS LINEAS: " << endl ;
	
	cout<< "\nCoches:  ";
	
	for(int i=0; i<solucion_def.size(); i++)
		cout << solucion_def[i]+1 << " " ;
	
	
	cout <<"\n\n*******************************************"<<endl;
	cout <<"\nTIEMPO DE SERVICIO:   " << tiempoSolucion     <<endl;
	cout <<"\n*******************************************"  <<endl;
	
}



/**
* @brief Funcion para calcular y mostrar por pantalla el tiempo de ejecucion de la funcion que realiza el backtracking
* @param numCoches Numero total de coches que hay
* @param t_despues tiempo registrado despues de la ejecucion de la funcion
* @param t_antes tiempo registrado antes de la ejecucion de la funcion
*/
void TiempoEjecucion(int numCoches,clock_t t_despues,clock_t t_antes){
	
	cout <<"TIEMPO DE EJECUCION PARA "<< numCoches << " COCHES: " << endl;
	
	cout<< "\n" << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << " segundos" << endl;   //Se restan el tiempo de despues menos el de antes para saber la diferencia
	
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]){
	
	//Comprobacion de que el numero de argumentos pasado sea el correcto (en este caso 3)
	bool sigue = comprobar_argumentos(argc, argv);
  	if(!sigue) return -1;
	
	//Inicializar semilla random
	srand (time(NULL));
	
	
	//Declaracion de variables
	vector<int>coches;     				//Vector que contendra para cada coche i, su tiempo de atencion segun sus caracteristicas (el coche 1 tarda coches[0] unidades de tiempo)
	vector<int>solucion;				//Auxiliar que tendra versiones temporales del orden en el que los coches pasan a las lineas (desestimado si se descarta esa combinacion)
	vector<int>solucion_def;			//Vector que contiene el orden en el que los coches pasaran a las lineas cuando las vean libres (el 4º coche en ser atendido sera solucion[3])
	vector<int>tiempos_lineas;			//Vector con "lineasCoches" posiciones que servirá para el calculo del tiempo completo y de la asignacion de fila para cada coche (no guardado)
	vector<int>cochesRestantes;			//Vector que contendra los indices de los coches que aun quedan por ser asignados a un orden concreto (al principio todos (= coches))
	int tiempoParcial = 0;				//Tiempo parcial de cada camino para comparar con el tiempo total y ver si se desestima el camino
	int tiempoSolucion = INT_MAX;		//Tiempo cota para descartar combinaciones hasta encontrar uno que ocupe menos tiempo que este original (se inicializa al maximo)
	int numCoches = atoi(argv[1]);		//Numero de coches a asignar pasados como parametros
	int lineasCoches= atoi(argv[2]);	//Numero de lineas en las que repatir


	//Generar tiempos segun las caracteristicas de los coches (aleatorio)
	generadorTiempos(coches, numCoches);
	
	
	//Muestra por pantalla cada coche con el tiempo que necesita (segun sus caracteristicas)
	MuestroCoches(coches, lineasCoches);
	
	
	//Inicializacion de vectores
	InicializaVectores(cochesRestantes, solucion, solucion_def, tiempos_lineas, numCoches, lineasCoches);
	
	
	//Funcion de calculo y reparto (Backtracking)
	clock_t t_antes = clock();
	ITV(lineasCoches, coches, 0, cochesRestantes, tiempoSolucion, tiempoParcial, solucion, solucion_def, tiempos_lineas); //Funcion principal
	clock_t t_despues = clock();
	
	
	//Mostrar orden de los coches y el tiempo que tardarian en ser atendidos todos
	MuestroCochesOrdenados(solucion_def, tiempoSolucion);
		
	
	//Calcula el tiempo de ejecucion y lo muestra por pantalla
	TiempoEjecucion(numCoches, t_despues, t_antes);
	

}
