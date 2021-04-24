#pragma once
#include "RenderComponent.h"
#include "LoadedMeshData.h"

namespace Engine::Components
{
    class CStaticMeshComponent : public CRenderComponent
    {
        GENERATED_CLASS_BODY(StaticMeshComponent, RenderComponent, Engine::Components)
    protected:
#pragma region ShaderData
        /*These are constant and set when shader is loaded, used to simplfy setting this kind of data*/

        uint shader_ambientLightIntensityId;
        uint shader_ambientLightReflectivityId;
        uint shader_ambientLightColorId;

        /*Buffer for mesh's verticies*/
        uint vertexBuffer;

        /*Buffer for mesh's uv data*/
        uint uvBuffer;

        uint shaderProgramId;
#pragma endregion

        LoadedMeshData mesh;
    public:
        void Draw() override;
    };
}

