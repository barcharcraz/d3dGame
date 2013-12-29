#include "ModelProcessing.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <vector>
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
    Components::Model generate_icosahedron(float radius) {
        using namespace Components;
        using LibCommon::Vertex;
        Model rv;
        //the golden ratio
        float phi = (1.0f + std::sqrt(5.0f)) / 2.0f;
        std::vector<Eigen::Vector4f> verts;
        std::vector<int> indicies;
        verts.push_back({-1, phi, 0, 1});
        verts.push_back({1, phi, 0, 1});
        verts.push_back({-1, -phi, 0, 1});
        verts.push_back({1, -phi, 0, 1});

        verts.push_back({0, -1, phi, 1});
        verts.push_back({0, 1, phi, 1});
        verts.push_back({0, -1, -phi, 1});
        verts.push_back({0, 1, -phi, 1});

        verts.push_back({phi, 0, -1, 1});
        verts.push_back({phi, 0, 1, 1});
        verts.push_back({-phi, 0, -1, 1});
        verts.push_back({-phi, 0, 1, 1});
        rv.indices = {
            0, 11, 5,
            0, 5, 1,
            0, 1, 7,
            0, 7, 10,
            0, 10, 11,
            1,5,9,
            5,11,4,
            11,10,2,
            10,7,6,
            7,1,8,
            3,9,4,
            3,4,2,
            3,2,6,
            3,6,8,
            3,8,9,
            4,9,5,
            2,4,11,
            6,2,10,
            8,6,7,
            9,8,1 };
        for(auto& elm : verts) {
            Vertex v;
            v.pos = elm.normalized() * radius;
            v.norm = elm.normalized();
            v.uv = elm.normalized().head<3>();
            rv.verts.push_back(v);
        }
        return rv;

        
    }
}
