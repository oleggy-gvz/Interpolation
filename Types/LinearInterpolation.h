#ifndef LINEAR_INTERPOLATION_H
#define LINEAR_INTERPOLATION_H

#include "Interpolation.h"

class LinearInterpolation : public Interpolation
{
private:
    // f(x) = a[i] * x + b[i], i = 0,1..n-2, n - count points
    vector<double> a; // a[i], coefficient a (angular coefficient)
    vector<double> b; // b[i], coefficient b (additional constant)
    // segments[i], i = 0,1..n-2, for easy index (i) lookup
    map<double, unsigned int> segments; // upper bound (x2) of segment x1..x2 <-> index of segment

    void calculateRatios();

public:
    LinearInterpolation(std::initializer_list<double> x, std::initializer_list<double> y);
    LinearInterpolation(initializer_list<pair<double, double>> p);
    double getFunction(double x);
};

#endif // LINEAR_INTERPOLATION_H
