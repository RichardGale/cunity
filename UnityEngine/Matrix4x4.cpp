#include "UnityEngine/Matrix4x4.h"

#include <string>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/gtx/matrix_query.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "UnityEngine/Mathf.h"

namespace UnityEngine
{
    const Matrix4x4 Matrix4x4::identity(1.0f);
    const Matrix4x4 Matrix4x4::zero(0.0f);

    float Matrix4x4::determinant() const
    {
        float result = glm::determinant(*this);
        return result;
    }

    Matrix4x4 Matrix4x4::inverse() const
    {
        glm::mat4x4 result = glm::inverse(*this);
        return static_cast<Matrix4x4>(result);
    }

    bool Matrix4x4::isIdentity() const
    {
        return glm::isIdentity(*this, Mathf::Epsilon);
    }

    Matrix4x4 Matrix4x4::transpose() const
    {
        glm::mat4x4 result = glm::transpose(*this);
        return static_cast<Matrix4x4>(result);
    }

    Matrix4x4::Matrix4x4(glm::mat4x4 m)
    : glm::mat4x4(m)
    {
    }

    Matrix4x4::Matrix4x4(float f)
    : glm::mat4x4(f)
    {
    }

    Vector4 Matrix4x4::GetColumn(int i) const
    {
        Vector4 result = static_cast<Vector4>(glm::column(*this, i));
        return result;
    }

    Vector4 Matrix4x4::GetRow(int i) const
    {
        Vector4 result = static_cast<Vector4>(glm::row(*this, i));
        return result;
    }

    Vector3 Matrix4x4::MultiplyPoint(Vector3 v) const
    {
        Vector3 result;
        result.x = (*this)[0][0] * v.x + (*this)[0][1] * v.y + (*this)[0][2] * v.z + (*this)[0][3];
        result.y = (*this)[1][0] * v.x + (*this)[1][1] * v.y + (*this)[1][2] * v.z + (*this)[1][3];
        result.z = (*this)[2][0] * v.x + (*this)[2][1] * v.y + (*this)[2][2] * v.z + (*this)[2][3];
        float num = (*this)[3][0] * v.x + (*this)[3][1] * v.y + (*this)[3][2] * v.z + (*this)[3][3];
        num = 1.0f / num;
        result.x *= num;
        result.y *= num;
        result.z *= num;
        return result;
    }

    Vector3 Matrix4x4::MultiplyPoint3x4(Vector3 v) const
    {
        Vector3 result;
        result.x = (*this)[0][0] * v.x + (*this)[0][1] * v.y + (*this)[0][2] * v.z + (*this)[0][3];
        result.y = (*this)[1][0] * v.x + (*this)[1][1] * v.y + (*this)[1][2] * v.z + (*this)[1][3];
        result.z = (*this)[2][0] * v.x + (*this)[2][1] * v.y + (*this)[2][2] * v.z + (*this)[2][3];
        return result;
    }

    Vector3 Matrix4x4::MultiplyVector(Vector3 v) const
    {
        Vector3 result;
        result.x = (*this)[0][0] * v.x + (*this)[0][1] * v.y + (*this)[0][2] * v.z;
        result.y = (*this)[1][0] * v.x + (*this)[1][1] * v.y + (*this)[1][2] * v.z;
        result.z = (*this)[2][0] * v.x + (*this)[2][1] * v.y + (*this)[2][2] * v.z;
        return result;
    }

    void Matrix4x4::SetColumn(int i, Vector4 v)
    {
        glm::column(*this, i, v);
    }

    void Matrix4x4::SetRow(int i, Vector4 v)
    {
        glm::row(*this, i, v);
    }

    void Matrix4x4::SetTRS(Vector3 pos, Quaternion q, Vector3 s)
    {
        glm::mat4x4 translate = glm::translate(pos);
        glm::mat4x4 rotate = glm::mat4_cast(q);
        glm::mat4x4 scale = glm::scale(s);

        *this = static_cast<Matrix4x4>(translate * rotate * scale);
    }

    std::string Matrix4x4::ToString() const
    {
        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "%0.5f\t%0.5f\t%0.5f\t%0.5f\n%0.5f\t%0.5f\t%0.5f\t%0.5f\n%0.5f\t%0.5f\t%0.5f\t%0.5f\n%0.5f\t%0.5f\t%0.5f\t%0.5f\n",
                 (*this)[0][0],
                 (*this)[0][1],
                 (*this)[0][2],
                 (*this)[0][3],
                 (*this)[1][0],
                 (*this)[1][1],
                 (*this)[1][2],
                 (*this)[1][3],
                 (*this)[2][0],
                 (*this)[2][1],
                 (*this)[2][2],
                 (*this)[2][3],
                 (*this)[3][0],
                 (*this)[3][1],
                 (*this)[3][2],
                 (*this)[3][3]);
        return message;
    }

    std::string Matrix4x4::ToString(std::string format) const
    {
        assert(false);
        return std::string();
    }

    Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        glm::mat4x4 result = glm::ortho(left, right, bottom, top, zNear, zFar);
        return static_cast<Matrix4x4>(result);
    }

    Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar)
    {
        glm::mat4x4 result = glm::perspective(fov, aspect, zNear, zFar);
        return static_cast<Matrix4x4>(result);
    }

    Matrix4x4 Matrix4x4::Scale(Vector3 v)
    {
        glm::mat4x4 result = glm::scale(v);
        return static_cast<Matrix4x4>(result);
    }

    Matrix4x4 Matrix4x4::TRS(Vector3 pos, Quaternion q, Vector3 s)
    {
        glm::mat4x4 translate = glm::translate(pos);
        glm::mat4x4 rotate = glm::mat4_cast(q);
        glm::mat4x4 scale = glm::scale(s);

        glm::mat4x4 result = translate * rotate * scale;
        return static_cast<Matrix4x4>(result);
    }
}  // namespace UnityEngine
