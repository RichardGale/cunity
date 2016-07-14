#ifndef SRC_UNITY_H_
#define SRC_UNITY_H_

#include <math.h>
#include <assert.h>

#include <string>
#include <vector>

#include "UnityEngine/String.h"
#include "UnityEngine/Object.h"
#include "UnityEngine/Color.h"
#include "UnityEngine/Mathf.h"
#include "UnityEngine/Time.h"
#include "UnityEngine/Vector2.h"
#include "UnityEngine/Vector3.h"
#include "UnityEngine/Vector4.h"
#include "UnityEngine/Quaternion.h"
#include "UnityEngine/Matrix4x4.h"
#include "UnityEngine/Ray.h"
#include "UnityEngine/Rect.h"
#include "UnityEngine/Bounds.h"
#include "UnityEngine/Component.h"
#include "UnityEngine/Behaviour.h"
#include "UnityEngine/MonoBehaviour.h"
#include "UnityEngine/GameObject.h"
#include "UnityEngine/Debug.h"
#include "UnityEngine/Transform.h"
#include "UnityEngine/KeyCode.h"

namespace UnityEngine
{
    struct AudioDataLoadState
    {
        enum Enum
        {
            Unloaded,
            Loading,
            Loaded,
            Failed
        };
    };

    struct AudioClipLoadType
    {
        enum Enum
        {
            DecompressOnLoad,
            CompressedInMemory,
            Streaming
        };
    };

    class AudioClip : public Object
    {
    public:
        int channels;
        int frequency;
        float length;
        bool loadInBackground;
        AudioDataLoadState loadState;
        AudioClipLoadType loadType;
        bool preloadAudioData;
        int samples;

        bool GetData(float *data, int offsetSamples);
        bool LoadAudioData();
        bool SetData(float *data, int offsetSamples);
        bool UnloadAudioData();
    };

    class Transform;
    class GameObject;

    class AudioSource : public Behaviour
    {
    public:
        //    bypassEffects;
        //    bypassListenerEffects;
        //    bypassRevertZones;
        //    clip;
        //    dopplerLevel;
        //    ignoreListenerPause;
        //    ignoreListenerVolume;
        //    isPlaying;
        //    isVirtual;
        //    loop;
        //    maxDistance;
        //    minDistance;
        //    mute;
        //    outputAudioMixerGroup;
        //    panStereo;
        //    pitch;
        //    playOnAwake;
        //    priority;
        //    reverbZoneMix;
        //    rolloffMide;
        //    spatialBLend;
        //    spatialize;
        //    spread;
        //    time;
        //    timeSamples;
        //    velocityUpdateMode;
        //    volume;
        //
        //    GetCustomCurve();
        //    GetSpatializerFloat();
        //    Pause();
        //    Play();
        //    PlayDelayed();
        //    PlayOneShot();
        //    PlayScheduled();
        //    SetCustomCurve();
        //    SetScheduledEndTime();
        //    SetScheduledStartTime();
        //    SetSpatializerFloat();
        //    Stop();
        //    UnPause();
        //
        //    static PlayClipAtPoint();
    };

    class Rigidbody : public Component
    {
    public:
        Vector3 velocity()
        {
            return Vector3::zero;
        }

        void velocity(Vector3 value)
        {
        }

        void AddForce(Vector3 force)
        {
        }
    };

    class PhysicMaterial
    {
    };

    struct RaycastHit
    {
    };

    class Collider : public Component
    {
    public:
        Rigidbody* attachedRigidbody()
        {
            return nullptr;
        }

        void attachedRigidbody(Rigidbody *value)
        {
        }

        Bounds bounds()
        {
            return Bounds();
        }

        void bounds(Bounds value)
        {
        }

        float contactOffset()
        {
            return 0.0f;
        }

        void contactOffset(float value)
        {
        }

        bool enabled()
        {
            return false;
        }

        void enabled(bool value)
        {
        }

        bool isTrigger()
        {
            return false;
        }

        void isTrigger(bool value)
        {
        }

        PhysicMaterial* material()
        {
            return nullptr;
        }

        void material(PhysicMaterial *value)
        {
        }

        PhysicMaterial* sharedMaterial()
        {
            return nullptr;
        }

        void sharedMaterial(PhysicMaterial *value)
        {
        }

        Vector3 ClosestPointOnBounds(Vector3 position)
        {
            return Vector3::zero;
        }

        bool Raycast(Ray ray, RaycastHit *hitInfo, float maxDistance)
        {
            return false;
        }
    };

    class SphereCollider : public Collider
    {
    public:
        Vector3 center()
        {
            return Vector3::zero;
        }

        void center(Vector3 value)
        {
        }

        float radius()
        {
            return 0.0f;
        }
        void radius(float value)
        {
        }
    };

    class Collider2D : public Behaviour
    {
        //    attachedRigidbody;
        //    bounds;
        //    density;
        //    isTrigger;
        //    offset;
        //    shapeCount;
        //    sharedMaterial;
        //    usedByEffector;
        //
        //    Cast()
        //    IsTouching()
        //    IsTouchingLayers()
        //    OverlapPoint()
        //    Raycast()
    };

    struct MaterialGlobalIlluminationFlags
    {
        enum Enum
        {
            None
        };
    };

    class Shader : public Object
    {
    public:
        static Shader* Find(std::string name)
        {
            return nullptr;
        }
    };

    struct FilterMode
    {
        enum Enum
        {
            Point,
            Bilinear,
            Trilinear
        };
    };

    struct TextureWrapMode
    {
        enum Enum
        {
            Repeat,
            Clamp
        };
    };

    class Rendering
    {
    public:
        struct TextureDimension
        {
            enum Enum
            {
                Unknown,
                None,
                Tex2D,
                Tex3D,
                Cube,
                Tex2DArray,
                Any
            };
        };
    };

    class Texture : public Object
    {
    public:
        int anisoLevel()
        {
            assert(false);
            return 0;
        }

        void anisoLevel(int value)
        {
        }

        Rendering::TextureDimension::Enum dimension()
        {
            return Rendering::TextureDimension::Tex2D;
        }

        FilterMode::Enum filterMode()
        {
            return FilterMode::Point;
        }

        void filterMode(FilterMode value)
        {
        }

        int height()
        {
            return 4;
        }

        float mipMapBias()
        {
            return 0.0f;
        }

        void mipMapBias(float value)
        {
        }

        int width()
        {
            return 4;
        }

        TextureWrapMode::Enum wrapMode()
        {
            return TextureWrapMode::Repeat;
        }

        void wrapMode(TextureWrapMode value)
        {
        }

        int* GetNativeTexturePtr()
        {
            assert(false);
            return nullptr;
        }

        static void SetGlobalAnistropicFilteringLimits(int forcedMin, int globalMax)
        {
        }
    };

    class Material : public Object
    {
    public:
        Color color;
        MaterialGlobalIlluminationFlags globalIlluminationFlags;
        Texture *mainTexture()
        {
            return nullptr;
        }
        void mainTexture(Texture *value)
        {
        }
        Vector2 mainTextureOffset;
        Vector2 mainTextureScale;
        int passCount;
        int renderQueue;
        Shader *shader;
        char **shaderKeywords;

        Material(Shader *shader)
        {
        }
        
        void CopyPropertiesFromMaterial(Material *mat);
        void DisableKeyword(const char *keyword);
        void EnableKeyword(const char *keyword);
        Color GetColor(const char *propertyName, int nameID);
        Color GetColor();
        void GetFloat();
        void GetInt();
        void GetMatrix();
        void GetTag();
        void GetTexture();
        void GetTextureOffset();
        void GetTextureScale();
        void GetVector();
        void HasProperty();
        void IsKeywordEnabled();
        void Lerp();
        void SetBuffer();
        void SetColor();
        void SetFloat();
        void SetInt();
        void SetMatrix();
        void SetOverrideTag();
        void SetPass();
        void SetTexture();
        void SetTextureOffset();
        void SetTextureScale();
        void SetVector();
    };

    struct FontStyle
    {
        enum Enum
        {
            Normal,
            Bold,
            Italic,
            BoldAndItalic
        };
    };

    class CharacterInfo
    {
    };

    class Font : public Object
    {
        int ascent;
        CharacterInfo *characterInfo;
        bool dynamic;
        int fontSize;
        int lineHeight;
        Material material;

        Font();
        Font(const char *name);
        bool GetCharacterInfo(char ch, CharacterInfo info, int size = 0, FontStyle::Enum style = FontStyle::Normal);

        bool HasCharacter(char c);
        void RequestCharactersInTexture(const char *characters, int size = 0, FontStyle::Enum style = FontStyle::Normal);

        static Font* CreateDynamicFontFromOSFont(const char *font, int size);
        static Font* CreateDynamicFontFromOSFont(const char **font, int size);
        static int GetMaxVertsForString(const char *str);
        static const char** GetOSInstalledFontNames();

        virtual void textureRebuilt();
    };

    struct TextAlignment
    {
        enum Enum
        {
            Left,
            Center,
            Right
        };
    };

    struct TextAnchor
    {
        enum Enum
        {
            UpperLeft,
            UpperCenter,
            UpperRight,
            MiddleLeft,
            MiddleCenter,
            MiddleRight,
            LowerLeft,
            LowerCenter,
            LowerRight
        };
    };

    class TextMesh : public Component
    {
    public:
        TextAlignment alignment;
        TextAnchor anchor;
        float characterSize;
        Color color;
        Font font;
        int fontSize;
        FontStyle fontStyle;
        float lineSpacing;
        float offsetZ;
        bool richText;
        float tTransformHandleize;
        const char* text;
    };

    class YieldInstruction
    {
    };

    class AsyncOperation : public YieldInstruction
    {
    public:
        bool allowSceneActivation;
        bool isDone;
        int priority;
        float progress;
    };

    class AssetBundleRequest : public AsyncOperation
    {
    public:
        std::vector<Object*> allAssets;
        Object* asset;
    };

    class AssetBundle;

    class AssetBundleCreateRequest : public AsyncOperation
    {
    public:
        AssetBundle *assetBundle;
    };

    class AssetBundle : public Object
    {
    public:
        Object *mainAsset;
        bool Contains(const char *name);
        const char** GetAllAssetNames();
        const char** GetAllScenePaths();

        template<class T>
        std::vector<T*> LoadAllAssets();

        AssetBundleRequest* LoadAllAssetsAsync();
        Object* LoadAsset(const char *name);
        AssetBundleRequest* LoadAssetAsync(const char *name);
        Object** LoadAssetWithSubAssets(const char *name);
        AssetBundleRequest* LoadAssesWithSubAssetsAsync(const char *name);
        void Unload(bool unloadAllLoadedObjects);

        static AssetBundle* LoadFromFile(const char *path, unsigned int crc = 0, size_t offset = 0);
        static AssetBundleCreateRequest* LoadFromFileAsync(const char *path, unsigned int crc = 0, size_t offset = 0);
        static AssetBundle* LoadFromMemory(void* binary, unsigned int crc = 0);
        static AssetBundleCreateRequest* LoadFromMemoryAsync(void* binary, unsigned int crc = 0);
    };

    class ResourceRequest : public AsyncOperation
    {
    public:
        Object *asset;
    };

    class Resources : public Object
    {
        //    static Object** FindObjectsOfTypeAll(Type type);
        //    static Object* Load(std::string path);
        //    static Object* Load(std::string path, Type systemTypeInstance);
        //    static Object* LoadAll(std::string path);
        //    static Object* LoadAll(std::string path, Type systemTypeInstance);
        //    static ResourceRequest LoadAsync(std::string path);
        //    static ResourceRequest LoadAsync(std::string path, Type systemTypeInstance);
        //    static void UnloadAsset(Object assetToUnload);
        //    static AsyncOperation UnloadUnusedAssets();
    };

    // All
    // Textures
    // AudioClips
    // Meshes
    // Materials
    // GameObjects
    // Components

    struct TextureFormat
    {
        enum Enum
        {
            ARGB4444,
            RGB24,
            RGBA32,
            ARGB32
        };
    };

    class Texture2D : public Texture
    {
    public:
        static Texture2D *blackTexture;
        static Texture2D *whiteTexture;
        TextureFormat format;
        int mipmapCount;

        Texture2D(int width, int height)
        {
        }

        void Apply(bool updateMipmaps = true, bool makeNoLongerReadable = false)
        {
        }

        void Compress(bool highQuality);
        //    EncodeToJPG();
        //    EncodeToPNG();
        //    GetPixel();
        //    GetPixelBilinear();
        //    GetPixels();
        //    GetPixels32();
        //    GetRawTextureData();
        void LoadRawTextureData(unsigned char *data, int size);
        void LoadRawTextureData(int *data, int size);
        //    PackTextures();
        //    ReadPixels();
        bool Resize(int width, int height, TextureFormat format, bool hasMipMap);
        //    SetPixel();
        void SetPixels(Color *pix)
        {
        }

        //    SetPixels32();
        void UpdateExternalTexture(int *nativeTex);

        static Texture2D CreateExternalTexture(int width, int height, TextureFormat format, bool mipmap, bool linear, int *nativeTex);
    };

    class Renderer : public Component
    {
    public:
        //    Bounds bounds;
        //    enabled;
        //    isPartOfStaticBatch;
        //    isVisible;
        //    lightmapIndex;
        //    lightmapScaleOffset;
        //    lightProbeProxyVolumeOverride;
        //    lightProbeUsage;
        //    localToWorldMatrix;
        Material* material()
        {
            return nullptr;
        }
        //    materials;
        //    motionVectors;
        //    probeAnchor;
        //    realtimeLightmapIndex;
        //    realtimeLightmapScaleOffset;
        //    receiveShadows;
        //    reflectionProbeUsage;
        //    shadowCastingMode;
        Material* sharedMaterial()
        {
            return nullptr;
        }
        void sharedMaterial(Material *value)
        {
        }
        //    sharedMaterials;
        //    sortingLayerID;
        //    sortingLayerName;
        //    sortingOrder;
        //    worldToLocalMatrix;
        //
        //    GetPropertyBlock;
        //    SetPropertyBlock;
        //
        //    OnBecameVisible;
    };

    struct SpritePackingMode
    {
        enum Enum
        {
            Tight,
            Rectangle
        };
    };

    struct SpritePackingRotation
    {
        enum Enum
        {
            None,
            Any
        };
    };

    class Sprite
    {
    public:
        Texture2D *associatedAlphaSplitTexture;
        Vector4 border;
        Bounds bounds;
        bool packed;
        SpritePackingMode packingMode;
        SpritePackingRotation packingRotation;
        Vector2 pivot;
        float pixelsPerUnit;
        Rect rect;
        Texture2D *texture;
        Rect textureRect;
        Vector2 textureRectOffset;
        uint16_t *triangles;
        Vector2 *uv;
        Vector2 *vertices;
    };

    class SpriteRenderer : public Renderer
    {
    public:
        Color color;
        bool flipX;
        bool flipY;
        Sprite *sprite;
    };

    struct QueryTriggerInteraction
    {
        enum Enum
        {
            UseGlobal,
            Ignore,
            Collide
        };
    };

    class Physics
    {
    public:
        static const int DefaultRaycastLayers = 0;

        static bool Raycast(Vector3 origin, Vector3 direction, float maxDistance = Mathf::Infinity, int layerMask = DefaultRaycastLayers, QueryTriggerInteraction::Enum queryTriggerInteraction = QueryTriggerInteraction::UseGlobal)
        {
            return false;
        }

        static bool Raycast(Vector3 origin, Vector3 direction, RaycastHit *hitInfo, float maxDistance = Mathf::Infinity, int layerMask = DefaultRaycastLayers, QueryTriggerInteraction::Enum queryTriggerInteraction = QueryTriggerInteraction::UseGlobal)
        {
            return false;
        }

        static bool Raycast(Ray ray, float maxDistance = Mathf::Infinity, int layerMask = DefaultRaycastLayers, QueryTriggerInteraction::Enum queryTriggerInteraction = QueryTriggerInteraction::UseGlobal)
        {
            return false;
        }
        
        static bool Raycast(Ray ray, RaycastHit *hitInfo, float maxDistance = Mathf::Infinity, int layerMask = DefaultRaycastLayers, QueryTriggerInteraction::Enum queryTriggerInteraction = QueryTriggerInteraction::UseGlobal)
        {
            return false;
        }
    };

    class Joint : public Component
    {
    };

    class HingeJoint : public Joint
    {
    public:
        bool useSpring()
        {
            return false;
        }

        void useSpring(bool value)
        {
        }
    };

    class Mesh : public Object
    {
    public:
        std::vector<Vector3> vertices()
        {
            return std::vector<Vector3>();
        }

        void vertices(std::vector<Vector3> value)
        {
        }
    };
    
    class MeshFilter : public Component
    {
    public:
        Mesh* mesh()
        {
            return nullptr;
        }

        void mesh(Mesh *value)
        {
        }

        Mesh* sharedMesh()
        {
            return nullptr;
        }

        void sharedMesh(Mesh *value)
        {
        }
    };

    class GUIElement : public Behaviour
    {
    };

    class GUITexture : public GUIElement
    {
    };

    class Image : public MonoBehaviour
    {
    };

    class Random
    {
    public:
        static Vector2 insideUnitCircle()
        {
            return Vector2::zero;
        }

        static Vector3 insideUnitSphere()
        {
            return Vector3::zero;
        }
    };

    class Input
    {
    public:
        static bool GetButton(std::string name)
        {
            return false;
        }

        static bool GetKeyDown(std::string name)
        {
            return false;
        }

        static bool GetKeyDown(KeyCode::Enum key)
        {
            return false;
        }
    };

    class WaitForSeconds : public YieldInstruction
    {
    private:
        float m_Seconds;
    public:
        WaitForSeconds(float seconds)
        {
            m_Seconds = seconds;
        }
    };

    class GUI
    {
    public:
        static void Label(Rect position, String text)
        {
        }
    };
}  // namespace UnityEngine

#endif  // SRC_UNITY_H_
