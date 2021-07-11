/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************TSP BRANCH AND BOUND*****************************

Compilacion: g++ -std=c++11 -o TSPBranchAndBound TSPBranchAndBound.cpp
Ejecucion: ./ejecutable [archivo.tsp]    

*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>
using namespace std;

int N;           //Numero de ciudades
int MAX=999999;  
//IMPORTANTE: MAX es una variable utilizada para maximos y ademas se utiliza para seleccionar en la matriz las posiciones que no se tengan que explorar. Vease en funcion minimizarMatriz

/**
 * @brief Struct donde poder guardar una ciudad con su indice, coordenada x y coordenada y
 * @param indice:   indice de la ciudad (1,2,3...)
 * @param x:  coordenada x de la ciudad
 * @param y:  coordenada y de la ciudad
*/

struct Ciudad{
    int indice;
    double x;
    double y;
};


/**
 * @brief Funcion para obtener las ciudades de los ficheros .tsp
 * @param ciuadadesRecogidas: almacena las ciudades obtenidas del fichero .tsp
 * @param tsp: vector de caracteres que representa al fichero .tsp
 * @return dimensionFichero representa el numero de ciudades del fichero 
*/

int obtenerInfoFichero(vector<Ciudad> &ciudadesRecogidas, const char tsp[]){

ifstream f(tsp);

int dimensionFichero = 0;
Ciudad ciudad;
string palabra, indice;
double x, y;

if(f){

    getline(f,palabra);

    while (palabra != "NODE_COORD_SECTION"){
        getline(f,palabra);
      }

      f >> indice;
      f >> x;
      f >> y;

    ciudad.indice = atoi(indice.c_str());
    ciudad.x = x;
    ciudad.y = y;

    ciudadesRecogidas.push_back(ciudad);
    dimensionFichero++;


    while (indice != "EOF"){

        f >> indice;

        if (indice != "EOF"){

        f >> x;
        f >> y;
        ciudad.indice = atoi(indice.c_str());
        ciudad.x = x;
        ciudad.y = y;
        ciudadesRecogidas.push_back(ciudad);
        dimensionFichero++;

       }

     }

    }
    else{
    cout << "Error en la lectura del fichero de datos" << endl ;
    exit(-1);
    }

    f.close();

    return dimensionFichero;
}


/**
 * @brief Función: Calcula la distancia entre dos ciudades
 * @param vectorCiudades1: representa un vector de ciudades
 * @param c1: representa la posicion de la ciudad en el vector "vectorCiudades1"
 * @param vectorCiudades2: representa otro vector de ciudades 
 * @param c2: representa la posicion de la ciudad en el vector "vectorCiudades2"
 * @return distanciaTotal representa la distancia total de las ciudades del vector 
*/

double obtenerDistanciaCiudades(vector<Ciudad> vectorCiudades1, int c1, vector<Ciudad> vectorCiudades2, int c2){

    double distanciaTotal = 0;        //Guarda la distancia entre las dos ciudades
    double x1, x2, y1, y2;            //Guardan las coordenadas de las ciudades

    x1 = vectorCiudades1[c1].x; //cordenada x de la ciudad 1
    y1 = vectorCiudades1[c1].y; //cordenada y de la ciudad 1
    x2 = vectorCiudades2[c2].x; //coordenada x de la ciudad 2
    y2 = vectorCiudades2[c2].y; //coordenada y de la ciudad 2

    //formula de la distancia euclidea entre dos puntos
    distanciaTotal += round(sqrt(pow(x1-x2, 2)+pow(y1-y2, 2)));

    return distanciaTotal; //distancia total entre las ciudades del vector
}

//####################################################################################################
//#--------------------------------#--------------------------------#--------------------------------#
//#--------------------------------#-HASTA AQUÍ SE PUEDE REUTILIZAR-#--------------------------------#
//#--------------------------------#--------------------------------#--------------------------------#
//####################################################################################################

//Funciones de depuracion---------------------------------------------------------#

/**
 * @brief Función:muestra matriz por pantalla
 * @param M1: Matriz
*/
void mostrarMatriz(double** M1){
	cout << "-------------------------------------------------" << endl;
	for(int i=0 ; i<N ; i++){
		for(int j=0 ; j<N ; j++)
			cout << M1[i][j] << " ";
		cout << endl;
	}
	cout << "-------------------------------------------------" << endl;
}

/**
 * @brief Función:muestra matriz por pantalla
 * @param ciudades: ciudades del vector de struct Ciudad
*/
void mostrarVector(vector<Ciudad> ciudades){
	cout << "(";
	for(int i=0 ; i<ciudades.size() ; i++)
		cout << " " << ciudades[i].indice;
	cout << ") ";
}

//Fin funciones de depuracion-----------------------------------------------------#



/**
 * @brief Función: Obtiene la matriz de distancias utilizando un vector de ciudades
 * @param ciudades: representa un vector de ciudades
 * @return M1: representa la matriz de distancias  obtenida del vector de ciudades
*/

double** obtenerMatriz(vector<Ciudad> &ciudades){
    double** M1= new double*[N];

    for(int i=0 ; i<N ; i++)
	M1[i] = new double[N];


    for(int i=0 ; i<N ; i++){
        for(int j=i+1 ; j<N ; j++){
            M1[j][i]=obtenerDistanciaCiudades(ciudades, i, ciudades, j);
	    M1[i][j]=obtenerDistanciaCiudades(ciudades, i, ciudades, j);
        }
	M1[i][i] = MAX; //Rellenamos la diagonal(i-i)de MAX ya que no se pude ir de la ciudad i a la i
    }

    return M1;
}

/**
 * @brief Función: Calcula la suma entre los valores minimos de cada fila
 * @param M1: es la matriz de la que se quiere obtener la suma de los minimos de cada fila
 * @return suma: representa la suma de los minimos de cada fila de la matriz M1
*/

double minimizarMatriz(double** M1){
	double min=MAX;
	double aux=0;
	double suma=0;
	bool entrado=false;//Se utiliza para que no se actualice la suma (suma+=..) en caso de que no se haya entrado en el segundo for durante toda su ejecucion

	//Minimizamos las filas...
	//Cojemos el menor de cada fila y los sumamos.
	//Nuestra funcion solo cojera valores diferentes a MAX, ya que las posiciones con este...
	//...valor son posiciones que no se tienen que explorar

	for(int i=0 ; i<N ; i++){
		min = MAX;
		entrado = false;
		for(int j=0 ; j<N ; j++){
			if(M1[i][j]!=MAX){
				entrado=true;
				aux = M1[i][j];
				if(aux<min) min = aux;
			}
		}
		if(entrado) suma+=min; 		
	}

	return suma;
}


/**
 * @brief Función: Se encarga de tachar de la matriz, para dejar solo los arcos validos para un nodo especifico, y de obtener la distancia de las iudades que ya ha visitado el nodo actual(M[][]+M[][]...)
 * @param Matriz: representa la matriz a la que se le aplica la modificacion
 * @param origen: representa EL INDICE de la ciudad de la que partimos
 * @param destino: representa EL INDICE de la ciudad de destino
 * @return suma: representa la suma de los minimos de cada fila de la matriz M1
*/
double actualizarMatrizParaNodo(double** &Matriz, int origen, int destino){
//Como son indice de la ciudad (1,2,3...) se les resta uno para poder acceder a la matrriz de distancias de manera correcta(0,1,2...)
	origen-=1;  
	destino-=1;

	double suma=0;
	suma = Matriz[origen][destino];
	Matriz[destino][origen]=MAX;//La posicion elegida tambien se rellena para no acceder mas en el recorrido
	
	for(int i=0 ; i<N ; i++){  //La fila elegida y la columna se rellenan de MAX
		Matriz[origen][i]=MAX;
		Matriz[i][destino]=MAX;
	}

	return suma;

}

/**
 * @brief Función: Se encarga de tachar de la matriz, para dejar solo los arcos validos para un nodo especifico, y de obtener la distancia de las iudades que ya ha visitado el nodo actual(M[][]+M[][]...)
 * @param Matriz: representa la matriz a la que se le aplica la modificacion
 * @param c_origen: representa EL INDICE de la ciudad de la que partimos
 * @param c_destino: representa EL INDICE de la ciudad de destino
 * @param destino: representa EL INDICE de la ciudad de destino
 * @return suma: representa el costo Minimo de la matriz
*/
double costoMatrizNodo(double** M1, vector<Ciudad> c_origen, vector<Ciudad> c_destino, int destino){
	
	double suma=0;

	double** m_aux= new double*[N];//Creamos matriz auxiliar para no modificar la principal
	for(int i=0 ; i<N ; i++)
		m_aux[i]=new double[N];

	for(int i=0 ; i<N ; i++)
		for(int j=0 ; j<N ; j++)
			m_aux[i][j] = M1[i][j]; //Le pasamos los valores


	if(c_origen.size() != 0){ //si no es el primer nodo...
		for(int i=0 ; i < c_origen.size()-1 ; i++)
			suma += actualizarMatrizParaNodo(m_aux, c_origen[i].indice, c_origen[i+1].indice);
	suma += actualizarMatrizParaNodo(m_aux, c_origen[c_origen.size()-1].indice, c_destino[destino].indice);
	}

	return suma += minimizarMatriz(m_aux); //devolvemos lo obtenido mas la suma de minimos


}

/**
 * @brief Función: Funcion principal encargada de obtener el camino con el menor coste
 * @param Matriz: representa la matriz de distancia entre ciudades
 * @param ciudadesRecogidas: vecctor que alamcena todas las ciudades
 * @param ciudadesRecorrido: vector que almacenará las ciudades en el orden del camino encontrado
*/

void TSP(double** M1, vector<Ciudad> &ciudadesRecogidas, vector<Ciudad> &ciudadesRecorrido){

	bool sigue = true;
	double costeMinimo = 999999;
	double coste = 0;
	int i_aux=0;
	int n_nodo=0;

	//durante el programa, el vector recorrido almacenara el recorrio y será desde donde se expandiran las demas ciudades. En la terminal se representa como (recorridoActual) -> (hijo), siendo el primero el vector ciudadesRecorrido y el segundo una ciudad del vector ciudadesRecogidas

	ciudadesRecorrido.push_back(ciudadesRecogidas[0]); //Paso primera ciudad a recorrido
	ciudadesRecogidas.erase(ciudadesRecogidas.begin()); //La borro de recogidas


	cout << "PRIMER NIVEL------------------------" << endl;
	while(sigue){
		sigue = false;
		costeMinimo = 999999;
		for(int i = 0 ; i < ciudadesRecogidas.size() ; i++){
			sigue = true;
			coste = costoMatrizNodo(M1, ciudadesRecorrido, ciudadesRecogidas, i);
			cout << " Coste Minimo     CAMINO DE NODOS  -->  HIJO DESPLEGADO" << endl;
			cout << "   [ " << ((int)coste) << " ]        ";
			mostrarVector(ciudadesRecorrido);
			cout << "---> ( "<< ciudadesRecogidas[i].indice << " )" << endl;
			if(coste <= costeMinimo){
				costeMinimo = coste;
				i_aux = i;
			}
	
		}
		if(sigue){
			ciudadesRecorrido.push_back(ciudadesRecogidas[i_aux]);
			ciudadesRecogidas.erase(ciudadesRecogidas.begin()+(i_aux));
			cout << "\nBAJO DE NIVEL------------------------" << endl;
		}
		

	}

	cout << "\nEl primer costo minimo es de --> {" << coste << "}" << endl;
		
}


/**
 * @brief Función: Calcula el tamaño del recorrido pasado como parametro utilizando la matriz de distancias
 * @param Matriz: representa la matriz de distancia entre ciudades
 * @param ciudadesRecorrido: vector que almacena las ciudades en el orden del camino encontrado
*/
int calcularTamanoRecorrido(double** M1, vector<Ciudad> &ciudadesRecorrido){

	int suma=0;

	for(int i=0 ; i<ciudadesRecorrido.size()-1 ; i++)
		suma+=M1[ciudadesRecorrido[i].indice-1][ciudadesRecorrido[i+1].indice-1];

	suma+=M1[ciudadesRecorrido[ciudadesRecorrido.size()-1].indice-1][ciudadesRecorrido[0].indice-1];

	return suma;

}


int main(int argc, char* argv[]){

	//IMPORTANTE: Si se comenta en el main lo indicado y se descomenta lo comentado, se procesa el ejemplo de verdegay propuesto en el pdf. Asi he comparado y he visto que da buen resultado.

	vector<Ciudad> ciudadesRecogidas;
	vector<Ciudad> ciudadesRecorrido;

	N = obtenerInfoFichero(ciudadesRecogidas, argv[1]); //comentar esto

	//N=5;						    //Descomentar
	double** matrizCiudades= new double*[N];
	for(int i=0 ; i<N ; i++)
		matrizCiudades[i]=new double[N];

	matrizCiudades = obtenerMatriz(ciudadesRecogidas);  //comentar esto
	

	//---- //Descomentar

	/*	

	for(int i=0 ; i<N ; i++){
		Ciudad nodo;
		nodo.indice = i+1;
		ciudadesRecogidas.push_back(nodo);
	}

	int adj[N][N] = {
	{MAX, 14, 4, 10, 20}, 
        {14, MAX, 7, 8, 7}, 
        {4, 5, MAX, 7, 16}, 
        {11, 7, 9, MAX, 2}, 
	{18, 7, 17, 4, MAX}};

 	for(int i=0 ; i<N ; i++)
       		for(int j=0 ; j<N ; j++)
			matrizCiudades[i][j] = adj[i][j];

	*/	

	//----

	
	cout << "MATRIZ DE DISTANCIA ENTRE CIUDADES" << endl;	
	
	for(int i=0 ; i<N ; i++){
		cout << "| ";
		for(int j=0 ; j<N ; j++){
			if(matrizCiudades[i][j] != MAX){
				cout << matrizCiudades[i][j];
				if(matrizCiudades[i][j]>9) cout << " ";
				else cout << "  ";
				
			}else{
				cout << 0 << "  ";
			}
		}
		cout << "|"<< endl;
	}
	cout << endl;

	clock_t t_antes = clock();
	TSP(matrizCiudades, ciudadesRecogidas, ciudadesRecorrido);
	clock_t t_despues = clock(); 


	cout << "El camino seguido es el siguiente: " << endl;
	
	cout << "[ ";
	for(int i=0 ; i<N ; i++)
		cout << ciudadesRecorrido[i].indice << " ";
 	cout << "]" << endl;
	
	cout << "El tamani0o del camino es el siguiente:";
	cout << calcularTamanoRecorrido(matrizCiudades, ciudadesRecorrido) << endl;

	for(int i=0 ; i<N ; i++)
		delete[] matrizCiudades[i];
	delete[] matrizCiudades;


    cout << "\nTiempo: " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << " segundos" << endl;

    return 0;
}















