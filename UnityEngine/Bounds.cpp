#include "UnityEngine/Bounds.h"

namespace UnityEngine
{
    Vector3 Bounds::center()
    {
        return m_center;
    }

    void Bounds::center(Vector3 value)
    {
        m_center = value;
    }

    Vector3 Bounds::extents()
    {
        return m_extents;
    }

    void Bounds::extents(Vector3 value)
    {
        m_extents = value;
    }

    Vector3 Bounds::max()
    {
        Vector3 result = m_center+m_extents;
        return result;
    }

    void Bounds::max(Vector3 value)
    {
        SetMinMax(min(), value);
    }

    Vector3 Bounds::min()
    {
        Vector3 result = m_center-m_extents;
        return result;
    }

    void Bounds::min(Vector3 value)
    {
        SetMinMax(value, max());
    }

    Vector3 Bounds::size()
    {
        return m_extents*2.0f;
    }

    void Bounds::size(Vector3 value)
    {
        m_extents = value*0.5f;
    }

    Bounds::Bounds(Vector3 center, Vector3 size)
    : m_center(center)
    , m_extents(size*0.5f)
    {
    }

    bool Bounds::operator==(Bounds rhs)
    {
        return (m_center == rhs.m_center && m_extents == rhs.m_extents);
    }

    bool Bounds::operator!=(Bounds rhs)
    {
        return !(*this == rhs);
    }

    Vector3 Bounds::ClosestPoint(Vector3 point)
    {
        Vector3 vmin = min();
        Vector3 vmax = max();

        for (int i = 0; i < 3; ++i)
        {
            point[i] = Mathf::Min(point[i], vmin[i]);
            point[i] = Mathf::Max(point[i], vmax[i]);
        }

        return point;
    }

    bool Bounds::Contains(Vector3 point)
    {
        Vector3 vmin = min();
        Vector3 vmax = max();

        if (point.x >= vmin.x &&
            point.x < vmax.x &&
            point.y >= vmin.y &&
            point.y < vmax.y &&
            point.z >= vmin.z &&
            point.z < vmax.z)
        {
            return true;
        }

        return false;
    }

    void Bounds::Encapsulate(Vector3 point)
    {
        SetMinMax(Vector3::Min(min(), point), Vector3::Max(max(), point));
    }

    void Bounds::Encapsulate(Bounds bounds)
    {
        Encapsulate(bounds.center() - bounds.extents());
        Encapsulate(bounds.center() + bounds.extents());
    }

    void Bounds::Expand(float amount)
    {
        amount *= 0.5f;
        m_extents.x += amount;
        m_extents.y += amount;
        m_extents.z += amount;
    }

    void Bounds::Expand(Vector3 amount)
    {
        m_extents.x += amount.x*0.5f;
        m_extents.y += amount.y*0.5f;
        m_extents.z += amount.z*0.5f;
    }

    bool Bounds::IntersectRay(Ray ray)
    {
        // http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms

        Vector3 dirfrac;

        // r.dir is unit direction vector of ray
        dirfrac.x = 1.0f / ray.direction().x;
        dirfrac.y = 1.0f / ray.direction().y;
        dirfrac.z = 1.0f / ray.direction().z;

        Vector3 lb = min();
        Vector3 rt = max();
        // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
        // r.org is origin of ray
        float t1 = (lb.x - ray.origin().x)*dirfrac.x;
        float t2 = (rt.x - ray.origin().x)*dirfrac.x;
        float t3 = (lb.y - ray.origin().y)*dirfrac.y;
        float t4 = (rt.y - ray.origin().y)*dirfrac.y;
        float t5 = (lb.z - ray.origin().z)*dirfrac.z;
        float t6 = (rt.z - ray.origin().z)*dirfrac.z;

        float tmin = Mathf::Max(Mathf::Max(Mathf::Min(t1, t2), Mathf::Min(t3, t4)), Mathf::Min(t5, t6));
        float tmax = Mathf::Min(Mathf::Min(Mathf::Max(t1, t2), Mathf::Max(t3, t4)), Mathf::Max(t5, t6));

        float t;

        // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
        if (tmax < 0)
        {
            t = tmax;
            return false;
        }
        
        // if tmin > tmax, ray doesn't intersect AABB
        if (tmin > tmax)
        {
            t = tmax;
            return false;
        }
        
        t = tmin;
        return true;
    }

    bool Bounds::Intersects(Bounds bounds)
    {
        if (min().x <= bounds.max().x &&
            max().x >= bounds.min().x &&
            (min().y <= bounds.max().y &&
             max().y >= bounds.min().y) &&
            min().z <= bounds.max().z)
        {
            return max().z >= bounds.min().z;
        }

        return false;
    }

    void Bounds::SetMinMax(Vector3 min, Vector3 max)
    {
        m_extents = (max - min) * 0.5f;
        m_center = min + m_extents;
    }

    float Bounds::SqrDistance(Vector3 point)
    {
        Vector3 vmin = min();
        Vector3 vmax = max();

        float sqDist = 0.0f;
        for (int i = 0; i < 3; ++i)
        {
            if (point[i] < vmin[i])
            {
                sqDist += (vmin[i]-point[i])*(vmin[i]-point[i]);
            }
            if (point[i] > vmax[i])
            {
                sqDist += (point[i]-vmax[i])*(point[i]-vmax[i]);
            }
        }
        return sqDist;
    }

    std::string Bounds::ToString()
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Center: %s, Extents: %s",
                 m_center.ToString().c_str(),
                 m_extents.ToString().c_str());
        return result;
    }

    std::string Bounds::ToString(std::string format)
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Center: %s, Extents: %s",
                 m_center.ToString(format).c_str(),
                 m_extents.ToString(format).c_str());
        return result;
    }
}

