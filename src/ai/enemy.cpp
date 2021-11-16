#include "enemy.h"
#include "entityenemy.h"
#include "entityplayer.h"
#include "game.h"
#include "sfx.h"
#include "texture.h"
Array<Ref<Enemy> > Enemy::list;

EntityEnemy* Enemy::spawn(const QPointF& loc, const UID& id) const {
  EntityEnemy* enemy = new EntityEnemy(tex, id, health, ai);
  enemy->setPos(loc);
  return enemy;
}

const Enemy Enemy::ENEMYTEST1(Texture::ENEMYTEMP, 50, [](EntityEnemy* enemy) {
  if (enemy->cycle(200, 50))
    enemy->moveTo({150, -300}, 50, QUICK);
  else if (enemy->cycle(200, 150))
    enemy->moveTo({-150, -300}, 50);
});
const Enemy Enemy::ENEMYTEST2(Texture::ENEMYTEMP, 100, [](EntityEnemy* enemy) {
  if (enemy->getAge() < 60)

    enemy->moveBy(0, 1);
  if (enemy->getAge() == 60)
    enemy->deleteLater();
});
const Enemy Enemy::SIMPLESHOTGUN_TOP_LEFT(Texture::ENEMYTEMP,
                                          5,
                                          [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 150))
    enemy->moveBy(2, .85);
  else if (enemy->cycle(1800, 181, 240))
    enemy->moveBy(1, 0);
  else if (enemy->cycle(1800, 271, 800))
    enemy->moveBy(0, -1);

  if (enemy->getAge() == 180) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC2, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 270) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC2, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 930)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SIMPLESHOTGUN_TOP_RIGHT(Texture::ENEMYTEMP,
                                           15,
                                           [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 150))
    enemy->moveBy(-2, .85);
  else if (enemy->cycle(1800, 181, 240))
    enemy->moveBy(-1, 0);
  else if (enemy->cycle(1800, 271, 800))
    enemy->moveBy(0, -1);

  if (enemy->getAge() == 180) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC2, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 270) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC2, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 930)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::TANKYBANG_UP_DOWN(Texture::ENEMYTEMP,
                                     100,
                                     [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 175))
    enemy->moveBy(0, 1.5);
  if (enemy->cycle(1800, 176, 350))
    enemy->moveBy(0, -.8);
  if (enemy->cycle(1800, 351, 525))
    enemy->moveBy(0, .8);
  if (enemy->cycle(1800, 526, 700))
    enemy->moveBy(0, -.8);
  if (enemy->cycle(1800, 701, 875))
    enemy->moveBy(0, .8);
  if (enemy->cycle(1800, 876, 1050))
    enemy->moveBy(0, -.8);
  if (enemy->cycle(1800, 1051, 1800))
    enemy->moveBy(0, -3);

  if (enemy->cycle(350, 175)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN5), 90);
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC10, Texture::ROUNDAQUA, Pattern::SHOTGUN5), 90);
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC12, Texture::ROUNDAQUA, Pattern::SHOTGUN5), 90);
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN5), 270);
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC10, Texture::ROUNDAQUA, Pattern::SHOTGUN5),
        270);
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC12, Texture::ROUNDAQUA, Pattern::SHOTGUN5),
        270);
    SFX::EXPL_MED2.play(25);
  }
  if (enemy->getAge() == 1900)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SIMPLESHOTGUN_MID_LEFT_UP(Texture::ENEMYTEMP,
                                             55,
                                             [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 120))
    enemy->moveBy(5, 0);
  if (enemy->cycle(1800, 160, 240))
    enemy->moveBy(0, -2);
  if (enemy->cycle(1800, 280, 900))
    enemy->moveBy(-2.75, -2.75);

  if (enemy->getAge() == 155) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 275) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN5));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 900)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SIMPLESHOTGUN_MID_RIGHT_UP(Texture::ENEMYTEMP,
                                              55,
                                              [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 120))
    enemy->moveBy(-5, 0);
  if (enemy->cycle(1800, 160, 240))
    enemy->moveBy(0, -2);
  if (enemy->cycle(1800, 280, 900))
    enemy->moveBy(2.75, -2.75);

  if (enemy->getAge() == 155) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
    SFX::EXPL_LIGHT1.play(25);
  }
  if (enemy->getAge() == 275) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN5));
    SFX::EXPL_LIGHT1.play(25);
  }

  if (enemy->getAge() == 900)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::WAVE1BASIC(Texture::ENEMYTEMP, 25, [](EntityEnemy* enemy) {
  if (enemy->cycle(240, 0, 100))
    enemy->moveBy(1, 2);
  else if (enemy->cycle(240, 140, 240))
    enemy->moveBy(1, -2);
  if (enemy->getAge() == 240)
    enemy->deleteLater();
  if (enemy->getAge() == 120)
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC8, Texture::ROUNDAQUA, Pattern::SHOTGUN3));
});
const Enemy Enemy::DIVER(Texture::ENEMYTEMP, 40, [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 900))
    enemy->moveBy(-0.75, 0);

  if (enemy->cycle(50)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC1, Texture::ROUNDRED, Pattern::CIRCLE16));
  }

  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::LARGE_SLOW_LEFTTORIGHT(Texture::ENEMYTEMP,
                                          80,
                                          [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 900))
    enemy->moveBy(-0.75, 0);

  if (enemy->cycle(150)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC5, Texture::ROUNDRED, SpawnInfo(), 6));
    SFX::MISSILE2.play(25);
  }
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::LARGE_SLOW_RIGHTTOLEFT(Texture::ENEMYTEMP,
                                          80,
                                          [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 900))
    enemy->moveBy(0.75, 0);

  if (enemy->cycle(150)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC5, Texture::ROUNDRED, SpawnInfo(), 6));
    SFX::MISSILE2.play(25);
  }
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SMALL_FAST_RIGHTTOLEFT(Texture::ENEMYTEMP,
                                          80,
                                          [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 900))
    enemy->moveBy(3, 0);

  if (enemy->cycle(50)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC5, Texture::ELLIPSERED, Pattern::CIRCLE6));
    SFX::EXPL_LIGHT3.play(25);
  }
  if (enemy->getAge() == 200)  // 3.75 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SMALL_FAST_LEFTTORIGHT(Texture::ENEMYTEMP,
                                          80,
                                          [](EntityEnemy* enemy) {
  if (enemy->cycle(1800, 1, 900))
    enemy->moveBy(-3, 0);

  if (enemy->cycle(50)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC5, Texture::ELLIPSERED, Pattern::CIRCLE6));
    SFX::EXPL_LIGHT3.play(25);
  }
  if (enemy->getAge() == 200)  // 3.75 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SMALL_FAST_TOPDOWNTOLEFT(Texture::ENEMYTEMP,
                                            80,
                                            [](EntityEnemy* enemy) {
  if (enemy->cycle(900, 1, 450))
    enemy->moveBy(0, 3);
  if (enemy->cycle(900, 451, 900))
    enemy->moveBy(-3, 0);

  if (enemy->cycle(1))
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC5, Texture::ELLIPSERED, Pattern::CIRCLE8));
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
});
const Enemy Enemy::SMALL_FAST_TOPDOWNTORIGHT(Texture::ENEMYTEMP,
                                             80,
                                             [](EntityEnemy* enemy) {
  if (enemy->cycle(900, 1, 450))
    enemy->moveBy(0, 3);
  if (enemy->cycle(1800, 901, 1700))
    enemy->moveBy(3, 0);
  if (enemy->cycle(1))
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC4, Texture::ELLIPSERED, Pattern::CIRCLE8));
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
});

const Enemy Enemy::DART1(Texture::ENEMYTEMP, 80, [](EntityEnemy* enemy) {
  if (enemy->cycle(500, 10) || enemy->cycle(1000, 100))
    enemy->moveTo({0, 50}, 50, QUICK);
  if (enemy->cycle(500, 110) || enemy->cycle(1000, 410))
    enemy->moveTo({0, -150}, 50, QUICK);
  if (enemy->cycle(1000, 210) || enemy->cycle(1000, 610))
    enemy->moveTo({0, -50}, 50, QUICK);
  if (enemy->cycle(1000, 310))
    enemy->moveTo({0, -500}, 50, SMOOTH);

  if (enemy->getAge() == 360)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(500, 110) || enemy->cycle(500, 210) ||
      enemy->cycle(500, 310)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC10, Texture::ELLIPSEORANGE, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC6,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::DART2(Texture::ENEMYTEMP, 80, [](EntityEnemy* enemy) {
  if (enemy->cycle(500, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({75, -200}, 75, QUICK);
  if (enemy->cycle(500, 110))
    enemy->moveTo({-200, -215}, 75, QUICK);
  if (enemy->cycle(500, 210))
    enemy->moveTo({-50, -150}, 75, QUICK);
  if (enemy->cycle(500, 310))
    enemy->moveTo({-500, 0}, 50, SMOOTH);

  if (enemy->getAge() == 360)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(500, 110) || enemy->cycle(500, 210) ||
      enemy->cycle(500, 310)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC10, Texture::ELLIPSEORANGE, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC6,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::DART3(Texture::ENEMYTEMP, 80, [](EntityEnemy* enemy) {
  if (enemy->cycle(500, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({-75, -200}, 100, QUICK);
  if (enemy->cycle(500, 110))
    enemy->moveTo({75, -200}, 75, QUICK);
  if (enemy->cycle(500, 210))
    enemy->moveTo({50, -150}, 100, QUICK);
  if (enemy->cycle(500, 310))
    enemy->moveTo({500, 0}, 50, SMOOTH);

  if (enemy->getAge() == 360)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(500, 110) || enemy->cycle(500, 210) ||
      enemy->cycle(500, 310)) {
    enemy->fireBullets(
        BulletInfo(Bullet::BASIC10, Texture::ELLIPSEORANGE, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC6,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::DART4(Texture::ENEMYTEMP, 50, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 310) ||
      enemy->cycle(1000, 610))
    enemy->moveTo({-100, -100}, 100, QUICK);
  if (enemy->cycle(1000, 110) || enemy->cycle(1000, 410) ||
      enemy->cycle(1000, 710))
    enemy->moveTo({0, -200}, 75, QUICK);
  if (enemy->cycle(1000, 210) || enemy->cycle(1000, 510) ||
      enemy->cycle(1000, 810))
    enemy->moveTo({100, -100}, 100, QUICK);

  if (enemy->cycle(1000, 910))
    enemy->moveTo({500, 0}, 50, SMOOTH);

  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(100)) {

    enemy->fireBullets(
        BulletInfo(Bullet::BASIC7, Texture::ELLIPSERED, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC4,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::DART5(Texture::ENEMYTEMP, 50, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 310) ||
      enemy->cycle(1000, 610))
    enemy->moveTo({100, -100}, 100, QUICK);
  if (enemy->cycle(1000, 110) || enemy->cycle(1000, 410) ||
      enemy->cycle(1000, 710))
    enemy->moveTo({-100, -100}, 75, QUICK);
  if (enemy->cycle(1000, 210) || enemy->cycle(1000, 510) ||
      enemy->cycle(1000, 810))
    enemy->moveTo({0, -200}, 100, QUICK);
  if (enemy->cycle(1000, 910))
    enemy->moveTo({-500, 0}, 50, SMOOTH);

  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(100)) {

    enemy->fireBullets(
        BulletInfo(Bullet::BASIC7, Texture::ELLIPSERED, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC4,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::DART6(Texture::ENEMYTEMP, 50, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 310) ||
      enemy->cycle(1000, 610))
    enemy->moveTo({0, -200}, 100, QUICK);
  if (enemy->cycle(1000, 110) || enemy->cycle(1000, 410) ||
      enemy->cycle(1000, 710))
    enemy->moveTo({100, -100}, 75, QUICK);
  if (enemy->cycle(1000, 210) || enemy->cycle(1000, 510) ||
      enemy->cycle(1000, 810))
    enemy->moveTo({-100, -100}, 100, QUICK);

  if (enemy->cycle(1000, 910))
    enemy->moveTo({500, 0}, 50, SMOOTH);

  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();

  if (enemy->cycle(100)) {

    enemy->fireBullets(
        BulletInfo(Bullet::BASIC7, Texture::ELLIPSERED, SpawnInfo(), 2)
            << BulletInfo(Bullet::BASIC4,
                          Texture::ELLIPSEORANGE,
                          SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10),
                          2),
        enemy->getDirectionOfEntity(Game::getPlayer()));
  }
});

const Enemy Enemy::SUNEASY(Texture::ENEMYTEMP, 100, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({0, -100}, 100, QUICK);
  if (enemy->cycle(1000, 850))
    enemy->moveTo({0, -500}, 50, SMOOTH);
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();

  {
    if (enemy->cycle(100)) {
      enemy->fireBullets(
          BulletInfo(Bullet::BASIC1, Texture::ARROWYELLOW, Pattern::CIRCLE16));
      SFX::EXPL_LIGHT3.play(25);
    }
  }
});
const Enemy Enemy::WHEEL(Texture::ENEMYTEMP, 200, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({0, -100}, 100, QUICK);
  {
    if (enemy->cycle(5)) {
      enemy->fireBullets(
          BulletInfo(Bullet::BASIC3, Texture::ELLIPSERED, Pattern::CIRCLE8),
          enemy->getDirectionOfEntity(Game::getPlayer()));
      SFX::EXPL_LIGHT3.play(25);
    }
  }
});

const Enemy Enemy::SUN(Texture::ENEMYTEMP, 100, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({0, -100}, 100, QUICK);
  {
    if (enemy->cycle(10)) {
      enemy->fireBullets(
          BulletInfo(Bullet::BASIC5, Texture::ARROWYELLOW, Pattern::CIRCLE16));
      SFX::EXPL_LIGHT3.play(25);
    }
  }
});

const Enemy Enemy::WHEELEASY(Texture::ENEMYTEMP, 200, [](EntityEnemy* enemy) {

  if (enemy->cycle(1000, 10) || enemy->cycle(1000, 510))
    enemy->moveTo({0, -100}, 35, QUICK);
  if (enemy->cycle(1000, 850))
    enemy->moveTo({0, -500}, 50, SMOOTH);
  if (enemy->getAge() == 1000)  // 15 seconds plus off screen
    enemy->deleteLater();
  {
    if (enemy->cycle(35)) {
      enemy->fireBullets(
          BulletInfo(Bullet::BASIC3, Texture::ELLIPSERED, Pattern::CIRCLE8),
          enemy->getDirectionOfEntity(Game::getPlayer()));
      SFX::EXPL_LIGHT3.play(25);
    }
  }
});
