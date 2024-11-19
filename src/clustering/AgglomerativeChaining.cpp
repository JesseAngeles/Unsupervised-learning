#include "clustering/AgglomerativeChaining.h"

AgglomerativeChaining::AgglomerativeChaining(std::vector<std::vector<float>> data, float threshold)
    : data(data), threshold(threshold)
{
    if (!data.empty())
        clusters.push_back(data[0]); // Inicializar con el primer dato
}

void AgglomerativeChaining::step()
{
    std::vector<std::vector<std::vector<float>>> clustered_points(clusters.size());

    // Iterar los puntos
    for (const std::vector<float> &point : data)
    {
        // Iterar los clusters
        float min_distance = threshold;
        int min_index = -1;
        for (int i = 0; i < clusters.size(); i++)
        {
            float distance = euclidianDistance(point, clusters[i]);
            if (distance <= min_distance)
            {
                min_distance = distance;
                min_index = i;
            }
        }

        // Si pertenece a un cluster
        if (min_index != -1)
        {
            clustered_points[min_index].push_back(point);
        }
        else // Crear un nuevo cluster
        {
            clusters.push_back(point);
            clustered_points.push_back({point});
        }
    }

    // Ajustar centroides
    std::vector<std::vector<float>> new_clusters;
    for (int i = 0; i < clusters.size(); i++)
        if (!clustered_points[i].empty())
            new_clusters.push_back(mean(clustered_points[i]));

    // Reemplazar clusters con los actualizados
    clusters = new_clusters;
}

std::vector<float> AgglomerativeChaining::mean(const std::vector<std::vector<float>> &data)
{
    std::vector<float> sum(data[0].size(), 0.0f);

    for (const std::vector<float> &point : data)
        for (int i = 0; i < point.size(); i++)
            sum[i] += point[i];

    for (float &dimension : sum)
        dimension /= data.size();

    return sum;
}

float AgglomerativeChaining::euclidianDistance(const std::vector<float> &a, const std::vector<float> &b)
{
    float sum = 0.0f;
    for (int i = 0; i < a.size(); i++)
        sum += std::pow(a[i] - b[i], 2);

    return std::sqrt(sum);
}

bool AgglomerativeChaining::areCentroidsEqual(const std::vector<std::vector<float>> &a, const std::vector<std::vector<float>> &b, float epsilon)
{
    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a[i].size(); j++)
            if (std::fabs(a[i][j] - b[i][j]) > epsilon)
                return false;

    return true;
}
