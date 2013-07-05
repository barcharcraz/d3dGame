#include "stdafx.h"
#include "ObjFile.h"
#include <fstream>
namespace LibCommon {
	ObjFile::ObjFile(const std::string& filename) {
		read(filename);
	}
	void ObjFile::read(const std::string& filename) {
		std::ifstream inFile(filename);
		read(inFile);
	}
	void ObjFile::read(std::istream& from) {
		std::vector<Eigen::Vector3f> verts;
		std::vector<int> indices;
		std::string curLine;
		while (!from.eof()) {
			std::getline(from, curLine);
			if (curLine[0] == 'v') {
				verts.push_back(parseLine(curLine));
			}
			else if (curLine[0] == 'f') {
				auto vec = parseIndex(curLine);
				indices.insert(indices.begin(), vec.begin(), vec.end());
			}
		}
		_verts = std::move(verts);
		_indices = std::move(indices);
	}
	Eigen::Vector3f parseLine(const std::string& line) {
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
		st >> x >> y >> z >> w;
		return Eigen::Vector3f(x, y, z, w);

	}
	std::vector<int> parseIndex(const std::string& line) {
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
}