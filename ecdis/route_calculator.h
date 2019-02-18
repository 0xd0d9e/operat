#pragma once

#include "voyage_state.h"

class RouteCalculator
{
public:
    RouteCalculator(VoyageState& state);

    void findTargetPoint();

private:
    void findNearPoint();

    VoyageState& state;

};

