#include <Rendering.h>
#include <windowing.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <LibCommon/Scene.h>
#include <Components.h>
#include <Utils/make_unique.h>
#include <memory>
#include <LibEffects/EffectsManagement.h>
#include <LibAssets/ObjFile.h>
#include <LibPrefabs/StaticModel.h>
#include <LibPrefabs/Camera.h>
#include <LibPrefabs/PointLight.h>
#include <LibPrefabs/DirectionalLight.h>
#include <LibPrefabs/SkyDome.h>
#include <LibImage/image.h>
#include <LibImage/targa.h>
#include <LibSystems/VelocitySystem3D.h>
#include <LibSystems/PremulVelocitySystem3D.h>
#include <LibSystems/MovementController3D.h>
#include <LibSystems/ParentingSystem.h>
#include <LibSystems/GunController.h>
#include <LibSystems/ProjectileSystem.h>
#include <LibSystems/CollisionDetectionSystem.h>
#include <LibSystems/SimpleCollisionSystem.h>
#include <LibSystems/AxisAlignedBBSystem.h>
#include <LibInput/Input.h>
#include <LibDirect3D/BoundingBoxRenderer.h>
#include <LibImage/ImageLoader.h>
static void load_effects();
static std::unique_ptr<Input::Input> construct_input();
int main ( int, char** ) {
    windowing::Window window;
    auto input = construct_input();
    window.AttachInput ( input.get() );
    load_effects();
    Assets::ObjFile teapot { "TestObj.obj" };
    Assets::ObjFile cone { "Cone.obj" };
    Assets::ObjFile helix { "Helix.obj" };
    Image::ImageData& tex = Image::GetImageData ( "Textures/wood_light/diffuse.tga" );
    Image::ImageData& background = Image::GetImageData ( "Textures/starfield/diffuse1024x1024.tga" );
    std::unique_ptr<LibCommon::Scene> scene ( new LibCommon::Scene() );
    auto mod = std::make_unique<Prefabs::StaticModel> ( cone, tex );
    auto leftMod = std::make_unique<Prefabs::StaticModel> ( teapot, tex );
    auto rightMod = std::make_unique<Prefabs::StaticModel> ( cone, tex );
    auto topMod = std::make_unique<Prefabs::StaticModel> ( helix, tex );
    auto bottomMod = std::make_unique<Prefabs::StaticModel> ( cone, tex );
    auto camera = ( *scene ).AddEntity<Prefabs::Camera>();
    camera->AddComponent ( std::move ( input ) );
    camera->AddComponent<Components::GunDefinition> ( "Textures/laser_test/diffuse.tga", 0.1f, std::chrono::milliseconds ( 2000 ) );
    camera->AddComponent<Components::Collision>();
    camera->AddComponent<Components::AxisAlignedBB> ( Eigen::AlignedBox3f { Eigen::Vector3f{ -1.5f, -1.5f, -1.5f }, Eigen::Vector3f{ 1.5f, 1.5f, 1.5f } } );
    mod->Get<Components::Transform3D>()->position = Eigen::Vector3f { 0, 0, -10 };
    leftMod->Get<Components::Transform3D>()->position = Eigen::Vector3f { -10, 0, -10 };
    rightMod->Get<Components::Transform3D>()->position = Eigen::Vector3f { 10, 0, -10 };
    topMod->Get<Components::Transform3D>()->position = Eigen::Vector3f { 0, 10, -10 };
    bottomMod->Get<Components::Transform3D>()->position = Eigen::Vector3f { 0, -10, -10 };
    mod->AddComponent<Components::Velocity3D> ( Eigen::Affine3f { Eigen::AngleAxisf{ 0.001f, Eigen::Vector3f::UnitZ() } } );
    //topMod->AddComponent<Components::Velocity3D> ( Eigen::Affine3f { Eigen::AngleAxisf{ 0.01f, Eigen::Vector3f::UnitX() } } );
    //topMod->Get<Components::Velocity3D>()->linear = Eigen::Vector3f{ 0.0f, 0.0f, -0.05f };
    scene->AddEntity<Prefabs::SkyDome> ( 50.0f, background, camera->Get<Components::ParentLink>() );
    scene->AddEntity ( std::move ( mod ) );
    scene->AddEntity ( std::move ( leftMod ) );
    scene->AddEntity ( std::move ( rightMod ) );
    scene->AddEntity ( std::move ( topMod ) );
    scene->AddEntity ( std::move ( bottomMod ) );
    
    scene->AddSystem<Systems::MovementController3D>();
    scene->AddSystem<Systems::GunController>();
    scene->AddSystem<Systems::VelocitySystem3D>();
    scene->AddSystem<Systems::PremulVelocitySystem3D>();
    scene->AddSystem<Systems::CollisionDetectionSystem>();
    scene->AddSystem<Systems::SimpleCollisionSystem>();
    scene->AddSystem<Systems::ParentingSystem>();
    scene->AddSystem<Systems::AxisAlignedBBSystem>();
    scene->AddSystem<Systems::ProjectileSystem>();
    
    
    scene->AddEntity<Prefabs::DirectionalLight> ( Eigen::Vector4f { 1.0f, 1.0f, 1.0f, 1.0f }, Eigen::Vector3f { 0.0f, 0.0f, -1.0f } );
    auto renderer = std::make_unique<Rendering::Renderer> ( &window );
    scene->AddSystem<Rendering::ModelRenderer> ( renderer.get() );
    scene->AddSystem<Rendering::BillboardRenderer> ( renderer.get() );
    scene->AddSystem<LibDirect3D::BoundingBoxRenderer>(renderer.get());
    window.Show();
    window.update = [&]() {
        ( *scene ).Update();
        window.Present();
        window.Clear();

    };
    return windowing::Run();
}
void load_effects() {
    using Effects::InputFormats;
    using Effects::SlotClass;
    using Effects::ShaderCaps;
    const std::vector<Effects::ShaderDesc> defaultLayout = {
        Effects::ShaderDesc{ "POSITION", 0, InputFormats::R32G32B32A32_FLOAT, 0, 0, SlotClass::PER_VERTEX, 0 },
        Effects::ShaderDesc{ "NORMAL", 0, InputFormats::R32G32B32A32_FLOAT, 0, Effects::APPEND_ALIGNED_ELEMENT, SlotClass::PER_VERTEX, 0 },
        Effects::ShaderDesc{ "TEXCOORD", 0, InputFormats::R32G32B32_FLOAT, 0, Effects::APPEND_ALIGNED_ELEMENT, SlotClass::PER_VERTEX, 0 }
    };
    const std::set<Effects::ShaderCaps> defaultCaps = {
        ShaderCaps::MESH_INDEXED,
        ShaderCaps::TEXTURE_MAPPED,
        ShaderCaps::LIT_DIRECTIONAL
    };
    Effects::Effect DefaultEffect { "DefaultVS", "DefaultPS", defaultLayout, defaultCaps };
    Effects::Effect BillboardEffect{ "BillboardVS", "BillboardPS", defaultLayout, std::set<ShaderCaps>{ ShaderCaps::RENDER_BILLBOARD } };
    Effects::Effect DebugEffect{ "DebugVS", "DebugPS", defaultLayout, { ShaderCaps::DEBUG_SOLID } };
    Effects::Effect SkydomeEffect{ "BillboardVS", "CubemappedPS", defaultLayout, { ShaderCaps::TEXTURE_MAPPED, ShaderCaps::TEXTURE_CUBEMAPPED, ShaderCaps::MESH_INDEXED } };
    DefaultEffect.defines = std::unordered_map<std::string, int> {{ { "NUM_DIRECTIONAL", 8 }, { "NUM_POINT", 8 } }};
    Effects::AddEffect ( DefaultEffect );
    Effects::AddEffect ( BillboardEffect );
    Effects::AddEffect(DebugEffect);
    Effects::AddEffect(SkydomeEffect);
}
std::unique_ptr<Input::Input> construct_input() {
    auto rv = std::make_unique<Input::Input>();
    rv->AddAction ( "Left", Input::A );
    rv->AddAction ( "Right", Input::D );
    rv->AddAction ( "Forward", Input::W );
    rv->AddAction ( "Backward", Input::S );
    rv->AddAction ( "SwapAPI", Input::Z );
    rv->AddAction ( "Fire", Input::F );
    rv->AddAxisAction ( "Horizontal", Input::MouseType, Input::AxisName::X );
    rv->AddAxisAction ( "Vertical", Input::MouseType, Input::AxisName::Y );
    return rv;
}
