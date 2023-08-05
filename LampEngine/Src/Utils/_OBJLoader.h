// I just coppied code from a github repo and modified it.
// https://github.com/Bly7/OBJ-Loader/blob/master/Source/OBJ_Loader.h
#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "Resources/Mesh.h"
#include "Core/Logger.h"

/* NOTE:
*		This objloader is still in progress, at the time it works but is slow.
*		It loads same textures twice
*/

namespace LampEngine {
	namespace obj_loader_math {
		float AngleBetweenV3(const glm::vec3& a, const glm::vec3& b);
	}

	namespace obj_loader_algorithm {
		bool SameSide(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& a, const glm::vec3& b);
		glm::vec3 GenTriNormal(const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3);
		bool inTriangle(const glm::vec3& point, const glm::vec3& tri1, const glm::vec3& tri2, const glm::vec3& tri3);
		// Function help with the loading of obj
		template <class T>
		inline const T& getElement(const std::vector<T>& elements, const std::string& index);
	}

	class OBJLoader
	{
	public:
		OBJLoader();
		~OBJLoader();
		bool loadFile(std::string Path);

		std::vector<Mesh*> LoadedMeshes;
		std::vector<Vertex> LoadedVertices;
		std::vector<unsigned int> LoadedIndices;
		std::vector<Material> LoadedMaterials;
	private:
		// This private function is responsible for parsing the data of obj and sorting them.
		void genVerticesFromRawOBJ(std::vector<Vertex>& outVerts,
			std::vector<glm::vec3>& inPositions,
			std::vector<glm::vec2>& inUVs,
			std::vector<glm::vec3>& inNormals,
			std::string inCurline);
		// Triangluate the vertices
		void vertexTriangluation(std::vector<unsigned int>& outIndices,
			std::vector<Vertex>& inVerts);
		// Load the materials to LoadedMaterials varible
		bool LoadMaterials(std::string path);
	};
}