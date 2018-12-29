#pragma once

class Viewport;

class Stage
{
public:
    virtual ~Stage() = default;

    virtual void setViewport(Viewport* viewport) = 0;
};

