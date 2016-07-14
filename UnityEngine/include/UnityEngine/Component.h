#ifndef SRC_UNITYENGINE_COMPONENT_H_
#define SRC_UNITYENGINE_COMPONENT_H_

#include "Object.h"

#include <string>
#include <vector>

#include "SendMessageOptions.h"
#include "GameObject.h"

namespace UnityEngine
{
    class Transform;
    
    class Component : public Object
    {
    public:
        GameObject* gameObject();
        std::string tag();
        void tag(std::string value);
        Transform* transform();

        void BroadcastMessage(std::string methodName,
                              void *parameter = nullptr,
                              SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        void BroadcastMessage(std::string methodName,
                              SendMessageOptions::Enum options);

        bool CompareTag(std::string tag);

        template<class T>
        T* GetComponent()
        {
            return m_gameObject->GetComponent<T>();
        }

        template<class T>
        T* GetComponentInChildren(bool includeInactive = false)
        {
            return m_gameObject->GetComponentInChildren<T>(includeInactive);
        }

        template<class T>
        T* GetComponentInParent()
        {
            return m_gameObject->GetComponentInParent<T>();
        }

        template<class T>
        std::vector<T*> GetComponents()
        {
            return m_gameObject->GetComponents<T>();
        }

        template<class T>
        std::vector<T*> GetComponentsInChildren(bool includeInactive = false)
        {
            return m_gameObject->GetComponentsInChildren<T>(includeInactive);
        }

        template<class T>
        std::vector<T*> GetComponentsInParent()
        {
            return m_gameObject->GetComponentsInParent<T>();
        }
        
        void SendMessage(std::string methodName,
                         void *value = nullptr,
                         SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        void SendMessage(std::string methodName, SendMessageOptions::Enum options);

        void SendMessageUpwards(std::string
                                methodName,
                                SendMessageOptions::Enum options);

        void SendMessageUpwards(std::string methodName,
                                void *value = nullptr,
                                SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

    public:
        Component();
    protected:
        virtual ~Component();
    private:
        GameObject *m_gameObject;
    };
};  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_COMPONENT_H_
