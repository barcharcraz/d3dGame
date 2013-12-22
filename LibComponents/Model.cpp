#include "Model.h"
namespace Components {
    sparse::ecs::ComponentInfo Model::sinfo = sparse::ecs::GenDefCompInfo<Model>();
    Model::Model(const std::vector<LibCommon::Vertex>& vertex, const std::vector<unsigned int>& index)
        : verts(vertex), indices(index) 
    {
        info = &Model::sinfo;
    }
    Model::Model(const Assets::GeometryFile& file)
        : Model(file.Verts(), file.Indices()) {}
    Model::Model() {
        info = &Model::sinfo;
    }
}
