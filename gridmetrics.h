#pragma once

class GridMetrics
{
public:
    GridMetrics(const double size);

    /// \name scene -> grid tile
    double floor(const double value) const;
    double ceil(const double value) const;
    double near(const double value) const;
    ///@}

    /// \name grid tile -> scene
    double unmap(const double value) const;
    ///@}

private:
    double size;
};
