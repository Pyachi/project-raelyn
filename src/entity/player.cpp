#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "src/game.h"
#include "src/assets/texture.h"
#include "src/network/connection.h"
#include "src/network/packet.h"
#include <QtMath>

Player::Player(PlayerType playerType,
							 const QString& user,
							 UUID id,
							 EntityType type)
		: Entity(type, Players::getTexture(playerType), id),
			playerType(playerType),
			user(user),
			firing(false),
			focus(false),
			level(1),
			power(0) {
	Game::addEntity(this);
}

void Player::tick() {
	if (type != PLAYER)
		return;
	age++;
	QSet<int> keys = Game::getKeys();

	firing = keys.contains(Qt::Key_Z);
	focus = keys.contains(Qt::Key_Shift);

	if (focus)
		hitbox.setZValue(4);
	else
		hitbox.setZValue(-1);
	hitbox.setPos(pos());

	if (firing) {
		Players::getShootingPattern(playerType, level, focus)(this);
		Connection::sendPacket(
				{PACKETPLAYINFIREBULLETS, QStringList() << QString::number(level)
																								<< QString::number(focus)});
	}

	int dx = 0, dy = 0;
	int speed = focus ? Players::getFocusSpeed(playerType)
										: Players::getSpeed(playerType);
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
	if (dx != 0 || dy != 0) {
		setPos(confineToPlayableArea(pos() + QPointF(dx, dy)));
		Connection::sendPacket({PACKETPLAYINUPDATEPLAYER,
														QStringList() << QString::number(pos().x())
																					<< QString::number(pos().y())});
	}

	if (power >= 100) {
		level++;
		if (level == 3)
			level = 2;
		power = 0;
	}

	List<Bullet*> bullets;
	for (Entity* entity : hitbox.getCollisions(BULLET)) {
		Bullet* bullet = dynamic_cast<Bullet*>(entity);
		if (bullet->ownerType == ENEMY)
			bullets.push_back(bullet);
	}

	//  if (!bullets.empty()) {
	//    Connection::sendPacket(PACKETPLAYINPLAYERDEATH);
	//    deleteLater();
	//    hitbox.scene()->removeItem(&hitbox);
	//  }
}

List<Bullet*> Player::fireBullets(const List<BulletInfo>& pattern,
																	double rot,
																	const QPointF& loc) {
	List<Bullet*> list = Entity::fireBullets(pattern, rot, loc);
	if (type == ONLINEPLAYER)
		for (Bullet* bullet : list) {
			bullet->damage = 0;
		}
	return list;
}
