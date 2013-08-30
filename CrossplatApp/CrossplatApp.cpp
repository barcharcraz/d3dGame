#include <Rendering.h>
#include <windowing.h>
#include <LibCommon/Scene.h>
#include <Components.h>
#include <Utils/make_unique.h>
#include <memory>
#include <LibEffects/EffectsManagement.h>
#include <LibAssets/ObjFile.h>
static void load_effects();
int main(int argc, char** argv) {
	auto window = windowing::Window(nullptr);
	Rendering::Renderer rend;
	LibCommon::ObjFile cone{"Cone.obj"};
	std::unique_ptr<LibCommon::Scene> scene(new LibCommon::Scene());
	(*scene).AddSystem<Rendering::ModelRenderer>(&rend);
	scene->AddEntity(cone.model());
	window.Show();
	window.update = [&]() {
		(*scene).Update();
	};
	return windowing::Run();
}
void load_effects() {
	using Effects::InputFormats;
	using Effects::SlotClass;
	using Effects::ShaderCaps;
	const std::vector<Effects::ShaderDesc> defaultLayout = {
		{ "POSITION", 0, InputFormats::R32G32B32A32_FLOAT, 0, 0, SlotClass::PER_VERTEX, 0}
	};
	const std::set<Effects::ShaderCaps> defaultCaps = {
		ShaderCaps::MESH_INDEXED,
		ShaderCaps::TEXTURE_MAPPED,
		ShaderCaps::LIT_DIRECTIONAL
	};
	Effects::AddEffect(Effects::Effect("DefaultVS.glsl", "DefaultPS.glsl", defaultLayout, defaultCaps);
}

