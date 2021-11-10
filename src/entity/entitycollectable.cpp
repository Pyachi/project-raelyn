#include "entitycollectable.h"
#include <QDebug>
#include <QtMath>
#include "entitybullet.h"
#include "entityenemy.h"
#include "entityplayer.h"
#include "src/ai/collectable.h"
#include "src/framework/game.h"
#include "src/network/user.h"

EntityCollectable::EntityCollectable(Tex tex, AI<EntityPlayer> ai)
		: Entity(COLLECTABLE, tex), ai(ai) {
	Game::addEntity(this);
}

void EntityCollectable::tick(void) {
	age++;
	int dir = Random::getInt() % 360;
	if (getAge() < 10)
		moveBy(20 * -sin(dir), 20 * cos(dir));
	else {
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
