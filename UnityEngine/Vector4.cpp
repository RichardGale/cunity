#include "UnityEngine/Vector4.h"

#include <string>

#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"

#include "bx/fpumath.h"

namespace UnityEngine
{
    const Vector4 Vector4::one(0.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::zero(0.0f, 0.0f, 0.0f, 0.0f);

    float Vector4::magnitude() const
    {
        float result = glm::length(static_cast<glm::vec4>(*this));
        return result;
    }

    Vector4 Vector4::normalized() const
    {
        glm::vec4 result = *this;
        glm::normalize(result);
        return static_cast<Vector4>(result);
    }

    float Vector4::sqrMagnitude() const
    {
        float result = glm::length2(static_cast<glm::vec4>(*this));
        return result;
    }

    Vector4::Vector4(glm::vec4 v)
    : glm::vec4(v)
    {
    }

    Vector4::Vector4(float x, float y, float z, float w)
    : glm::vec4(x, y, z, w)
    {
    }

    Vector4::Vector4(Vector3 v)
    : glm::vec4(v.x, v.y, v.z, 0.0f)
    {
    }
    
    void Vector4::Normalize()
    {
        glm::normalize(static_cast<glm::vec4>(*this));
    }

    void Vector4::Set(float new_x, float new_y, float new_z, float new_w)
    {
        x = new_x;
        y = new_y;
        z = new_z;
        w = new_w;
    }

    std::string Vector4::ToString() const
    {
        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%0.1f, %0.1f, %0.1f, %0.1f)",
                 x,
                 y,
                 z,
                 w);
        return message;
    }

    std::string Vector4::ToString(std::string format) const
    {
        char messageX[1023+1];
        char messageY[1023+1];
        char messageZ[1023+1];
        char messageW[1023+1];

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
        snprintf(messageW,
                 sizeof(messageW),
                 format.c_str(),
                 w);

        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "(%s, %s, %s, %s)",
                 messageX,
                 messageY,
                 messageZ,
                 messageW);
        return message;
    }

    float Vector4::Distance(Vector4 a, Vector4 b)
    {
        float result = glm::distance(static_cast<glm::vec4>(a),
                                     static_cast<glm::vec4>(b));
        return result;
    }

    float Vector4::Dot(Vector4 lhs, Vector4 rhs)
    {
        float result = glm::dot(static_cast<glm::vec4>(lhs),
                                static_cast<glm::vec4>(rhs));
        return result;
    }

    Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
    {
        t = bx::fclamp(t, 0.0f, 1.0f);
        return LerpUnclamped(a, b, t);
    }

    Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
    {
        glm::vec4 result = a*(1.0f-t) + b*t;
        return static_cast<Vector4>(result);
    }

    Vector4 Vector4::Max(Vector4 lhs, Vector4 rhs)
    {
        glm::vec4 result = glm::max(static_cast<glm::vec4>(lhs),
                                    static_cast<glm::vec4>(rhs));
        return static_cast<Vector4>(result);
    }

    Vector4 Vector4::Min(Vector4 lhs, Vector4 rhs)
    {
        glm::vec4 result = glm::min(static_cast<glm::vec4>(lhs),
                                    static_cast<glm::vec4>(rhs));
        return static_cast<Vector4>(result);
    }

    Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
    {
        glm::vec4 delta = target - current;
        glm::vec4 result = (maxDistanceDelta >= glm::length(delta)) ? target : current + maxDistanceDelta;
        return static_cast<Vector4>(result);
    }

    Vector4 Vector4::Project(Vector4 a, Vector4 b)
    {
        assert(false);
        return zero;
    }

    Vector4 Vector4::Scale(Vector4 a, Vector4 b)
    {
        glm::vec4 result = a * b;
        return static_cast<Vector4>(result);
    }
}  // namespace UnityEngine
