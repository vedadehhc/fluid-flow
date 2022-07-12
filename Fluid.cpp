#include "Fluid.h"
#include "Screen.h"

using namespace dev;

namespace fluidFlow
{

    Fluid::Fluid(int width, int height) : grid(height, width), grid2(height, width) {}

    void Fluid::update(int elapsedMs)
    {
        
    }

    bool Fluid::render(Screen &screen)
    {
    }
}