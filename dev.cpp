#include <SDL.h>
#include <cmath>
#include <stdio.h>

#include "dev.h"

namespace dev
{
    float randFloat()
    {
        return ((float)rand()) / ((float)RAND_MAX);
    }

    float sqDistance(float x1, float y1, float x2, float y2)
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    float sqDistanceTorus(float x1, float y1, float x2, float y2, Box torus)
    {
        x1 = rangeMod(x1, torus.minX, torus.maxX);
        x2 = rangeMod(x2, torus.minX, torus.maxX);
        float width = torus.maxX - torus.minX;
        float dx = rangeMod(x1 - x2, -width / 2, width / 2);

        y1 = rangeMod(y1, torus.minY, torus.maxY);
        y2 = rangeMod(y2, torus.minY, torus.maxY);
        float height = torus.maxY - torus.minY;
        float dy = rangeMod(y1 - y2, -height / 2, height / 2);

        return dx * dx + dy * dy;
    }

    bool pointInCircle(float px, float py, float cx, float cy, float radius)
    {
        return sqDistance(px, py, cx, cy) <= radius * radius;
    }

    bool pointInCircleTorus(float px, float py, float cx, float cy, float radius, Box torus)
    {
        return sqDistanceTorus(px, py, cx, cy, torus) <= radius * radius;
    }

    float pointTowards(float fromX, float fromY, float toX, float toY)
    {
        return atan2(toY - fromY, toX - fromX);
    }

    float pointTowardsTorus(float fromX, float fromY, float toX, float toY, Box torus)
    {
        fromX = rangeMod(fromX, torus.minX, torus.maxX);
        toX = rangeMod(toX, torus.minX, torus.maxX);

        float xL = (toX - (torus.maxX - torus.minX)) - fromX;
        float xR = (toX + (torus.maxX - torus.minX)) - fromX;

        float dx = toX - fromX;
        if (abs(xL) < abs(dx))
        {
            dx = xL;
        }
        if (abs(xR) < abs(dx))
        {
            dx = xR;
        }

        fromY = rangeMod(fromY, torus.minY, torus.maxY);
        toY = rangeMod(toY, torus.minY, torus.maxY);

        float yT = (toY - (torus.maxY - torus.minY)) - fromY;
        float yB = (toY + (torus.maxY - torus.minY)) - fromY;

        float dy = toY - fromY;
        if (abs(yT) < abs(dy))
        {
            dy = yT;
        }
        if (abs(yB) < abs(dy))
        {
            dy = yB;
        }

        return atan2(dy, dx);
    }

    float rangeMod(float val, float min, float max)
    {
        if (val >= min && val <= max)
        {
            return val;
        }

        float size = max - min;
        val = fmod(val - min, size);
        while (val < 0)
            val += size;

        return val + min;
    }

    int uMod(int val, int mod)
    {
        val %= mod;
        if (val < 0)
            val += mod;
        return val;
    }

    float clamp(float val, float min, float max)
    {
        if (val < min)
            return min;
        else if (val > max)
            return max;
        else
            return val;
    }

    void colorComponentsInt(Uint32 color, int &r, int &g, int &b, int &a)
    {
        r = color >> 24;
        g = (color >> 16) & 0xFF;
        b = (color >> 8) & 0xFF;
        a = color & 0xFF;
    }

    // https://en.wikipedia.org/wiki/Alpha_compositing
    // c1 over c2
    Uint32 colorOver(Uint32 c1, Uint32 c2)
    {
        int r1, g1, b1, a1;
        colorComponentsInt(c1, r1, g1, b1, a1);

        int r2, g2, b2, a2;
        colorComponentsInt(c2, r2, g2, b2, a2);

        // new alpha is a2 * (1 - a1)
        // but we have to adjust formula to use 256 alpha values instead of [0, 1]
        int c2Intensity = (a2 * (0xFF ^ a1)) >> 8;

        int a3 = (a1 + c2Intensity) & 0xFF;
        Uint8 r3 = ((r1 * a1 + r2 * c2Intensity) / a3) & 0xFF;
        Uint8 g3 = ((g1 * a1 + g2 * c2Intensity) / a3) & 0xFF;
        Uint8 b3 = ((b1 * a1 + b2 * c2Intensity) / a3) & 0xFF;

        Uint32 c3 = (r3 << 24) + (g3 << 16) + (b3 << 8) + a3;
        return c3;
    }
}
