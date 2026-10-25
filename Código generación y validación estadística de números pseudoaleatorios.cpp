#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

int main() {

    // --------------------------------
    // DATOS DEL CONGRUENCIAL MIXTO
    // --------------------------------
    int m = 100;
    int a = 21;
    int c = 7;
    int X0 = 13;

    int n = 100;

    vector<double> R;

    int X = X0;

    // --------------------------------
    // 1. GENERAR NUMEROS Ri
    // --------------------------------
    cout << "NUMEROS GENERADOS\n";
    cout << "-----------------\n";

    for (int i = 0; i < n; i++) {

        X = (a * X + c) % m;

        double Ri = (double) X / m;

        R.push_back(Ri);

        cout << "R[" << i + 1 << "] = "
             << fixed << setprecision(4)
             << Ri << endl;
    }

    // --------------------------------
    // 2. PRUEBA DE HUECOS
    // --------------------------------

    double alfa = 0.3;
    double beta = 0.7;

    double p = beta - alfa;

    cout << "\n\nPRUEBA DE HUECOS\n";
    cout << "----------------\n";

    cout << "Intervalo: [" << alfa
         << ", " << beta << ")\n";

    cout << "p = " << p << endl;

    // Vector para guardar los huecos
    vector<int> huecos;

    int contador = 0;
    bool primerExito = false;

    for (int i = 0; i < n; i++) {

        // Verificar si Ri pertenece al intervalo
        if (R[i] >= alfa && R[i] < beta) {

            if (primerExito) {
                huecos.push_back(contador);
            }

            primerExito = true;
            contador = 0;

        } else {

            if (primerExito) {
                contador++;
            }
        }
    }

    // --------------------------------
    // MOSTRAR HUECOS
    // --------------------------------

    cout << "\nHuecos encontrados:\n";

    for (int i = 0; i < huecos.size(); i++) {
        cout << "Hueco " << i + 1
             << " = " << huecos[i] << endl;
    }

    // --------------------------------
    // FRECUENCIA OBSERVADA
    // --------------------------------

    int frecuencia[6] = {0};

    for (int h : huecos) {

        if (h >= 0 && h <= 4) {
            frecuencia[h]++;
        } else {
            frecuencia[5]++;
        }
    }

    cout << "\nFRECUENCIAS OBSERVADAS\n";
    cout << "----------------------\n";

    cout << "Hueco 0: " << frecuencia[0] << endl;
    cout << "Hueco 1: " << frecuencia[1] << endl;
    cout << "Hueco 2: " << frecuencia[2] << endl;
    cout << "Hueco 3: " << frecuencia[3] << endl;
    cout << "Hueco 4: " << frecuencia[4] << endl;
    cout << "Hueco >=5: " << frecuencia[5] << endl;

    // --------------------------------
    // FRECUENCIA ESPERADA
    // --------------------------------

    int totalHuecos = huecos.size();

    cout << "\nFRECUENCIAS ESPERADAS\n";
    cout << "--------------------\n";

    for (int j = 0; j <= 4; j++) {

        double probabilidad =
            pow(1 - p, j) * p;

        double esperada =
            totalHuecos * probabilidad;

        cout << "Hueco " << j
             << ": " << esperada << endl;
    }

    double probabilidadMayor =
        pow(1 - p, 5);

    double esperadaMayor =
        totalHuecos * probabilidadMayor;

    cout << "Hueco >=5: "
         << esperadaMayor << endl;

    return 0;
}