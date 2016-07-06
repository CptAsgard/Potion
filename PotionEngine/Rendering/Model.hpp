#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Material.hpp"

namespace Potion
{
	class Model
	{
	public:
		Model( const std::string& path, Material* tempMat );
		~Model();

		std::vector<Mesh*> m_meshes;
		std::vector<Material*> m_materials;

	private:
		Material* tempMat;

		std::string directory;

		void ProcessAssimpNode( aiNode* node, const aiScene* scene );

		void ProcessAssimpMesh( aiMesh* mesh, const aiScene* scene );
		void ProcessAssimpMaterial( aiMaterial* mat );

	};
}