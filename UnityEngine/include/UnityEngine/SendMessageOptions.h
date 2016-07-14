#ifndef SRC_UNITYENGINE_SENDMESSAGEOPTIONS_H_
#define SRC_UNITYENGINE_SENDMESSAGEOPTIONS_H_

namespace UnityEngine
{
    struct SendMessageOptions
    {
        enum Enum
        {
            RequireReceiver,
            DontRequireReceiver
        };
    };
}  // namespace UnityEngine

#endif  // SRC_UNITYENGINE_SENDMESSAGEOPTIONS_H_
