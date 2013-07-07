#include "stdafx.h"
#include "ObjFile.h"
#include <fstream>
#include <Utils/strings.h>

namespace LibCommon {
	ObjFile::ObjFile(const std::string& filename) {
		read(filename);
	}
	ObjFile::ObjFile(std::istream& from) {
		read(from);
	}
	std::vector<Eigen::Vector4f> ObjFile::points() {
		return _points;
	}
	std::vector<int> ObjFile::indices() {
		return _indices;
	}
	std::vector<Vertex> ObjFile::verts() {
		if (_verts.empty()) {
			_verts = constructVerts();
		}
		return _verts;
	}
	std::vector<Vertex> ObjFile::constructVerts() {
		//initialize the return value to the proper size
		std::vector<Vertex> retval(_points.size());
		for (int i = 0; i < _points.size(); ++i) {
			retval[i].pos = _points[i];
			//find the first position of the vertex in the set of indexes
			//from this information we can find the associated UV value
			int indexPos = std::find(_indices.begin(), _indices.end(), i) - _indices.begin();
			int uvIndex = _uvIndices[indexPos];
			retval[i].uv = _uvs[uvIndex];

		}
		return retval;
	}
	void ObjFile::read(const std::string& filename) {
		std::ifstream inFile(filename);
		read(inFile);
	}
	void ObjFile::read(std::istream& from) {
		std::vector<Eigen::Vector4f> points;
		std::vector<int> indices;
		std::vector<int> uvIndices;
		std::vector<Eigen::Vector3f> uvs;
		std::string curLine;
		while (!from.eof()) {
			std::getline(from, curLine);
			utils::trim(&curLine);
			if (curLine[0] == 'v') {
				
				points.push_back(parseVertex(curLine));
			}
			else if (curLine[0] == 'f') {
				auto pair = parseIndex(curLine);
				indices.insert(indices.end(), pair.first.begin(), pair.first.end());
				uvIndices.insert(uvIndices.end(), pair.second.begin(), pair.second.end());
				
			} else if (curLine[0] == 'vt') {
				uvs.insert.push_back(parseUV(curLine));
			}
		}
		_points = std::move(points);
		_indices = std::move(indices);
		_uvIndices = std::move(uvIndices);
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
			throw std::exception("not a valid vertex record");
		}
		st >> x >> y >> z;
		if (!st.eof()) {
			st >> w;
		} else {
			w = 1.0f;
		}
		return Eigen::Vector4f(x, y, z, w);

	}
	std::pair<std::vector<int>, std::vector<int>> ObjFile::parseIndex(const std::string& line) {
		std::vector<int> indices;
		std::vector<int> uvIndices;
		std::stringstream st(line);
		char type;
		st >> type;
		if (type != 'f') {
			throw std::exception("not a valid face record");
		}
		int curIdx;
		
		while (!st.eof()) {
			if (st.peek() == '/') {
				int uvIndex;
				//pull off the /
				st >> type;
				st >> uvIndex;
				uvIndices.push_back(uvIndex);
			} else {
				st >> curIdx;
				indices.push_back(curIdx);
			}
		}
		return std::pair<std::vector<int>, std::vector<int>>(indices, uvIndices);
	}
	Eigen::Vector3f ObjFile::parseUV(const std::string& line) {
		float u;
		float v;
		float w;
		std::stringstream st(line);
		char type;
		st >> type;
		if (type != 'vt') {
			throw std::exception("not a valid vt record");
		}
		st >> u >> v;
		if (!st.eof()) {
			st >> w;
		} else {
			w = 0.0f;
		}
		return Eigen::Vector3f(u, v, w);
	}
}