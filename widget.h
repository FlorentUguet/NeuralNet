#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "neural/net.h"
#include "neural/trainingdata.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void generateTest();
    QString vectorToString(QString caption, std::vector<double> values);

private:
    QTreeWidget *treeWidgetResults;
};

#endif // WIDGET_H
