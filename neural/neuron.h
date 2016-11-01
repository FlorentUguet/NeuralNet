#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <cmath>
#include <cstdlib>

//#include "net.h"
class Neuron;
typedef std::vector<Neuron> Layer;

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val);
    double getOutputVal() const;
    void feedForward(Layer &prevLayer);

    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);

private:
    static double randomWeight();
    static double transferFunction(double x);
    static double transferFunctionDerivative(double x);
    double sumDOW(const Layer &nextLayer) const;

    double m_outputVal;
    std::vector<Connection> m_outputWeights;
    unsigned m_myIndex;
    double m_gradient;

    static double alpha; //[0.0..1.0] overall net training rate
    static double eta; //[0.0..n] multiplier of last weight charge (momentum)
};

#endif // NEURON_H
