#include "trainingdata.h"

TrainingData::TrainingData()
{

}

void TrainingData::generateVals(int type, int numPasses)
{
    passes.clear();
    topology.clear();

    //Topography
    switch(type)
    {
    case DATA_AND:
    case DATA_OR:
    case DATA_XOR:
        topology.push_back(2);
        topology.push_back(4);
        topology.push_back(1);
        break;
    }

    //Values
    for(int i=0;i<numPasses;i++)
    {
        passes.push_back(Pass());
        switch(type)
        {
        case DATA_AND:
            generateAND();
            break;
        case DATA_OR:
            generateOR();
            break;
        case DATA_XOR:
            generateXOR();
            break;
        }
    }
}

void TrainingData::generateXOR()
{
    double val1 = (double) (rand()%2);
    double val2 = (double) (rand()%2);

    passes.back().inputVals.push_back(val1);
    passes.back().inputVals.push_back(val2);

    if(val1 != val2)
    {
        passes.back().targetVals.push_back(1.0);
    }
    else
    {
        passes.back().targetVals.push_back(0.0);
    }
}

void TrainingData::generateOR()
{
    double val1 = (double) (rand()%2);
    double val2 = (double) (rand()%2);

    passes.back().inputVals.push_back(val1);
    passes.back().inputVals.push_back(val2);

    if((val1 == 1.0) || (val2 == 1.0))
    {
        passes.back().targetVals.push_back(1.0);
    }
    else
    {
        passes.back().targetVals.push_back(0.0);
    }
}

void TrainingData::generateAND()
{
    double val1 = (double) (rand()%2);
    double val2 = (double) (rand()%2);

    passes.back().inputVals.push_back(val1);
    passes.back().inputVals.push_back(val2);

    if(val1 == 1.0 &&  val2 == 1.0)
    {
        passes.back().targetVals.push_back(1.0);
    }
    else
    {
        passes.back().targetVals.push_back(0.0);
    }
}

void TrainingData::generateReport()
{
    string out;

    //Topography
    cout << "Topography : ";

    for(unsigned i=0;i<topology.size();i++)
    {
        cout << topology.at(i) << " ";
    }
    cout << endl << endl;

    //Vals
    out = out + "Vals:\n";

    for(unsigned i = 0;i<passes.size();i++)
    {
        //In
        cout << "IN : ";
        for(unsigned n = 0;n<passes.at(i).inputVals.size();n++)
        {
            cout << passes.at(i).inputVals.at(n) << " ";
        }

        cout << endl;

        //Targets
        cout << "OUT : ";
        for(unsigned n = 0;n<passes.at(i).targetVals.size();n++)
        {
            cout << passes.at(i).targetVals.at(n) << " ";
        }
        cout << endl;
    }
}

vector<Pass> TrainingData::getPasses() const
{
    return passes;
}

vector<unsigned> TrainingData::getTopology() const
{
    return this->topology;
}
