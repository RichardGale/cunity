#ifndef SRC_UNITYENGINE_VECTOR2_H_
#define SRC_UNITYENGINE_VECTOR2_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/vec2.hpp"

#include "Mathf.h"
#include "Time.h"

namespace UnityEngine
{
    class Vector2 : public glm::vec2
    {
    public:
        static const Vector2 down;
        static const Vector2 left;
        static const Vector2 one;
        static const Vector2 right;
        static const Vector2 up;
        static const Vector2 zero;

        float magnitude() const;
        Vector2 normalized() const;
        float sqrMagnitude() const;

        /*explicit*/ Vector2(glm::vec2 v);
        Vector2(float x = 0.0f, float y = 0.0f);

        void Normalize();
        void Set(float new_x, float new_y);
        std::string ToString() const;
        std::string ToString(std::string format) const;

        static float Angle(Vector2 from, Vector2 to);
        static Vector2 ClampMagnitude(Vector2 vector, float maxLength);
        static float Distance(Vector2 a, Vector2 b);
        static float Dot(Vector2 lhs, Vector2 rhs);
        static Vector2 Lerp(Vector2 a, Vector2 b, float t);
        static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
        static Vector2 Max(Vector2 lhs, Vector2 rhs);
        static Vector2 Min(Vector2 lhs, Vector2 rhs);
        static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);
        static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);
        static Vector2 Scale(Vector2 a, Vector2 b);
        static Vector2 SmoothDamp(Vector2 current,
                                  Vector2 target,
                                  Vector2 *currentVelocity,
                                  float smoothTime,
                                  float maxSpeed = Mathf::Infinity,
                                  float deltaTime = Time::deltaTime());
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_VECTOR2_H_
