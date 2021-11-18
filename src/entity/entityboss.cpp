#include "entityboss.h"
#include <QPainter>
#include "collectable.h"
#include "connection.h"
#include "entity.h"
#include "entitybullet.h"
#include "packet.h"
#include "sfx.h"

EntityBoss::EntityBoss(const Texture& tex,
                       const UID& id,
                       const Array<int>& health,
                       const AI<EntityBoss>& ai)
    : Entity(ENEMY, tex, id),
      health(health[0]),
      phase(0),
      totalHealth(health),
			ai(ai),
			healthBarDisplay(this) {
	healthBar.setFormat("");
	healthBar.setRange(0, health[0]);
	healthBar.setValue(health[0]);
	healthBar.setAttribute(Qt::WA_TranslucentBackground);
	healthBarDisplay.setWidget(&healthBar);
	healthBarDisplay.adjustSize();
	healthBarDisplay.setPos(-healthBarDisplay.boundingRect().center());
}

void EntityBoss::tick(void) {
  age++;
  ai(this);
  handleMovement();
	if (invFrames != 0) {
		int flashTime = invFrames < 40 ? 5 : 10;
		if (cycle(flashTime, 1))
			setOpacity(0);
		else if (cycle(flashTime, flashTime / 2))
			setOpacity(type == ONLINEPLAYER ? 0.25 : 1);
		invFrames--;
		if (invFrames == 0)
			setOpacity(type == ONLINEPLAYER ? 0.25 : 1);
	} else {
		List<EntityBullet*> bullets;
		for (Entity* entity : getCollisions(BULLET)) {
			EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
			if (bullet->collisionCheck &&
					(bullet->ownerType == PLAYER || bullet->ownerType == ONLINEPLAYER))
				bullets.push_back(bullet);
		}
		for (EntityBullet* bullet : bullets) {
			SFX::EXPL_LIGHT2.play(10);
			health -= bullet->damage;
			bullet->deleteLater();
			healthBar.setValue(health);
			if (health <= 0) {
				advancePhase();
				Connection::sendPacket(
						{PACKETPLAYINADVANCEPHASE, QStringList() << id.toString()});
				break;
			}
    }
  }
}

void EntityBoss::kill(void) {
  if (cleanup)
    return;
	for (int i = 0; i < (Random::getInt() % 5) + 50; i++)
		Collectable::POWER.spawn(pos(), 200);
	for (int i = 0; i < (Random::getInt() % 20) + 100; i++)
		Collectable::POINTS.spawn(pos(), 200);
  Connection::sendPacket(PACKETPLAYINRESUMELEVEL);
  deleteLater();
}

void EntityBoss::advancePhase() {
  phase++;
  for (Entity* entity : getNearbyEntities(BULLET, 1000000)) {
    EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
    if (bullet->ownerType == BULLET || bullet->ownerType == ENEMY) {
			Collectable::POINTS.spawn(bullet->pos(), 0, 0);
      bullet->deleteLater();
    }
  }
  if (phase == totalHealth.size()) {
    kill();
    return;
  } else {
    health = totalHealth[phase];
		healthBar.setMaximum(health);
		healthBar.setValue(health);
    age = 0;
		invFrames = 200;
		for (int i = 0; i < (Random::getInt() % 15) + 15; i++)
			Collectable::POWER.spawn(pos(), 100);
		for (int i = 0; i < (Random::getInt() % 30) + 20; i++)
			Collectable::POINTS.spawn(pos(), 100);
		if (Random::getInt(5) == 0)
			Collectable::HEALTH.spawn(pos());
		else if (Random::getInt(3) == 0)
			Collectable::BOMB.spawn(pos());
  }
}

EntityBoss::~EntityBoss() {
	healthBarDisplay.setWidget(nullptr);
	healthBar.deleteLater();
}

ProgressBar::ProgressBar() : QProgressBar() {
	setMinimumSize({128, 128});
}

void ProgressBar::paintEvent(QPaintEvent*) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
	QPen pen(QColor(255, 255, 255, 200));
	pen.setWidth(3);
	painter.setPen(pen);
	painter.drawArc(5, 5, 118, 118, 1440,
									static_cast<int>((static_cast<double>(value()) /
																		static_cast<double>(maximum())) *
																	 5760.0));
	pen.setColor(Qt::darkRed);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.drawArc(3, 3, 122, 122, 0, 5760);
	painter.drawArc(7, 7, 114, 114, 0, 5760);
	update();
}
