#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <functional>
#include <vector>


using namespace std;
using funkcja = std::function<double(std::vector<double>)>;

void wypiszWartosci(std::vector<double> numbers, funkcja fun) {
    using namespace std;
    cout << fun(numbers) << endl;
}
// argc ilosc argumentów, **argv podwójny wskaznik na tablice + lista przekazywanych argumentów

int main(int argc, char **argv) {
    vector<string> lista(argv, argc + argv);//vector wskazuje na pierwsze ostatnie miejsce w tablicy
    map<string, funkcja> opcje; //mapa opcje klucz jako string, value funkcja, opcje zwraca float
    opcje["mod"] = [](vector<double> numbers) { return (int)numbers.front() % (int)numbers.back();};

    opcje["add"] = [](vector<double> numbers) { return  numbers.front() + numbers.back();};

    opcje["sin"] = [](vector<double> numbers) { return sin(numbers.front());};

    try {
        vector<string> arguments(argv, argv + argc);
        auto selected_f = arguments.at(1);

        vector<double> numbers = {{stod(arguments.at(2)), stod(arguments.back())}};
        wypiszWartosci(numbers, opcje.at(selected_f));
    } catch (std::out_of_range aor) {
        cout << "Źle, dostępne opcje: : ";
        for (auto [k, v] : opcje) cout << " " << k;
        cout << endl;
        return 1;
    }

    return 0;
}
