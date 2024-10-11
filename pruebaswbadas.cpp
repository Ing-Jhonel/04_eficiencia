#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void ordenarBidireccional(int a[], int);
int busquedaSecuOrd(int a[], int, int);
int busquedaBinaria(int a[], int, int);

int main() {
    srand(time(0));
    int tamanio, busquedas, valor;
    char aleatorio;
    cout << "Indique la cantidad de elementos de su arreglo: ";
    cin >> tamanio;
    cout << "Indique cuántas búsquedas quiere hacer: ";
    cin >> busquedas;

    bool seguir = true;
    do {
        cout << "Buscar elemento aleatorio? (s/n): ";
        cin >> aleatorio;

        if (aleatorio == 's') {
            valor = rand() % 100;
        } else if (aleatorio == 'n') {
            cout << "Indique el elemento a buscar: ";
            cin >> valor;
        } else {
            seguir = false;
        }
    } while (!seguir);

    int arr[tamanio];
    for (int i = 0; i < tamanio; i++) {
        arr[i] = rand() % 100;
    }
    ordenarBidireccional(arr, tamanio);

    int opcion;
    cout << "Elija el tipo de búsqueda: " << endl;
    cout << "1) Búsqueda secuencial en datos ordenados" << endl;
    cout << "2) Búsqueda binaria" << endl;
    cout << "= ";
    cin >> opcion;

    double tiemposBusqueda[busquedas];  // Arreglo para guardar los tiempos individuales de cada búsqueda
    clock_t inicio, fin;

    const int REPETICIONES = 10000;  // Repetir cada búsqueda varias veces

    switch (opcion) {
        case 1:
            for (int i = 0; i < busquedas; i++) {
                inicio = clock();
                for (int j = 0; j < REPETICIONES; j++) {  // Repetir la misma búsqueda
                    busquedaSecuOrd(arr, tamanio, valor);
                }
                fin = clock();
                tiemposBusqueda[i] = double(fin - inicio) * 1000 / CLOCKS_PER_SEC;  // Tiempo en ms
            }
            break;
        case 2:
            for (int i = 0; i < busquedas; i++) {
                inicio = clock();
                for (int j = 0; j < REPETICIONES; j++) {  // Repetir la misma búsqueda
                    busquedaBinaria(arr, tamanio, valor);
                }
                fin = clock();
                tiemposBusqueda[i] = double(fin - inicio) * 1000 / CLOCKS_PER_SEC;  // Tiempo en ms
            }
            break;
        default:
            cout << "No válido." << endl;
            return 0;
    }

    // Imprimir los tiempos guardados
    cout << "Tiempos de cada búsqueda (en milisegundos):" << endl;
    for (int i = 0; i < busquedas; i++) {
        cout << "Búsqueda " << i + 1 << ": " << tiemposBusqueda[i] / REPETICIONES << " ms" << endl;
    }

    return 0;
}

void ordenarBidireccional(int a[], int n) {
    int izq = 0, der = n - 1, k = n - 1;

    while (izq <= der) {
        for (int i = der; i > izq; i--) {
            if (a[i - 1] > a[i]) {
                int aux = a[i - 1];
                a[i - 1] = a[i];
                a[i] = aux;
                k = i;
            }
        }
        izq = k;

        for (int i = izq; i < der; i++) {
            if (a[i] > a[i + 1]) {
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                k = i + 1;
            }
        }
        der = k - 1;
    }
}

int busquedaSecuOrd(int a[], int n, int x) {
    int i = 0, pos;
    while (i < n && a[i] < x) {
        i++;
    }
    if (i >= n || a[i] > x) {
        pos = -i;
    } else {
        pos = i;
    }
    return pos;
}

int busquedaBinaria(int a[], int n, int x) {
    int izq = 0, der = n - 1, cen = 0, m;

    while (izq <= der && cen == 0) {
        m = (izq + der) / 2;
        if (a[m] == x) {
            cen = 1;
        } else {
            if (x > a[m]) {
                izq = m + 1;
            } else {
                der = m - 1;
            }
        }
    }
    int pos;
    if (cen == 1) {
        pos = m;
    } else {
        pos = -izq;
    }
    return pos;
}

