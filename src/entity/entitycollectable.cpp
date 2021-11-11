#include "entitycollectable.h"
#include <QDebug>
#include <QtMath>
#include "entitybullet.h"
#include "entityenemy.h"
#include "entityplayer.h"
#include "src/ai/collectable.h"
#include "src/framework/game.h"
#include "src/framework/user.h"

EntityCollectable::EntityCollectable(Texture tex, AI<EntityPlayer> ai)
		: Entity(COLLECTABLE, tex), ai(ai) {
	Game::addEntity(this);
}

void EntityCollectable::tick(void) {
	age++;
	if (getAge() == 1) {
		dir = Random::getInt() % 360;
		speed = Random::getInt() % 30;
	} else if (getAge() < 5) {
		moveBy(speed * cos(dir), speed * sin(dir));
	} else {
		EntityPlayer* player = Game::getPlayer();
		if (player->distanceSquared(*this) < 150 * 150 || player->pos().y() < -200)
			moveTowardsPoint(player->pos(), 15);
		else
			moveBy(0, getAge() / 30.0);
		if (!isOnScreen() && pos().y() > 0)
			deleteLater();
		if (collidesWithItem(player)) {
			ai(player);
			deleteLater();
		}
	}
}
