#include "NeuronalNetwork.h"

// Constructor
NeuronalNetwork::NeuronalNetwork(std::vector<std::vector<float>> firstClass,
                                 std::vector<std::vector<float>> secondClass,
                                 Perceptron perceptron)
    : firstClass(firstClass), secondClass(secondClass), perceptron(perceptron) {}

// Functions
void NeuronalNetwork::calculate()
{

    bool isFit;
    int count = 0;
    do
    {
        isFit = true;
        for (int i = 0; i < firstClass.size(); i++)
            isFit *= perceptron.adjustmentFunction(firstClass[i], 0);

        for (int i = 0; i < secondClass.size(); i++)
            isFit *= perceptron.adjustmentFunction(secondClass[i], 1);

        if (count % 100 == 0)
            perceptron.setTrainingRate(perceptron.getTrainingRate() / 2);

    } while (!isFit && count++ < 10000);
}