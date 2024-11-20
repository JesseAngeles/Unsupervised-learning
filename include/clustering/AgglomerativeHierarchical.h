#ifndef AGGLOMERATIVE_HERARCHICAL_H
#define AGGLOMERATIVE_HERARCHICAL_H

#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <random>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <string>

struct VectorCompare
{
    bool operator()(const std::vector<float> &a, const std::vector<float> &b) const
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
};

class AgglomerativeHierarchical
{
private:
    std::vector<std::vector<float>> data;
    std::vector<std::set<std::vector<float>, VectorCompare>> clusters;
    std::vector<std::tuple<int, int, float, int>> linkage_matrix;
    std::vector<int> cluster_sizes;

public:
    // Constructor
    AgglomerativeHierarchical(std::vector<std::vector<float>> data);

    // Functions
    void step();
    bool run(int max_iterations);
    float euclidianDistance(const std::vector<float> &a, const std::vector<float> &b);
    bool arePointsEqual(const std::vector<float> &a, const std::vector<float> &b, float epsilon = 2);
    void saveLinkageMatrixToCSV(const std::string &filename);
    // Getters
    std::vector<std::vector<float>> getData() const { return data; }
    std::vector<std::set<std::vector<float>, VectorCompare>> getClusters() const { return clusters; }
    const std::vector<std::tuple<int, int, float, int>>& getLinkageMatrix() const;

    // Setters
    void setData(std::vector<std::vector<float>> data) { this->data = data; }

    // Prints
    void printClusters();
};

#endif // AGGLOMERATIVE_HERARCHICAL_H