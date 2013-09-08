#include <Rendering.h>
#include <windowing.h>
#include <LibCommon/Scene.h>
#include <Components.h>
#include <Utils/make_unique.h>
#include <memory>
#include <LibEffects/EffectsManagement.h>
#include <LibAssets/ObjFile.h>
#include <LibPrefabs/StaticModel.h>
#include <LibImage/image.h>
#include <LibImage/targa.h>
static void load_effects();
int main(int argc, char** argv) {
	windowing::Window window;
	Rendering::Renderer rend;
	load_effects();
	Assets::ObjFile cone{"Cone.obj"};
	Image::Targa::Targa tex{"Textures/wood_black/diffuse.tga"};
	std::unique_ptr<LibCommon::Scene> scene(new LibCommon::Scene());
	(*scene).AddSystem<Rendering::ModelRenderer>(&rend);
	scene->AddEntity<Prefabs::StaticModel>(cone, Image::ImageData(tex));
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
		Effects::ShaderDesc{ "POSITION", 0, InputFormats::R32G32B32A32_FLOAT, 0, 0, SlotClass::PER_VERTEX, 0}
	};
	const std::set<Effects::ShaderCaps> defaultCaps = {
		ShaderCaps::MESH_INDEXED,
		ShaderCaps::TEXTURE_MAPPED,
		ShaderCaps::LIT_DIRECTIONAL
	};
	Effects::AddEffect(Effects::Effect("DefaultVS.glsl", "DefaultPS.glsl", defaultLayout, defaultCaps));
}

