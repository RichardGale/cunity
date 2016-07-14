#ifndef SRC_UNITYENGINE_VECTOR3_H_
#define SRC_UNITYENGINE_VECTOR3_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/vec3.hpp"

#include "Mathf.h"
#include "Time.h"

namespace UnityEngine
{
    class Vector3 : public glm::vec3
    {
    public:
        static const Vector3 back;
        static const Vector3 down;
        static const Vector3 forward;
        static const Vector3 left;
        static const Vector3 one;
        static const Vector3 right;
        static const Vector3 up;
        static const Vector3 zero;

        float magnitude() const;
        Vector3 normalized() const;
        float sqrMagnitude() const;

        /*explicit*/ Vector3(glm::vec3 v);
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void Normalize();
        void Set(float new_x, float new_y, float new_z);
        std::string ToString() const;
        std::string ToString(std::string format) const;

        Vector3 operator*(int value) const;
        Vector3 operator*(float value) const;

        static float Angle(Vector3 from, Vector3 to);
        static Vector3 ClampMagnitude(Vector3 vector, float maxLength);
        static float Distance(Vector3 a, Vector3 b);
        static float Dot(Vector3 lhs, Vector3 rhs);
        static Vector3 Lerp(Vector3 a, Vector3 b, float t);
        static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
        static Vector3 Max(Vector3 lhs, Vector3 rhs);
        static Vector3 Min(Vector3 lhs, Vector3 rhs);
        static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
        static void OrthoNormalize(Vector3 *normal, Vector3 *tangent);
        static Vector3 Project(Vector3 vector, Vector3 onNormal);
        static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);
        static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);
        static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);
        static Vector3 Scale(Vector3 a, Vector3 b);
        static Vector3 Slerp(Vector3 a, Vector3 b, float t);
        static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
        static Vector3 SmoothDamp(Vector3 current,
                                  Vector3 target,
                                  Vector3 *currentVelocity,
                                  float smoothTime,
                                  float maxSpeed = Mathf::Infinity,
                                  float deltaTime = Time::deltaTime());
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_VECTOR2_H_
