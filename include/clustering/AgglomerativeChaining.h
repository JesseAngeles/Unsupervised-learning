#ifndef AGGLOMERATIVE_CHAINING_H
#define AGGLOMERATIVE_CHAINING_H

#include <vector>
#include <cmath>
#include <iostream>

class AgglomerativeChaining
{
private:
    std::vector<std::vector<float>> data;
    std::vector<std::vector<float>> clusters;
    float threshold;

    std::vector<float> mean(const std::vector<std::vector<float>> &data);

public:
    // Constructor
    AgglomerativeChaining(std::vector<std::vector<float>> data, float threshold);

    // Functions
    void step();

    float euclidianDistance(const std::vector<float> &a, const std::vector<float> &b);
    bool areCentroidsEqual(const std::vector<std::vector<float>> &a, const std::vector<std::vector<float>> &b, float epsilon = 1e-4);

    // Getters
    std::vector<std::vector<float>> getData() const { return data; }
    std::vector<std::vector<float>> getClusters() const { return clusters; }
    float getThreshold() const { return threshold; }

    // Setters
    void setData(std::vector<std::vector<float>> data) { this->data = data; }
    void setThreshold(float threshold) { this->threshold = threshold; }

    // Prints
    void printClusters()
    {
        std::cout << "\n";
        for (std::vector<float> point : clusters)
        {
            for (float dimention : point)
                std::cout << dimention << " ";
            std::cout << "\n";
        }
    }
};

#endif // AGGLOMERATIVE_CHAINING_H