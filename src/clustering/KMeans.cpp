#include "clustering/KMeans.h"

KMeans::KMeans(std::vector<std::vector<float>> data, int k)
    : data(data), k(k)
{
    // Inicializar centroides aleatoriamente
    centroids.resize(k);
    for (int i = 0; i < k; i++)
        centroids[i] = data[i];
}

void KMeans::step()
{
    // Arreglos auziliares
    std::vector<std::vector<std::vector<float>>> clustered_points(k);

    // Iteramos sobre todos los puntos
    for (const std::vector<float> &point : data)
    {
        // Calculamos la distancia a cada centroide
        float min_distance = std::numeric_limits<float>::max();
        int min_index = -1;
        for (int i = 0; i < k; i++)
        {
            float distance = euclidianDistance(point, centroids[i]);
            if (distance < min_distance)
            {
                min_distance = distance;
                min_index = i;
            }
        }

        clustered_points[min_index].push_back(point);
    }

    centroidUpdate(clustered_points);
}

bool KMeans::run(int max_iterations)
{
    std::vector<std::vector<float>> last_centroids = centroids;

    int count = 0;
    do
    {
        last_centroids = centroids;
        step();
    } while (++count < max_iterations && !areCentroidsEqual(last_centroids, centroids));

    return (count < max_iterations);
}

void KMeans::centroidUpdate(std::vector<std::vector<std::vector<float>>> data)
{
    for (int i = 0; i < k; i++)
    {
        if (data[i].empty())
            continue;

        std::vector<float> sum(data[i][0].size(), 0.0f);
        for (const std::vector<float> &point : data[i])
            for (int j = 0; j < point.size(); j++)
                sum[j] += point[j];

        for (int j = 0; j < sum.size(); j++)
            sum[j] /= data[i].size();

        centroids[i] = sum;
    }
}

float KMeans::euclidianDistance(const std::vector<float> &a, const std::vector<float> &b)
{
    float sum = 0.0f;
    for (int i = 0; i < a.size(); i++)
        sum += std::pow(a[i] - b[i], 2);

    return std::sqrt(sum);
}

bool KMeans::areCentroidsEqual(const std::vector<std::vector<float>> &a, const std::vector<std::vector<float>> &b, float epsilon)
{
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a[i].size(); j++)
            if (std::fabs(a[i][j] - b[i][j]) > epsilon)
                return false;

    return true;
}

void KMeans::printCentroids()
{
    std::cout << "----------------------------------\n";
    for (std::vector<float> centroid : centroids)
    {   
        std::cout << "Centroid pos: (";
        for (float dimention : centroid)
            std::cout << dimention << " ";
        std::cout << ")\n";
    }
}