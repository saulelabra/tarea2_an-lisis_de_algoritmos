#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "BST.h"

using namespace std;

class Arreglo
{
private:
    int *arr;
    int tam;
public:
    Arreglo(){}
    Arreglo(int n) // rellena arreglo con n cantidad de enteros aleatorios
    {

        srand(time(NULL));
        tam = n;

        arr = new int[n];

        ofstream archivo;
        archivo.open("numeros.txt");

        archivo << n << endl;

        for(int i=0; i<n; i++)
        {
            arr[i] = rand()%n;
            archivo << arr[i] << endl;
            //cout << "Valor " << i << ": " << arr[i] << endl;
        }

        archivo.close();
    }

    Arreglo(string nombre) // rellena arreglo con los números del archivo, el primer elemento en el archivo determina el tamaño del arreglo
    {
        ifstream archivo;
        archivo.open(nombre);

        archivo >> tam;
        arr = new int[tam];

        for(int i=0; i<tam; i++)
        {
            archivo >> arr[i];
            //cout << "Elemento " << i << ": " << arr[i] << endl;
        }
    }

    void printArr()
    {
        for(int i=0; i<tam; i++)
        {
            cout << "Elemento " << i << ": " << arr[i] << endl;
        }
    }

    int getTam()
    {
        return tam;
    }

    void intercambio(int a, int b)
    {
        int tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }

    void bubbleSort()
    {
        for(int i=1; i<tam; i++)
        {
            for(int j=0; j<tam-1; j++)
            {
                if(arr[j] > arr[j+1])
                {
                    intercambio(j, j+1);
                }
            }
        }

        cout << endl << "Bubble sort aplicado" << endl << endl;
    }

    void cocktailSort()
    {
        bool intercambiado = false;
        do
        {
            for(int i=0; i<tam-2; i++)
            {
                if(arr[i] > arr[i+1])
                {
                    intercambio(i, i+1);
                    intercambiado = true;
                }
            }

            if(!intercambiado)
            {
                break;
            }

            intercambiado = false;

            for(int i=tam-2; i>=0; i--)
            {
                if(arr[i] > arr[i+1])
                {
                    intercambio(i, i+1);
                    intercambiado = true;
                }
            }
        }while(intercambiado == true);

        cout << endl << "Se aplicó cocktailSort" << endl << endl;
    }

    void insertionSort()
    {
        for(int i=1; i<tam; i++)
        {
            if(arr[i-1] > arr[i])
            {
                intercambio(i-1, i);
                for(int j=i-1; j>=0; j--)
                {
                    if(arr[j] < arr[j-1])
                    {
                        intercambio(j, j-1);
                    }
                }
            }
        }

        cout << endl << "insertionSort aplicado" << endl << endl;
    }

    void bucketSort()
    {
        vector<int> b[tam];

        for(int i=0; i<tam; i++)
        {
            int indice = (tam*arr[i])%tam;
            b[indice].push_back(arr[i]);
        }

        for(int i=0; i<tam; i++)
        {
            sort(b[i].begin(), b[i].end());
        }

        int indice2 = 0;
        for(int i=0; i<tam; i++)
        {
            for(int j=0; j<b[i].size(); j++)
            {
                arr[indice2++] = b[i][j];
            }
        }

        cout << endl << "Se aplico bucketSort" << endl;
    }

    void countingSort()
    {
        int k = *max_element(arr, arr+tam);
        int i, j;
        int ordenado[tam], temporal[k+1];

        for (int i=0; i<=k; i++)
            temporal[i] = 0;
        for (int j=0; j<tam; j++)
            temporal[arr[j]] = temporal[arr[j]] + 1;

        for (int i=1; i<k+1; i++)
            temporal[i] = temporal[i] + temporal[i-1];

        for (int j=tam-1; j>=0; j--)
        {
            ordenado[temporal[arr[j]]-1] = arr[j];
            temporal[arr[j]] = temporal[arr[j]] - 1;
        }
        for(int i=0; i<tam; i++)
        {
            arr[i] = ordenado[i];
        }
    }

    void merge(int lo, int mid, int hi)
    {
      int arrAux[hi+1];//se crea el arreglo auxiliar en base a los datos ingresados

      for(int i=lo; i<=hi; i++)//se copian los datos
      {
        arrAux[i] = arr[i];
      }

      int i = lo;
      int j = mid+1;
      int k = lo;

      while (i<=mid && j<=hi)//ciclo que corre mientras los apuntadores i y j estén paralelos y avancen conjuntamente
      {
        if(arrAux[i] < arrAux[j])// si el valor del lado izquierdo es menor se pasa al arreglo final
        {
          arr[k] = arrAux[i];
          k++;//se suma 1 a la posición del arreglo final
          i++;//se recorre el lado izquierdo para pasar al siguiente valor
        }
        else
        {
          arr[k] = arrAux[j];
          k++;//se suma 1 a la posición del arreglo final
          j++;//se recorre el lado derecho para pasar al siguiente valor
        }
      }

      while(i <= mid)//cuando j deja de avanzar simplemente se copian los valores restantes del lado izquierdo
      {
        arr[k] = arrAux[i];
        i++;// se recorre el lado izquierdo hasta terminar
        k++;// se suma 1 a la posición del arreglo final
      }

      while(j <= hi)// cuando i deja de avanzar, los valores restantes del lado derecho se copian
      {
        arr[k] = arrAux[j];
        j++; // se recorre el lado derecho hasta terminar
        k++; // se suma 1 a la posición del arreglo final
      }
    }

    void mergeSort(int lo, int hi)
    {
      if(hi<=lo)//a menos que hi sea menor que lo no va a salirse de la recursión
      {
        return;
      }else{
        int mid = lo + ((hi - lo)/2);//se saca el punto medio

        mergeSort(lo, mid);//se ordena la parte izquierda
        mergeSort(mid+1, hi);//se ordena la parte derecha
        merge(lo, mid, hi);//se juntan ambas partes para ser ordenadas
      }
    }

    float binaryTreeSort()
    {
      BST arbol;
      return arbol.creaYOrdena(arr, tam);
    }

    void countradix(int exp)
    {
      int ordenado[tam];
      int i, temp[10] = {0};

      for (i = 0; i < tam; i++)
          temp[ (arr[i]/exp)%10 ]++;

      for (i = 1; i < 10; i++)
          temp[i] += temp[i - 1];

      for (i = tam - 1; i >= 0; i--)
      {
          ordenado[temp[ (arr[i]/exp)%10 ] - 1] = arr[i];
          temp[ (arr[i]/exp)%10 ]--;
      }

      for (i = 0; i < tam; i++)
          arr[i] = ordenado[i];
    }

    void radixSort()
    {
      int k = *max_element(arr,arr+tam);

      for (int exp = 1; k/exp > 0; exp *= 10)
          countradix(exp);

      cout << endl << "radixSort aplicado" << endl;
    }

    void shellSort()
    {
        for (int rango = tam/2; rango > 0; rango /= 2)
        {

            for (int i = rango; i < tam; i += 1)
            {
                int temporal = arr[i];

                int j;
                for (j = i; j >= rango && arr[j - rango] > temporal; j -= rango)
                    arr[j] = arr[j - rango];

                arr[j] = temporal;
            }
        }
    }

    void SelectionSort() //método de ordenamiento selection sort
    {
        int minimo;

        for (int i=0;i<tam ; i++) //voy recorriendo todos los elementos
        {
            minimo=i; //el mínimo elemento (por el que voy a empezar)
            for (int j=i+1;j<tam; j++) //otra vez recorro todos a partir de donde empecé
            {
                if(arr[j]<arr[minimo]) //si encuentro un valor menor al que se encuentra donde empecé, guardaré ese índice
                {
                    minimo=j;

                }
            }
            intercambio(i,minimo); //al final intercambio el valor mínimo que encontré por el de mi índice
        }
    }

    void MaxHeapify(int a[], int i, int n)
    {
    	int j, temp;
    	temp = a[i];
    	j = 2*i;

     	while (j <= n)
    	{
    		if (j < n && a[j+1] > a[j])
    		j = j+1;
    		// Break if parent value is already greater than child value.
    		if (temp > a[j])
    			break;
    		// Switching value with the parent node if temp < a[j].
    		else if (temp <= a[j])
    		{
    			a[j/2] = a[j];
    			j = 2*j;
    		}
    	}
    	a[j/2] = temp;
    	return;
    }

    void HeapSort()
    {
    	Build_MaxHeap(arr, tam-1);

    	int i, temp;
    	for (i = tam; i >= 2; i--)
    	{
    		// Storing maximum value at the end.
    		temp = arr[i];
    		arr[i] = arr[1];
    		arr[1] = temp;
    		// Building max heap of remaining element.
    		MaxHeapify(arr, 1, i - 1);
    	}
    }

    void Build_MaxHeap(int a[], int n)
    {
    	int i;
    	for(i = n/2; i >= 1; i--)
    		MaxHeapify(a, i, n);
    }

    int partition(int inicio, int fin) //método de quicksort para dividir imaginariamente
    {
      int principio, final, ref; //variables para mi principio, final y pivote.


      ref = arr[inicio]; //mi pivote será el primer elemento de mi arreglo
      principio = inicio; //igualo los inicios
      final = fin; //igualo los fines


      while (principio < final) //si todavía no se cruzan
      {
        for(final;arr[final]>ref;final--); //recorro el índice del final hacia la izquierda mientras el valor de derecha sea mayor que mi referencia
       	for(principio;principio<final&&arr[principio]<=ref;principio++);  //recorro el índice del inicio a la derecha mientras mi valor sea menor que mi referencia

    	  if(principio < final) //si ya se cruzaron, ya terminé de ver hasta dónde se dividen todos los menores que mi punto y todos los mayores a este
          intercambio(principio,final); //entonces intercambio mi valor del principio con el del final porque es el último que todavía era menor
      }


      intercambio(final,inicio); //cambio de lugar mi pivote

      //La nueva posición del pivote
      return final;
    }

    void quickSort(int inicio, int fin) //método de ordenamiento QuickSort
    {
      int referencia; //este es el punto con el que voy a comparar primero (pivote)
      if(inicio < fin) //si todavía no se cruzan mis índices
      {
        referencia = partition(inicio, fin); //mando a llamar el método que divide imaginariamente para sacar la nueva referencia
        quickSort(inicio, referencia - 1 );//Ordeno la primera mitad de mi arreglo
        quickSort(referencia + 1, fin );//Ordeno la segunda mitad de mi arreglo
      }
    }
};

int main()
{
    clock_t tiempo;
    Arreglo a1(100000);
    //a1.printArr();

    tiempo = clock();
    //a1.bubbleSort();
    //a1.cocktailSort();
    //a1.insertionSort();
    a1.bucketSort();
    //a1.countingSort();
    //a1.mergeSort(0, 1000000-1);
    //cout << a1.binaryTreeSort() << "ms" << endl;
    //a1.radixSort();
    //a1.shellSort();
    //a1.SelectionSort();
    //a1.HeapSort();
    //a1.quickSort(0, 1000000-1);
    tiempo = clock() - tiempo;
    cout << endl;
    //a1.printArr();
    cout << (float(tiempo))*1000/CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
