#pragma once

#include "Entity.h"
#include "MaterialData.h"
#include "PlayerInfo.h"

class Player : public Entity {
	public:
		Player();
		void Initialize(b2World& world, b2Vec2 position);
		void Update(sf::Event event);
		void UpdatePassive();
		void Move(Entity::Direction direction);
		void StopMove();
		void Jump();

		PlayerInfo getPlayerInfo();
		void Knockback(b2Vec2 otherPosition);
		void setMovementSpeed(float speed);
		void setJumpSpeed(float speed);

		void IncrementFootContacts();
		void DecrementFootContacts();

		void IncrementHealth(int value);
		void DecrementHealth(int value);

		void AddResource(MaterialData::material_type material_type, int value);
		
	private:
		int hasControl, hasImmunity;
		b2PolygonShape shape;
		PlayerInfo cPlayerInfo;
};