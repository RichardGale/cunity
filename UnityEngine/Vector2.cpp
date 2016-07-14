#include "UnityEngine/Vector2.h"

#include <string>

#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/vector_angle.hpp"

namespace UnityEngine
{
    const Vector2 Vector2::down(0.0f, -1.0f);
    const Vector2 Vector2::left(-1.0f, 0.0f);
    const Vector2 Vector2::one(1.0f, 1.0f);
    const Vector2 Vector2::right(1.0f, 0.0f);
    const Vector2 Vector2::up(0.0f, 1.0f);
    const Vector2 Vector2::zero(0.0f, 0.0f);

    float Vector2::magnitude() const
    {
        float result = glm::length(static_cast<glm::vec2>(*this));
        return result;
    }

    Vector2 Vector2::normalized() const
    {
        glm::vec2 result = *this;
        glm::normalize(result);
        return static_cast<Vector2>(result);
    }

    float Vector2::sqrMagnitude() const
    {
        float result = glm::length2(static_cast<glm::vec2>(*this));
        return result;
    }

    Vector2::Vector2(glm::vec2 v)
    : glm::vec2(v)
    {
    }

    Vector2::Vector2(float x, float y)
    : glm::vec2(x, y)
    {
    }

    void Vector2::Normalize()
    {
        glm::normalize(static_cast<glm::vec2>(*this));
    }

    void Vector2::Set(float new_x, float new_y)
    {
        x = new_x;
        y = new_y;
    }

    std::string Vector2::ToString() const
    {
        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%0.1f, %0.1f)",
                 x,
                 y);
        return message;
    }

    std::string Vector2::ToString(std::string format) const
    {
        char messageX[1023+1];
        char messageY[1023+1];

        snprintf(messageX,
                 sizeof(messageX),
                 format.c_str(),
                 x);
        snprintf(messageY,
                 sizeof(messageY),
                 format.c_str(),
                 y);

        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%s, %s)",
                 messageX,
                 messageY);
        return message;
    }

    float Vector2::Angle(Vector2 from, Vector2 to)
    {
        glm::vec2 a = glm::normalize(static_cast<glm::vec2>(from));
        glm::vec2 b = glm::normalize(static_cast<glm::vec2>(to));
        float result = glm::angle(a, b);
        return result;
    }

    Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength)
    {
        float length = glm::length(static_cast<glm::vec2>(vector));
        glm::vec2 result = vector;
        result *= maxLength / length;
        return static_cast<Vector2>(result);
    }

    float Vector2::Distance(Vector2 a, Vector2 b)
    {
        float result = glm::distance(static_cast<glm::vec2>(a),
                                     static_cast<glm::vec2>(b));
        return result;
    }

    float Vector2::Dot(Vector2 lhs, Vector2 rhs)
    {
        float result = glm::dot(static_cast<glm::vec2>(lhs),
                                static_cast<glm::vec2>(rhs));
        return result;
    }

    Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
    {
        t = glm::clamp(t, 0.0f, 1.0f);
        return LerpUnclamped(a, b, t);
    }

    Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t)
    {
        glm::vec2 result = a*(1.0f-t) + b*t;
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::Max(Vector2 lhs, Vector2 rhs)
    {
        glm::vec2 result = glm::max(static_cast<glm::vec2>(lhs),
                                    static_cast<glm::vec2>(rhs));
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::Min(Vector2 lhs, Vector2 rhs)
    {
        glm::vec2 result = glm::min(static_cast<glm::vec2>(lhs),
                                    static_cast<glm::vec2>(rhs));
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta)
    {
        glm::vec2 delta = target - current;
        glm::vec2 result = (maxDistanceDelta >= glm::length(delta)) ? target : current + maxDistanceDelta;
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::Reflect(Vector2 inDirection, Vector2 inNormal)
    {
        glm::vec2 result = glm::reflect(static_cast<glm::vec2>(inDirection),
                                        static_cast<glm::vec2>(inNormal));
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::Scale(Vector2 a, Vector2 b)
    {
        glm::vec2 result = a * b;
        return static_cast<Vector2>(result);
    }

    Vector2 Vector2::SmoothDamp(Vector2 current,
                                Vector2 target,
                                Vector2 *currentVelocity,
                                float smoothTime,
                                float maxSpeed,
                                float deltaTime)
    {
        smoothTime = glm::max(0.0001f, smoothTime);
        float omega = 2.0f / smoothTime;
        float x = omega * deltaTime;
        float exp = 1.0f / (1.0f + x + 0.48f*x*x + 0.235f*x*x*x);
        glm::vec2 deltaX = target - current;
        float maxDelta = maxSpeed * smoothTime;

        // ensure we do not exceed our max speed
        float length = glm::length(deltaX);
        if (length > maxDelta)
        {
            deltaX = glm::normalize(deltaX) * maxDelta;
        }
        else if (length < -maxDelta)
        {
            deltaX = glm::normalize(deltaX) * -maxDelta;
        }

        glm::vec2 temp = (static_cast<glm::vec2>(*currentVelocity) + omega * deltaX) * deltaTime;
        glm::vec2 result = static_cast<glm::vec2>(current) - deltaX + (deltaX + temp) * exp;
        *currentVelocity = static_cast<Vector2>((static_cast<glm::vec2>(*currentVelocity) - omega * temp) * exp);

        // ensure that we do not overshoot our target
        if (glm::length(static_cast<glm::vec2>(target) - static_cast<glm::vec2>(current)) > 0.0f == glm::length(result) > glm::length(static_cast<glm::vec2>(target)))
        {
            result = target;
            *currentVelocity = zero;
        }
        return static_cast<Vector2>(result);
    }
}  // namespace UnityEngine
