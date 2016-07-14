#include "UnityEngine/Mathf.h"

#include <vector>

#include "glm/gtc/constants.hpp"

#define STB_PERLIN_IMPLEMENTATION
#include "stb/stb_perlin.h"

namespace UnityEngine
{
    const float Mathf::Deg2Rad = (glm::pi<float>() * 2.0f) / 360.0f;
    const float Mathf::Epsilon = glm::epsilon<float>();
    const float Mathf::Infinity = 0.0f;
    const float Mathf::NegativeInfinity = 0.0f;
    const float Mathf::PI = glm::pi<float>();
    const float Mathf::Rad2Deg = 360.0f / (glm::pi<float>() * 2.0f);

    float Mathf::Max(const std::vector<float>& values)
    {
        float result = 0.0f;
        if (values.size() > 0)
        {
            result = values[0];

            if (values.size() > 1)
            {
                for (size_t i = 1; i < values.size(); ++i)
                {
                    result = Max(result, values[i]);
                }
            }
        }
        return result;
    }

    float Mathf::Min(const std::vector<float>& values)
    {
        float result = 0.0f;
        if (values.size() > 0)
        {
            result = values[0];

            if (values.size() > 1)
            {
                for (size_t i = 1; i < values.size(); ++i)
                {
                    result = Min(result, values[i]);
                }
            }
        }
        return result;
    }

    float Mathf::PerlinNoise(float x, float y)
    {
        float result = stb_perlin_noise3(x, y, 0.0f);
        return result;
    }

    float Mathf::SmoothDamp(float current,
                            float target,
                            float *currentVelocity,
                            float smoothTime,
                            float maxSpeed,
                            float deltaTime)
    {
        // https://graemepottsfolio.wordpress.com/tag/damped-spring/

        smoothTime = Max(0.0001f, smoothTime);
        float omega = 2.0f / smoothTime;
        float x = omega * deltaTime;
        float exp = 1.0f / (1.0f + x + 0.48f*x*x + 0.235f*x*x*x);
        float deltaX = target - current;
        float maxDelta = maxSpeed * smoothTime;

        // ensure we do not exceed our max speed
        deltaX = Mathf::Clamp(deltaX, -maxDelta, maxDelta);
        float temp = (*currentVelocity + omega * deltaX) * deltaTime;
        float result = current - deltaX + (deltaX + temp) * exp;
        *currentVelocity = (*currentVelocity - omega * temp) * exp;

        // ensure that we do not overshoot our target
        if (target - current > 0.0f == result > target)
        {
            result = target;
            *currentVelocity = 0.0f;
        }
        return result;
    }

    float Mathf::SmoothDampAngle(float current,
                                 float target,
                                 float *currentVelocity,
                                 float smoothTime,
                                 float maxSpeed,
                                 float deltaTime)
    {
        smoothTime = Max(0.0001f, smoothTime);
        float omega = 2.0f / smoothTime;
        float x = omega * deltaTime;
        float exp = 1.0f / (1.0f + x + 0.48f*x*x + 0.235f*x*x*x);
        float deltaX = target - current;
        float maxDelta = maxSpeed * smoothTime;

        // ensure we do not exceed our max speed
        deltaX = Mathf::Clamp(deltaX, -maxDelta, maxDelta);
        float temp = (*currentVelocity + omega * deltaX) * deltaTime;
        float result = current - deltaX + (deltaX + temp) * exp;
        *currentVelocity = (*currentVelocity - omega * temp) * exp;

        // ensure that we do not overshoot our target
        if (target - current > 0.0f == result > target)
        {
            result = target;
            *currentVelocity = 0.0f;
        }
        return result;
    }
}  // namespace UnityEngine
