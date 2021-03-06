#include "Transform.h"
#include <LibComponents/ParentLink.h>
#include <LibCommon/Entity.h>
namespace Components {
    Transform3D::Transform3D ( const Eigen::Affine3f& trans )
        : Transform3D ( trans.translation(), Eigen::Quaternionf ( trans.rotation() ) )
    {}
    Transform3D::Transform3D ( const Eigen::Vector3f& trans )
        : Transform3D ( trans, Eigen::Quaternionf::Identity() ) {}
    Transform3D::Transform3D ( const Eigen::Quaternionf& rot )
        : Transform3D ( Eigen::Vector3f::Identity(), rot ) {}
    Transform3D::Transform3D ( const Eigen::Vector3f& trans, const Eigen::Quaternionf& rot )
        : position ( trans ), rotation ( rot ) {}

    Eigen::Matrix4f Transform3D::GenMatrix() const {
        auto realTransform = ent->GetOptional<Components::ParentLink>();
        if ( realTransform ) {
            return ( Eigen::Translation3f ( realTransform->position ) * realTransform->rotation ).matrix();
        } else {
            return ( Eigen::Translation3f ( position ) * rotation ).matrix();
        }
    }
    Eigen::Matrix4f Transform3D::GenRotTransMatrix() const {
        auto realTransform = ent->GetOptional<Components::ParentLink>();
        if ( realTransform ) {
            return ( realTransform->rotation * Eigen::Translation3f ( realTransform->position ) ).matrix();
        } else {
            return ( rotation * Eigen::Translation3f ( position ) ).matrix();
        }
    }
}
