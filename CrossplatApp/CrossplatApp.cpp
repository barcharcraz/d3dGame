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
#include <LibImage/image.h>
#include <LibImage/targa.h>
#include <LibSystems/VelocitySystem3D.h>
#include <LibSystems/MovementController3D.h>
#include <LibInput/Input.h>
static void load_effects();
static std::unique_ptr<Input::Input> construct_input();
int main(int argc, char** argv) {
    windowing::Window window;
    Rendering::Renderer rend(window.Hwnd());
	auto input = construct_input();
	window.AttachInput(input.get());
    load_effects();
    Assets::ObjFile cone{"Cone.obj"};
    Image::Targa::Targa tex{"Textures/wood_black/diffuse.tga"};
    std::unique_ptr<LibCommon::Scene> scene(new LibCommon::Scene());
    auto mod = std::make_unique<Prefabs::StaticModel>(cone, Image::ImageData(tex)); 

    auto camera = (*scene).AddEntity<Prefabs::Camera>();
	camera->AddComponent(std::move(input));
    mod->Get<Components::Transform3D>()->transform.translate(Eigen::Vector3f{0,0,-10});
    mod->AddComponent<Components::Velocity3D>(Eigen::Affine3f{Eigen::AngleAxisf{0.001f, Eigen::Vector3f::UnitZ()}});

    scene->AddEntity(std::move(mod));
	scene->AddSystem<Systems::MovementController3D>();
	scene->AddSystem<Systems::VelocitySystem3D>();
	
    
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
	Effects::Effect DefaultEffect{ "DefaultVS.cso", "DefaultPS.cso", defaultLayout, defaultCaps };
	DefaultEffect.defines = { { "NUM_DIRECTIONAL", 8 }, { "NUM_POINT", 8 } };
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
