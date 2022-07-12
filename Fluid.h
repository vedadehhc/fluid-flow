#ifndef FLUID_H
#define FLUID_H

#include "Screen.h"
#include "Matrix.h";

using namespace dev;

namespace fluidFlow
{
    class Fluid
    {
    private:
        Matrix<float> grid, grid2;

    public:
        Fluid(int width, int height);

        void update(int elapsedMs);
        bool render(Screen& screen);
    };
}

#endif