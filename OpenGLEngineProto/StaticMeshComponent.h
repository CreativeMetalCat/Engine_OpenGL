#pragma once
#include "Shader.h"
#include "RenderComponent.h"
#include "LoadedMeshData.h"
#include "Material.h"

struct Shader;
namespace Engine::Components
{
    class CStaticMeshComponent : public CRenderComponent
    {
        GENERATED_CLASS_BODY(StaticMeshComponent, RenderComponent, RenderComponents, Engine::Components)
    private:
            void construct(Material::Material* material, String shaderName);

            glm::mat4 getModelMatrix()const;
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

        /*Buffer for mesh's verticies normals data*/
        uint normalsBuffer;

        uint shaderProgramId;

        /*Id of uniform value for model's martix in shader*/
        GLuint modelViewPerspectiveMatrixId;

        /*Id of uniform value for model's martix in shader*/
        GLuint modelMatrixId;

        /*Id of uniform value for camera view's martix in shader*/
        GLuint viewMatrixId;
#pragma endregion

        LoadedMeshData mesh;

        Shader shader;

        Material::Material* material;
    public:
        Shader GetShader()const;

        CStaticMeshComponent(Material::Material* material,LoadedMeshData mesh,String shaderName,String name, CActor* owner, Vector Location, Vector Rotation, Vector Scale);

        CStaticMeshComponent(Material::Material* material, LoadedMeshData mesh, String shaderName, String name, CActor* owner);

        // Inherited via CRenderComponent
        virtual void EndDraw() override;
        virtual void BeingDraw()override;

        ~CStaticMeshComponent();
    };
}

