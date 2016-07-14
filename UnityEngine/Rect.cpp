#include "UnityEngine/Rect.h"

namespace UnityEngine
{
    Vector2 Rect::center()
    {
        return m_position+m_size*0.5f;
    }

    void Rect::center(Vector2 value)
    {
        m_position = value-m_size*0.5f;
    }

    float Rect::height()
    {
        return m_size.y;
    }

    void Rect::height(float value)
    {
        m_size.y = value;
    }

    Vector2 Rect::max()
    {
        return m_position+m_size;
    }

    void Rect::max(Vector2 value)
    {
        m_size = value-m_position;
    }

    Vector2 Rect::min()
    {
        return m_position;
    }

    void Rect::min(Vector2 value)
    {
        m_size = (m_position+m_size)-value;
        m_position = value;
    }

    Vector2 Rect::position()
    {
        return m_position;
    }

    void Rect::position(Vector2 value)
    {
        m_position = value;
    }

    Vector2 Rect::size()
    {
        return m_size;
    }

    void Rect::size(Vector2 value)
    {
        m_size = value;
    }

    float Rect::width()
    {
        return m_size.x;
    }

    void Rect::width(float value)
    {
        m_size.x = value;
    }

    float Rect::x()
    {
        return m_position.x;
    }

    void Rect::x(float value)
    {
        m_position.x = value;
    }

    float Rect::xMax()
    {
        return m_position.x+m_size.x;
    }

    void Rect::xMax(float value)
    {
        m_size.x = value-m_position.x;
    }

    float Rect::xMin()
    {
        return m_position.x;
    }

    void Rect::xMin(float value)
    {
        m_size.x = (m_position.x+m_size.x)-value;
        m_position.x = value;
    }

    float Rect::y()
    {
        return m_position.y;
    }

    void Rect::y(float value)
    {
        m_position.y = value;
    }

    float Rect::yMax()
    {
        return m_position.y+m_size.y;
    }

    void Rect::yMax(float value)
    {
        m_size.y = value-m_position.y;
    }

    float Rect::yMin()
    {
        return m_position.y;
    }

    void Rect::yMin(float value)
    {
        m_size.y = (m_position.y+m_size.y)-value;
        m_position.y = value;
    }

    Rect::Rect(float x, float y, float width, float height)
    : m_position(x, y)
    , m_size(width, height)
    {
    }

    bool Rect::Contains(Vector2 point)
    {
        bool result = (point.x >= m_position.x &&
                       point.y >= m_position.y &&
                       point.x < m_position.x+m_size.x &&
                       point.y < m_position.y+m_size.y);
        return result;
    }

    bool Rect::Contains(Vector3 point, bool allowInverse)
    {
        Vector2 vMin = m_position;
        Vector2 vMax = m_position+m_size;

        if (allowInverse)
        {
            vMin = Vector2::Min(m_position, m_position+m_size);
            vMax = Vector2::Max(m_position, m_position+m_size);
        }

        bool result = (point.x >= vMin.x &&
                       point.x < vMax.x &&
                       point.y >= vMin.y &&
                       point.y < vMax.y);
        return result;
    }

    bool Rect::Overlaps(Rect other, bool allowInverse)
    {
        Vector2 vMin = m_position;
        Vector2 vMax = m_position+m_size;

        Vector2 vMinOther = other.m_position;
        Vector2 vMaxOther = other.m_position+other.m_size;


        if (allowInverse)
        {
            vMin = Vector2::Min(m_position, m_position+m_size);
            vMax = Vector2::Max(m_position, m_position+m_size);

            vMinOther = Vector2::Min(other.m_position, other.m_position+other.m_size);
            vMaxOther = Vector2::Max(other.m_position, other.m_position+other.m_size);
        }

        bool result = (vMin.x < vMaxOther.x &&
                       vMax.x > vMinOther.x &&
                       vMin.y < vMax.y &&
                       vMax.y > vMin.y);
        return result;
    }

    void Rect::Set(float x, float y, float width, float height)
    {
        m_position.x = x;
        m_position.y = y;
        m_size.x = width;
        m_size.y = height;
    }

    std::string Rect::ToString()
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Position: %s, Size: %s",
                 m_position.ToString().c_str(),
                 m_size.ToString().c_str());
        return result;
    }

    std::string Rect::ToString(std::string format)
    {
        char result[1023+1];
        snprintf(result,
                 sizeof(result),
                 "Position: %s, Size: %s",
                 m_position.ToString(format).c_str(),
                 m_size.ToString(format).c_str());
        return result;
    }

    Rect Rect::MinMaxRect(float xmin, float ymin, float xmax, float ymax)
    {
        Rect result(xmin, ymin, xmax-xmin, ymax-ymin);
        return result;
    }

    Vector2 Rect::NormalizedToPoint(Rect rectangle, Vector2 normalizedRectCoordinates)
    {
        Vector2 result = Vector2(Mathf::Lerp(rectangle.x(),
                                             rectangle.xMax(),
                                             normalizedRectCoordinates.x),
                                 Mathf::Lerp(rectangle.y(),
                                             rectangle.yMax(),
                                             normalizedRectCoordinates.y));
        return result;
    }
}
