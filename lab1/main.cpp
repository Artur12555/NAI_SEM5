#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <functional>
#include <vector>


using namespace std;
using funkcja = function<float(int x, int y)>;

void wypiszWartosci(const funkcja& func, int x, int y=0){
    cout << func(x, y) << endl;
}
// argc ilosc argumentów, **argv podwójny wskaznik na tablice + lista przekazywanych argumentów

int main(int argc, char **argv) {
    vector<string> lista(argv, argc + argv);//vector wskazuje na pierwsze ostatnie miejsce w tablicy
    map<string, funkcja> opcje; //mapa opcje klucz jako string, value funkcja, opcje zwraca float
    opcje["add"] = [](int x, int y) { return x + y; };

    opcje["mod"] = [](int x, int y) { return x % y; };

    opcje["sin"] = [](int x, int y=0) { return sin(x); };

    if (lista.at(1)=="sin") {
            wypiszWartosci(opcje[lista.at(1)], stoi(lista.at(2)));
        } else if (lista.at(1)=="add" || lista.at(1)=="mod") {
            wypiszWartosci(opcje[lista.at(1)], stoi(lista.at(2)), stoi(lista.at(3)));
        }else{
            cout << "Opcje do wyboru: add, mod, sin" << endl;
        }


    return 0;
}
