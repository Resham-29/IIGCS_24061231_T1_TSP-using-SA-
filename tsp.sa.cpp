 #include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;


struct City {
    int id;
    double x, y;
};


double distance(const City& a, const City& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


double totalCost(const vector<City>& cities, const vector<int>& path) {
    double cost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cost += distance(cities[path[i]], cities[path[i + 1]]);
    }
    
    cost += distance(cities[path.back()], cities[path[0]]);
    return cost;
}

eneration)
void swapCities(vector<int>& path) {
    int i = rand() % path.size();
    int j = rand() % path.size();
    while (i == j) {
        j = rand() % path.size();
    }
    swap(path[i], path[j]);
}


vector<int> simulatedAnnealing(const vector<City>& cities, double initialTemp, double coolingRate, int maxIterations) {
    
    vector<int> currentPath(cities.size());
    for (int i = 0; i < cities.size(); ++i) currentPath[i] = i;
    random_shuffle(currentPath.begin(), currentPath.end());

    double currentCost = totalCost(cities, currentPath);
    vector<int> bestPath = currentPath;
    double bestCost = currentCost;

    double temperature = initialTemp;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        
        vector<int> newPath = currentPath;
        swapCities(newPath);
        double newCost = totalCost(cities, newPath);

       
        if (newCost < currentCost) {
            currentPath = newPath;
            currentCost = newCost;
        } else {
            
            double acceptanceProbability = exp((currentCost - newCost) / temperature);
            if (((double)rand() / RAND_MAX) < acceptanceProbability) {
                currentPath = newPath;
                currentCost = newCost;
            }
        }

       
        if (currentCost < bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }

       
        temperature *= coolingRate;
    }

    cout << "Final cost: " << bestCost << endl;
    return bestPath;
}


vector<City> readCities(const string& filename) {
    vector<City> cities;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file!" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line == "EOF") break;  
        int id;
        double x, y;
        if (sscanf(line.c_str(), "%d %lf %lf", &id, &x, &y) == 3) {
            cities.push_back({id, x, y});
        }
    }
    file.close();
    return cities;
}

int main() {
    srand(time(0));

    
    string filename = "xqf131.tsp";
    vector<City> cities = readCities(filename);

    
    double initialTemp = 10000.0;
    double coolingRate = 0.999;
    int maxIterations = 10000;

    
    vector<int> bestPath = simulatedAnnealing(cities, initialTemp, coolingRate, maxIterations);

   
    cout << "Best path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}