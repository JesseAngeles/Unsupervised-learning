#ifndef K_MEANS_H
#define K_MEANS_H

#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <iostream>

class KMeans
{
private:
    std::vector<std::vector<float>> data;
    std::vector<std::vector<float>> centroids;

    int k;

    // Functions
    void centroidUpdate(std::vector<std::vector<std::vector<float>>>);

public:
    // Cosntructor
    KMeans() = default;
    KMeans(std::vector<std::vector<float>> data, int k);

    // Functions
    void step();
    bool run(int max_iterations);
    float euclidianDistance(const std::vector<float> &a, const std::vector<float> &b);
    bool areCentroidsEqual(const std::vector<std::vector<float>> &a, const std::vector<std::vector<float>> &b, float epsilon = 1e-4);

    // Getters
    std::vector<std::vector<float>> getData() const { return data; }
    std::vector<std::vector<float>> getCentroids() const { return centroids; }
    int getK() const { return k; }

    // Setters
    void setData(std::vector<std::vector<float>> data) { this->data = data; }
    void setK(int k) { this->k = k; }

    // Prints
    void printCentroids();
};

#endif // K_MEANS_H