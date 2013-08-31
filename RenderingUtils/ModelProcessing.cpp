#include "ModelProcessing.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace utils {
	Components::Model generate_quad(float width, float height) {
		using namespace Components;
		using LibCommon::Vertex;
		Model rv;
		float x = (width / 2);
		float y = (height / 2);
		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
		topLeft.pos = Eigen::Vector4f{ -x, y, 0, 1 };
		topLeft.norm = Eigen::Vector4f{ 0, 0, 1, 1 };
		topLeft.uv = Eigen::Vector3f{ 0, 0, 0 };
		topRight.pos = Eigen::Vector4f{ x, y, 0, 1 };
		topRight.norm = Eigen::Vector4f{ 0, 0, 1, 1 };
		topRight.uv = Eigen::Vector3f{ 1, 0, 0 };
		bottomLeft.pos = Eigen::Vector4f{ -x, -y, 0, 1 };
		bottomLeft.norm = Eigen::Vector4f{ 0, 0, 1, 1 };
		bottomLeft.uv = Eigen::Vector3f{ 0, 1, 0 };
		bottomRight.pos = Eigen::Vector4f{ x, -y, 0, 1 };
		bottomRight.norm = Eigen::Vector4f{ 0, 0, 1, 1 };
		bottomRight.uv = Eigen::Vector3f{ 1, 1, 0 };
		rv.verts.push_back(topLeft);
		rv.verts.push_back(topRight);
		rv.verts.push_back(bottomLeft);
		rv.verts.push_back(bottomRight);
		rv.indices = { 0, 1, 2, 2, 1, 3 };
		return rv;
	}
}