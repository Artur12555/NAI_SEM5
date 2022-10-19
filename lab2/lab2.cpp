#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <math.h>

using namespace std;
using f = function<double(double, double)>;
random_device rd;
mt19937 mt_generator(rd());

void print(vector<double> arguments){
    cout  << "x: " << arguments.at(0)<<endl;
    cout  << "y: " << arguments.at(1)<<endl;

}

auto findLowest(f function, vector<double> domain, int max_iterations) {
    uniform_real_distribution<double> dist(domain.at(0), domain.at(1));
    double lowest = function(domain.at(0), domain.at(1));
    vector<double> res;
    for (int i = 0; i < max_iterations; i++) {

        double r1 = dist(mt_generator);
        double r2 = dist(mt_generator);
        double temp = function(r1, r2);
        if (temp < lowest) {
            lowest = temp;
            res = {r1,r2};

        }
    }
    return res;
}

int main() {

//    auto himmelblau = [](double x, double y) {
//        return ((pow((pow(x,2)+y+11),2))+(x+ pow(y, 2)-7));
//    };

    auto threehumpCamel = [](double x, double y) {
        return ((2 * pow(x,2)) - (1.05 * pow(x,4)) + ((pow(x,6))/6) + (x*y) + (pow(y,2)));
    };

    auto beale = [](double x, double y) {
        return ((pow(1.5 - x + (x*y), 2))+(pow((2.25 - x + (x*pow(y,2))),2))+(pow((2.625 - x + (x* pow(y, 3))), 2)));
    };

    auto matyas = [](double x, double y) {
        return ((0.26*(pow(x, 2) + pow(y, 2))) - (0.48 * x * y));
    };

//    auto goldsteinPrice = [](double x, double y) {
//        return (((1 + (pow((x + y + 1),2))) * (19 - (14*x) + (3 * (pow(x,2))) - (14*y) + (6*x*y) + (3 * (pow(y,2))))) *
//        (30 + ((pow(((2*x) - (3*y)),2)) * (18-(32*x) + (12*(pow(x,2))) + (48*y) - (36*x*y) + (27 * pow(y,2))))));
//    };

//    cout<<"Lowest Himmelblau's function is:    "<< findLowest(himmelblau, {-5.0, 5.0},10000)<<endl;

    cout << "Lowest Three-hump camel function is:" << endl;
    print(findLowest(threehumpCamel, {-5.0, 5.0}, 10000));
    cout << "\nLowest Beale function is:" << endl;
    print(findLowest(beale, {-4.5, 4.5}, 10000));
    cout << "\nLowest Matyas function is:" << endl;
    print(findLowest(matyas, {-4.5, 4.5}, 10000));

//    cout<<"GoldsteinPrice                           : "<< findLowest(goldsteinPrice, {-2.0, 2.0},10000)<<endl;
    return 0;
}