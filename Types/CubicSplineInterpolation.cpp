#include "CubicSplineInterpolation.h"

CubicSplineInterpolation::CubicSplineInterpolation(std::initializer_list<double> x, std::initializer_list<double> y)
{
    setPoints(x, y);
}

CubicSplineInterpolation::CubicSplineInterpolation(initializer_list<pair<double, double>> p)
{
    setPoints(p);
}

void CubicSplineInterpolation::calculateRatios()
{
    if (points.size() < 3)
    {
        throw Exception(Exception::NO_POINTS_CUBICSPLINE);
    }
    // clean old ratios
    segments.clear(); // clean segments[i]
    a.clear(); // clean a[i]
    b.clear(); // clean b[i]
    c.clear(); // clean c[i]
    d.clear(); // clean d[i]

    vector<double> delta; // delta[i]
    vector<double> h; // h[i]
    auto it_p1 = points.begin();
    auto it_p2 = ++(points.begin());
    unsigned int i;
    for (i = 0; it_p2 != points.end(); ++it_p1, ++it_p2, i++) // i = 0..n-1
    {
        segments.emplace(it_p2->first, make_pair(i, it_p1->first)); // add: <x[i+1], <i, f(x[i])>, i = 0..n-1
        //segments[it_p2->first] = make_pair(i, it_p1->first); // add: <x[i+1], <i, f(x[i])>, i = 0..n-1
        double h_i = it_p2->first - it_p1->first; // h[i] = x[i+1] - x[i], i = 0..n-1
        h.push_back(h_i);
        double delta_i = (it_p2->second - it_p1->second) / h_i;
        delta.push_back(delta_i);
        a.push_back(it_p1->second); // a[i] = f(x[i]), i = 0..n-1
    }
    vector<double> A, B, C, F; // A[i], B[i], C[i], F[i]

    // three starting points: x[2] - x[0]
    it_p1 = points.begin(); // x[0]
    double x_3 = -it_p1->first;
    ++it_p1; ++it_p1; // x[2]
    x_3 += it_p1->first;

    // three ending points: x[n-1] - x[n-3]
    auto it_pn = points.rbegin(); // x[n-1]
    double x_n = it_pn->first;
    ++it_pn; ++it_pn; // x[n-3]
    x_n -= it_pn->first;

    A.push_back(x_3); // A[0]
    B.push_back(h[0]); // B[0]
    C.push_back(h[0]); // C[0]
    F.push_back(((h[0] + 2 * x_3) * h[1] * delta[0] + h[0] * h[0] * delta[1]) / x_3);
    for (i = 1; i < h.size(); i++) // i = 0..n-1
    {
        A.push_back(h[i]); // A[i]
        B.push_back(h[i]); // B[i]
        C.push_back(2 * (h[i-1] + h[i])); // C[i]
        F.push_back(3 * (h[i] * delta[i-1] + h[i-1] * delta[i]));
    }
    A.push_back(h[i-1]); // A[i]
    B.push_back(x_n); // B[i]
    C.push_back(h[i-1]); // C[i]
    F.push_back((h[i-1] * h[i-1] * delta[i-2] + (2 * x_n + h[i-1]) * h[i-2] * delta[i-1]) / x_n);

    vector<double> alph, beta; // alpha[i], beta[i]
    alph.push_back(-B[0] / C[0]);
    beta.push_back(F[0] / C[0]);
    for (i = 1; i < h.size(); i++) // i = 1..n-2
    {
        double denom = A[i] * alph[i-1] + C[i];
        alph.push_back(-B[i] / denom);
        beta.push_back((F[i] - A[i] * beta[i-1]) / denom);
    }
    auto it_prev = b.insert(b.begin(), (F[i] - A[i] * beta[i-1]) / (A[i] * alph[i-1] + C[i])); // i = n-1
    for (int i = h.size() - 1; i >= 0; i--) // i = n-2..0
    {
        it_prev = b.insert(it_prev, *it_prev * alph[i] + beta[i]);
    }
    for (i = 0; i < h.size(); i++)
    {
        d.push_back((b[i+1] + b[i] - 2 * delta[i]) / (h[i] * h[i]));
        c.push_back(2 * (delta[i] - b[i]) / h[i] - (b[i+1] - delta[i]) / h[i]);
    }
}

double CubicSplineInterpolation::getFunction(double x)
{
    if (points.size() < 3)
    {
        throw Exception(Exception::NO_POINTS_CUBICSPLINE);
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
            double x_xi = x - (it_n->second).second; // x - x[i], x > x[i]
            return a[(it_n->second).first] + b[(it_n->second).first] * x_xi + c[(it_n->second).first] * x_xi * x_xi + d[(it_n->second).first] * x_xi * x_xi * x_xi;
        }
    }
}
