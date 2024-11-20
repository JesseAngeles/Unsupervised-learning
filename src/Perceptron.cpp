#include "Perceptron.h"

Perceptron::Perceptron(std::vector<float> weights, float training_rate)
    : weights(weights), training_rate(training_rate) {}

// Public functions
bool Perceptron::adjustmentFunction(std::vector<float> input_layer, bool cls)
{
    input_layer.push_back(1);
    float exit_func = exitFunction(input_layer);

    // Mala clasificacion
    if ((!cls && exit_func >= 0) || (cls && exit_func <= 0))
    {
        adjust(input_layer, cls);
        return false;
    }
    return true;
}

// Private functions

float Perceptron::exitFunction(std::vector<float> input_layer)
{
    float exit = 0;
    for (int i = 0; i < input_layer.size(); i++)
        exit += weights[i] * input_layer[i];

    return exit;
}

void Perceptron::adjust(std::vector<float> input_layer, bool cls)
{
    float num = (!cls ? -training_rate : training_rate);
    for (int i = 0; i < weights.size(); i++)
        weights[i] += num * input_layer[i];
}
