#ifndef SRC_UNITYENGINE_OBJECT_H_
#define SRC_UNITYENGINE_OBJECT_H_

#include <string>

#include "Vector3.h"
#include "Quaternion.h"
#include "Color.h"

namespace UnityEngine
{
    class GameObjectHandle;
    class Object;
    typedef Object* ObjectHandle;

    struct HideFlags
    {
        enum Enum
        {
            None,
            HideInHierarchy,
            HideInInspector,
            DontSaveInEditor,
            NotEditable,
            DontSaveInBuild,
            DontUnloadUnusedAsset,
            DontSave,
            HideAndDontSave
        };
    };

    class Object
    {
    public:
        HideFlags::Enum hideFlags();
        void hideFlags(HideFlags::Enum value);
        std::string name();
        void name(std::string value);

        Object(std::string name = "");
        Object(Object *obj);

    protected:
        virtual ~Object();
    public:
        int GetInstanceID();
        std::string ToString();

        static void Destroy(Object *obj, float t = 0.0f);
        static void DestroyImmediate(Object *obj,
                                     bool allowDestroyingAssets = false);
        static void DontDestroyOnLoad(Object *obj);

        static void Destroy(GameObjectHandle go, float t = 0.0f);
        static void DestroyImmediate(GameObjectHandle go,
                                     bool allowDestroyingAssets = false);

        template<class T>
        static T* FindObjectOfType()
        {
            return nullptr;
        }

        template<class T>
        static std::vector<T*> FindObjectsOfType()
        {
            return std::vector<T*>();
        }

        template<class T>
        static T* Instantiate(T *obj)
        {
            T* result = new T();
            return result;
        }

        template<class T>
        static T* Instantiate(T *obj,
                              Vector3 position,
                              Quaternion rotation)
        {
            T* result = new T(obj);
            result->transform()->position(position);
            result->transform()->rotation(rotation);
            return result;
        }

    private:
        static int s_instanceID;
        static std::vector<Object*> s_pendingDeletes;

        int m_instanceID;
        HideFlags::Enum m_hideFlags;
        std::string m_name;

    protected:
        virtual void Destroy_Internal();

        int m_refCount;
        float m_deleteTime;
        bool m_destroyAssets;

    public:
        static void Update_Internal();
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_OBJECT_H_
