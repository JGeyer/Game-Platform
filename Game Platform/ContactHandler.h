#include "ElementsInclude.h"

class ContactHandler {
	public:
		ContactHandler() {};
		void PlayerContactedSurface(ContactUserData* playerData) {
			Player* player = static_cast<Player*>(playerData->data);
			player->IncrementFootContacts();
		}

		void PlayerLeftSurface(ContactUserData* playerData) {
			Player* player = static_cast<Player*>(playerData->data);
			player->DecrementFootContacts();
		}

		void PlayerContactedMaterial(ContactUserData* playerData, ContactUserData* materialData) {
			Material* material = static_cast<Material*>(materialData->data);
			material->SetIsDead(true);
			Player* player = static_cast<Player*>(playerData->data);
			if (material->mat_type == MaterialData::material_type::COPPER) {
				player->addResource(MaterialData::material_type::COPPER, 1);
			}
			if (material->mat_type == MaterialData::material_type::IRON) {
				player->addResource(MaterialData::material_type::IRON, 1);
			}
			if (material->mat_type == MaterialData::material_type::CARBON) {
				player->addResource(MaterialData::material_type::CARBON, 1);
			}
			if (material->mat_type == MaterialData::material_type::ZINC) {
				player->addResource(MaterialData::material_type::ZINC, 1);
			}
		}

		void PlayerContactedEnemy(ContactUserData* playerData, ContactUserData* enemyData) {
			Player* player = static_cast<Player*>(playerData->data);
			Enemy* enemy = static_cast<Enemy*>(enemyData->data);

			int damage = enemy->getEnemyInfo().damage;
			player->DecrementHealth(damage);
			player->Knockback(enemy->GetBody()->GetPosition());
		}
};