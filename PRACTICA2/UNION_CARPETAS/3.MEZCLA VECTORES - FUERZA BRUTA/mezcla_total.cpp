/*

GRUPO6: Javier Ramirez Pulido, Manuel Ángel Rodríguez Segura, Alejandro Ruiz Rodríguez, Ángel Solano Corral

*****************************ALGORITMO DEL PROBLEMA PROPUESTO: FUERZA BRUTA****************************

Compilacion: g++ mezcla_total.cpp -o ejecutable
Ejecucion: ./ejecutable [nº_elementos] [nº_vectores]


EJEMPLO:
Vectores                                 
1 2 3                                           
1 2 3                                           
1 2 3                                          
          
Vector resultante ordenado:

1 1 1 2 2 2 3 3 3                                 

*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>

using namespace std;

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamaï¿½o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaï¿½o n para obtener los k vectores. Estï¿½n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un nï¿½mero uniformemente distribuido en el
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
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


int **T;
T =  new int * [k];
  assert(T);

 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
assert(aux);

srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;

//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
for (int i=0; i<k; i++) {
   int t=0;
   int m=0;
   while (m<n) {
    double u=uniforme();
    if ((N-t)*u >= (n-m)) t++;
    else {
        T[i][m]=aux[t];
	t++;
	m++;
    }
  }
}

delete [] aux;
/*
cout << "\nMATRIZ DE VECTORES" << endl;

for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}
*/

//Comienza la mezcla de vectores ordenados

/* Variables para medir el tiempo de ejecuciï¿½n */
clock_t tantes; 
clock_t tdespues;

vector<int> v_mezcla;  //Vector en el que iremos mezclando los vectores y que contendrï¿½ la mezcla final
vector<int> auxiliar;  //Vector que utilizaremos para ir mezclando los vectores de 2 en 2

int iter1, iter2; //iteradores para saber cuando llego al final de los vectores en la mezcla de 2 en 2

tantes = clock(); //empiezo a contar el tiempo

for(int i = 0; i < k; i++){  //bucle for que recorre las filas de la matriz de vectores ordenados (T)

  iter1 = 0; iter2 = 0;

  while ((iter1<n) && (iter2<auxiliar.size())) { //While que va metiendo de menor a mayor los elementos de los 2 vectores a mezclar en
    if (T[i][iter1]<auxiliar[iter2]) {
        v_mezcla.push_back(T[i][iter1]);
        iter1++;
    } else {
         v_mezcla.push_back(auxiliar[iter2]);
         iter2++;
    }
  } 
  while (iter1<k) { //While que mete los elementos que falten del vector mezcla 1
      v_mezcla.push_back(T[i][iter1]);
      iter1++;
  }
  while (iter2<auxiliar.size()) { ///While que mete los elementos que falten del vector mezcla 2
      v_mezcla.push_back(auxiliar[iter2]);
      iter2++;
  }

  if (i < k-1){       // En la Ãºltima iteraciÃ³n no ejecuto el if para no borrar el vector final

  // cout << "Version  " << i << " del vector final: " << endl;

  for (int i = 0; i < auxiliar.size(); i++)
    //cout << auxiliar[i] << " ";

    //cout << endl;

    auxiliar.clear(); // Borro el auxiliar
    auxiliar.swap(v_mezcla); // Meto el auxiliar la versiÃ³n inacabada del final para seguir mezclando con el siguiente vector de la matriz T
  }

}

tdespues = clock(); //Termino de contar el tiempo

 cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

 //cout << endl << "Tiempo de ejecucion: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

/*
cout << "\n\n-----------------VECTOR FINAL------------------" << endl; 


for (int i = 0; i < N; i++)
  cout << v_mezcla[i] << " ";

*/

}
