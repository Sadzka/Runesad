#include "Utils/AnimationUtils.hpp"

namespace utils
{
    float parametricBlend(float t)
    {
        float sqt = t * t;
        return sqt / (2.0f * (sqt - t) + 1.0f);
    }
}