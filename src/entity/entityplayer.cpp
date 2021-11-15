#include "entityplayer.h"
#include "connection.h"
#include "entitybullet.h"
#include "game.h"
#include "packet.h"
#include "sfx.h"
#include "user.h"

EntityPlayer::EntityPlayer(const Character& character,
                           const QString& user,
                           const UID& id,
                           EntityType type)
    : Entity(type, character.tex, id),
      hitbox(Texture::HITBOX, this),
      character(character),
      display(user, this),
      name(user),
      firing(false),
      focus(false),
      level(1),
      power(0),
      points(0),
      health(3),
      invFrames(0) {
  hitbox.setOffset(-hitbox.boundingRect().center());
  setRotation(180);
  if (type == PLAYER)
    display.hide();
  display.setBrush(Qt::white);
  display.setRotation(180);
  display.setPos({display.boundingRect().center().x(), -40});
}

void EntityPlayer::tick(void) {
  age++;
  if (type != PLAYER)
    return;
  QSet<int> keys = Game::getKeys();

  firing = keys.contains(User::getKeyShoot());
  focus = keys.contains(User::getKeyFocus());

  if (focus)
    hitbox.setOpacity(1);
  else
    hitbox.setOpacity(0);

  if (firing) {
    fireBullets(character.pattern(this));
		character.shootSound(this).play();
    Connection::sendPacket(
				{PACKETPLAYINFIREBULLETS, QStringList() << QString::number(level)
																								<< QString::number(focus)});
  }

  int dx = 0, dy = 0;
  int speed = focus ? character.focusSpeed : character.speed;
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

  if (power >= 100 && level != 4) {
    SFX::POWERUP1.play();
    level++;
    if (level != 4)
      power = 0;
  }

  if (invFrames == 0) {
    bool hit = false;
    for (QGraphicsItem* entity : hitbox.collidingItems()) {
      if (EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity))
        if (bullet->ownerType == ENEMY || bullet->ownerType == BULLET)
          hit = true;
    }

    if (hit) {
      health--;
      if (health == 0) {
        SFX::EXPL_SUPERHEAVY1.play();
        Connection::sendPacket(PACKETPLAYINPLAYERDEATH);
        deleteLater();
      } else {
        invFrames = 100;
        SFX::HIT1.play();
      }
    }
  } else {
    int flashTime = invFrames < 40 ? 5 : 10;
    if (cycle(flashTime, 1))
      setOpacity(0);
    else if (cycle(flashTime, flashTime / 2))
      setOpacity(1);
    invFrames--;
    if (invFrames == 0)
      setOpacity(1);
  }
}
