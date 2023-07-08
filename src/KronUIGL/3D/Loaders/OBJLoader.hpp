#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Elements/mesh.hpp"
#include <memory>
class OBJLoader {
public:
    std::vector<std::shared_ptr<Mesh>> loadModel(const std::string& path);

private:
    std::vector<std::shared_ptr<Mesh>> processNode(aiNode* node, const aiScene* scene);

    std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
};