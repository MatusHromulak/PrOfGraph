#include "Model.h"

Model::Model(const char * vertexFile, const char * fragmentFile, const char * objectFile, const char *textureFile)
{
	shader = new Shader(vertexFile, fragmentFile);
	texture = new Texture(textureFile);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	load(objectFile);
}

void Model::load(const char * objectFile)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slou�en� mal�ch plo�ek
		| aiProcess_JoinIdenticalVertices       // NUTN� jinak hodn� duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy


												//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(objectFile, importOptions);

	if (scene) { //pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			aiMesh* mesh = scene->mMeshes[i];

			Vertex* pVertices = new Vertex[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(Vertex)* mesh->mNumVertices);

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].Position[0] = mesh->mVertices[i].x;
					pVertices[i].Position[1] = mesh->mVertices[i].y;
					pVertices[i].Position[2] = mesh->mVertices[i].z;
				}
				if (mesh->HasNormals())
				{
					pVertices[i].Normal[0] = mesh->mNormals[i].x;
					pVertices[i].Normal[1] = mesh->mNormals[i].y;
					pVertices[i].Normal[2] = mesh->mNormals[i].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].TexCoords[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].TexCoords[1] = mesh->mTextureCoords[0][i].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					pVertices[i].Tangent[0] = mesh->mTangents[i].x;
					pVertices[i].Tangent[1] = mesh->mTangents[i].y;
					pVertices[i].Tangent[2] = mesh->mTangents[i].z;
				}
			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{

				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(vao);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl; return;
			} indicesCount = mesh->mNumFaces * 3;

			delete[] pVertices;
			delete[] pIndices;
		}
	}
	else {
		printf("Error during parsing mesh from %s : %s \n", objectFile, importer.GetErrorString());
	}
	glBindVertexArray(0);
}

void Model::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	shader->use();
	texture->bind();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}

Model::~Model()
{
}
