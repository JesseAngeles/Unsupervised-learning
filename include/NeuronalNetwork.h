#ifndef NEURONAL_NETWORK_H
#define NEURONAL_NETWORK_H

#include <vector>

#include "Perceptron.h"

class NeuronalNetwork
{
private:
    std::vector<std::vector<float>> firstClass;
    std::vector<std::vector<float>> secondClass;
    Perceptron perceptron;

public:
    // Constructor
    NeuronalNetwork(std::vector<std::vector<float>> firstClass, std::vector<std::vector<float>> secondClass, Perceptron);

    // Functions
    void calculate();

    // Getters
    std::vector<std::vector<float>> getFirstClass() const { return firstClass; }
    std::vector<std::vector<float>> getSecondClass() const { return secondClass; }
    Perceptron getPerceptron() const { return perceptron; }

    // Setters
    void setFirtsClass(std::vector<std::vector<float>> firstClass) { this->firstClass = firstClass; }
    void setSecondClass(std::vector<std::vector<float>> secondClass) { this->secondClass = secondClass; }
};

#endif // NEURONAL_NETWORK_H