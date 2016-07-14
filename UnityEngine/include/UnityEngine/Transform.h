#ifndef SRC_UNITYENGINE_TRANSFORM_H_
#define SRC_UNITYENGINE_TRANSFORM_H_

#include <string>

//#include "Component.h"

#include "Object.h"

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4x4.h"

namespace UnityEngine
{
    class GameObject;

    struct Space
    {
        enum Enum
        {
            World,
            Self
        };
    };

    class Transform : public Object //: public Component
    {
    public:
        Transform();
        GameObject* gameObject();

        int childCount();
        Vector3 eulerAngles();
        void eulerAngles(Vector3 value);
        Vector3 forward();
        void forward(Vector3 value);
        bool hasChanged();
        void hasChanged(bool changed);
        Vector3 localEulerAngles();
        void localEulerAngles(Vector3 eulerAngles);
        Vector3 localPosition();
        void localPosition(Vector3 position);
        Quaternion localRotation();
        void localRotation(Quaternion rotation);
        Vector3 localScale();
        void localScale(Vector3 scale);
        Matrix4x4 localToWorldMatrix();
        Vector3 lossyScale();
        Transform* parent();
        void parent(Transform *parent);
        Vector3 position();
        void position(Vector3 pos);
        Vector3 right();
        void right(Vector3 value);
        Transform* root();
        Quaternion rotation();
        void rotation(Quaternion r);
        Vector3 up();
        void up(Vector3 value);
        Matrix4x4 worldToLocalMatrix();

        void DetachChildren();
        Transform* Find(const char *name);
        Transform* GetChild(int index);
        int GetSiblingIndex();
        Vector3 InverseTransformDirection(Vector3 direction);
        Vector3 InverseTransformDirection(float x, float y, float z);
        Vector3 InverseTransformPoint(Vector3 position);
        Vector3 InverseTransformPoint(float x, float y, float z);
        Vector3 InverseTransformVector(Vector3 vector);
        Vector3 InverseTransformVector(float x, float y, float z);
        bool IsChildOf(Transform *parent);
        void LookAt(Transform *target, Vector3 worldUp = Vector3::up);
        void LookAt(Vector3 worldPosition, Vector3 worldUp = Vector3::up);
        void Rotate(Vector3 eulerAngles, Space::Enum relativeTo = Space::Self);
        void Rotate(float xAngle, float yAngle, float zAngle, Space::Enum relativeTo = Space::Self);;
        void Rotate(Vector3 axis, float angle, Space::Enum relativeTo = Space::Self);
        void RotateAround(Vector3 point, Vector3 axis, float angle);
        void SetAsFirstSibling();
        void SetAsLastSibling();
        void SetParent(Transform *parent, bool worldPositionStays);
        void SetSiblingIndex(int index);
        Vector3 TransformDirection(Vector3 direction);
        Vector3 TransformDirection(float x, float y, float z);
        Vector3 TransformPoint(Vector3 position);
        Vector3 TransformPoint(float x, float y, float z);
        Vector3 TransformVector(Vector3 vector);
        Vector3 TransformVector(float x, float y, float z);
        void Translate(Vector3 translation, Space::Enum relativeTo = Space::Self);
        void Translate(float x, float y, float z, Space::Enum relativeTo = Space::Self);
        void Translate(Vector3 translation, Transform *relativeTo);

        std::vector<Transform*> GetChildren_Internal(bool recursive, bool includeInactive);

    private:
        GameObject *m_gameObject;

        Transform *m_parent;
        std::vector<Transform*> m_children;
        bool m_changed;

        Vector3 m_localPosition;
        Vector3 m_localScale;
        Quaternion m_localRotation;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_TRANSFORM_H_

