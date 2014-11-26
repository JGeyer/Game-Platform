#pragma once

#include <Box2D\Box2D.h>
#include "ContactHandler.h"

class ContactListener : public b2ContactListener {
	public:
		ContactListener() : contactHandler() {}
		void BeginContact(b2Contact* contact) {
			ContactUserData* fixtureUserData_A = static_cast<ContactUserData*>(contact->GetFixtureA()->GetUserData());
			ContactUserData* fixtureUserData_B = static_cast<ContactUserData*>(contact->GetFixtureB()->GetUserData());

			if (fixtureUserData_A && fixtureUserData_B) {
				//check if foot sensor is fixture A or B
				if (fixtureUserData_A->type == ContactUserData::Type::FOOT_SENSOR) {
					contactHandler.PlayerContactedSurface(fixtureUserData_A);
				}
				if (fixtureUserData_B->type == ContactUserData::Type::FOOT_SENSOR) {
     				contactHandler.PlayerContactedSurface(fixtureUserData_B);
				}
				//check if the player touched a material
				if (fixtureUserData_A->type == ContactUserData::Type::MATERIAL &&
					fixtureUserData_B->type == ContactUserData::Type::PLAYER) {
					contactHandler.PlayerContactedMaterial(fixtureUserData_B, fixtureUserData_A);
				}
				if (fixtureUserData_B->type == ContactUserData::Type::MATERIAL &&
					fixtureUserData_A->type == ContactUserData::Type::PLAYER) {
					contactHandler.PlayerContactedMaterial(fixtureUserData_A, fixtureUserData_B);
				}
				
				//check if the player touched an enemy
				if (fixtureUserData_A->type == ContactUserData::Type::ENEMY &&
					fixtureUserData_B->type == ContactUserData::Type::PLAYER) {
					contactHandler.PlayerContactedEnemy(fixtureUserData_B, fixtureUserData_A);
				}
				if (fixtureUserData_B->type == ContactUserData::Type::ENEMY &&
					fixtureUserData_A->type == ContactUserData::Type::PLAYER) {
					contactHandler.PlayerContactedEnemy(fixtureUserData_A, fixtureUserData_B);
				}
			}
		}
  
		void EndContact(b2Contact* contact) {
			ContactUserData* fixtureUserData_A = static_cast<ContactUserData*>(contact->GetFixtureA()->GetUserData());
			ContactUserData* fixtureUserData_B = static_cast<ContactUserData*>(contact->GetFixtureB()->GetUserData());

			if (fixtureUserData_A && fixtureUserData_B) {
				//check if foot sensor is fixture A or B
				if (fixtureUserData_A->type == ContactUserData::Type::FOOT_SENSOR) {
					contactHandler.PlayerLeftSurface(fixtureUserData_A);
				}
				if (fixtureUserData_B->type == ContactUserData::Type::FOOT_SENSOR) {
					contactHandler.PlayerLeftSurface(fixtureUserData_B);
				}
			}
		}
		ContactHandler contactHandler;
};