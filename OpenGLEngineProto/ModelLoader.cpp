#include "ModelLoader.h"
#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#else
#error TinyObjLoader was included more then once.
#endif

#include "openFBXLoader/ofbx.h"

//#define TINYOBJ
MeshData ModelLoader::LoadModel_tinyOBJ(std::string filepath, float scale)
{
    tinyobj::ObjReaderConfig reader_config;
    //reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;
    if(!reader.ParseFromFile(filepath, reader_config)) 
    {
        if (!reader.Error().empty()) 
        {
            printf(reader.Error().c_str());
        }
    }
    if (!reader.Warning().empty())
    {
        printf(reader.Warning().c_str());
    }

    tinyobj::attrib_t attrib = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
    std::vector<tinyobj::material_t> materials = reader.GetMaterials();

    MeshData data;
#ifdef TINYOBJ
    for (size_t s = 0; s < shapes.size(); s++)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) 
            {
                if (index_offset >= shapes[s].mesh.indices.size())
                {
                    continue;
                }
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                
                data.Verticies.push_back(vx);
                data.Verticies.push_back(vy);  
                data.Verticies.push_back(vz);
                

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

                    data.UVs.push_back(tx);
                    data.UVs.push_back(ty);
                }
                index_offset += fv;
                shapes[s].mesh.material_ids[f];
            }
        }
    }

#else
    for (int i = 0; i < attrib.vertices.size(); i++)
    {     
        data.Verticies.push_back(attrib.vertices[i]);
    }
    data.QuadMesh = true;
   //data.Verticies = attrib.vertices;

    data.UVs = attrib.texcoords;
#endif // TINYOBJ

    
    return data;
}

LoadedMeshData ModelLoader::LoadModel_openFBX(std::string filepath, float scale)
{
   return LoadModelFromScene(filepath, scale)[0];
}

std::vector<LoadedMeshData> ModelLoader::LoadModelFromScene_openFBX(std::string filepath, float scale)
{
    std::string fbx;
    std::ifstream fbxFileStream(filepath, std::ios::binary);
    if (fbxFileStream.is_open())
    {
        std::stringstream sstr;
        sstr << fbxFileStream.rdbuf();
        fbx = sstr.str();
        fbxFileStream.close();
    }

    if (fbx.empty())
    {
        printf("Failed to read scene: %s", filepath.c_str());
        return std::vector<LoadedMeshData>();
    }

    ofbx::IScene* scene = ofbx::load((ofbx::u8*)fbx.c_str(), fbx.size(), (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
    if (!scene)
    {
        printf(ofbx::getError());
        return std::vector<LoadedMeshData>();
    }
    if (scene->getMeshCount() > 0 && scene->getMeshCount() == scene->getGeometryCount())
    {
        std::vector<LoadedMeshData> result = std::vector<LoadedMeshData>();
        for (int i = 0; i < scene->getMeshCount(); i++)
        {
           
            LoadedMeshData data = LoadedMeshData();
            //0 index is a placeholder because currently we only care about one mesh -> in the future i should implement loading into multiple meshes if there is more then one
            std::vector< ofbx::Vec3> verticies = std::vector<ofbx::Vec3>(scene->getGeometry(i)->getVertices(), scene->getGeometry(i)->getVertices() + scene->getGeometry(i)->getVertexCount());
            for (auto it = verticies.begin(); it != verticies.end(); ++it)
            {
                data.Data.Verticies.push_back((*it).x);
                data.Data.Verticies.push_back((*it).y);
                data.Data.Verticies.push_back((*it).z);
            }

            std::vector<ofbx::Vec2> uvs = std::vector<ofbx::Vec2>(scene->getGeometry(i)->getUVs(), scene->getGeometry(i)->getUVs() + scene->getGeometry(i)->getVertexCount());
            for (auto it = uvs.begin(); it != uvs.end(); ++it)
            {
                data.Data.UVs.push_back((*it).x);
                data.Data.UVs.push_back(1 - (*it).y);
            }

            std::vector< ofbx::Vec3> normals = std::vector<ofbx::Vec3>(scene->getGeometry(i)->getNormals(), scene->getGeometry(i)->getNormals() + scene->getGeometry(i)->getIndexCount());
            for (auto it = normals.begin(); it != normals.end(); ++it)
            {
                data.Data.Normals.push_back((*it).x);
                data.Data.Normals.push_back((*it).y);
                data.Data.Normals.push_back((*it).z);
            }

            data.RelativeLocation = glm::vec3
            (
                scene->getMesh(i)->getLocalTranslation().x,
                scene->getMesh(i)->getLocalTranslation().y,
                scene->getMesh(i)->getLocalTranslation().z
            );


            data.Scale = scale;

            //note FBX's rotation is different from OpenGL's rotation so currently rotation is ignored
            data.RelativeRotation = glm::vec3
            (
                
                scene->getMesh(i)->getLocalRotation().y,
                scene->getMesh(i)->getLocalRotation().x,
                scene->getMesh(i)->getLocalRotation().z
               
            );

            //there is no point in implementing loading of the full material info because
            //1) FBX scene loading is a placeholder before actual scene loading will be implemented(that will have it's own model and texture info)
            //2) there is no support for multi texture meshes yet
            data.MaterialNames.push_back(scene->getMesh(i)->getMaterial(0)->name);
            //how to get texure used
            //scene->getMesh(0)->getMaterial(0)->getTexture(ofbx::Texture::DIFFUSE)->getFileName();
            result.push_back(data);
            //printf(scene->getMesh(i)->getMaterial(0)->name);
        }
        
        return result;
    }
    else 
    {
        printf("Provided scene: %s is empty!",filepath.c_str());
        return std::vector<LoadedMeshData>();
    }
}

LoadedMeshData ModelLoader::LoadModel(std::string filepath, float scale)
{
    return LoadModel_openFBX(filepath,scale);
}

std::vector<LoadedMeshData> ModelLoader::LoadModelFromScene(std::string filepath, float scale)
{
    return  LoadModelFromScene_openFBX(filepath, scale);
}
