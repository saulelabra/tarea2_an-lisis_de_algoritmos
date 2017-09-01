#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Nodo
{
public:
	int dato;
	Nodo *izquierdo;
	Nodo *derecho;
};

class BST
{
public:
	Nodo *raiz;

	BST()
	{
		raiz = NULL;
	}

	float creaYOrdena(int *arr, int tam)
	{
		cout << "número de elementos: " << tam << endl;

		time_t tiempo = clock();
		for (int i = 0; i<tam; i++)
		{
			//cout << "Entra al for de la inserci�n, iteraci�n: " << i << endl;
			insertarTail(raiz, arr[i]); // lama a la funci�n recursiva de inserci�n
		}
		return float(clock() - tiempo) * 1000 / CLOCKS_PER_SEC;
	}

	void insertarTail(Nodo *raiz, int numero)
	{
		//cout << "Entra a insertar Tail" << endl;
		if (raiz == NULL)
		{
			Nodo *n = new Nodo;
			n->dato = numero;
			n->izquierdo = NULL;
			n->derecho = NULL;
			raiz = n;

			//cout << "Guard� el dato " << numero << " en el �rbol" << endl;
		}
		else {
			//cout << "raiz no es NULL" << endl;
			if (numero < raiz->dato)
			{
				insertarTail(raiz->izquierdo, numero);
			}
			else {
				if (numero >= raiz->dato)
				{
					insertarTail(raiz->derecho, numero);
				}
			}
		}
	}

	void insertar(int dato)
	{
		insertarTail(raiz, dato);
	}

	void inorden(Nodo *raiz)
	{
		if (raiz == NULL)
		{
			return;
		}

		inorden(raiz->izquierdo);

		cout << raiz->dato << " - ";

		inorden(raiz->derecho);
	}

	void inordenTail(Nodo *raiz, int *arr, int i)
	{
		if (raiz == NULL)
		{
			return;
		}

		inordenTail(raiz->izquierdo, arr, i);

		arr[i] = raiz->dato;
		cout << endl << "dato transferido: " << arr[i];
		i++;

		inordenTail(raiz->derecho, arr, i);
	}
};

#endif
