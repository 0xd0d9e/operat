#pragma once

#include "route_calculator.h"
#include "voyage_state.h"

#include <components/component.h>

class Line;
class Route;
class Label;

class RouteMonitor : public Component
{
public:
    DECLARE_CONSTRUCTOR(RouteMonitor, Component)

    DECLARE_PROPERTY_CD(bool, enabled, Enabled, onEnabledChanged, false)

    void setRoute(Route* route);
    void setShip(Component* ship);
    void resetState();

    void update(const double time) final;

    void setupUi(Component* ui);

private:
    void init() final;

    void onEnabledChanged(const bool enabled);

    Route* route;
    Component* ship;

    VoyageState state;
    RouteCalculator* calculator = nullptr;

    Line* addTraverseLine;
    Line* traverseLine;

    Line* targetLine;

    Line* nextTurnLine;
    Line* turnLine;

    Label* textLabel;
};

