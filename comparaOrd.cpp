#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void ordenarBidireccional(int a[], int);
int busquedaSecuOrd(int a[], int, int);
int busquedaBinaria(int a[], int, int);


struct Tiempo{
	double busquedaSecuOrd, busquedaBinaria;
};

double tiempoPromedioMetodoBusqueda(Tiempo a[], int, bool);

void crearArregloAleatorio(int a[], int);
void imprimirArreglo(int a[], int);

int main(){
	
    srand(time(0));
    int tamanio, busquedas;
    char aleatorio;
    cout << "Indique la cantidad de elementos de su arreglo: ";
    cin >> tamanio;
    cout << "Indique cuantas busquedas quiere hacer: ";
    cin >> busquedas;
    Tiempo tiempo[busquedas];
    int valor[busquedas], valor1;
    bool seguir=true, valorPorBusqueda=true;
    do{
    	cout << "Buscar elemento aleatorio por busqueda?(s/n): ";
	    cin >> aleatorio;
	    
		if(aleatorio== 'n'){
			valor1=rand() % 100;
			valorPorBusqueda=false; //no crear valor de busqueda aleatorio por busqueda
		} else if(aleatorio== 's'){
			seguir=true;
		} else {
			seguir=false;
		}
	} while(!seguir);
	cout << endl;
    int arr[tamanio];
    
    /*
    for(int i=0; i<tamanio; i++){
        arr[i] = rand() % 100;
        //cout << arr[i] << " ";	
    }
    */
    //cout << endl << endl << "Arreglo ordenado:" << endl << endl;
    /*
	for(int i=0; i<tamanio; i++){
        cout << arr[i] << " ";	
    } 
    cout << endl;
	*/
	system("cls");
	
	bool encontrado=false;
	int posicion;
	clock_t inicio, fin;
	int REPETICIONES=50000;
	
	if(valorPorBusqueda){
		for(int i=0; i<busquedas; i++){
	    	valor[i]=rand() % 100; //si antes se eligio por cada busqueda crear un elemento a buscar aleatoriament, se crea
		}
	}
	
    for(int i=0; i<busquedas; i++){ //cantidad de busquedas
    	
    	crearArregloAleatorio(arr, tamanio); 	//crea un arreglo aleatorio por cada busqueda o iteracion de busqueda
	    ordenarBidireccional(arr, tamanio);		//ordena el arreglo anterior creado aleatoriamente
    	cout << endl << endl << i+1 << "| "; imprimirArreglo(arr, tamanio); cout << endl << endl;
	    
        inicio = clock();
        for(int j=0; j<REPETICIONES; j++){
        	if(valorPorBusqueda){
        		posicion=busquedaSecuOrd(arr, tamanio, valor[i]);
			} else{
				posicion=busquedaSecuOrd(arr, tamanio, valor1);
			}
		}
		fin = clock();
		
		if(posicion>=0){
			encontrado=true;
		}
		if(encontrado){
			tiempo[i].busquedaSecuOrd= (double(fin - inicio)* 1000 / CLOCKS_PER_SEC)/REPETICIONES;
		} else {
			tiempo[i].busquedaSecuOrd=-1;
		}
	}
			
    for(int i=0; i<busquedas; i++){
    	
    	crearArregloAleatorio(arr, tamanio);
	    ordenarBidireccional(arr, tamanio);
    	cout << endl << endl << i+1 << "| "; imprimirArreglo(arr, tamanio); cout << endl << endl;
	    
        inicio = clock();
        for(int j=0; j<REPETICIONES; j++){
        	if(valorPorBusqueda){
        		posicion=busquedaBinaria(arr, tamanio, valor[i]);
			} else{
				posicion=busquedaBinaria(arr, tamanio, valor1);
			}
		}
        fin = clock();
        if(posicion>=0){
			encontrado=true;
		}
		if(encontrado){
			tiempo[i].busquedaBinaria= (double(fin - inicio)* 1000 / CLOCKS_PER_SEC)/REPETICIONES;
		} else {
			tiempo[i].busquedaBinaria=-1;
		}
	}
	
	cout << "\t\tTIEMPO POR BUSQUEDA POR METODO DE BUSQUEDA ORDENADA" << endl << endl;
	if(valorPorBusqueda){
		cout << "\t\t\tElemento a buscar: Por busqueda" << endl;
	} else {
		cout << "\t\t\tElemento a buscar: " << valor1 << endl;
	}
	cout << "\t\t\tDatos: " << tamanio << endl
		<< "\t\t\tBusquedas: " << busquedas << endl << endl;
	cout << "\tBusqueda Secuncial Ordenada\t\tBusqueda Binaria" << endl << endl;
	
	if(valorPorBusqueda){
		for(int i=0; i<busquedas; i++){
			cout << "(" << valor[i] << ") Busqueda "<< i+1 << " -> \t\t" << tiempo[i].busquedaSecuOrd << " ms.\t\t\t\t" << tiempo[i].busquedaBinaria << " ms." << endl;
		}
	} else{
		for(int i=0; i<busquedas; i++){
			cout << "Busqueda "<< i+1 << " -> \t\t" << tiempo[i].busquedaSecuOrd << " ms.\t\t\t\t" << tiempo[i].busquedaBinaria << " ms." << endl;
		}
	}
	cout << endl << endl << "\t\tPromedio = " << tiempoPromedioMetodoBusqueda(tiempo, busquedas, true) << "\t\t\t  Promedio = " << tiempoPromedioMetodoBusqueda(tiempo, busquedas, false) << endl;
    return 0;
}

void imprimirArreglo(int a[], int n){
	for(int i=0; i<n; i++){
		cout << a[i] << " ";
	}
}
void crearArregloAleatorio(int a[], int n){
	
	for(int i=0; i<n; i++){
	    a[i] = rand() % 100;
	}
}

double tiempoPromedioMetodoBusqueda(Tiempo a[], int n, bool metodoBusqueda) {
    double suma = 0;
    for(int i = 0; i < n; i++) {
        if(metodoBusqueda) {
            suma += a[i].busquedaSecuOrd;  // Acceso al miembro de cada estructura
        } else {
            suma += a[i].busquedaBinaria;  // Acceso al miembro de cada estructura
        }
    }
    return suma / n;
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
