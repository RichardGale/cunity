#include "UnityEngine/Ray.h"

#include <string>

namespace UnityEngine
{
    Vector3 Ray::direction()
    {
        return m_direction;
    }

    void Ray::direction(Vector3 value)
    {
        m_direction = value;
    }

    Vector3 Ray::origin()
    {
        return m_origin;
    }

    void Ray::origin(Vector3 value)
    {
        m_origin = value;
    }

    Ray::Ray(Vector3 origin, Vector3 direction)
    : m_origin(origin)
    , m_direction(direction)
    {
    }

    Vector3 Ray::GetPoint(float distance)
    {
        return m_origin+m_direction*distance;
    }

    std::string Ray::ToString()
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Origin: %s, Dir: %s",
                 m_origin.ToString().c_str(),
                 m_direction.ToString().c_str());
        return result;
    }

    std::string Ray::ToString(std::string format)
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Origin: %s, Dir: %s",
                 m_origin.ToString(format).c_str(),
                 m_direction.ToString(format).c_str());
        return result;
    }
}  // namespace UnityEngine
