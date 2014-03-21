#ifndef LIBCOMPONENTS_TRANSFORM_H
#define LIBCOMPONENTS_TRANSFORM_H
#include "IComponent.h"
#include <Eigen/Geometry>
#include <Utils/event.h>
namespace Components {
    struct Transform3D : public IComponent {
        Transform3D ( const Eigen::Affine3f& trans );
        Transform3D ( const Eigen::Vector3f& translation );
        Transform3D ( const Eigen::Quaternionf& rotation );
        Transform3D ( const Eigen::Vector3f& trans, const Eigen::Quaternionf& rotation );
        Eigen::Matrix4f GenMatrix() const;
        Eigen::Matrix4f GenRotTransMatrix() const;
        Eigen::Vector3f position;
        Eigen::Quaternionf rotation;
    };
    class Transform3DUpdate : public IComponent {};
}
#endif
