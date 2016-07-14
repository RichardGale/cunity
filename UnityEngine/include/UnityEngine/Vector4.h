#ifndef SRC_UNITYENGINE_VECTOR4_H_
#define SRC_UNITYENGINE_VECTOR4_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/vec4.hpp"

#include "Vector3.h"

namespace UnityEngine
{
    class Vector4 : public glm::vec4
    {
    public:
        static const Vector4 one;
        static const Vector4 zero;

        float magnitude() const;
        Vector4 normalized() const;
        float sqrMagnitude() const;

        /*explicit*/ Vector4(glm::vec4 v);
        Vector4(float x, float y, float z, float w);
        Vector4(Vector3 v);
        void Normalize();
        void Set(float new_x, float new_y, float new_z, float new_w);
        std::string ToString() const;
        std::string ToString(std::string format) const;

        static float Distance(Vector4 a, Vector4 b);
        static float Dot(Vector4 lhs, Vector4 rhs);
        static Vector4 Lerp(Vector4 a, Vector4 b, float t);
        static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
        static Vector4 Max(Vector4 lhs, Vector4 rhs);
        static Vector4 Min(Vector4 lhs, Vector4 rhs);
        static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);
        static Vector4 Project(Vector4 a, Vector4 b);
        static Vector4 Scale(Vector4 a, Vector4 b);

        //        Vector4 operator-(Vector4 rhs);
        //        bool operator!=(Vector4 rhs);
        //        Vector4 operator*(float rhs);
        //        Vector4 operator/(float rhs);
        //        Vector4 operator+(Vector4 rhs);
        //        bool operator==(Vector4 rhs);
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_VECTOR4_H_
