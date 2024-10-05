#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void ordenarBidireccional(int a[], int);
int busquedaSecuOrd(int a[], int, int);
int busquedaBinaria(int a[], int, int);

int main(){
	
    srand(time(0));
    int tamanio, busquedas, valor;
    char aleatorio;
    cout << "Indique la cantidad de elementos de su arreglo: ";
    cin >> tamanio;
    cout << "Indique cuantas busquedas quiere hacer: ";
    cin >> busquedas;
    
    bool seguir=true;
    do{
    	cout << "Buscar elemento aleatorio?(s/n): ";
	    cin >> aleatorio;
	    
	    if(aleatorio=='s'){
	    	valor=rand() % 100;
		} else if(aleatorio=='n'){
			cout << "Indique el elemento a buscar: ";
			cin >> valor;
		} else {
			seguir=false;
		}
	} while(!seguir);
	cout << endl;
    int arr[tamanio];
    
    for(int i=0; i<tamanio; i++){
        arr[i] = rand() % 100;
        //cout << arr[i] << " ";	
    }
    //cout << endl << endl << "Arreglo ordenado:" << endl << endl;
    ordenarBidireccional(arr, tamanio);
    /*
	for(int i=0; i<tamanio; i++){
        cout << arr[i] << " ";	
    } 
    cout << endl;
	*/
	
	system("cls");
    int opcion;
	double tiempoBusquedaSecuOrd[busquedas], tiempobusquedaBinaria[busquedas];
    cout << "Elija el tipo de busqueda: " << endl << endl;
    cout << "1) Busqueda secuencial en datos ordenados" << endl;
    cout << "2) Busqueda binaria " << endl << endl;
    cout << "= "; cin >> opcion;
	
    system("cls");
    switch(opcion){
        case 1:
            for(int i=0; i<busquedas; i++){
            	clock_t inicio = clock();
            	busquedaSecuOrd(arr, tamanio, valor);
            	clock_t fin = clock();
            	tiempoBusquedaSecuOrd[i]= double(fin - inicio) / CLOCKS_PER_SEC * 1000;
			}
			for(int i=0; i<busquedas; i++){
		    	cout << tiempoBusquedaSecuOrd[i] << endl;
			}
            break;
        case 2:
            for(int i=0; i<busquedas; i++){
            	clock_t inicio = clock();
            	busquedaBinaria(arr, tamanio, valor);
            	clock_t fin = clock();
            	tiempobusquedaBinaria[i]= double(fin - inicio) / CLOCKS_PER_SEC * 1000;
			}
			for(int i=0; i<busquedas; i++){
		    	cout << tiempobusquedaBinaria[i] << " ms." << endl;
			}
            break;
        default:
            cout << "No valido.";
            break;
    }
    
    return 0;
}

void ordenarBidireccional(int a[], int n){
	
	int izq=0;
	int der=n-1;
	int k=n-1;
	
	while(izq<=der){//para que ambas partes de la mitad se hallan recorrido
		for(int i=der; i>izq; i--){ //  |izq=0			n=der|
			if(a[i-1]>a[i]){
				int aux=a[i-1];
				a[i-1]=a[i];
				a[i]=aux;
				k=i; //cantidad de elementos ordenados en la izq
			}
		}
		izq=k;
		
		for(int i=izq; i<der; i++){ //  |izq=0			n=der|
			if (a[i] > a[i + 1]) {
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                k = i + 1;  // Actualiza k a la última posición de intercambio
            }
        }
		der=k-1;
	}
}

int busquedaSecuOrd(int a[], int n, int x){
	
	int i=0, pos;
	while(i<n && a[i]<x){
		i++;
	}
	if(i>=n || a[i]>x){
		pos=-i;
	} else {
		pos=i;
	}
	return pos;
}

int busquedaBinaria(int a[], int n, int x) {
	
    int izq=0, der=n-1, cen=0, m;  

    while (izq<=der && cen==0) {
        m=(izq+der)/2;
        if(a[m]==x) {
            cen=1;
        } else {
            if (x>a[m]) {
                izq=m+1;
            } else {
                der=m-1;
            }
        }
    }
    int pos;
    if(cen==1) {
	 	pos=m;
    } else {
        pos=-izq;
    }
    return pos;
}
