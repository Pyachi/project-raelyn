#include "entityplayer.h"
#include "collectable.h"
#include "connection.h"
#include "entityboss.h"
#include "entitybullet.h"
#include "entityenemy.h"
#include "game.h"
#include "packet.h"
#include "sfx.h"
#include "user.h"

EntityPlayer::EntityPlayer(const Character& character,
                           const String& user,
                           const UID& id,
                           EntityType type)
    : Entity(type, character.tex, id),
      hitbox(Texture::HITBOX, this),
      character(character),
      focus(false),
			level(1),
			invFrames(0),
      display(QString::fromStdString(user), this),
			name(user),
			firing(false) {
	setPos({0.5, 0.5});
  hitbox.setOffset(-hitbox.boundingRect().center());
  setRotation(180);
  if (type == PLAYER)
    display.hide();
	else {
		setOpacity(0.25);
		hitbox.hide();
	}
  display.setBrush(Qt::white);
  display.setRotation(180);
  display.setPos({display.boundingRect().center().x(), -40});
}

void EntityPlayer::tick(void) {
  age++;
	if (invFrames != 0) {
		int flashTime = invFrames < 40 ? 5 : 10;
		if (cycle(flashTime, 1))
			setOpacity(0);
		else if (cycle(flashTime, flashTime / 2))
			setOpacity(type == ONLINEPLAYER ? 0.25 : 1);
		invFrames--;
		if (invFrames == 0)
			setOpacity(type == ONLINEPLAYER ? 0.25 : 1);
	}
  if (type != PLAYER)
    return;
  QSet<int> keys = Game::getKeys();

	firing = keys.contains(User::getControls().getKeyShoot());
	focus = keys.contains(User::getControls().getKeyFocus());

  if (focus)
    hitbox.setOpacity(1);
  else
    hitbox.setOpacity(0);

  if (firing) {
    fireBullets(character.pattern(this));
    character.shootSound(this).play(3);
    Connection::sendPacket(
				{PACKETPLAYINFIREBULLETS, QStringList() << QString::number(focus)});
  }

  int dx = 0, dy = 0;
  int speed = focus ? character.focusSpeed : character.speed;
	if (keys.contains(User::getControls().getKeyRight()))
    dx += speed;
	if (keys.contains(User::getControls().getKeyLeft()))
		dx -= speed;
	if (keys.contains(User::getControls().getKeyDown()))
    dy += speed;
	if (keys.contains(User::getControls().getKeyUp()))
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

  if (invFrames == 0) {
    bool hit = false;
    for (QGraphicsItem* entity : hitbox.collidingItems()) {
      if (dynamic_cast<EntityEnemy*>(entity) ||
          dynamic_cast<EntityBoss*>(entity)) {
        hit = true;
        break;
      }
      if (EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity))
        if (bullet->ownerType == ENEMY || bullet->ownerType == BULLET) {
          hit = true;
          break;
        }
		}
    if (hit) {
			Game::takeDamage();
      level = 1;
			invFrames = 150;
    }
	}
}
