#ifndef SRC_UNITYENGINE_MATHF_H_
#define SRC_UNITYENGINE_MATHF_H_

#include <assert.h>

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/epsilon.hpp"
#include "glm/gtx/compatibility.hpp"

#include "Time.h"

namespace UnityEngine
{
    class Mathf
    {
    public:
        static const float Deg2Rad;
        static const float Epsilon;
        static const float Infinity;
        static const float NegativeInfinity;
        static const float PI;
        static const float Rad2Deg;

        static inline float Abs(float f)
        {
            return glm::abs(f);
        }

        static float Acos(float f)
        {
            return glm::acos(f);
        }

        static inline bool Approximately(float a, float b)
        {
            return glm::epsilonEqual(a, b, Epsilon);
        }

        static inline float Asin(float f)
        {
            return glm::asin(f);
        }

        static inline float Atan(float f)
        {
            return glm::atan(f);
        }

        static inline float Atan2(float y, float x)
        {
            return glm::atan(y, x);
        }

        static inline float Ceil(float f)
        {
            return glm::ceil(f);
        }

        static inline int CeilToInt(float f)
        {
            return int(glm::ceil(f));
        }

        static inline float Clamp(float value, float min, float max)
        {
            return glm::clamp(value, min, max);
        }

        static inline float Clamp01(float value)
        {
            return glm::clamp(value, 0.0f, 1.0f);
        }

        static inline int ClosestPowerOfTwo(int value)
        {
            // assert(false);
            return 0;
        }

        static inline float Cos(float f)
        {
            return glm::cos(f);
        }

        static inline float DeltaAngle(float current, float target)
        {
            float num = Mathf::Repeat(target - current, 360.0f);
            if (num > 180.0f)
            {
                num -= 360.0f;
            }
            return num;
        }

        static inline float Exp(float power)
        {
            return glm::exp(power);
        }

        static inline float Floor(float f)
        {
            return glm::floor(f);
        }

        static inline int FloorToInt(float f)
        {
            return int(glm::floor(f));
        }

        static inline float GammaToLinearSpace(float value)
        {
            assert(false);
            return 0.0f;
        }

        static inline float InverseLerp(float a, float b, float value)
        {
            if (a < b)
            {
                if (value < a)
                {
                    return 0.0f;
                }
                if (value > b)
                {
                    return 1.0f;
                }
                value -= a;
                value /= b - a;
                return value;
            }
            else
            {
                if (a <= b)
                {
                    return 0.0f;
                }
                if (value < b)
                {
                    return 1.0f;
                }
                if (value > a)
                {
                    return 0.0f;
                }
                return 1.0f - (value - b) / (a - b);
            }
        }

        static inline bool IsPowerOfTwo(int value)
        {
            return (value & (value-1)) == 0;
        }

        static inline float Lerp(float a, float b, float t)
        {
            t = glm::clamp(t, 0.0f, 1.0f);
            return glm::mix(a, b, t);
        }

        static inline float LerpAngle(float a, float b, float t)
        {
            float num = Mathf::Repeat(b - a, 360.0f);
            if (num > 180.0f)
            {
                num -= 360.0f;
            }
            return a + num * Mathf::Clamp01(t);
        }

        static inline float LerpUnclamped(float a, float b, float t)
        {
            return glm::mix(a, b, t);
        }

        static inline float LinearToGammaSpace(float f)
        {
            assert(false);
            return 0.0f;
        }

        static inline float Log(float f, float p)
        {
            assert(false);
            return 0.0f;
        }

        static inline float Log10(float f)
        {
            return glm::log(f);
        }

        static inline float Max(float a, float b)
        {
            return glm::max(a, b);
        }

        static float Max(const std::vector<float>& values);

        static inline float Min(float a, float b)
        {
            return glm::min(a, b);
        }

        static float Min(const std::vector<float>& values);

        static inline float MoveTowards(float current, float target, float maxDelta)
        {
            float delta = target - current;
            float result = (maxDelta >= delta) ? target : current + maxDelta;
            return result;
        }

        static inline float MoveTowardsAngle(float current, float target, float maxDelta)
        {
            target = current + Mathf::DeltaAngle(current, target);
            return Mathf::MoveTowards(current, target, maxDelta);
        }

        static inline int NextPowerOfTwo(int value)
        {
            value--;
            value |= value >> 1;
            value |= value >> 2;
            value |= value >> 4;
            value |= value >> 8;
            value |= value >> 16;
            return value+1;
        }

        static float PerlinNoise(float x, float y);

        static inline float PingPong(float t, float length)
        {
            float result = t;
            if (t >= 0.0f && t < length)
            {
                length *= 2.0f;
                t = glm::modf(t, length);
                result = length - t;
            }
            return result;
        }

        static inline float Pow(float f, float p)
        {
            return glm::pow(f, p);
        }

        static inline float Repeat(float t, float length)
        {
            return glm::modf(t, length);
        }

        static inline float Round(float f)
        {
            return glm::round(f);
        }

        static inline int RoundToInt(float f)
        {
            return int(glm::round(f));
        }

        static inline float Sign(float f)
        {
            return glm::sign(f);
        }

        static inline float Sin(float f)
        {
            return glm::sin(f);
        }

        static float SmoothDamp(float current,
                                float target,
                                float *currentVelocity,
                                float smoothTime,
                                float maxSpeed = Mathf::Infinity,
                                float deltaTime = Time::deltaTime());

        static float SmoothDampAngle(float current,
                                     float target,
                                     float *currentVelocity,
                                     float smoothTime,
                                     float maxSpeed = Mathf::Infinity,
                                     float deltaTime = Time::deltaTime());

        static inline float SmoothStep(float from, float to, float value)
        {
            float t = Mathf::Clamp01(value);
            t = -2.0f * t * t * t + 3.0f * t * t;
            return to * t + from * (1.0f - t);
        }

        static inline float Sqrt(float f)
        {
            return glm::sqrt(f);
        }

        static inline float Tan(float f)
        {
            return glm::tan(f);
        }
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_MATHF_H_
