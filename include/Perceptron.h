#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <cmath>

class Perceptron
{
private:
    // Atributes
    std::vector<float> weights;
    float training_rate;
    
    // Functions
    float exitFunction(std::vector<float> input_layer);
    void adjust(std::vector<float> input_layer, bool cls);

public:
    // Constructor
    Perceptron(std::vector<float> weights, float training_rate);

    // Functions
    bool adjustmentFunction(std::vector<float> input_layer, bool cls);

    // Getters
    std::vector<float> getWeights() const { return weights; }
    float getTrainingRate() const { return training_rate; }

    // Setters
    void setWeights(std::vector<float> weights) { this->weights = weights; }
    void setTrainingRate(float training_rate) { this->training_rate = training_rate; }
};

#endif // PERCEPTRON_H