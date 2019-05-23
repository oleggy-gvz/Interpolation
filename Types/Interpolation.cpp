#include "Interpolation.h"

void Interpolation::addPoint(double x, double y)
{
    points[x] = y;
    calculateRatios();
}

void Interpolation::setPoints(initializer_list<double> x, initializer_list<double> y)
{
    if (x.size() != y.size())
    {
        throw Exception(Exception::WRONG_SIZE);
    }
    points.clear();
    auto it_x = x.begin();
    auto it_y = y.begin();
    for (; it_x != x.end(); ++it_x, ++it_y)
    {
        points[*it_x] = *it_y;
    }
    calculateRatios();
}

void Interpolation::setPoints(initializer_list<pair<double, double>> p)
{
    points.clear();
    for(const auto& item : p)
    {
        points[item.first] = item.second;
    }
    calculateRatios();
}

double Interpolation::getLowerBoundArgument()
{
    return points.begin()->first;
}

double Interpolation::getUpperBoundArgument()
{
    return points.rbegin()->first;
}
