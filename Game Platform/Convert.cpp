#include "Convert.h"

b2Vec2 Convert::CoordWorldToPixels(b2Vec2 world, b2Vec2 size) {
	return CoordWorldToPixels(world.x, world.y, size.x, size.y);
}

b2Vec2 Convert::CoordWorldToPixels(float x, float y, float width, float height) {
	float pixel_x = WORLD_TO_PIXELS * (x + (width / 2));
	float pixel_y = WORLD_TO_PIXELS * (y + (height / 2));
	return b2Vec2(pixel_x, pixel_y);
}

b2Vec2 Convert::CoordPixelsToWorld(b2Vec2 pixels, b2Vec2 size) {
	return CoordPixelsToWorld(pixels.x, pixels.y, size.x, size.y);
}

b2Vec2 Convert::CoordPixelsToWorld(float x, float y, float width, float height) {
	float world_x = PIXELS_TO_WORLD * (x - (width / 2));
	float world_y = PIXELS_TO_WORLD * (y - (height / 2));
	return b2Vec2(world_x, world_y);
}