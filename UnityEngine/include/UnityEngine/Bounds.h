#ifndef SRC_UNITYENGINE_BOUNDS_H_
#define SRC_UNITYENGINE_BOUNDS_H_

#include "Vector3.h"

#include "Ray.h"
#include "Vector3.h"

namespace UnityEngine
{
    class Bounds
    {
    public:
        Vector3 center();
        void center(Vector3 value);
        Vector3 extents();
        void extents(Vector3 value);
        Vector3 max();
        void max(Vector3 value);
        Vector3 min();
        void min(Vector3 value);
        Vector3 size();
        void size(Vector3 value);

        Bounds(Vector3 center = Vector3::zero, Vector3 size = Vector3::zero);

        bool operator==(Bounds rhs);
        bool operator!=(Bounds rhs);

        Vector3 ClosestPoint(Vector3 point);
        bool Contains(Vector3 point);
        void Encapsulate(Vector3 point);
        void Encapsulate(Bounds bounds);
        void Expand(float amount);
        void Expand(Vector3 amount);
        bool IntersectRay(Ray ray);
        bool Intersects(Bounds bounds);
        void SetMinMax(Vector3 min, Vector3 max);
        float SqrDistance(Vector3 point);
        
        std::string ToString();
        std::string ToString(std::string format);
        
    private:
        Vector3 m_center;
        Vector3 m_extents;
    };
}

#endif  // SRC_UNITYENGINE_BOUNDS_H_
