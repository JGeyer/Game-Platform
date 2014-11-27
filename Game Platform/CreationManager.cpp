#include "CreationManager.h"

CreationManager &CreationManager::Instance() {
	static CreationManager instance;
	return instance;
}

void CreationManager::LoadContent(char* lfFilename, b2World &world) {
	std::vector<std::vector<std::string>> attributes, contents, textures, songs;
	std::string texturePath, musicPath;

	// Load Attributes and Contents
	FileManager::Instance().LoadContent(lfFilename, attributes, contents);
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i][0] == "path") {
			if (attributes[i][1] == "texture") {
				texturePath = contents[i][0];
			}
			else {
				musicPath = contents[i][0];
			}
		}
		if (attributes[i][0] == "texture") {
			textures.push_back(contents[i]);
		}
		if (attributes[i][0] == "music") {
			songs.push_back(contents[i]);
		}
		if (attributes[i][0] == "object") {
			objectLibrary.push_back(contents[i]);
		}
		if (attributes[i][0] == "consumable") {
			consumableLibrary.push_back(contents[i]);
		}
		if (attributes[i][0] == "entity") {
			entityLibrary.push_back(contents[i]);
		}
	}

	// Setup Texture Library
	TextureManager::Instance().LoadContent(texturePath, textures);

	// Setup Music Library
	MusicManager::Instance().LoadContent(musicPath, songs);

	attributes.clear();
	contents.clear();
	textures.clear();
	songs.clear();
}

void CreationManager::UnloadContent() {
	FileManager::Instance().UnloadContent();
	TextureManager::Instance().UnloadContent();
	MusicManager::Instance().UnloadContent();
	objectLibrary.clear();
	consumableLibrary.clear();
	entityLibrary.clear();
}

std::string CreationManager::GetSong(std::string id) {
	return MusicManager::Instance().getMusicPath(id);
}

std::vector<Object*> CreationManager::GetObjects(b2World &world) {
	std::vector<Object*> levelObjects;
	for (std::vector<std::vector<std::string>>::iterator it = objectLibrary.begin(); it != objectLibrary.end(); ++it) {
		Object* currentObject = CreateObject(world, (*it));
		levelObjects.push_back(currentObject);
	}
	return levelObjects;
}

std::vector<Consumable*> CreationManager::GetConsumables(b2World &world) {
	std::vector<Consumable*> levelConsumables;
	for (std::vector<std::vector<std::string>>::iterator it = consumableLibrary.begin(); it != consumableLibrary.end(); ++it) {
		Consumable* currentConsumable = CreateConsumable(world, (*it));
		levelConsumables.push_back(currentConsumable);
	}
	return levelConsumables;
}

std::vector<Entity*> CreationManager::GetEntities(b2World &world) {
	std::vector<Entity*> levelEntities;
	for (std::vector<std::vector<std::string>>::iterator it = entityLibrary.begin(); it != entityLibrary.end(); ++it) {
		Entity* currentEntity = CreateEntity(world, (*it));
		levelEntities.push_back(currentEntity);
	}
	return levelEntities;
}

Object* CreationManager::CreateObject(b2World &world, std::vector<std::string> contents) {
	sf::Texture texture(TextureManager::Instance().getTexture(contents[11]));
	if (contents[1].compare("box") == 0) {
		// Make new box
		Box* box = new Box();
		
		// BodyType static or dynamic? 
		b2BodyType type;
		if (contents[10].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[10].compare("dynamic") == 0
			type = b2_dynamicBody;
		}

		// Create and return box
		box->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f), 
					   b2Vec2(std::stof(contents[4]), std::stof(contents[5])), std::stof(contents[8]), std::stof(contents[9]));
		box->LoadContent(texture, b2Vec2(std::stof(contents[6]), std::stof(contents[7])));
		return box;
	}
	if (contents[1].compare("circle") == 0) {
		// Make new circle
		Circle* circle = new Circle();
		
		// BodyType static or dynamic? 
		b2BodyType type;
		if (contents[9].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[9].compare("dynamic") == 0
			type = b2_dynamicBody;
		}

		// Create and return circle
		circle->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f),
						  std::stof(contents[4]), std::stof(contents[7]), std::stof(contents[8]));
		circle->LoadContent(texture, b2Vec2(std::stof(contents[5]), std::stof(contents[6])));
		return circle;
	}
	//TODO: Proper handle here
	return NULL;
}

Consumable* CreationManager::CreateConsumable(b2World &world, std::vector<std::string> contents) {
	sf::Texture texture(TextureManager::Instance().getTexture(contents[12]));
	if (contents[1].compare("material") == 0) {
		Material* material = new Material();
		b2BodyType type;
		if (contents[11].compare("static") == 0) {
			type = b2_staticBody;
		}
		else { //contents[11].compare("dynamic") == 0
			type = b2_dynamicBody;
		}
		MaterialData::material_type mat_type;
		if (contents[10].compare("copper") == 0) {
			mat_type = MaterialData::material_type::COPPER;
		}
		if (contents[10].compare("iron") == 0) {
			mat_type = MaterialData::material_type::IRON;
		}
		if (contents[10].compare("carbon") == 0) {
			mat_type = MaterialData::material_type::CARBON;
		}
		if (contents[10].compare("zinc") == 0) {
			mat_type = MaterialData::material_type::ZINC;
		}

		material->Initialize(world, type, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f), 
							 b2Vec2(std::stof(contents[4]), std::stof(contents[5])), std::stof(contents[8]),
							 std::stof(contents[9]), mat_type);
		material->LoadContent(texture, b2Vec2(std::stof(contents[6]), std::stof(contents[7])));
		return material;
	}
	//TODO: Proper handle here
	return NULL;
}

Entity* CreationManager::CreateEntity(b2World &world, std::vector<std::string> contents) {
	sf::Texture texture(TextureManager::Instance().getTexture(contents[6]));
	if (contents[1].compare("player") == 0) {
		Player* player = new Player();
		player->Initialize(world, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f));
		player->LoadContent(texture, b2Vec2(std::stof(contents[4]), std::stof(contents[5])));
		return player;
	}
	if (contents[1].compare("grunt") == 0) {
		Enemy* enemy = new Enemy(EnemyInfo::EnemyData::enemy_type::GRUNT, EnemyInfo::EnemyData::enemy_rank::REGULAR);
		enemy->Initialize(world, b2Vec2(std::stof(contents[2]) / 30.0f, std::stof(contents[3]) / 30.0f));
		enemy->LoadContent(texture, b2Vec2(std::stof(contents[4]), std::stof(contents[5])));
		return enemy;
	}
	//TODO: Proper handle here
	return NULL;
}