#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void ordenarBidireccional(int a[], int);
int busquedaSecuOrd(int a[], int, int);
int busquedaBinaria(int a[], int, int);

int main(){
	
    srand(time(0));
    int tamanio;
    cout << "Indique la cantidad de elementos de su arreglo: ";
    cin >> tamanio;
    int arr[tamanio];
    for(int i=0; i<tamanio; i++){
        arr[i]= rand() % 100;
        cout << arr[i] << " ";	
    }
    int valor;
    cout << endl << "Indique el elemento a buscar: ";
    cin >> valor;
    cout << endl;
    int opcion;
    cout << "Elija el tipo de busqueda: " << endl;
    cout << "1) Busqueda secuencial en datos ordenados" << endl;
    cout << "2) Busqueda binaria " << endl << endl;
    cin >> opcion;
	
    cout << endl;
    ordenarBidireccional(arr, tamanio);
    
    clock_t inicio, fin;
    double duracion;

    switch(opcion){
        case 1:
            inicio = clock();
            cout << "El valor " << valor << " esta en la posicion: " << busquedaSecuOrd(arr, tamanio, valor);
            fin = clock();
            duracion = double(fin - inicio) / CLOCKS_PER_SEC;
            cout << endl << "Tiempo de ejecución (secuencial ordenada): " << duracion * 1000 << " ms (" << duracion << " s)" << endl;
            break;
            
        case 2:
            inicio = clock();
            cout << "El valor " << valor << " esta en la posicion: " << busquedaBinaria(arr, tamanio, valor);
            fin = clock();
            duracion = double(fin - inicio) / CLOCKS_PER_SEC;
            cout << endl << "Tiempo de ejecución (binaria): " << duracion * 1000 << " ms (" << duracion << " s)" << endl;
            break;
            
        default:
            cout << "No valido.";
            break;
    }
    cout << endl;
    return 0;
}

void ordenarBidireccional(int a[], int n){
	
	int izq=0;
	int der=n-1;
	int k=n;
	
	while(izq<=der){
		
		for(int i=der; i>izq; i--){
			if(a[i-1]>a[i]){
				int aux=a[i-1];
				a[i-1]=a[i];
				a[i]=aux;
				k=i;
			}
		}
		izq=k;
		
		for(int i=izq; i<der; i++){
			if(a[i-1]>a[i]){
				int aux=a[i-1];
				a[i-1]=a[i];
				a[i]=aux;
				k=i;
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
