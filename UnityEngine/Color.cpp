#include "UnityEngine/Color.h"

#include <string>

#include "glm/geometric.hpp"
#include "glm/gtx/color_space.hpp"
#include "glm/gtc/color_space.hpp"

#include "bx/fpumath.h"

#include "UnityEngine/Mathf.h"

namespace UnityEngine
{
    const Color Color::black(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::blue(0.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::clear(0.0f, 0.0f, 0.0f, 0.0f);
    const Color Color::cyan(0.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::gray(0.5f, 0.5f, 0.5f, 1.0f);
    const Color Color::green(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::grey(0.5f, 0.5f, 0.5f, 1.0f);
    const Color Color::magenta(1.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::red(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::white(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::yellow(1.0f, 0.92f, 0.016f, 1.0f);

    Color Color::gamma()
    {
        glm::vec3 rgb(r, g, b);
        glm::vec3 srgb = glm::convertLinearToSRGB(rgb);

        return Color(srgb.r, srgb.g, srgb.b, 1.0f);
    }

    float Color::grayscale()
    {
        float result = 0.299f * r + 0.587f * g + 0.114f * b;
        return result;
    }

    Color Color::linear()
    {
        glm::vec3 rgb(r, g, b);
        glm::vec3 linear = glm::convertSRGBToLinear(rgb);

        return Color(linear.r, linear.g, linear.b, 1.0f);
    }

    float Color::maxColorComponent()
    {
        return bx::fmax3(r, g, b);
    }

    Color::Color(glm::vec4 v)
    : glm::vec4(v)
    {
    }

    Color::Color(float r, float g, float b, float a)
    : glm::vec4(r, g, b, a)
    {
    }

    std::string Color::ToString() const
    {
        char message[1023+1];
        snprintf(message,
                 sizeof(message),
                 "RGBA(%0.3f, %0.3f, %0.3f, %0.3f)",
                 r,
                 g,
                 b,
                 a);
        return message;
    }

    std::string Color::ToString(std::string format) const
    {
        return std::string();
    }

    Color Color::HSVToRGB(float H, float S, float V, bool hdr)
    {
        assert(hdr == false);
        glm::vec3 hsv(H, S, V);
        glm::vec3 rgb = glm::rgbColor(hsv);
        return Color(rgb.r, rgb.g, rgb.b, 1.0f);
    }

    Color Color::Lerp(Color a, Color b, float t)
    {
        t = bx::fclamp(t, 0.0f, 1.0f);
        return LerpUnclamped(a, b, t);
    }

    Color Color::LerpUnclamped(Color a, Color b, float t)
    {
        glm::vec4 result = a*(1.0f-t) + b*t;
        return static_cast<Color>(result);
    }

    void RGBToHSV(Color rgbColor, float *H, float *S, float *V)
    {
        glm::vec3 rgb(rgb.r, rgb.g, rgb.b);
        glm::vec3 hsv = glm::hsvColor(rgb);
        *H = hsv.r;
        *S = hsv.g;
        *V = hsv.b;
    }
}  // namespace UnityEngine
