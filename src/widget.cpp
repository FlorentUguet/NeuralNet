#include "widget.h"

#include <vector>

Widget::Widget(QWidget *parent): QWidget(parent)
{
    treeWidgetResults = new QTreeWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(treeWidgetResults);
    setLayout(layout);

    this->generateTest();
}

Widget::~Widget()
{

}

void Widget::generateTest()
{
    std::vector<double> results;

    TrainingData data;
    data.generateVals(DATA_OR,1000);

    Net* net = new Net(data.getTopology());

    for(unsigned i=0;i<data.getPasses().size();i++)
    {
        Pass p = data.getPasses()[i];

        net->feedForward(p.inputVals);
        net->backProp(p.targetVals);
        net->getResults(results);

        /* Display */
        QTreeWidgetItem *root = new QTreeWidgetItem;
        root->setText(0,QString("Pass ") + QString::number(i) + QString(" : ") + QString::number(net->getRecentAverageError()));

        //Input
        QTreeWidgetItem *in = new QTreeWidgetItem;
        in->setText(0,vectorToString("Input",p.inputVals));

        //Output
        QTreeWidgetItem *out = new QTreeWidgetItem;
        out->setText(0,vectorToString("Output",results));

        //Target
        QTreeWidgetItem *target = new QTreeWidgetItem;
        target->setText(0,vectorToString("Target",p.targetVals));

        //Error
        QTreeWidgetItem *err = new QTreeWidgetItem;
        err->setText(0,QString("Error : ") + QString::number(net->getRecentAverageError()));

        root->addChild(in);
        root->addChild(out);
        root->addChild(target);
        root->addChild(err);

        treeWidgetResults->insertTopLevelItem(i,root);
    }
}

QString Widget::vectorToString(QString caption, std::vector<double> values)
{
    QString out;

    out += caption + " : ";

    for(unsigned i=0;i<values.size();i++)
    {
        out += QString::number(values.at(i)) + " ";
    }

    return out;
}
