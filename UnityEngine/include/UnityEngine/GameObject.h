#ifndef SRC_UNITYENGINE_GAMEOBJECT_H_
#define SRC_UNITYENGINE_GAMEOBJECT_H_

#include <string>
#include <vector>

#include "Object.h"
#include "Transform.h"
#include "SendMessageOptions.h"

namespace UnityEngine
{
    class Component;

    namespace SceneManagement
    {
        struct Scene
        {
        };
    }

    struct PrimitiveType
    {
        enum Enum
        {
            Sphere,
            Capsule,
            Cylinder,
            Cube,
            Plane,
            Quad
        };
    };

    class GameObjectHandle;

    class GameObject : public Object
    {
    public:
        bool activeInHierarchy();
        bool activeSelf();
        bool isStatic();
        void isStatic(bool value);
        int layer();
        void layer(int value);
        SceneManagement::Scene* scene();
        std::string tag();
        void tag(std::string value);
        GameObject* gameObject();
        Transform* transform();

    private:
        GameObject(std::string name = "");
        GameObject(std::string name, std::vector<Component*> components);
        GameObject(GameObject *go);
        virtual ~GameObject();

    public:
        static GameObject *s_gameObject;
        static std::vector<GameObject*> s_gameObjects;
        static std::vector<GameObject*> s_justActive;
        static std::vector<GameObject*> s_justInactive;

        template<class T>
        T* AddComponent()
        {
            s_gameObject = this;

            T* result = new T();
            if (result)
            {
                m_components.push_back(result);
            }

            return result;
        }

        Component* AddComponent(Component *value)
        {
            m_components.push_back(value);
            return value;
        }

        void BroadcastMessage(std::string methodName,
                              void *parameter = nullptr,
                              SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        void BroadcastMessage(std::string methodName,
                              SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        bool CompareTag(std::string tag);

        Component* GetComponent(std::string name);

        template<class T>
        T* GetComponent()
        {
            for (int i = 0; i < m_components.size(); ++i)
            {
                T *component = dynamic_cast<T*>(m_components[i]);
                if (component)
                {
                    return component;
                }
            }
            return nullptr;
        }

        template<class T>
        T* GetComponentInChildren(bool includeInactive = false)
        {
            if (activeInHierarchy())
            {
                T *component = GetComponent<T>();
                if (component != nullptr)
                {
                    return component;
                }
            }
            std::vector<Transform*> children = m_transform->GetChildren_Internal(true, includeInactive);
            for (int i = 0; i < children.size(); ++i)
            {
                T *component = children[i]->gameObject()->GetComponent<T>();
                if (component != nullptr)
                {
                    return component;
                }
            }
            return nullptr;
        }

        template<class T>
        T* GetComponentInParent()
        {
            if (activeInHierarchy())
            {
                T *component = GetComponent<T>();
                if (component != nullptr)
                {
                    return component;
                }
            }
            Transform *parent = m_transform->parent();
            while (parent != nullptr)
            {
                if (parent->gameObject()->activeInHierarchy())
                {
                    T *component = parent->gameObject()->GetComponent<T>();
                    if (component != nullptr)
                    {
                        return component;
                    }
                }
                parent = parent->parent();
            }
            return nullptr;
        }

        template<class T>
        std::vector<T*> GetComponents()
        {
            std::vector<T*> result;

            for (int i = 0; i < m_components.size(); ++i)
            {
                T* component = dynamic_cast<T*>(m_components[i]);
                if (component)
                {
                    result.push_back(component);
                }
            }

            return result;
        }

        template<class T>
        std::vector<T*> GetComponentsInChildren(bool includeInactive = false)
        {
            std::vector<T*> result;

            std::vector<Transform*> children = m_transform->GetChildren_Internal(true, includeInactive);
            for (int i = 0; i < children.size(); ++i)
            {
                for (int j = 0; j < children[i]->gameObject()->m_components.size(); ++j)
                {
                    T* component = dynamic_cast<T*>(children[i]->gameObject()->m_components[j]);
                    if (component)
                    {
                        result.push_back(component);
                    }
                }
            }

            return result;
        }

        template<class T>
        std::vector<T*> GetComponentsInParent()
        {
            std::vector<T*> result;

            if (activeInHierarchy())
            {
                result = GetComponents<T>();
            }

            if (result.empty())
            {
                Transform *parent = m_transform->parent();
                while (parent != nullptr)
                {
                    GameObject *parentGO = parent->gameObject();
                    if (parentGO->activeInHierarchy())
                    {
                        for (int i = 0; i < parentGO->m_components.size(); ++i)
                        {
                            T* component = dynamic_cast<T*>(parentGO->m_components[i]);
                            if (component)
                            {
                                result.push_back(component);
                            }
                        }
                    }
                    parent = parent->parent();
                }
            }

            return result;
        }

        void SendMessage(std::string methodName,
                         void *value = nullptr,
                         SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        void SendMessage(std::string methodName,
                         SendMessageOptions::Enum options);

        void SendMessageUpwards(std::string methodName,
                                SendMessageOptions::Enum options);

        void SendMessageUpwards(std::string methodName,
                                void *value = nullptr,
                                SendMessageOptions::Enum options = SendMessageOptions::RequireReceiver);

        void SetActive(bool value);

        static GameObjectHandle CreatePrimitive(PrimitiveType::Enum type);
        static GameObjectHandle Find(std::string name);
        static std::vector<GameObjectHandle> FindGameObjectsWithTag(std::string tag);
        static GameObjectHandle FindWithTag(std::string tag);

        static void Update_Internal();
        void SetActive_Internal(bool activeSelf, bool activeInHierarchy);

        virtual void Destroy_Internal();
    protected:

        Transform *m_transform;
        
        bool m_activeSelf;
        bool m_activeInHierarchy;
        bool m_isStatic;
        int m_layer;
        std::string m_tag;

        std::vector<Component*> m_components;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_GAMEOBJECT_H_
