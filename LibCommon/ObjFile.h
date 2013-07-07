#ifndef LIBCOMMON_OBJFILE_H
#define LIBCOMMON_OBJFILE_H
#include "stdafx.h"
#include "GeometryFile.h"
namespace LibCommon {
	class ObjFile : public VertexFile, public IndexFile {
	public:
		ObjFile(const std::string& filename);
		ObjFile(std::istream& from);
		virtual std::vector<Eigen::Vector4f> points() override;
		virtual std::vector<int> indices() override;
		
		
	private:
		void read(const std::string& filename);
		void read(std::istream& from);
		Eigen::Vector4f parseVertex(const std::string& line);
		std::vector<int> parseIndex(const std::string& line);
		Eigen::Vector3f parseUV(const std::string& line);
		std::vector<int> _indices;
		std::vector<Eigen::Vector3f> _uvs;
		std::vector<Eigen::Vector4f> _points;
	};
}

#endif