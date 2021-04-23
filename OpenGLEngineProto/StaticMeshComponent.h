#pragma once
#include "RenderComponent.h"
#include "LoadedMeshData.h"

namespace Engine::Components
{
    class CStaticMeshComponent : public CRenderComponent
    {
        GENERATED_CLASS_BODY(StaticMeshComponent, RenderComponent, Engine::Components)
    public:
        void Draw() override;
    };
}

