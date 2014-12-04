#pragma once

#include "Entity.h"
#include "MaterialData.h"
#include "PlayerInfo.h"

class Player : public Entity {
	public:
		Player();
		void Initialize(b2World& world, b2Vec2 position);
		void Update();
		void UpdatePassives();

		void SetLeftPressed(bool state);
		void SetRightPressed(bool state);

		void Move(Cell::Direction direction);
		void StopMove();
		void Jump();

		PlayerInfo GetPlayerInfo();
		void Knockback(b2Vec2 otherPosition);
		void SetMovementSpeed(float speed);
		void SetJumpSpeed(float speed);

		void IncrementFootContacts();
		void DecrementFootContacts();

		void IncrementHealth(int value);
		void DecrementHealth(int value);

		void AddResource(MaterialData::material_type material_type, int value);
		
	private:
		bool leftPressed, leftHeld, rightPressed, rightHeld;
		int hasControl, hasImmunity;
		b2PolygonShape shape;
		PlayerInfo cPlayerInfo;
};