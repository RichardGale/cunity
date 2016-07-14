#ifndef SRC_UNITYENGINE_MATRIX4X4_H_
#define SRC_UNITYENGINE_MATRIX4X4_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/mat4x4.hpp"

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

namespace UnityEngine
{
    class Matrix4x4 : public glm::mat4x4
    {
    public:
        static const Matrix4x4 identity;
        static const Matrix4x4 zero;

        float determinant() const;
        Matrix4x4 inverse() const;
        bool isIdentity() const;
        Matrix4x4 transpose() const;

        /*explicit*/ Matrix4x4(glm::mat4x4 m);
        /*explicit*/ Matrix4x4(float f = 1.0f);

        Vector4 GetColumn(int i) const;
        Vector4 GetRow(int i) const;
        Vector3 MultiplyPoint(Vector3 v) const;
        Vector3 MultiplyPoint3x4(Vector3 v) const;
        Vector3 MultiplyVector(Vector3 v) const;
        void SetColumn(int i, Vector4 v);
        void SetRow(int i, Vector4 v);
        void SetTRS(Vector3 pos, Quaternion q, Vector3 s);
        std::string ToString() const;
        std::string ToString(std::string format) const;

        static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
        static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);
        static Matrix4x4 Scale(Vector3 v);
        static Matrix4x4 TRS(Vector3 pos, Quaternion q, Vector3 s);
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_MATRIX4X4_H_
