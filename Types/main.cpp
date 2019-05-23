#include <iostream>
#include <memory>
#include "Interpolation.h"
#include "LinearInterpolation.h"
#include "CubicSplineInterpolation.h"

using namespace std;

int main()
{
    shared_ptr<Interpolation> i(new CubicSplineInterpolation{{-1, 0.756802495},
                                                              {-0.5, -0.909297427},
                                                              {0, 0},
                                                              {0.5, 0.909297427},
                                                              {1, -0.756802495}});

    double x;
    x = -0.99;
    cout << "x = " << x << ", f(x) = " << i->getFunction(x) << endl;
    x = -0.49;
    cout << "x = " << x << ", f(x) = " << i->getFunction(x) << endl;
    x = 0.4;
    cout << "x = " << x << ", f(x) = " << i->getFunction(x) << endl;
    x = 0.99;
    cout << "x = " << x << ", f(x) = " << i->getFunction(x) << endl;

    system("pause");
    return 0;
}
