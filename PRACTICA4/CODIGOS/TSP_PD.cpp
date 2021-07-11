/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO TSP PROGRAMACION DINAMICA. PRACTICA 4**********************************

Compilacion: 
		g++ TSP_PD.cpp -o ejecutable

Alternativa de compilacion: 
		make
		
Limpieza de todos los ejecutables tras el make: 

		make clean

Ejecucion: 
		./ejecutable [fichero].tsp


*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

//Defino el valor máximo que puede contener un entero para las busquedas en las que busco valores <
#define MAX 2147483647

using namespace std;

/**
 * @struct Ciudad
 * @brief Representa una estructura vacia
 */
struct Ciudad{
	
	int indice;   ///Indica el indice unico representa a una ciudad concreta
	double coordx;///Indica la coordenada X en la representacion de la ciudad "indice" sobre los ejes
	double coordy;///Indica la coordenada Y en la representacion de la ciudad "indice" sobre los ejes
	
};


/**
* @brief Funcion para leer las ciudades que se encuentran en los ficheros .tsp
* @param ciuadadesRecogidas contiene todas las ciudades recogidas del fichero .tsp
* @param tsp es un vector de caracteres que representa al fichero .tsp del que recogemos la info
*/
int obtenerInfoFichero(vector<Ciudad> &ciudadesRecogidas, const char tsp[]){

	ifstream f(tsp); //definimos la lectura del fichero tsp que pasamos por parametro a esta funcion
	
	int dimensionFichero = 0; //es la dimension que tendra nuestro fichero, 280 en el caso de a280.tsp
	Ciudad ciudad; //declaramos una ciudad que serÃ¡ la que iremos insertando a nuestro vector de ciudades
	string palabra, indice;
	double x, y;
	
	if(f){ //si el fichero se ha podido leer
	
		getline(f,palabra);
		
		while (palabra != "NODE_COORD_SECTION"){ //saltamos esta linea hasta obtener los primeros valores
			getline(f,palabra);
		}
		
		f >> indice;
		f >> x;
		f >> y;
		
		ciudad.indice = atoi(indice.c_str());
		ciudad.coordx = x;
		ciudad.coordy = y;
		
		ciudadesRecogidas.push_back(ciudad);
		dimensionFichero++;
		
		
		while (indice != "EOF"){
		
			f >> indice;
			
			if (indice != "EOF"){
			
				//recogemos el resto de valores
				f >> x;
				f >> y;
				ciudad.indice = atoi(indice.c_str());
				ciudad.coordx = x;
				ciudad.coordy = y;
				ciudadesRecogidas.push_back(ciudad);
				dimensionFichero++;
			
			}
		
		}
	
	}
	else{ //en caso de que no se haya leido el fichero de datos
		cout << "Error en la lectura del fichero de datos" << endl ;
		exit(-1);
	}
	
	f.close(); //cerramos el fichero
	
	return dimensionFichero;
}



/**
* @brief Funcion para calcular la distancia euclidea entre los puntos que conforman un vector de ciudades
* @param vectorCiudades representa el vector de ciudades al que le queremos calcular la distancia entre sus ciudades
* @return distanciaTotal representa la distancia total de las ciudades del vector
*/
int calcularDistanciaCiudades(vector<Ciudad> vectorCiudades){

	int distanciaTotal = 0; //variable que acumulara la distancia del vector de las ciudades
	double x1 = 0, x2 = 0, y1 = 0, y2 = 0; //definimos las variables de la formula de la distancia euclidea
	
	for(int i = 1; i < vectorCiudades.size(); i++){ //empezamos en 1 para poder coger la 0 como la primera del vector
		x1 = vectorCiudades[i-1].coordx; //cordenada x de la ciudad
		y1 = vectorCiudades[i-1].coordy; //cordenada y de la ciudad
		x2 = vectorCiudades[i].coordx; //coordenada x de la ciudad que le sigue
		y2 = vectorCiudades[i].coordy; //coordenada y de la ciuad que le sigue
		
		distanciaTotal += round(sqrt(pow(x1-x2, 2)+pow(y1-y2, 2))); //formula de la distancia euclidea entre dos puntos redondeando estas
	}
	
	return distanciaTotal; //distancia total entre las ciudades del vector
}



/**
* @brief Funcion recursiva que aplica un razonamiento/resolucion basado en PD para sacar el camino mas optimo 
* @param nodo_inicio representa la ciudad ( = indice - 1) de la que salimos en el recorrido
* @param nodos_por_pasar representa el vector de ciudades por el que debemos pasar antes de llegar a 1 
* @param ciudadesRecogidas representa el vector de ciudades que las contiene todas, utilizado para calcular las distancias entre ellas
* @return solucion pair que contiene como primer elemento la distancia mas corta de todos los caminos disponibles desde nodo_inicio y en el segundo la secuencia de ciudades para ello
*/
pair<int, vector<int> > DistanciaYRecorridoMinimo(int nodo_inicio, vector<int> nodos_por_pasar, vector<Ciudad>&ciudadesRecogidas, int nodo_empece){ 

	//Declaracion de variables
	int masCorto = MAX;     //Se inicia un valor en cada recursividad que nos asegure que la primera comparacion es menor si o si, en este caso el valor maximo de un int
	int distancia;          //Contendra la distancia entre nodo_inicio y cualquier vecino más la distancia más corta de pasar por todos los restantes
	int elementoBorrado;    //Guarda el nodo que borramos de la lista de nodos para volver a insertarlo una vez se ha hecho la recursividad
	int indiceMasCorto;     //Almacena el indice del nodo actual cuando se cumple la condicion de que la distancia de un camino es menor que la de otro pasando por = nº nodos
	vector<Ciudad>comprobaciones;      //Vector en el que se introducen las dos ciudades de las que obtener las distancias en cada iteracion
	pair<int, vector<int> > solucion;  //Sera el pair que contiene la solucion que se va devolviendo en cada recursividad
	pair<int, vector<int> > aux;       //Pair auxiliar para poder calcular las distancias sin aplastar los datos del camino mas corto
	
	
	//Calculo del camino
	if(nodos_por_pasar.size() == 0){   //CasoBase (los indices por los que hay que pasar son 0)
			
			comprobaciones.push_back(ciudadesRecogidas[nodo_empece]);                  //Introduzco la ciudad 1 que es el retorno
			comprobaciones.push_back(ciudadesRecogidas[nodo_inicio]);        //Introduzco la ciudad de la que partimos  
			solucion.first = calcularDistanciaCiudades(comprobaciones);      //Calculo la distancia entre estas y lo introduzco en el pair de soluciones a devolver
			solucion.second.push_back(nodo_inicio);                          //Introduce en la secuencia de ciudades la ciudad de la que partimos (a la que llegamos es 1 en el CB)
			return solucion;                                                 //Devuelve la distancia y el recorrido necesario para llegar al nodo de partida
	
	}else{                             //Quedan nodos por recorrer en nodos_por_pasar
		for(int j=0; j<nodos_por_pasar.size(); j++){
			
			//Introducimos las dos ciudades entre las que queremos saber la distancia
			comprobaciones.push_back(ciudadesRecogidas[nodo_inicio]);
			comprobaciones.push_back(ciudadesRecogidas[nodos_por_pasar[j]]);
			
			//Almacenamos el elemento borrado del vector para su posterior reintroduccion y lo borramos de los nodos por los que pasar
			elementoBorrado = nodos_por_pasar[j];
			nodos_por_pasar.erase(nodos_por_pasar.begin()+j);
			
			//Almacenamos en un auxiliar el resultado de la recursividad que calcula el camino mas corto por los nodos restantes (puede no ser definitivo porque sea mas largo que otro)
			aux = DistanciaYRecorridoMinimo(elementoBorrado, nodos_por_pasar, ciudadesRecogidas, nodo_empece);
			
			//Calcula la distancia entre nodo_inicio y una ciudad X de nodos_por_pasar sumads a la distancia mas corta de los caminos que salen de X y llegan a 1 sin repetir nodo
			distancia = calcularDistanciaCiudades(comprobaciones) + aux.first; 
			
			//Reinserta en nodos_por_pasar el elemento que habia sido borrado para que en la siguiente iteracion se tenga en cuenta como uno a recorrer y no como uno de salida
			nodos_por_pasar.insert(nodos_por_pasar.begin()+j, elementoBorrado);
			
			//Vaciamos lo que hay en el vector de las comparaciones para no calcular distancias incorrectas
			comprobaciones.clear();
	
	
			//Si el camino calculado es mas corto que uno calculado previamente
			if(distancia < masCorto){           
				
				//El auxiliar que contenia la solucion pasaria a ser definitiva y se pega en la variable que se devuelve
				solucion = aux;
				
				//Se actualiza el valor de la distancia, que hasta ahora contenia la del camino anterior (ahora tiene en cuenta un nodo mas, del que partimo actualmente)
				solucion.first = distancia;
				
				//Almacena en variables la distancia mas corta de los caminos y la ciudad de la que partir para que eso ocurra
				masCorto = distancia;
				indiceMasCorto = nodo_inicio;
				
			}
			
		}
		
		//Al terminar actualiza los valores de la solucion a devolver. Tiene en cuenta la nueva distancia contando con una ciudad mas e introduce esta en la secuencia que llevabamos
		solucion.first = masCorto;
		solucion.second.push_back(indiceMasCorto);
		
	}
	
	return solucion;        //Devolucion del pair con los valores que necesitamos
	
}



/**
* @brief Funcion para calcular la distancia entre todas las ciudades con todas las ciudades 
* @param dimension numero de ciudades que hay 
* @param ciudadesRecogidas representa el vector de ciudades que las contiene todas, utilizado para calcular las distancias entre ellas
* @param distancias_directas matriz que contendra en cada casilla con localizacion (i, j) la distancia entre las ciudades con los indices i+1 y j+1
*/
void CalculoDistanciasMinimas(int dimension, vector<Ciudad> ciudadesRecogidas, int **distancias_directas){

	//Vector que contendra dos ciudades entre las que medir la distancia
	vector<Ciudad> ciudades_a_medir;

	for (int i = 0; i < dimension; i++){
		
		for ( int j = 0; j < dimension; j++){
			
			//introduce las ciudades a medir en el vector
			ciudades_a_medir.push_back(ciudadesRecogidas[i]);
			ciudades_a_medir.push_back(ciudadesRecogidas[j]);
			
			//rellena la posicion correcta de la matriz con la distancia entre estas
			distancias_directas[i][j] = calcularDistanciaCiudades(ciudades_a_medir);
			
			//limpia el vector para calcular la distancia entre otras dos ciudades
			ciudades_a_medir.clear();
			
		}
	
	}

}

/**
* @brief Funcion para mostrar por pantalla la matriz que contiene la distancia entre todas las ciudades con todas las ciudades 
* @param dimension numero de ciudades que hay 
* @param distancias_directas matriz que contendra en cada casilla con localizacion (i, j) la distancia entre las ciudades con los indices i+1 y j+1
*/
void MuestroDistanciasMinimas(int dimension, int **distancias_directas){

	cout <<"******************************************************************************************************************"<<endl;
	cout <<"                                                  DISTANCIAS DIRECTAS                                                  " << endl;
	cout <<"******************************************************************************************************************"<<endl;
	cout <<endl;
	
	//Para dar formato de tabla y facilitar la visualizacion de los datos
	cout <<"\t\t";
	for(int i = 0; i < dimension; i++)		
		cout<< "--------";
		
	cout <<endl;
	
	cout <<"\t\t";
	for(int i = 0; i < dimension; i++)	
		cout<< i+1 << "\t";
	
	cout<<endl;
	
	cout <<"\t\t";
	for(int i = 0; i < dimension; i++)		
		cout<< "--------";
		
	cout  << endl;
	
	//Muestra la matriz por pantalla
	for (int i = 0; i < dimension; i++){
		
		cout<<"|   Ciudad "<< i+1 << "\t|";
		
		for ( int j = 0; j < dimension; j++)
			cout << distancias_directas[i][j] << "   \t";
		
		cout << endl;
		
	}

	cout << endl ;

	cout <<"******************************************************************************************************************"<<endl;
	cout <<"\n******************************************************************************************************************"<<endl;
	
}

/**
* @brief Funcion para calcular cuales son los nodos por los que hay que pasar dependendiendo del que salgamos. Da flexibilidad a poder salir de diferentes ciudades
* @param dimension numero de ciudades que hay 
* @param ciudadInicio variable que contiene la ciudad de la que se inicia el recorrido
* @param vectorNodosPaso representa el vector de ciudades por el que debemos pasar antes de llegar a 1 
*/
void CalcularRestoDeNodos(int dimension, int ciudadInicio, vector<int> &vectorNodosPaso){

	for(int i=0; i<dimension; i++){
		
		if(i!=ciudadInicio)        //Si el nodo es igual a aque del que partimos, no se incluye en los que tenemos que recorrer, si no, si se aniade como uno pendiente por visitar
			vectorNodosPaso.push_back(i);
	
	}
	
}


/**
* @brief Funcion para mostrar la informacion final por pantalla
* @param solucion pair que contiene tanto la distancia minima como la secuencia de ciudades a seguir
* @param ciudadInicio variable que contiene la ciudad de la que se inicia el recorrido
*/
void ResultadoFinal(pair<int,vector<int> > solucion, int ciudadInicio){

	cout << "\nLA DISTANCIA MAS CORTA MIDE: " << solucion.first << endl ;
	cout << "\nEL RECORRIDO FINAL ES : " ;
	for(int i=solucion.second.size()-1; i>=0; i--)         //Muestra el recorrido al reves porque la recursividad hace que los nodos se almacenen de destino a origen, al reves
		cout << solucion.second[i]+1 << " -> " ;

	cout<< ciudadInicio+1 << "\n";	   //Aniade al recorrido final que se muestra por pantalla la vuelta al nodo de inicio

}



int main(int argc, char * argv[]){

	vector<Ciudad> ciudadesRecogidas; 								//vector de ciudades que recogeremos del fichero
	int dimension = obtenerInfoFichero(ciudadesRecogidas, argv[1]); //rellenamos el vector ciudadesRecogidas con las ciudades del fichero y devuelve la cantidad de ciudades que hay
	int ciudadInicio = 0;                         //Variable que indica la ciudad de la que parte el camino (en nuestro caso el camino empieza y termina en la primera)
	vector<int> vectorNodosPaso;				  //Vector que contiene el resto de ciudades por las que pasar
	pair<int,vector<int> > solucion;			  //Pair que contendra la solucion final al problema. En el primer elemento la distancia mas corta y en el segundo el recorrido final
	int **distancias_directas;                    //Creo la matriz de distancias entre ciudades
	
	
	//Reserva para la matriz de distancias	
	distancias_directas = new int *[dimension];

	for (int i = 0; i < dimension; i++)
		distancias_directas[i] = new int [dimension];
	
	//Calcular las distancias directas entre todas las ciudades (matriz de distancias)
	CalculoDistanciasMinimas(dimension, ciudadesRecogidas, distancias_directas);
	
	//Mostrar las distancias directas entre todas las ciudades (matriz de distancias)
	MuestroDistanciasMinimas(dimension, distancias_directas);
	
	//Calcular cual es el resto de nodos por los que pasar para empezar por el que queramos
	CalcularRestoDeNodos(dimension, ciudadInicio, vectorNodosPaso);
	
	//Funcion que calcula el camino mas corto y el recorrido necesario
	solucion = DistanciaYRecorridoMinimo( ciudadInicio, vectorNodosPaso, ciudadesRecogidas, ciudadInicio); 

	//Salida de datos finales
	ResultadoFinal(solucion, ciudadInicio);
	
	//Liberar memoria de la matriz
	for (int i = 0; i < dimension; i++)
		delete [] distancias_directas[i];

	delete [] distancias_directas;
	
}
