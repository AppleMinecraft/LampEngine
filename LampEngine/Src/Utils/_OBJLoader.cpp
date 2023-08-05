// I just coppied code from a github repo and modified it.
// https://github.com/Bly7/OBJ-Loader/blob/master/Source/OBJ_Loader.h
#include "_OBJLoader.h"
#include <fstream>
#include "Core/Logger.h"
#include "Utils/FileUtils.h"
#include "Utils/StringUtils.h"

namespace LampEngine
{
	namespace obj_loader_math
	{

		float AngleBetweenV3(const glm::vec3& a, const glm::vec3& b)
		{
			float angle = glm::dot(a, b);
			angle /= (glm::length(a) * glm::length(b));
			return glm::degrees(acosf(angle));
		}
	}

	namespace obj_loader_algorithm
	{
		bool SameSide(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& a, const glm::vec3& b) {
			glm::vec3 cp1 = glm::cross(b - a, p1 - a);
			glm::vec3 cp2 = glm::cross(b - a, p2 - a);

			return glm::dot(cp1, cp2) >= 0.0f;
		}

		glm::vec3 GenTriNormal(const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3) {
			glm::vec3 u = t2 - t1;
			glm::vec3 v = t3 - t1;
			glm::vec3 normal = glm::cross(u, v);

			return normal;
		}

		bool inTriangle(const glm::vec3& point, const glm::vec3& tri1, const glm::vec3& tri2, const glm::vec3& tri3)
		{
			bool within_tri_prism = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
				&& SameSide(point, tri3, tri1, tri2);
			if (!within_tri_prism)
				return false;

			glm::vec3 n = cross(tri1 - tri2, tri1 - tri3);
			glm::vec3 proj = point - dot(point - tri1, n) * n;

			if (length2(proj) < glm::epsilon<float>())
				return true;
			else
				return false;
		}

		template <class T>
		inline const T& getElement(const std::vector<T>& elements, const std::string& index) {
			int idx = std::stoi(index);

			if (idx < 0)
				idx = elements.size() + idx;
			else
				idx--;

			return elements[idx];
		}
	}

	OBJLoader::OBJLoader() {
	}
	OBJLoader::~OBJLoader() {
		LoadedMeshes.clear();
	}

	bool OBJLoader::loadFile(std::string path)
	{
		LOGinfo("Loading OBJ Model at '{}'", path);

		// Verify obj extension
		if (FileUtils::GetFileExtension(path) != "obj")
			return false;

		// Opening the file
		std::ifstream file(path);
		if (!file.is_open())
			return false;

		// Clearing any existing mesh data
		LoadedMeshes.clear();
		LoadedVertices.clear();
		LoadedIndices.clear();

		// Temporary mesh data
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec2> TextureUVs;
		std::vector<glm::vec3> vertexNormals;
		std::vector<std::string> meshMaterialNames;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Mesh* tempMesh;
		std::string meshname;
		bool listening = false;
		std::string curline;

		// Looping throught every line
		while (std::getline(file, curline)) {
			std::string firstToken = StringUtils::GetFirstToken(curline);

			// Generate a mesh object or prepare for an object to be created
			if (firstToken == "o" || firstToken == "g" || curline[0] == 'g') {
				if (!listening) {
					listening = true;

					if (firstToken == "o" || firstToken == "g")
						meshname = StringUtils::GetTail(curline);
					else
						meshname = "unnamed"; // No mesh name found
				}
				// Generate the mesh
				else {
					// If previous mesh data is loaded
					if (!indices.empty() && !vertices.empty()) {
						// Create mesh
						tempMesh = new Mesh(meshname, vertices, indices);
						LoadedMeshes.push_back(tempMesh);
						// Cleanup
						vertices.clear();
						indices.clear();
						meshname.clear();

						meshname = StringUtils::GetTail(curline);
					}
					// If new mesh found but previous mesh data is empty
					// In that case we dont add the mesh
					else {
						if (firstToken == "o" || firstToken == "g")
							meshname = StringUtils::GetTail(curline);
						else
							meshname = "unnamed"; // No mesh name found
					}
				}
			}
			// Generate the vertex position
			if (firstToken == "v") {
				// Vetex positons in string
				std::vector<std::string> strPosition;
				// Loaded vertex positions from string
				glm::vec3 vertexPosition;

				StringUtils::Split(StringUtils::GetTail(curline), strPosition, " ");

				vertexPosition.x = std::stof(strPosition[0]);
				vertexPosition.y = std::stof(strPosition[1]);
				vertexPosition.z = std::stof(strPosition[2]);

				// Insert position into temporary vertex array
				vertexPositions.push_back(vertexPosition);
			}
			// Generate the vertex UV
			if (firstToken == "vt") {
				// Vetex UVs in string
				std::vector<std::string> stringUV;
				// Loaded vertex UV from string
				glm::vec2 vertexUV;

				StringUtils::Split(StringUtils::GetTail(curline), stringUV, " ");

				vertexUV.x = std::stof(stringUV[0]);
				vertexUV.y = std::stof(stringUV[1]);

				// Insert position into temporary vertex array
				TextureUVs.push_back(vertexUV);
			}
			// Generate the vertex normal
			if (firstToken == "vn") {
				// Vetex normals in string
				std::vector<std::string> stringNormal;
				// Loaded vertex normals from string
				glm::vec3 VertexNormal;

				StringUtils::Split(StringUtils::GetTail(curline), stringNormal, " ");

				VertexNormal.x = std::stof(stringNormal[0]);
				VertexNormal.y = std::stof(stringNormal[1]);
				VertexNormal.z = std::stof(stringNormal[2]);

				vertexNormals.push_back(VertexNormal);
			}
			// Generate a face (vertices & indices)
			if (firstToken == "f") {
				// Generate the vertices
				std::vector<Vertex> vVerts;
				genVerticesFromRawOBJ(vVerts, vertexPositions, TextureUVs, vertexNormals, curline);

				// Add Vertices
				for (int i = 0; i < vVerts.size(); i++) {
					vertices.push_back(vVerts[i]);
					LoadedVertices.push_back(vVerts[i]);
				}

				// Trisngluate the mesh
				std::vector<unsigned int> iIndices;
				vertexTriangluation(iIndices, vVerts);

				// Add Indices
				for (int i = 0; i < int(iIndices.size()); i++) {
					unsigned int indNum = (unsigned int)((vertices.size()) - vVerts.size()) + iIndices[i];
					indices.push_back(indNum);

					indNum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
					LoadedIndices.push_back(indNum);

				}
			}
			// Get Mesh Material Name
			if (firstToken == "usemtl") {
				meshMaterialNames.push_back(StringUtils::GetTail(curline));

				// Create new Mesh, if Material changes within a group
				if (!indices.empty() && !vertices.empty()) {
					// Create Mesh
					tempMesh = new Mesh(meshname, vertices, indices);
					int i = 2;
					while (1) {
						tempMesh->name = meshname + "_" + std::to_string(i);

						for (auto& m : LoadedMeshes)
							if (m->name == tempMesh->name)
								continue;
						break;
					}

					// Insert Mesh
					LoadedMeshes.push_back(tempMesh);

					// Cleanup
					vertices.clear();
					indices.clear();
				}

			}
			// Load Materials
			if (firstToken == "mtllib") {
				// Generate LoadedMaterial

				// Generate a path to the material file
				std::vector<std::string> temp;
				StringUtils::Split(path, temp, "/");

				std::string pathtomat = "";

				if (temp.size() != 1) {
					for (int i = 0; i < temp.size() - 1; i++) {
						pathtomat += temp[i] + "/";
					}
				}

				pathtomat += StringUtils::GetTail(curline);

				// Load Materials
				LOGdebug("Finding materials in: {}", pathtomat);
				LoadMaterials(pathtomat);
			}
		}

		// Deal with last mesh

		if (!indices.empty() && !vertices.empty())
		{
			// Create Mesh
			tempMesh = new Mesh(meshname, vertices, indices);

			// Insert Mesh
			LoadedMeshes.push_back(tempMesh);
		}

		file.close();

		// Set Materials for each Mesh
		for (int i = 0; i < meshMaterialNames.size(); i++)
		{
			std::string matname = meshMaterialNames[i];

			// Find corresponding material name in loaded materials
			// when found copy material variables into mesh material
			for (int j = 0; j < LoadedMaterials.size(); j++)
			{
				if (LoadedMaterials[j].name == matname)
				{
					LoadedMeshes[i]->material = LoadedMaterials[j];
					break;
				}
			}
		}

		if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void OBJLoader::genVerticesFromRawOBJ(std::vector<Vertex>& outVerts,
		std::vector<glm::vec3>& inPositions,
		std::vector<glm::vec2>& inUVs,
		std::vector<glm::vec3>& inNormals,
		std::string inCurline)
	{
		// The variable "stringFace" holds face data in string format, while the variable "stringVertex" stores individual position, normal, and UV data.
		std::vector<std::string> stringFace, stringVertex;
		Vertex vertex;
		StringUtils::Split(StringUtils::GetTail(inCurline), stringFace, " ");

		// For every given vertex do this
		bool noNormal = false;
		for (int i = 0; i < stringFace.size(); i++) {
			// Determine the type of the vertex: position, normal, or UV.
			int vType = 0;

			// Split data "4/5/3" into ["4", "5", "3"]
			StringUtils::Split(stringFace[i], stringVertex, "/");

			// Check for just position - v1
			if (stringVertex.size() == 1) {
				// Only position
				vType = 1;
			}

			// Check for position & texture - v1/vt1
			if (stringVertex.size() == 2) {
				// Position & Texture
				vType = 2;
			}

			// Check for Position, Texture and Normal - v1/vt1/vn1
			// or if Position and Normal - v1//vn1
			if (stringVertex.size() == 3) {
				if (stringVertex[1] != "") {
					// Position, Texture, and Normal
					vType = 4;
				}
				else {
					// Position & Normal
					vType = 3;
				}
			}

			// Calculate and store the vertex
			switch (vType) {
			case 1: { // Just position
				noNormal = true;

				vertex.position = obj_loader_algorithm::getElement(inPositions, stringVertex[0]);
				vertex.uv = glm::vec2(0, 0);

				// Inserting the data
				outVerts.push_back(vertex);
				break;
			}
			case 2: { // Position and UV
				noNormal = true;

				vertex.position = obj_loader_algorithm::getElement(inPositions, stringVertex[0]);
				vertex.uv = obj_loader_algorithm::getElement(inUVs, stringVertex[1]);

				// Inserting the data
				outVerts.push_back(vertex);
				break;
			}
			case 3: { // Position and Normal
				vertex.position = obj_loader_algorithm::getElement(inPositions, stringVertex[0]);
				vertex.uv = glm::vec2(0, 0);
				vertex.normal = obj_loader_algorithm::getElement(inNormals, stringVertex[2]);

				// Inserting the data
				outVerts.push_back(vertex);
				break;
			}
			case 4: { // Prsition, Normal and UV
				vertex.position = obj_loader_algorithm::getElement(inPositions, stringVertex[0]);
				vertex.uv = obj_loader_algorithm::getElement(inUVs, stringVertex[1]);
				vertex.normal = obj_loader_algorithm::getElement(inNormals, stringVertex[2]);

				// Inserting the data
				outVerts.push_back(vertex);
				break;
			}
			default: {
				break;
			}
			}

			// Calculating the normals if no normals exists
			if (noNormal) {
				glm::vec3 A = outVerts[0].position - outVerts[1].position;
				glm::vec3 B = outVerts[2].position - outVerts[1].position;
				glm::vec3 normal = glm::cross(A, B);

				for (int i = 0; i < outVerts.size(); i++) {
					outVerts[i].normal = normal;
				}
			}
		}
	}

	void OBJLoader::vertexTriangluation(std::vector<unsigned int>& outIndices,
		std::vector<Vertex>& inVerts)
	{
		if (inVerts.size() < 3)
			return;

		if (inVerts.size() == 3) {
			outIndices.push_back(0);
			outIndices.push_back(1);
			outIndices.push_back(2);
			return;
		}

		std::vector<Vertex> tVerts = inVerts;

		while (true) {
			for (int i = 0; i < tVerts.size(); i++) {
				Vertex pPrev;

				if (i == 0)
					pPrev = tVerts[tVerts.size() - 1];
				else
					pPrev = tVerts[i - 1];

				Vertex pCur = tVerts[i];
				Vertex pNext;

				if (i == tVerts.size() - 1)
					pNext = tVerts[0];
				else
					pNext = tVerts[i + 1];

				if (tVerts.size() == 3) {
					for (int j = 0; j < int(tVerts.size()); j++) {
						if (inVerts[j].position == pCur.position)
							outIndices.push_back(j);
						if (inVerts[j].position == pPrev.position)
							outIndices.push_back(j);
						if (inVerts[j].position == pNext.position)
							outIndices.push_back(j);
					}

					tVerts.clear();
					break;
				}
				if (tVerts.size() == 4) {
					for (int j = 0; j < int(inVerts.size()); j++) {
						if (inVerts[j].position == pCur.position)
							outIndices.push_back(j);
						if (inVerts[j].position == pPrev.position)
							outIndices.push_back(j);
						if (inVerts[j].position == pNext.position)
							outIndices.push_back(j);
					}

					glm::vec3 tempVec;
					for (int j = 0; j < int(tVerts.size()); j++) {
						if (tVerts[j].position != pCur.position
							&& tVerts[j].position != pPrev.position
							&& tVerts[j].position != pNext.position)
						{
							tempVec = tVerts[j].position;
							break;
						}
					}

					for (int j = 0; j < int(inVerts.size()); j++) {
						if (inVerts[j].position == pPrev.position)
							outIndices.push_back(j);
						if (inVerts[j].position == pNext.position)
							outIndices.push_back(j);
						if (inVerts[j].position == tempVec)
							outIndices.push_back(j);
					}

					tVerts.clear();
					break;
				}

				float angle = obj_loader_math::AngleBetweenV3(pPrev.position - pCur.position, pNext.position - pCur.position) * (180 / 3.14159265359);
				if (angle <= 0 && angle >= 180)
					continue;

				// If any vertices are within this triangle
				bool inTri = false;
				for (int j = 0; j < int(inVerts.size()); j++) {
					if (obj_loader_algorithm::inTriangle(inVerts[j].position, pPrev.position, pCur.position, pNext.position)
						&& inVerts[j].position != pPrev.position
						&& inVerts[j].position != pCur.position
						&& inVerts[j].position != pNext.position)
					{
						inTri = true;
						break;
					}
				}
				if (inTri)
					continue;

				// Create a triangle from pCur, pPrev, pNext
				for (int j = 0; j < int(inVerts.size()); j++) {
					if (inVerts[j].position == pCur.position)
						outIndices.push_back(j);
					if (inVerts[j].position == pPrev.position)
						outIndices.push_back(j);
					if (inVerts[j].position == pNext.position)
						outIndices.push_back(j);
				}

				// Delete pCur from the list
				for (int j = 0; j < int(tVerts.size()); j++) {
					if (tVerts[j].position == pCur.position)
					{
						tVerts.erase(tVerts.begin() + j);
						break;
					}
				}

				// reset i to the start
				// -1 since loop will add 1 to it
				i = -1;
			}

			// if no triangles were created
			if (outIndices.size() == 0)
				break;

			// if no more vertices
			if (tVerts.size() == 0)
				break;
		}
	}

	// Load Materials from .mtl file
	bool OBJLoader::LoadMaterials(std::string path)
	{
		// If the file is not a material file return false
		if (FileUtils::GetFileExtension(path) != "mtl")
			return false;

		std::ifstream file(path);

		// If the file is not found return false
		if (!file.is_open())
			return false;

		Material tempMaterial;

		bool listening = false;

		// Go through each line looking for material variables
		std::string curline;
		while (std::getline(file, curline))
		{
			std::string firstToken = StringUtils::GetFirstToken(curline);
			// new material and material name
			if (firstToken == "newmtl")
			{
				if (!listening)
				{
					listening = true;

					if (curline.size() > 7)
					{
						tempMaterial.name = StringUtils::GetTail(curline);
					}
					else
					{
						tempMaterial.name = "none";
					}
				}
				else
				{
					// Generate the material

					// Push Back loaded Material
					LoadedMaterials.push_back(tempMaterial);

					// Clear Loaded Material
					tempMaterial = Material();

					if (curline.size() > 7)
					{
						tempMaterial.name = StringUtils::GetTail(curline);
					}
					else
					{
						tempMaterial.name = "none";
					}
				}
			}
			// Diffuse Color
			if (firstToken == "Kd")
			{
				std::vector<std::string> temp;
				StringUtils::Split(StringUtils::GetTail(curline), temp, " ");

				if (temp.size() != 3)
					continue;

				tempMaterial.baseColor.x = std::stof(temp[0]);
				tempMaterial.baseColor.y = std::stof(temp[1]);
				tempMaterial.baseColor.z = std::stof(temp[2]);
			}
			// Specular Exponent
			if (firstToken == "Ns")
			{
				tempMaterial.roughness = std::clamp(std::stof(StringUtils::GetTail(curline)), 0.0f, 1.0f);
			}
			// Diffuse Color Map
			if (firstToken == "map_Kd") {
				std::string texPath = StringUtils::GetTail(curline);
				if (FileUtils::FileExists(texPath))
					tempMaterial.baseTexture = texPath;
				else {
					size_t lastPosition = path.find_last_of("/");
					if (lastPosition != std::string::npos) {
						std::string newPath = path.substr(0, lastPosition + 1) + texPath;
						if (FileUtils::FileExists(newPath))
							tempMaterial.baseTexture = newPath;
					}
				}
			}
			// Specular Hightlight Map
			if (firstToken == "map_Ns") {
				std::string texPath = StringUtils::GetTail(curline);
				if (FileUtils::FileExists(texPath))
					tempMaterial.roughnessTexture = texPath;
				else {
					size_t lastPosition = path.find_last_of("/");
					if (lastPosition != std::string::npos) {
						std::string newPath = path.substr(0, lastPosition + 1) + texPath;
						if (FileUtils::FileExists(newPath))
							tempMaterial.roughnessTexture = newPath;
					}
				}
			}
			// Bump Map
			if (firstToken == "map_Bump" || firstToken == "map_bump" || firstToken == "bump") {
				std::string texPath = StringUtils::GetTail(curline);
				if (FileUtils::FileExists(texPath))
					tempMaterial.normalMapTexture = texPath;
				else {
					size_t lastPosition = path.find_last_of("/");
					if (lastPosition != std::string::npos) {
						std::string newPath = path.substr(0, lastPosition + 1) + texPath;
						if (FileUtils::FileExists(newPath))
							tempMaterial.normalMapTexture = newPath;
					}
				}
			}
		}

		LoadedMaterials.push_back(tempMaterial);
		if (LoadedMaterials.empty())
			return false;
		else
			return true;
	}
}