#ifndef SRC_UNITYENGINE_MONOBEHAVIOUR_H
#define SRC_UNITYENGINE_MONOBEHAVIOUR_H

#include "Behaviour.h"

#include "String.h"
#include "Debug.h"

namespace UnityEngine
{
    class GameObject;
    class GameObjectHandle;
    
    class Coroutine
    {
    };

    typedef void* IEnumerator;

    class MonoBehaviour : public Behaviour
    {
    public:
        MonoBehaviour();
        virtual ~MonoBehaviour();

        virtual void enabled(bool value);

        bool useGUILayout();
        void useGUILayout(bool value);

        void CancelInvoke();
        void Invoke(const char *methodName, float time);
        void InvokeRepeating(const char *methodName,
                             float time,
                             float repeatRate);

        bool IsInvoking(const char *methodName);
        Coroutine* StartCoroutine(IEnumerator routine);
        void StopAllCoroutines();
        void StopCoroutine(const char *methodName);
        void StopCoroutine(IEnumerator routine);

        static void print(int value)
        {
            Debug::Log(String(value));
        }

        static void print(float value)
        {
            Debug::Log(String(value));
        }

        static void print(const char *message)
        {
            Debug::Log(String(message));
        }

        static void print(std::string message)
        {
            Debug::Log(String(message));
        }

        static void print(Color color)
        {
            Debug::Log(String(color.ToString()));
        }

        template<class T>
        static void print(T message)
        {
            Debug::Log(message.ToString());
        }

        virtual void Awake();
        virtual void FixedUpdate();
        virtual void LateUpdate();
        virtual void OnApplicationFocus(bool focusStatus);
        virtual void OnApplicationPause(bool pauseStatus);
        virtual void OnApplicationQuit();
        virtual void OnBecameInvisible();
        virtual void OnBecameVisible();
        virtual void OnDestroy();
        virtual void OnDisable();
        virtual void OnEnable();
        virtual void OnTransformChildrenChanged();
        virtual void OnTransformParentChanged();

        virtual void Reset();
        virtual void Start();
        virtual void Update();

        //
        virtual bool CanReceiveMessage(std::string methodName);
        virtual void OnMessage(std::string methodName, void *parameters);
        //

        static void Update_Internal();

    protected:
        virtual void Destroy_Internal();

    private:
        static std::vector<MonoBehaviour*> s_new;
        static std::vector<MonoBehaviour*> s_enabled;
        static std::vector<MonoBehaviour*> s_justEnabled;
        static std::vector<MonoBehaviour*> s_justDisabled;
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_MONOBEHAVIOUR_H
