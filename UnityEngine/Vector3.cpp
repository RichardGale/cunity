#include "UnityEngine/Vector3.h"

#include <string>

#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/orthonormalize.hpp"

namespace UnityEngine
{
    const Vector3 Vector3::back(0.0f, 0.0f, -1.0f);
    const Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
    const Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
    const Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);

    float Vector3::magnitude() const
    {
        return glm::length(static_cast<glm::vec3>(*this));
    }

    Vector3 Vector3::normalized() const
    {
        glm::vec3 result = *this;
        glm::normalize(result);
        return Vector3(result);
    }

    float Vector3::sqrMagnitude() const
    {
        float result = glm::length2(static_cast<glm::vec3>(*this));
        return result;
    }

    Vector3::Vector3(glm::vec3 v)
    : glm::vec3(v)
    {
    }

    Vector3::Vector3(float x, float y, float z)
    : glm::vec3(x, y, z)
    {
    }

    void Vector3::Normalize()
    {
        glm::normalize(static_cast<glm::vec3>(*this));
    }

    void Vector3::Set(float new_x, float new_y, float new_z)
    {
        x = new_x;
        y = new_y;
        z = new_z;
    }

    std::string Vector3::ToString() const
    {
        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%0.1f, %0.1f, %0.1f)",
                 x,
                 y,
                 z);
        return message;
    }

    std::string Vector3::ToString(std::string format) const
    {
        char messageX[1023+1];
        char messageY[1023+1];
        char messageZ[1023+1];

        snprintf(messageX,
                 sizeof(messageX),
                 format.c_str(),
                 x);
        snprintf(messageY,
                 sizeof(messageY),
                 format.c_str(),
                 y);
        snprintf(messageZ,
                 sizeof(messageZ),
                 format.c_str(),
                 z);

        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%s, %s, %s)",
                 messageX,
                 messageY,
                 messageZ);
        return message;
    }

    Vector3 Vector3::operator*(int value) const
    {
        Vector3 result(x*value, y*value, z*value);
        return result;
    }

    Vector3 Vector3::operator*(float value) const
    {
        Vector3 result(x*value, y*value, z*value);
        return result;
    }

    float Vector3::Angle(Vector3 from, Vector3 to)
    {
        glm::vec3 a = glm::normalize(static_cast<glm::vec3>(from));
        glm::vec3 b = glm::normalize(static_cast<glm::vec3>(to));
        float result = glm::angle(a, b);
        return result;
    }

    Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
    {
        float length = glm::length(static_cast<glm::vec3>(vector));
        glm::vec3 result = vector;
        result *= maxLength / length;
        return static_cast<Vector3>(result);
    }

    float Vector3::Distance(Vector3 a, Vector3 b)
    {
        float result = glm::distance(static_cast<glm::vec3>(a),
                                     static_cast<glm::vec3>(b));
        return result;
    }

    float Vector3::Dot(Vector3 lhs, Vector3 rhs)
    {
        float result = glm::dot(static_cast<glm::vec3>(lhs),
                                static_cast<glm::vec3>(rhs));
        return result;
    }

    Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
    {
        t = glm::clamp(t, 0.0f, 1.0f);
        return LerpUnclamped(a, b, t);
    }

    Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
    {
        glm::vec3 result = a*(1.0f-t) + b*t;
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::Max(Vector3 lhs, Vector3 rhs)
    {
        glm::vec3 result = glm::max(static_cast<glm::vec3>(lhs),
                                    static_cast<glm::vec3>(rhs));
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::Min(Vector3 lhs, Vector3 rhs)
    {
        glm::vec3 result = glm::min(static_cast<glm::vec3>(lhs),
                                    static_cast<glm::vec3>(rhs));
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
    {
        glm::vec3 delta = target - current;
        glm::vec3 result = (maxDistanceDelta >= glm::length(delta)) ? target : current + maxDistanceDelta;
        return static_cast<Vector3>(result);
    }

    void Vector3::OrthoNormalize(Vector3 *normal, Vector3 *tangent)
    {
        glm::orthonormalize(*normal, *tangent);
    }

    Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal)
    {
        float num = Vector3::Dot(onNormal, onNormal);
        if (num < Mathf::Epsilon)
        {
            return Vector3::zero;
        }
        return onNormal * Vector3::Dot(vector, onNormal) / num;
    }

    Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
    {
        return vector - Vector3::Project(vector, planeNormal);
    }

    Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal)
    {
        glm::vec3 result = glm::reflect(static_cast<glm::vec3>(inDirection),
                                        static_cast<glm::vec3>(inNormal));
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta)
    {
        assert(false);
        return zero;
    }

    Vector3 Vector3::Scale(Vector3 a, Vector3 b)
    {
        glm::vec3 result = a * b;
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t)
    {
        t = glm::clamp(t, 0.0f, 1.0f);
        return SlerpUnclamped(a, b, t);
    }

    Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t)
    {
        glm::vec3 result = glm::slerp(static_cast<glm::vec3>(a),
                                      static_cast<glm::vec3>(b),
                                      t);
        return static_cast<Vector3>(result);
    }

    Vector3 Vector3::SmoothDamp(Vector3 current,
                                Vector3 target,
                                Vector3 *currentVelocity,
                                float smoothTime,
                                float maxSpeed,
                                float deltaTime)
    {
        smoothTime = glm::max(0.0001f, smoothTime);
        float omega = 2.0f / smoothTime;
        float x = omega * deltaTime;
        float exp = 1.0f / (1.0f + x + 0.48f*x*x + 0.235f*x*x*x);
        glm::vec3 deltaX = target - current;
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

        glm::vec3 temp = (static_cast<glm::vec3>(*currentVelocity) + omega * deltaX) * deltaTime;
        glm::vec3 result = static_cast<glm::vec3>(current) - deltaX + (deltaX + temp) * exp;
        *currentVelocity = static_cast<Vector3>((static_cast<glm::vec3>(*currentVelocity) - omega * temp) * exp);

        // ensure that we do not overshoot our target
        if (glm::length(static_cast<glm::vec3>(target) - static_cast<glm::vec3>(current)) > 0.0f == glm::length(result) > glm::length(static_cast<glm::vec3>(target)))
        {
            result = target;
            *currentVelocity = zero;
        }
        return static_cast<Vector3>(result);
    }
}  // namespace UnityEngine
