#ifndef DEV_H
#define DEV_H

#include <cmath>

namespace dev
{
    struct Box
    {
    public:
        float minX, minY, maxX, maxY;
        Box(float minX, float minY, float maxX, float maxY) : minX(minX), minY(minY), maxX(maxX), maxY(maxY) {}
    };

    float randFloat();

    float sqDistance(float x1, float y1, float x2, float y2);
    float sqDistanceTorus(float x1, float y1, float x2, float y2, Box torus);

    bool pointInCircle(float px, float py, float cx, float cy, float radius);
    bool pointInCircleTorus(float px, float py, float cx, float cy, float radius, Box torus);

    float pointTowards(float fromX, float fromY, float toX, float toY);
    float pointTowardsTorus(float fromX, float fromY, float toX, float toY, Box torus);

    float rangeMod(float val, float min, float max);
    int uMod(int val, int mod);
    float clamp(float val, float min, float max);

    void colorComponentsInt(Uint32 color, int &r, int &g, int &b, int &a);

    // https://en.wikipedia.org/wiki/Alpha_compositing
    Uint32 colorOver(Uint32 c1, Uint32 c2);
}

#endif