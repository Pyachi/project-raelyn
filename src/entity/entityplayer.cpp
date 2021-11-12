#include "entityplayer.h"
#include "Framework"
#include "Network"
#include "Entity"

EntityPlayer::EntityPlayer(PlayerType playerType,
													 const QString& user,
													 UID id,
													 EntityType type)
		: Entity(type, Players::getTexture(playerType), id),
			playerType(playerType),
			name(user),
			firing(false),
			focus(false),
			level(1),
			power(0) {
	Game::addEntity(this);
	setRotation(180);
}

void EntityPlayer::tick(void) {
	age++;
	if (type != PLAYER)
		return;
	QSet<int> keys = Game::getKeys();

	firing = keys.contains(User::getKeyShoot());
	focus = keys.contains(User::getKeyFocus());

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
	if (keys.contains(User::getKeyRight()))
		dx += speed;
	if (keys.contains(User::getKeyLeft()))
		dx -= speed;
	if (keys.contains(User::getKeyDown()))
		dy += speed;
	if (keys.contains(User::getKeyUp()))
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

	List<EntityBullet*> bullets;
	for (Entity* entity : hitbox.getCollisions(BULLET)) {
		EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
		if (bullet->ownerType == ENEMY)
			bullets.push_back(bullet);
	}

	//  if (!bullets.empty()) {
	//    Connection::sendPacket(PACKETPLAYINPLAYERDEATH);
	//    deleteLater();
	//    hitbox.scene()->removeItem(&hitbox);
	//  }
}

EntityBullet* EntityPlayer::fireBullet(BulletInfo info,
																			 BulletAI ai,
																			 Texture texture,
																			 double rot,
																			 const QPointF& loc,
																			 int scale,
																			 int damage) {
	EntityBullet* bullet =
			Entity::fireBullet(info, ai, texture, rot, loc, scale, damage);
	bullet->setOpacity(0.25);
	if (type == ONLINEPLAYER)
		bullet->damage = 0;
	return bullet;
}
