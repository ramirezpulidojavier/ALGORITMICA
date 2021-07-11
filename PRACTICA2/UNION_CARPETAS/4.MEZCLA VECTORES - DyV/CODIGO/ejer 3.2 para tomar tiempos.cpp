#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tamanio k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores. Están ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}



// Funcion que une los vectores procedentes de la union recursiva en uno final con todos los valores
// y llama a quicksort para ordenarlo
void unionFinal (int *&array1, int *&array2, int start, int end, int end2){

    int tam = end+end2; //el tamanio sera la suma del tamanio de cada vector
    int *array = new int [tam]; // se reserva memoria para un array con dimension tam
	int contadorarray = 0 ;
    int contador1 = 0 ; // se inicializa un contador
	int contador2 = 0 ; // se inicializa otro contador

	while( (contador1 + contador2) < tam){
		if(contador1!=end && contador2!=end2){
			
			if(array1[contador1] > array2[contador2]){
			
			array[contadorarray] = array2[contador2];
			contador2++;
			contadorarray++;
			
			}
			else{
				if(array1[contador1] <= array2[contador2]){
					
					array[contadorarray] = array1[contador1];
					contador1++;
					contadorarray++;
					
				}
				
			}	
			
		}
		else if(contador1 == end){
			array[contadorarray] = array2[contador2];
			contador2++;
			contadorarray++;
		}
		else{
			
			array[contadorarray] = array1[contador1];
			contador1++;
			contadorarray++;
			
		}
		
	}

    array1 = array2 = array; //se igualan los punteros de array1 y array2 con array para que tengan ambos el vector final unido


}

// Funcion que une los vectores de la matriz de vectores ordenados de forma recursiva
void uneVectores(int **matriz, int primerafila, int ultimafila, int *&tamanios, int &util){


  if(primerafila < ultimafila){


  int filadelmedio = (primerafila + ultimafila)/2;

  uneVectores(matriz,primerafila,filadelmedio, tamanios, util);


  uneVectores(matriz,filadelmedio+1, ultimafila, tamanios, util);


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

  unionFinal(matriz[primerafila],matriz[ultimafila],0,tamanios[primerafila],tamanios[ultimafila]);

  tamanios[primerafila] += tamanios[ultimafila];
  tamanios[ultimafila] = tamanios[primerafila];

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

 }



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
  int N=k*n;

int **T;
T =  new int * [k];
  assert(T);


 for (int i = 0; i < k; i++)
      T[i]= new int [N];


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


int *tamanios = new int [k];
int util = 0;
for(util  = 0 ; util < k ; util++)
    tamanios[util] = n ;


/*
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

*/

clock_t t_antes = clock();

uneVectores(T, 0, k-1, tamanios, util);

clock_t t_despues = clock();

cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

delete [] aux;

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

/*
cout <<"---------------------------------------"<<endl;
cout << "***********RESULTADO FINAL***********"  << endl ;
cout <<"---------------------------------------"<<endl;
cout<<"La mezcla final y ordenada es: ";
for (int i=0; i<N; i++)
    cout << T[0][i] << " ";

cout << endl ;
*/

delete [] tamanios;

}
  
