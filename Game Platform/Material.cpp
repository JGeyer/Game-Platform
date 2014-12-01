#include "Material.h"

Material::Material() : Consumable() {
	shape = b2PolygonShape();
	type = ConsumableData::consumable_type::MATERIAL;
	mat_type = MaterialData::material_type::NONE;
}

void Material::Initialize(b2World& world, b2BodyType type, b2Vec2 position, b2Vec2 size, MaterialData::material_type mat_type) {
	bodyDef.position = position;
	bodyDef.type = type;
	body = world.CreateBody(&bodyDef);
	shape.SetAsBox((size.x / 2) / 30.0f, (size.y / 2) / 30.0f);
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
	this->mat_type = mat_type; 

	b2Fixture* objectSensorFixture = body->CreateFixture(&fixtureDef);
	ContactUserData* cud = new ContactUserData();
	cud->type = ContactUserData::Type::MATERIAL;
	cud->data = this;
	objectSensorFixture->SetUserData(cud);
}