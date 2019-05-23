#include "Exception.h"

Exception::Exception(std::string error)
    : m_error(error)
{}

Exception::Exception(ExceptionType error)
{
    switch(error)
    {
    case NO_POINTS_LINEAR:
        m_error = "for linear interpolation, the number of points must be two and more";
        break;

    case NO_POINTS_CUBICSPLINE:
        m_error = "for cubic spline interpolation, the number of points must be three and more";
        break;

    case LESS_LOWER_BOUND:
        m_error = "out of interpolation range: below the lower interpolation value";
        break;

    case MORE_UPPER_BOUND:
        m_error = "out of interpolation range: above the upper interpolation value";
        break;

    case WRONG_SIZE:
        m_error = "x and y arrays of coordinate do not match";
        break;
    }
}

const char* Exception::what() const noexcept
{
    return m_error.c_str();
}
