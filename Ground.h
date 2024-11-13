#pragma once
#include "ofMain.h"
#include "Vector.h"

class Ground {
public:
    Ground()
    {
        setGroundPoints();
    }

    void setGroundPoints();

    std::vector<Vector> groundPoints;

private:
    
};
