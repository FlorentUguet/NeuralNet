#ifndef TRAININGDATA_H
#define TRAININGDATA_H

#include <vector>
#include <iostream>

using namespace std;

struct Pass{
    std::vector<double> inputVals;
    std::vector<double> targetVals;
};

enum Type{
    DATA_XOR = 0,
    DATA_OR,
    DATA_AND
};

class TrainingData
{
public:
    TrainingData();
    void generateVals(int type, int numPasses);
    void generateReport();

    vector<Pass> getPasses() const;
    vector<unsigned> getTopology() const;

private:
    void generateXOR();
    void generateOR();
    void generateAND();

    std::vector<Pass> passes;
    std::vector<unsigned> topology;

};

#endif // TRAININGDATA_H
