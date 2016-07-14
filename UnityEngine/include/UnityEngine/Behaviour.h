#ifndef SRC_UNITYENGINE_BEHAVIOUR_H
#define SRC_UNITYENGINE_BEHAVIOUR_H

#include "Component.h"

namespace UnityEngine
{
    class Behaviour : public Component
    {
    protected:
        virtual ~Behaviour()
        {
        }
        
    public:
        bool enabled()
        {
            return m_enabled;
        }

        virtual void enabled(bool value)
        {
            m_enabled = value;
        }

        bool isActiveAndEnabled()
        {
            bool result = m_enabled;
            if (m_enabled)
            {
                result = gameObject()->activeInHierarchy();
            }
            return result;
        }

    private:
        bool m_enabled;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_MONOBEHAVIOUR_H
