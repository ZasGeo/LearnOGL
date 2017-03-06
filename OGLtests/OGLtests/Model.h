#ifndef _MODELZASOP_
#define _MODELZASOP_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>
#include "Mesh.h"

class Model {

public:

	Model(const std::string& path)	{
		this->loadModel(path);
	}

	inline void Draw(const Shader& shader) const {

		for (GLuint i = 0; i < this->meshes.size(); ++i)
			this->meshes[i].Draw(shader);
	}

//private:

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	void loadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

};

GLint TextureFromFile(const char* path, std::string directory);



#endif