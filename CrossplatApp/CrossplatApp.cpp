#include <windowing.h>
#include <Rendering.h>
#include <Utils/make_unique.h>
int main(int argc, char** argv) {
	auto window = windowing::Window();
	Rendering::Renderer rend;
	auto ModelRenderSys = std::make_unique<Rendering::ModelRenderer>(&rend);
	
	window.Show();
	return windowing::Run();
}
