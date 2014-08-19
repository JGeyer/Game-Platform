#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Basic {
	public:
		Basic() : SCALE(30.0f), TIMESTEP(1 / 60.0f) {};
		bool CreateGround(b2World& world, float x, float y);
		bool CreateBox(b2World& world, int mouse_x, int mouse_y);
		bool BasicTest();

	private:
		const float SCALE;
		const float TIMESTEP;
};