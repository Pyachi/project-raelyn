#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "src/network/connection.h"
#include "src/ai/playertype.h"

Player::Player(PlayerType type, const QPointF& spawn, const QString& user)
		: Entity(PlayerInfo::getTexture(type), spawn),
			type(type),
			user(user),
			firing(false),
			focus(false),
			level(1),
			power(0),
			online(false),
			hitbox() {
	Game::addEntity(this);
}

bool Player::isHit() {
	if (hitbox.getCollisions<Enemy>().size() > 0)
		return true;
	else
		foreach(Bullet * bullet, hitbox.getCollisions<Bullet>()) {
			if (dynamic_cast<Enemy*>(bullet->owner))
				return true;
		}
	return false;
}

void Player::tick() {
	if (online)
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

	if (firing)
		PlayerInfo::getShootingPattern(type, level, focus)(this);

	int dx = 0, dy = 0;
	int speed =
			focus ? PlayerInfo::getFocusSpeed(type) : PlayerInfo::getSpeed(type);
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
		Connection::sendPacket(Packet(PACKETPLAYINUPDATEPLAYER,
																	QStringList() << QString::number(pos().x())
																								<< QString::number(pos().y())));
	}

	if (power >= 100) {
		level++;
		if (level == 3)
			level = 2;
		power = 0;
	}

	if (isHit()) {
		Connection::sendPacket(PACKETPLAYINPLAYERDEATH);
		deleteLater();
		hitbox.scene()->removeItem(&hitbox);
	}
}

void Player::setOnline() { online = true; }
