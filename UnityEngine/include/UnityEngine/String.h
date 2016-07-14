#ifndef SRC_UNITYENGINE_STRING_H_
#define SRC_UNITYENGINE_STRING_H_

#include "Object.h"

namespace UnityEngine
{
    class String : public Object
    {
    public:
        String()
        {
        }

        String(int number)
        {
            str = std::to_string(number);
        }

        String(float number)
        {
            str = std::to_string(number);
        }

        String(Color color)
        {
        }

        String(char* string)
        {
            str = std::string(string);
        }

        String(const char* string)
        {
            str = std::string(string);
        }

        String(std::string string)
        {
            str = string;
        }

        String(Object* object)
        {
            if (object)
            {
                str = object->ToString();
            }
            else
            {
                str = "NULL";
            }
        }

        virtual ~String()
        {
            m_refCount = 0;
        }

        String operator+ (const char* string)
        {
            str += std::string(string);
            return *this;
        }

        String operator+ (int number)
        {
            str += std::to_string(number);
            return *this;
        }

        String operator+ (float number)
        {
            str += std::to_string(number);
            return *this;
        }
        
        const char* c_str()
        {
            return str.c_str();
        }
        
    private:
        std::string str;
    };
};

#endif // SRC_UNITYENGINE_STRING_H_