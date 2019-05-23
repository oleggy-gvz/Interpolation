#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <map>
#include <vector>
#include "Exception.h"

using namespace std;

class Interpolation
{
protected:
    map<double, double> points; // interpolation table: argument / value
    virtual void calculateRatios() = 0;

public:
    void addPoint(double x, double y);
    void setPoints(initializer_list<double> x, initializer_list<double> y);
    void setPoints(initializer_list<pair<double, double>> p);
    double getLowerBoundArgument();
    double getUpperBoundArgument();

    virtual double getFunction(double x) = 0;
};

#endif // INTERPOLATION_H
