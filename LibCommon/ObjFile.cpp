#include "stdafx.h"
#include "ObjFile.h"
#include <fstream>
#include <Utils/strings.h>
#include <exception>
#include <algorithm>
#include <cassert>
#include <unordered_map>
namespace LibCommon {
	ObjFile::ObjFile(const std::string& filename) {
		read(filename);
	}
	ObjFile::ObjFile(std::istream& from) {
		read(from);
	}
    Components::Model ObjFile::model() {
		return std::move(constructModel());
	}
	Components::Model ObjFile::constructModel() {
		Components::Model retval;
		//this map is used to speed up checks for duplicate values
		//when we add a vertex to the return value we cache its index here
		//this way we can get O(1) searches for duplicates
		std::unordered_map<Vertex, int> indexMap;
		//assert(_vnIndices.size() == _indices.size() == _uvIndices.size());
		for (unsigned int i = 0; i < _indices.size(); ++i) {
			Vertex vert;
			vert.pos = _points[_indices[i]];
			vert.norm = _normals[_vnIndices[i]] * -1;
			vert.norm.w() = 1;
			vert.uv = _uvs[_uvIndices[i]];
			//auto iter = std::find(retval.verts.begin(), retval.verts.end(), vert);
			//unsigned int position = iter - retval.verts.begin();
			if (indexMap.count(vert) == 0) {
				retval.verts.push_back(vert);
				retval.indices.push_back(retval.verts.size() - 1);
				indexMap[vert] = retval.verts.size() - 1;
			} else {
				retval.indices.push_back(indexMap.at(vert));
			}
			
		}
		reverseIndices(retval.indices);
		//std::reverse(retval.verts.begin(), retval.verts.end());
		return retval;
	}
	void ObjFile::read(const std::string& filename) {
		std::ifstream inFile(filename, std::ifstream::in);
		read(inFile);
	}
	void ObjFile::read(std::istream& from) {
		std::vector<Eigen::Vector4f> points;
		std::vector<Eigen::Vector4f> normals;
		std::vector<int> indices;
		std::vector<int> uvIndices;
		std::vector<int> vnIndices;
		std::vector<Eigen::Vector3f> uvs;
		std::string curLine;
		while (!from.eof()) {
			std::getline(from, curLine);
			utils::trim(&curLine);
			if (curLine.compare(0, 2, "v ") == 0) {
				
				points.push_back(parseVertex(curLine));
			}
			else if (curLine.compare(0, 2, "f ") == 0) {
				auto tuple = parseIndex(curLine);
				
				indices.insert(indices.end(), std::get<0>(tuple).begin(), std::get<0>(tuple).end());
				uvIndices.insert(uvIndices.end(), std::get<1>(tuple).begin(), std::get<1>(tuple).end());
				vnIndices.insert(vnIndices.end(), std::get<2>(tuple).begin(), std::get<2>(tuple).end());
				
			} else if (curLine.compare(0, 3, "vt ") == 0) {
				uvs.push_back(parseUV(curLine));
			} else if (curLine.compare(0, 3, "vn ") == 0) {
				normals.push_back(parseNormal(curLine));
			}
		}
		//std::reverse(indices.begin(), indices.end());
		//std::reverse(vnIndices.begin(), vnIndices.end());
		//std::reverse(uvIndices.begin(), uvIndices.end());
		_points = std::move(points);
		_indices = std::move(indices);
		_normals = std::move(normals);
		_uvIndices = std::move(uvIndices);
		_vnIndices = std::move(vnIndices);
		_uvs = std::move(uvs);
	}
	Eigen::Vector4f ObjFile::parseVertex(const std::string& line) {
		float x;
		float y;
		float z;
		float w;
		std::stringstream st(line);
		char type;
		st >> type;
		
        if (type != 'v') {
            throw std::runtime_error("not a valid vertex record");
		}
		st >> x >> y >> z;
		if (!st.eof()) {
			st >> w;
		} else {
			w = 1.0f;
		}
		return Eigen::Vector4f(x, y, z, w);

	}
	Eigen::Vector4f ObjFile::parseNormal(const std::string& line) {
		float x;
		float y;
		float z;
		float w;
		std::stringstream st(line);
		std::string type;
		st >> type;
		if (type != "vn") {
			throw std::runtime_error("not a valid vertex normal record");
		}
		st >> x >> y >> z;
		if (!st.eof()) {
			st >> w;
		} else {
			w = 1.0f;
		}
		return Eigen::Vector4f(x, y, z, w);
	}
	std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> ObjFile::parseIndex(const std::string& line) {
		std::vector<int> indices;
		std::vector<int> uvIndices;
		std::vector<int> vnIndices;
		std::stringstream st(line);
		char type;
		st >> type;
		if (type != 'f') {
            throw std::runtime_error("not a valid face record");
		}
		int curIdx;
		//we use this to only take the "UV"
		//once instead of taking both the UV and the normal
		while (!st.eof()) {
			if (st.peek() == '/') {
				int uvIndex;
				//pull off the /
				st >> type;
				st >> uvIndex;
				uvIndices.push_back(uvIndex - 1);
				if (st.peek() == '/') {
					int vnIdx;
					st >> type;
					st >> vnIdx;
					vnIndices.push_back(vnIdx - 1);
					
				}
			} else {
				st >> curIdx;
				indices.push_back(curIdx - 1);
			}
		}
		return std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>(
			std::move(indices), std::move(uvIndices), std::move(vnIndices));
	}
	Eigen::Vector3f ObjFile::parseUV(const std::string& line) {
		float u;
		float v;
		float w;
		std::stringstream st(line);
		std::string type;
		st >> type;
		if (type != "vt") {
            throw std::runtime_error("not a valid vt record");
		}
		st >> u >> v;
		if (!st.eof()) {
			st >> w;
		} else {
			w = 0.0f;
		}
		return Eigen::Vector3f(u, v, w);
	}
	void ObjFile::reverseIndices(std::vector<unsigned int>& indices) {
		for (unsigned int i = 0; i < _indices.size(); i += 3) {
			auto temp = indices[i];
			indices[i] = indices[i + 1];
			indices[i + 1] = temp;
		}
	}
}
