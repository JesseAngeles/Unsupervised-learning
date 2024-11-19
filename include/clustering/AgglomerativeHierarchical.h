#ifndef AGGLOMERATIVE_HERARCHICAL_H
#define AGGLOMERATIVE_HERARCHICAL_H

#include <vector>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <iostream>

class AgglomerativeHierarchical
{
private:
    std::vector<std::vector<float>> data;
    std::vector<std::vector<std::vector<float>>> clusters;

public:
    // Constructor
    AgglomerativeHierarchical(std::vector<std::vector<float>> data);

    // Functions
    void step();
    bool run(int max_iterations);
    float euclidianDistance(const std::vector<float> &a, const std::vector<float> &b);
    bool arePointsEqual(const std::vector<float> &a, const std::vector<float> &b, float epsilon = 2);

    // Getters
    std::vector<std::vector<float>> getData() const { return data; }
    std::vector<std::vector<std::vector<float>>> getClusters() const { return clusters; }

    // Setters
    void setData(std::vector<std::vector<float>> data) { this->data = data; }

    // Prints
    void printClusters();
};

#endif // AGGLOMERATIVE_HERARCHICAL_H