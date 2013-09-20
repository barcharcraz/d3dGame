#ifndef LIBCOMMON_DATA_H
#define LIBCOMMON_DATA_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>
namespace LibCommon {
	class Entity;
	struct Vertex {
		Eigen::Vector4f pos;
		Eigen::Vector4f norm;
		Eigen::Vector3f uv;
	};
	inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
		return (
			lhs.pos == rhs.pos &&
			lhs.norm == rhs.norm &&
			lhs.uv == rhs.uv
			);
	}
	
	struct Transforms {
		Eigen::Matrix4f model;
		Eigen::Matrix4f view;
		Eigen::Matrix4f proj;
	};
	struct point_light {
		Eigen::Vector4f diffuse;
		Eigen::Vector4f specular;
		Eigen::Vector4f position;
	};
	struct directional_light {
		Eigen::Vector4f diffuse;
		Eigen::Vector4f specular;
		Eigen::Vector4f direction;
	};
	//! \brief returns a list of point lights in a format that can be sent to the GPU
	//!
	//! this this function is needed because we would like to define a light as an
	//! entity with a transform and lighting component, not as a component that has
	//! transform information
	std::vector<point_light> fuse_point_lights(const std::vector<Entity*>& lights);
	//! \brief returns a list of directional lights in a format that can be sent to the
	//! GPU
	std::vector<directional_light> fuse_dir_lights(const std::vector<Entity*>& lights);
}
namespace std {
	template<>
	struct hash<LibCommon::Vertex> {
		std::size_t operator()(const LibCommon::Vertex& v) const {
			const unsigned long long int p = 167776199234521;
			std::size_t hash = 2166136261;
			hash = (hash ^ (std::size_t)v.pos.x()) * p;
			hash = (hash ^ (std::size_t)v.pos.y()) * p;
			hash = (hash ^ (std::size_t)v.pos.z()) * p;
			hash = (hash ^ (std::size_t)v.pos.w()) * p;
			hash = (hash ^ (std::size_t)v.norm.x()) * p;
			hash = (hash ^ (std::size_t)v.norm.y()) * p;
			hash = (hash ^ (std::size_t)v.norm.z()) * p;
			hash = (hash ^ (std::size_t)v.norm.w()) * p;
			hash = (hash ^ (std::size_t)v.uv.x()) * p;
			hash = (hash ^ (std::size_t)v.uv.y()) * p;
			hash = (hash ^ (std::size_t)v.uv.z()) * p;
			//scramble the hash
			hash += hash << 13;
			hash ^= hash >> 7;
			hash += hash << 3;
			hash ^= hash >> 17;
			hash += hash << 5;
			return hash;
		}
	};
}
#endif