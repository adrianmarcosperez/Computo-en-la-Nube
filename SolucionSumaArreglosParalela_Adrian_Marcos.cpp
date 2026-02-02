#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {

    // Tamaño del arreglo
    const int n = 1000;

    // Declaración de arreglos
    int A[n], B[n], R[n];

    // Semilla para valores aleatorios
    srand(time(0));

    // ===============================
    // 1. Llenar arreglos con valores aleatorios
    // ===============================
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    cout << "Arreglos generados correctamente.\n";

    // ===============================
    // 2. Forzar uso de múltiples hilos
    // ===============================
    cout << "\nNumero maximo de hilos disponibles: "
        << omp_get_max_threads() << endl;

    // Forzar que se usen 4 hilos
    omp_set_num_threads(4);

    cout << "Numero de hilos forzados: 4\n";

    // ===============================
    // 3. Mostrar hilos activos
    // ===============================
    cout << "\nHilos activos:\n";

#pragma omp parallel num_threads(4)
    {
        int hilo = omp_get_thread_num();
        int total = omp_get_num_threads();

#pragma omp critical
        {
            cout << "Hola, soy el hilo " << hilo
                << " de un total de " << total << endl;
        }
    }

    // ===============================
    // 4. Suma paralela con OpenMP
    // ===============================
    cout << "\nSuma paralela en proceso...\n\n";

#pragma omp parallel for schedule(static,1) num_threads(4)
    for (int i = 0; i < n; i++) {

        int hilo = omp_get_thread_num();

        // Suma elemento a elemento
        R[i] = A[i] + B[i];

        // Mostrar evidencia solo en algunos índices
        if (i % 250 == 0) {

            // Sección crítica para que no se mezcle la salida
#pragma omp critical
            {
                cout << "Hilo " << hilo
                    << " sumo el indice " << i
                    << " -> " << A[i] << " + " << B[i]
                    << " = " << R[i] << endl;
            }
        }
    }

    cout << "\nSuma paralela realizada correctamente.\n";

    // ===============================
    // 5. Imprimir primeros 10 elementos para comprobar
    // ===============================
    cout << "\nPrimeros 10 elementos del resultado:\n";

    cout << "\nA: ";
    for (int i = 0; i < 10; i++)
        cout << A[i] << " ";

    cout << "\nB: ";
    for (int i = 0; i < 10; i++)
        cout << B[i] << " ";

    cout << "\nR: ";
    for (int i = 0; i < 10; i++)
        cout << R[i] << " ";

    cout << "\n\nProceso terminado correctamente.\n";

    return 0;
}