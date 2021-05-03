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
            void construct(String materialName, String shaderName);

            Matrix getModelMatrix()const;
    protected:
#pragma region ShaderData
        /*These are constant and set when shader is loaded, used to simplfy setting this kind of data*/

        /*Id for world's color*/
        uint shader_AmbientLightColorId;

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

        uint VertexArrayID;

        uint UVArrayID;

        LoadedMeshData mesh;

        Shader shader;

        Material::Material* material;
    public:
        Shader GetShader()const;

        CStaticMeshComponent(String name, CActor* owner, String materialName, LoadedMeshData mesh,String shaderName, Vector Location = Vector(0), Vector Rotation = Vector(0), Vector Scale = Vector(1));

        // Inherited via CRenderComponent
        virtual void EndDraw() override;
        virtual void BeingDraw()override;

        ~CStaticMeshComponent();
    };
}

