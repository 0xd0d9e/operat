#include "gridmetrics.h"

#include <cmath>

GridMetrics::GridMetrics(const double size) : size(size)
{

}

double GridMetrics::floor(const double value) const
{
    return ::floor(value / size);
}

double GridMetrics::ceil(const double value) const
{
    return ::ceil(value / size);
}

double GridMetrics::near(const double value) const
{
    return ::round(value / size);
}

double GridMetrics::unmap(const double value) const
{
    return value * size;
}
