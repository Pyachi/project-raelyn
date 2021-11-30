#include "collectable.h"
#include "entitycollectable.h"
#include "entityplayer.h"
#include "game.h"
#include "sfx.h"
#include "texture.h"
#include "user.h"

EntityCollectable* Collectable::spawn(const QPointF& loc,
																			int maxDis,
																			int force) const {
	EntityCollectable* col = new EntityCollectable(tex, ai, force);
  if (maxDis != 0) {
    double randRot = Random::getInt() % 360;
    double dist = 0;
    for (int i = 0; i < 2; i++)
      dist += (Random::getInt() % maxDis) - (maxDis / 2);
    col->setPos(loc + QPointF(dist * cos(randRot), dist * sin(randRot)));
  } else
    col->setPos(loc);
  return col;
}

const Collectable Collectable::POWER(Texture::POWER, []() {
	Game::gainPower();
  SFX::COLLECT1.play(10);
});

const Collectable Collectable::POINTS(Texture::POINTS, []() {
	User::addScore(200);
	SFX::COLLECT3.play(10);
});

const Collectable Collectable::HEALTH(Texture::HEALTH, []() {
	SFX::POWERUP2.play();
	Game::gainHealth();
});

const Collectable Collectable::BOMB(Texture::BOMB, []() {
	SFX::POWERUP3.play();
	Game::gainBomb();
});
