#include "entityinfo.h"

PlayerInfo::PlayerInfo(Texture& texture, EntityAI<Player>& ai)
		: texture(texture), ai(ai) {}

EnemyInfo::EnemyInfo(Texture& texture, EntityAI<Enemy>& ai, int health)
		: texture(texture), ai(ai), health(health) {}

BulletInfo::BulletInfo(Texture& texture, EntityAI<Bullet>& ai, bool boundsCheck)
		: texture(texture), ai(ai), boundsCheck(boundsCheck) {}
