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
#include <LibImage/image.h>
#include <LibImage/targa.h>
#include <LibSystems/VelocitySystem3D.h>
#include <LibSystems/PremulVelocitySystem3D.h>
#include <LibSystems/MovementController3D.h>
#include <LibInput/Input.h>
static void load_effects();
static std::unique_ptr<Input::Input> construct_input();
int main(int, char**) {
    windowing::Window window;
    Rendering::Renderer rend(&window);
    auto input = construct_input();
    window.AttachInput(input.get());
    load_effects();
    Assets::ObjFile teapot{ "TestObj.obj" };
    Assets::ObjFile cone{ "Cone.obj" };
    Assets::ObjFile helix{ "Helix.obj" };
    Image::Targa::Targa tex{ "Textures/wood_light/diffuse.tga" };
    std::unique_ptr<LibCommon::Scene> scene(new LibCommon::Scene());
    auto mod = std::make_unique<Prefabs::StaticModel>(cone, Image::ImageData(tex));
    auto leftMod = std::make_unique<Prefabs::StaticModel>(teapot, Image::ImageData(tex));
    auto rightMod = std::make_unique<Prefabs::StaticModel>(cone, Image::ImageData(tex));
    auto topMod = std::make_unique<Prefabs::StaticModel>(helix, Image::ImageData(tex));
    auto bottomMod = std::make_unique<Prefabs::StaticModel>(cone, Image::ImageData(tex));
    auto camera = (*scene).AddEntity<Prefabs::Camera>();
    camera->AddComponent(std::move(input));
    mod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{ 0, 0, -10 });
    leftMod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{ -10, 0, -10 });
    rightMod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{ 10, 0, -10 });
    topMod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{ 0, 10, -10 });
    bottomMod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{ 0, -10, -10 });
    mod->AddComponent<Components::Velocity3D>(Eigen::Affine3f{ Eigen::AngleAxisf{ 0.001f, Eigen::Vector3f::UnitZ() } });
    topMod->AddComponent<Components::Velocity3D>(Eigen::Affine3f{ Eigen::AngleAxisf{ 0.01f, Eigen::Vector3f::UnitX() } });

    scene->AddEntity(std::move(mod));
    scene->AddEntity(std::move(leftMod));
    scene->AddEntity(std::move(rightMod));
    scene->AddEntity(std::move(topMod));
    scene->AddEntity(std::move(bottomMod));
    scene->AddSystem<Systems::MovementController3D>();
    scene->AddSystem<Systems::VelocitySystem3D>();
    scene->AddSystem<Systems::PremulVelocitySystem3D>();
    scene->AddEntity<Prefabs::DirectionalLight>(Eigen::Vector4f{ 1.0f, 1.0f, 1.0f, 1.0f }, Eigen::Vector3f{ 0.0f, 0.0f, -1.0f });
    
    (*scene).AddSystem<Rendering::ModelRenderer>(&rend);
    
    window.Show();
    window.update = [&]() {
        (*scene).Update();
        rend.Present();
        rend.Clear();
        
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
    Effects::Effect DefaultEffect{ "DefaultVS.glsl", "DefaultPS.glsl", defaultLayout, defaultCaps };
    DefaultEffect.defines = std::unordered_map<std::string, int>{{ { "NUM_DIRECTIONAL", 8 }, { "NUM_POINT", 8 } }};
    Effects::AddEffect(DefaultEffect);
}
std::unique_ptr<Input::Input> construct_input() {
    auto rv = std::make_unique<Input::Input>();
    rv->AddAction("Left", Input::A);
    rv->AddAction("Right", Input::D);
    rv->AddAction("Forward", Input::W);
    rv->AddAction("Backward", Input::S);
    rv->AddAxisAction("Horizontal", Input::MouseType, Input::AxisName::X);
    rv->AddAxisAction("Vertical", Input::MouseType, Input::AxisName::Y);
    return rv;
}
