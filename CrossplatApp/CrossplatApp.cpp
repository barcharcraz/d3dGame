#include <windowing.h>
int main(int argc, char** argv) {
	auto window = windowing::Window();
	window.Show();
	return windowing::Run();
}
