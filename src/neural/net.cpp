#include "net.h"

double Net::m_recentAverageSmoothingFactor = 100.0; //Number of training samples to average over

Net::Net(const std::vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        m_layers.push_back(Layer());

        //If the next layer isn't the last (output layer), uses the number of neurons in the next layer
        unsigned numOutputs = layerNum == topology.size() -1 ? 0 : topology[layerNum +1];

        //We have made a new Layer, now fill it with neurons, and
        // add a bias neuron to the layer

        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum];++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }

        //Forces the bias node's output value to 1.0. It's the last neuron created above
        m_layers.back().back().setOutputVal(1.0);
    }
}

void Net::feedForward(const std::vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size()-1);

    //Assign the inputs
    for(unsigned i = 0; i < inputVals.size(); ++i)
    {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    //Forward propagate
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
    {
        Layer &prevLayer = m_layers[layerNum - 1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1 ; ++n)
        {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

void Net::backProp(const std::vector<double> &targetVals)
{
    // Calculate overall net error (RMS of output errors)
    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }

    m_error /= outputLayer.size() - 1; //Get average error squared
    m_error = sqrt(m_error); //RMS

    //Implement a recent average measurement :
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients
    for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    //Calculate gradientso n hidden layers
    for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
    {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum +1];

        for(unsigned n=0; n<hiddenLayer.size();++n)
        {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from output to first hidden layer,
    // update connection weights

    for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
    {
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for(unsigned n = 0; n< layer.size() - 1; ++n)
        {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::getResults(std::vector<double> &resultVals) const
{
    resultVals.clear();

    for(unsigned n = 0; n < m_layers.back().size() - 1; ++n)
    {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

double Net::getRecentAverageError() const
{
    return this->m_recentAverageError;
}
