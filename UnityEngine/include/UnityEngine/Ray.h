#ifndef SRC_UNITYENGINE_RAY_H_
#define SRC_UNITYENGINE_RAY_H_

#include <string>

#include "Vector3.h"

namespace UnityEngine
{
    class Ray
    {
    public:
        Vector3 direction();
        void direction(Vector3 value);
        Vector3 origin();
        void origin(Vector3 value);

        Ray(Vector3 origin = Vector3::zero, Vector3 direction = Vector3::zero);

        Vector3 GetPoint(float distance);
        std::string ToString();
        std::string ToString(std::string format);

    private:
        Vector3 m_origin;
        Vector3 m_direction;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_RAY_H_
