#include <iostream>
#include <iomanip>
#include <fstream>
#include "Hora.h"
#include<vector>
using namespace std;
// El coste del algoritmo es logaritmico en v.size() (busqueda binaria)
void resolver(const vector<Hora>& v, Hora const& h, Hora& out, int c, int f) {
    // CB: Un elemento
    if (c == f) {
        if (h < v[c] || h == v[c]) out = v[c];
    }
    // CB: Dos elementos
    else if (c == f - 1) {
        if (h < v[c] || h == v[c]) out = v[c];
        else if (h < v[f] || h == v[f]) out = v[f];
    }
    // CR
    else {
        int m = (c + f) / 2;
        (v[m] < h ? resolver(v, h, out, m + 1, f)
            : resolver(v, h, out, 0, m));
    }
}
// El coste del algorimto es lineal en v.size() == trenes
pair<bool, Hora> resolver(const vector<Hora>& v, const Hora& hora, int trenes) {
    int i = 0; bool exit = false;
    pair<bool, Hora> ret = { false, Hora() };
    while (i < trenes && !exit) {
        if (hora < v[i] || hora == v[i]) {
            ret.first = true;
            ret.second = v[i];
            exit = true;
        }
        i++;
    }
    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int trenes, horas; cin >> trenes >> horas;
    if (trenes == 0 && horas == 0) return false;
    vector<Hora>v(trenes);
    for (int i = 0; i < trenes; i++)
        cin >> v[i];
    for (int i = 0; i < horas; i++) {
        try {
            Hora hora, sol, aux; cin >> hora;
            resolver(v, hora, sol, 0, trenes - 1);
            if (!(sol == aux)) cout << sol << "\n";
            else cout << "NO\n";
            //pair<bool, Hora> sol = resolver(v, hora, trenes);
            //if (sol.first) cout << sol.second << "\n";
            //else cout << "NO\n";
        }
        catch (Error e) { cout << e.getMsg() << "\n"; }
    }
    cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
