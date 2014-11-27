#pragma once

#include <Box2D/Box2D.h>

class Convert {
	public:
		Convert() : PIXELS_TO_WORLD(0.033f), WORLD_TO_PIXELS(30.0f) {};
		b2Vec2 CoordWorldToPixels(b2Vec2 world, b2Vec2 size);
		b2Vec2 CoordWorldToPixels(float x, float y, float width, float height);
		b2Vec2 CoordPixelsToWorld(b2Vec2 pixels, b2Vec2 size);
		b2Vec2 CoordPixelsToWorld(float x, float y, float width, float height);

	private:
		const float PIXELS_TO_WORLD;
		const float WORLD_TO_PIXELS;
};