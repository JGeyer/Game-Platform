#ifndef BOX_H
#define BOX_H

#include "Object.h"

class Box : public Object {
	public:
		Box(InputManager &inputManager);
		~Box();

		void Initialize(b2World& world, b2BodyType type, b2Vec2 position, 
						b2Vec2 size, float density, float friction);

	protected:
		b2PolygonShape shape;
};

#endif