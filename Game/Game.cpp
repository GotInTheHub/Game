#include "../EngineCore/Core/engine.hpp"

int main()
{
	Engine::Engine engine(800, 600, "My Game");
	engine.run();
	return 0;
}