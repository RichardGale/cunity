#ifndef SRC_UNITYENGINE_RECT_H_
#define SRC_UNITYENGINE_RECT_H_

#include <string>

#include "Vector2.h"
#include "Vector3.h"

namespace UnityEngine
{
    class Rect
    {
    public:
        Vector2 center();
        void center(Vector2 value);
        float height();
        void height(float value);
        Vector2 max();
        void max(Vector2 value);
        Vector2 min();
        void min(Vector2 value);
        Vector2 position();
        void position(Vector2 value);
        Vector2 size();
        void size(Vector2 value);
        float width();
        void width(float value);
        float x();
        void x(float value);
        float xMax();
        void xMax(float value);
        float xMin();
        void xMin(float value);
        float y();
        void y(float value);
        float yMax();
        void yMax(float value);
        float yMin();
        void yMin(float value);

        Rect(float x, float y, float width, float height);

        bool Contains(Vector2 point);
        bool Contains(Vector3 point, bool allowInverse);
        bool Overlaps(Rect other, bool allowInverse);

        void Set(float x, float y, float width, float height);

        std::string ToString();
        std::string ToString(std::string format);

        static Rect MinMaxRect(float xmin, float ymin, float xmax, float ymax);
        static Vector2 NormalizedToPoint(Rect rectangle, Vector2 normalizedRectCoordinates);

    private:
        Vector2 m_position;
        Vector2 m_size;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_RECT_H_
