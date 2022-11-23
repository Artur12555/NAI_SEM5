#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;
random_device rd;
mt19937 mt_generator(rd());
using f = function<double(pair<double, double>)>;
using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;

population_t populate(int popSize, int chromSize){
    srand(time(nullptr));
    population_t population;
    for(int i=0;i<popSize;i++){
        chromosome_t chromosome;
        for(int j=0;j<chromSize;j++){
            chromosome.push_back(rand()%2);
        }
        population.push_back(chromosome);
    }
    return population;
}

pair<double, double> mutate(chromosome_t chromosome){
    pair<double, double> result={0,0};
    bool flagax = false;
    bool flagay = false;
    if(chromosome.at(0)==1){flagax=true;}
    if(chromosome.at(1)==1){flagay=true;}
    int splitter = chromosome.size() / 2;
    int z = 1;
    int y = 10000;
    for(int i=splitter; i > 1; i--){
        result.first += (chromosome.at(i) * pow(z, 4) * sqrt(i) + z * sqrt(y));
        z++;
        if (y<2) { y++; } else {y--;};
    }
    z = 1;
    y=10000;
    for (int i = chromosome.size()-1; i > splitter; i--) {
        result.second += (chromosome.at(i) * pow(z, 4) * sqrt(i) + z * sqrt(y));
        z++;
        if (y<2) { y++; } else {y--;};
    }

    if(flagax){ result.first*=-1;}
    if(flagay){ result.second*=-1;}
    result.first = result.first/100000000;
    result.second = result.second/100000000;
    return result;
}

vector<double> fitness_function(population_t pop, f function, vector<double> domain, double goal){
    vector<double> result;
    pair <double, double> currPair;
    for (int i = 0; i < pop.size(); i++){
        currPair = mutate(pop.at(i));
        if (currPair.first > domain.at(0) && currPair.first < domain.at(1) && currPair.second > domain.at(0) && currPair.second < domain.at(1)){
            result.push_back(10000 - function(currPair));
        }
        else {
            result.push_back(0 + function(currPair));
        }
    }
    for (double p: result) {
        if(p>9000){
            cout << p << endl;
        }
    }
    return result;
}


auto genetic_algorithm = [](
        auto initial_population, auto fitness, auto term_condition,
        auto selection, double p_crossover,
        auto crossover, double p_mutation,  auto mutation, f function,
        vector<double> domain, double goal) {
    using namespace std;
    uniform_real_distribution<double> uniform(0.0,1.0);
    auto population = initial_population;
    vector<double> population_fit = fitness(population, function, domain, goal);
    while (!term_condition(population,population_fit)) {
        auto parents_indexes = selection(population_fit);
        decltype(population) new_population;
        for (int i = 0 ; i < parents_indexes.size(); i+=2) {
            decltype(initial_population) offspring = {population[i],population[i+1]};
            if (uniform(mt_generator) < p_crossover) {
                offspring = crossover(offspring);
            }
            for (auto chromosome : offspring) new_population.push_back(chromosome);
        }
        for (auto & chromosome : new_population) {
            chromosome = mutation(chromosome,p_mutation);
        }
        population = new_population;
        population_fit = fitness(population, function, domain, goal);
    }
    return population;
};
using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;

vector<int> selection_empty(std::vector<double> fitnesses) {
    uniform_real_distribution<> randomNumb(0.0,1.0);
    double R = randomNumb(mt_generator);
    double S = 0;
    double P = 0;
    double lastP = 0;
    for (double elem : fitnesses){
        S += elem;
    }
    double p = 0;
    std::vector<int> resVector;
    for (int i = 0; i < fitnesses.size(); i++) {
        p = fitnesses.at(i) / S;
        P = lastP + p;
        if(lastP <= R && lastP <= P){
            resVector.push_back(i);
        }
        lastP = P;
    }
    return resVector;
}
vector<chromosome_t > crossover_empty(std::vector<chromosome_t > parents) {
    uniform_real_distribution<double> randomPoint(0,parents.at(0).size());
    int swapPoint = randomPoint(mt_generator);
    for (int i = swapPoint; i < parents.at(0).size(); i++) {
        int temp = parents.at(0).at(i);
        parents.at(0).at(i) = parents.at(1).at(i);
        parents.at(1).at(i) = temp;
    }
    return parents;
}
chromosome_t mutation_empty(chromosome_t parent, double p_mutation) {
    uniform_real_distribution<> randomNumb(0.0,1.0);
    for (int i = 0; i < parent.size(); i++) {
        if (parent.at(i) == 0){
            parent.at(i) = 1;
        } else{
            parent.at(i) = 0;
        }
    }
    return parent;
}
int main() {
    auto beale = [](pair<double, double> xy) {
        return ((pow(1.5 - xy.first + (xy.first*xy.second), 2))+(pow((2.25 - xy.first + (xy.first*pow(xy.second,2))),2))+(pow((2.625 - xy.first + (xy.first* pow(xy.second, 3))), 2)));
    };

    population_t population = populate(10000, 100+(22984%10)*2);

    auto result = genetic_algorithm(population,
                                    fitness_function,
                                    [](auto a, auto b) {  for (auto elem: b) {
                                        if(elem >= 9999.999){
                                            cout << endl << 10000 - elem;
                                            return true;
                                        }
                                    };
                                        return false; },                                    selection_empty, 1.0,
                                    crossover_empty,
                                    0.01, mutation_empty, beale, {-4.5,4.5}, 0);
    for (chromosome_t chromosome: result) {
//        cout << "[";
//        for (int p: chromosome) {
//            cout << p;
//        }
//        cout << "] ";
    }
    cout << endl;
    return 0;


}