#include "player.h"
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "playerhitbox.h"

Player::Player(Game* game, const PlayerInfo& stats, const QPointF& spawn)
		: AIEntity<Player>(
					game,
					stats.texture,
					[](Player* player) {
						QSet<int> keys = player->game->getKeys();

						player->firing = keys.contains(Qt::Key_Z);
						player->focus = keys.contains(Qt::Key_Shift);

						player->hitbox->setVisible(player->focus);

						if (player->firing)
							player->firingPattern(player);

						int dx = 0, dy = 0;
						int speed =
								player->focus ? player->focusSpeed : player->normalSpeed;
						if (keys.contains(Qt::Key_Right))
							dx += speed;
						if (keys.contains(Qt::Key_Left))
							dx -= speed;
						if (keys.contains(Qt::Key_Down))
							dy += speed;
						if (keys.contains(Qt::Key_Up))
							dy -= speed;
						if (dx != 0 && dy != 0) {
							dx /= sqrt(2);
							dy /= sqrt(2);
						}
						player->setPos(
								player->confineToPlayableArea(player->pos() + QPointF(dx, dy)));

						if (player->isHit()) {
							player->cleanup = true;
							player->hitbox->cleanup = true;
						}
					},
					spawn),
			firing(false),
			focus(false),
			level(1),
			normalSpeed(stats.normalSpeed),
			focusSpeed(stats.focusSpeed),
			firingPattern(stats.firingPattern),
			hitbox(new PlayerHitbox(game, this)) {}

bool Player::isHit() {
	foreach (BaseEntity* entity, hitbox->getCollisions()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Enemy*>(bullet->owner))
				return true;
		if (dynamic_cast<Enemy*>(entity))
			return true;
	}
	return false;
}

void Player::tick() {
	timeAlive++;
	ai(this);
}
