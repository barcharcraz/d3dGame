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
	void ObjFile::read(const std::string& filename) {
		std::ifstream inFile(filename);
		read(inFile);
	}
	void ObjFile::read(std::istream& from) {
		std::vector<Eigen::Vector4f> points;
		std::vector<int> indices;
		std::vector<Eigen::Vector3f> uvs;
		std::string curLine;
		while (!from.eof()) {
			std::getline(from, curLine);
			utils::trim(&curLine);
			if (curLine[0] == 'v') {
				
				points.push_back(parseVertex(curLine));
			}
			else if (curLine[0] == 'f') {
				auto vec = parseIndex(curLine);
				indices.insert(indices.end(), vec.begin(), vec.end());
			} else if (curLine[0] == 'vt') {
				uvs.insert.push_back(parseUV(curLine));
			}
		}
		_points = std::move(points);
		_indices = std::move(indices);
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
	std::vector<int> ObjFile::parseIndex(const std::string& line) {
		std::vector<int> retval;
		std::stringstream st(line);
		char type;
		st >> type;
		if (type != 'f') {
			throw std::exception("not a valid face record");
		}
		int curIdx;
		while (!st.eof()) {
			st >> curIdx;
			retval.push_back(curIdx);
		}
		return retval;
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