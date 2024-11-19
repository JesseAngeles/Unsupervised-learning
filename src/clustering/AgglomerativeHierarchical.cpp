#include "clustering/AgglomerativeHierarchical.h"

AgglomerativeHierarchical::AgglomerativeHierarchical(std::vector<std::vector<float>> data)
    : data(data)
{
    clusters.resize(data.size());
    for (int i = 0; i < data.size(); i++)
        clusters[i].push_back(data[i]);
}

void AgglomerativeHierarchical::step()
{
    float min_distance = std::numeric_limits<float>::max();
    int index_a = -1;
    int index_b = -1;

    // Encontrar los clusters más cercanos
    for (int i = 0; i < clusters.size() - 1; i++)
        for (int j = i + 1; j < clusters.size(); j++)
            for (std::vector<float> point_a : clusters[i])
                for (std::vector<float> point_b : clusters[j])
                {
                    float distance = euclidianDistance(point_a, point_b);
                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        index_a = i;
                        index_b = j;
                    }
                }

    // Fusionar clusters
    if (index_a != -1 && index_b != -1)
    {
        std::vector<std::vector<float>> new_cluster = clusters[index_a];
        new_cluster.insert(new_cluster.end(), clusters[index_b].begin(), clusters[index_b].end());

        if (index_a > index_b)
            std::swap(index_a, index_b);

        clusters.erase(clusters.begin() + index_b);
        clusters.erase(clusters.begin() + index_a);
        clusters.push_back(new_cluster);
    }
}


float AgglomerativeHierarchical::euclidianDistance(const std::vector<float> &a, const std::vector<float> &b)
{
    float sum = 0.0f;
    for (int i = 0; i < a.size(); i++)
        sum += std::pow(a[i] - b[i], 2);

    return std::sqrt(sum);
}

void AgglomerativeHierarchical::printClusters()
{
    for (std::vector<std::vector<float>> cluster : clusters)
    {
        for (std::vector<float> point : cluster)
        {
            for (float dimention : point)
            {
                std::cout << dimention << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

bool AgglomerativeHierarchical::arePointsEqual(const std::vector<float> &a, const std::vector<float> &b, float epsilon)
{
    if (a.empty() || b.empty())
    {
        std::cerr << "Error: Empty vector encountered in arePointsEqual.\n";
        return false;
    }

    if (a.size() != b.size())
    {
        std::cerr << "Error: Vectors of different sizes in arePointsEqual.\n";
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        if (std::abs(a[i] - b[i]) > epsilon)
            return false;
    }
    return true;
}