#ifndef SRC_UNITYENGINE_QUATERNION_H_
#define SRC_UNITYENGINE_QUATERNION_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/gtc/quaternion.hpp"

#include "Vector3.h"

namespace UnityEngine
{
    class Quaternion : public glm::quat
    {
    public:
        static const Quaternion identity;

        Vector3 eulerAngles() const;

        /*explicit*/ Quaternion(glm::quat q);
        /*explicit*/ Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

        void Set(float new_x, float new_y, float new_z, float new_w);
        void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection);
        void SetLookRotation(Vector3 view, Vector3 up = Vector3::up);
        void ToAngleAxis(float *angle, Vector3 *axis);
        std::string ToString() const;
        std::string ToString(std::string format) const;

        static float Angle(Quaternion a, Quaternion b);
        static Quaternion AngleAxis(float angle, Vector3 axis);
        static float Dot(Quaternion a, Quaternion b);
        static Quaternion Euler(float x, float y, float z);
        static Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection);
        static Quaternion Inverse(Quaternion rotation);
        static Quaternion Lerp(Quaternion a, Quaternion b, float t);
        static Quaternion LerpUnclamped(Quaternion a, Quaternion b, float t);
        static Quaternion LookRotation(Vector3 forward, Vector3 upwards = Vector3::up);
        static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta);
        static Quaternion Slerp(Quaternion a, Quaternion b, float t);
        static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t);

        //        bool operator!=(Quaternion rhs);
        //        Quaternion operator*(Quaternion rhs);
        //        bool operator==(Quaternion rhs);
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_QUATERNION_H_
