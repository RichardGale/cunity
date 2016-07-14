#ifndef SRC_UNITYENGINE_COLOR_H_
#define SRC_UNITYENGINE_COLOR_H_

#include <string>

#define GLM_FORCE_EXPLICIT_CTOR
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_FORCE_SIZE_FUNC
#include "glm/vec4.hpp"

namespace UnityEngine
{
    class Color : public glm::vec4
    {
    public:
        static const Color black;
        static const Color blue;
        static const Color clear;
        static const Color cyan;
        static const Color gray;
        static const Color green;
        static const Color grey;
        static const Color magenta;
        static const Color red;
        static const Color white;
        static const Color yellow;

        Color gamma();
        float grayscale();
        Color linear();
        float maxColorComponent();

        /* explicit */ Color(glm::vec4 v);
        Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

        std::string ToString() const;
        std::string ToString(std::string format) const;
        static Color HSVToRGB(float H, float S, float V, bool hdr = false);
        static Color Lerp(Color a, Color b, float t);
        static Color LerpUnclamped(Color a, Color b, float t);
        static void RGBToHSV(Color rgbColor, float *H, float *S, float *V);
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_COLOR_H_
