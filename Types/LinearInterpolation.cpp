#include "LinearInterpolation.h"

LinearInterpolation::LinearInterpolation(std::initializer_list<double> x, std::initializer_list<double> y)
{
    setPoints(x, y);
}

LinearInterpolation::LinearInterpolation(initializer_list<pair<double, double>> p)
{
    setPoints(p);
}

void LinearInterpolation::calculateRatios()
{
    if (points.size() < 2)
    {
        throw Exception(Exception::NO_POINTS_LINEAR);
    }
    // clean old ratios
    a.clear(); // clean a[i]
    b.clear(); // clean b[i]
    segments.clear(); // clean segments[i]

    auto it_p1 = points.begin();
    auto it_p2 = ++(points.begin());
    for (unsigned int i = 0; it_p2 != points.end(); ++it_p1, ++it_p2, i++) // i = 0..n-1
    {
        segments[it_p2->first] = i; // segment[i]
        double a_i = (it_p2->second - it_p1->second) / (it_p2->first - it_p1->first);
        double b_i = it_p1->second - a_i * it_p1->first;
        a.push_back(a_i); // a[i]
        b.push_back(b_i); // b[i]
    }
}

double LinearInterpolation::getFunction(double x)
{
    if (points.size() < 2)
    {
        throw Exception(Exception::NO_POINTS_LINEAR);
    }
    else
    {
        if (x < points.begin()->first)
        {
            throw Exception(Exception::LESS_LOWER_BOUND);
        }
        if (x > points.rbegin()->first)
        {
            throw Exception(Exception::MORE_UPPER_BOUND);
        }
        auto it = points.find(x);
        if (it != points.end()) // if the point is in table
        {
            return it->second;
        }
        else // else, calculate independently
        {
            auto it_n = segments.upper_bound(x);
            return a[it_n->second] * x + b[it_n->second];
        }
    }
}
