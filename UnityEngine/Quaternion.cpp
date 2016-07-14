#include "UnityEngine/Quaternion.h"

#include <string>

#include "glm/gtx/vector_angle.hpp"

#include "UnityEngine/Vector3.h"

namespace UnityEngine
{
    const Quaternion Quaternion::identity(0.0f, 0.0f, 0.0f, 0.0f);

    Vector3 Quaternion::eulerAngles() const
    {
        glm::vec3 result = glm::eulerAngles(*this);
        return static_cast<Vector3>(result);
    }

    Quaternion::Quaternion(glm::quat q)
    : glm::quat(q)
    {
    }

    Quaternion::Quaternion(float x, float y, float z, float w)
    : glm::quat(x, y, z, w)
    {
    }

    void Quaternion::Set(float new_x, float new_y, float new_z, float new_w)
    {
        x = new_x;
        y = new_y;
        z = new_z;
        w = new_w;
    }

    void Quaternion::SetFromToRotation(Vector3 fromDirection, Vector3 toDirection)
    {
        glm::quat result = glm::rotation(fromDirection, toDirection);
        x = result.x;
        y = result.y;
        z = result.z;
        w = result.w;
    }

    void Quaternion::SetLookRotation(Vector3 view, Vector3 up)
    {
        assert(false);
    }

    void Quaternion::ToAngleAxis(float *angle, Vector3 *axis)
    {
        assert(false);
    }

    std::string Quaternion::ToString() const
    {
        return std::string();
    }

    std::string Quaternion::ToString(std::string format) const
    {
        return std::string();
    }

    float Quaternion::Angle(Quaternion a, Quaternion b)
    {
        assert(false);
        return 0.0f;
    }

    Quaternion Quaternion::AngleAxis(float angle, Vector3 axis)
    {
        glm::quat result = glm::angleAxis(angle, static_cast<glm::vec3>(axis));
        return static_cast<Quaternion>(result);
    }

    float Quaternion::Dot(Quaternion a, Quaternion b)
    {
        float result = glm::dot(static_cast<glm::quat>(a), static_cast<glm::quat>(b));
        return result;
    }

    Quaternion Quaternion::Euler(float x, float y, float z)
    {
        glm::quat result = glm::quat(glm::vec3(x, y, z));
        return static_cast<Quaternion>(result);
    }

    Quaternion Quaternion::FromToRotation(Vector3 fromDirection, Vector3 toDirection)
    {
        glm::quat result = glm::rotation(fromDirection, toDirection);
        return static_cast<Quaternion>(result);
    }

    Quaternion Quaternion::Inverse(Quaternion rotation)
    {
        glm::quat result = glm::inverse(rotation);
        return static_cast<Quaternion>(result);
    }

    Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
    {
        t = glm::clamp(t, 0.0f, 1.0f);
        return LerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        glm::quat result = glm::lerp(a, b, t);
        return static_cast<Quaternion>(result);
    }

    Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
    {
        assert(false);
        return identity;
    }

    Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta)
    {
        assert(false);
        return identity;
    }

    Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
    {
        t = glm::clamp(t, 0.0f, 1.0f);
        return SlerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        glm::quat result = glm::mix(static_cast<glm::quat>(a), static_cast<glm::quat>(b), t);
        return static_cast<Quaternion>(result);
    }
}  // namespace UnityEngine
