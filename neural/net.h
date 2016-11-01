#ifndef NET_H
#define NET_H

#include <iostream>
#include <cassert>
#include <vector>
#include "neuron.h"

typedef std::vector<Neuron> Layer;


class Net
{
public:
    Net(const std::vector<unsigned> &topology);
    void feedForward(const std::vector<double> &inputVals);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector<double> &resultVals) const;

    double getRecentAverageError() const;

private:
    std::vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
    double m_error;
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
};

#endif // NET_H
