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
	Model ObjFile::model() {
		Model retval;
		retval.verts = verts();
		retval.indices = indices();
		return retval;
	}
	std::vector<Vertex> ObjFile::constructVerts() {
		//initialize the return value to the proper size
		std::vector<Vertex> retval(_points.size());
		for (int i = 0; i < _points.size(); ++i) {
			retval[i].pos = _points[i];
			//find the first position of the vertex in the set of indexes
			//from this information we can find the associated UV value
			auto indexIterators = std::find(_indices.begin(), _indices.end(), i+1);
			if (indexIterators == _indices.end()) {
				retval[i].uv = Eigen::Vector3f(0, 0, 0);
			} else {
				int indexPos = static_cast<int>(indexIterators - _indices.begin());
				int uvIndex = _uvIndices[indexPos];
				retval[i].uv = _uvs[uvIndex];
			}

		}
		return retval;
	}
	void ObjFile::read(const std::string& filename) {
		std::ifstream inFile(filename, std::ifstream::in);
		read(inFile);
	}
	void ObjFile::read(std::istream& from) {
		std::vector<Eigen::Vector4f> points;
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
	std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> ObjFile::parseIndex(const std::string& line) {
		std::vector<int> indices;
		std::vector<int> uvIndices;
		std::vector<int> vnIndices;
		std::stringstream st(line);
		char type;
		st >> type;
		if (type != 'f') {
			throw std::exception("not a valid face record");
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