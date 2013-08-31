#ifndef LIBCOMMON_OBJFILE_H
#define LIBCOMMON_OBJFILE_H
#include "stdafx.h"
#include "GeometryFile.h"
#include <LibCommon/Data.h>
#include <LibComponents/Model.h>
namespace Assets {
	class ObjFile : public GeometryFile {
	public:
		ObjFile(const std::string& filename);
		ObjFile(std::istream& from);
		virtual const std::vector<unsigned int>& Indices() const override;
		virtual const std::vector<LibCommon::Vertex>& Verts() const override;
		
	private:
		void read(const std::string& filename);
		void read(std::istream& from);
		Eigen::Vector4f parseVertex(const std::string& line);
		Eigen::Vector4f parseNormal(const std::string& line);
		std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> parseIndex(const std::string& line);
		Eigen::Vector3f parseUV(const std::string& line);
		Components::Model constructModel() const;
		mutable Components::Model modelCache;
		std::vector<int> _indices;
		std::vector<int> _uvIndices;
		std::vector<int> _vnIndices;
		std::vector<Eigen::Vector4f> _normals;
		std::vector<Eigen::Vector3f> _uvs;
		std::vector<Eigen::Vector4f> _points;
		
	};
}

#endif