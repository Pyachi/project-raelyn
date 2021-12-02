#include "bullet.h"
#include "entitybullet.h"
#include "game.h"

const Bullet Bullet::BASIC1([](EntityBullet* bullet) {
  bullet->moveForward(1);
});
const Bullet Bullet::BASIC2([](EntityBullet* bullet) {
  bullet->moveForward(2);
});
const Bullet Bullet::BASIC3([](EntityBullet* bullet) {
  bullet->moveForward(3);
});
const Bullet Bullet::BASIC4([](EntityBullet* bullet) {
  bullet->moveForward(4);
});
const Bullet Bullet::BASIC5([](EntityBullet* bullet) {
  bullet->moveForward(5);
});
const Bullet Bullet::BASIC6([](EntityBullet* bullet) {
  bullet->moveForward(6);
});
const Bullet Bullet::BASIC7([](EntityBullet* bullet) {
  bullet->moveForward(7);
});
const Bullet Bullet::BASIC8([](EntityBullet* bullet) {
  bullet->moveForward(8);
});
const Bullet Bullet::BASIC9([](EntityBullet* bullet) {
  bullet->moveForward(9);
});
const Bullet Bullet::BASIC10([](EntityBullet* bullet) {
  bullet->moveForward(10);
});
const Bullet Bullet::BASIC11([](EntityBullet* bullet) {
  bullet->moveForward(11);
});
const Bullet Bullet::BASIC12([](EntityBullet* bullet) {
  bullet->moveForward(12);
});
const Bullet Bullet::BASIC40([](EntityBullet* bullet) {
	bullet->moveForward(40);
});
const Bullet Bullet::HOMING6([](EntityBullet* bullet) {
	if (bullet->getAge() < 30) {
		double dir = bullet->getDirectionOfEntity(Game::getPlayer());
		dir -= bullet->rotation();
		if (dir == 180 || dir == -180)
			dir = 0;
		while (dir > 180)
			dir -= 360;
		while (dir < -180)
			dir += 360;
		dir = dir > 2 ? 2 : dir < -2 ? -2 : dir;
		bullet->rotate(dir);
	}
	bullet->moveForward(6);
});
const Bullet Bullet::HOMING7([](EntityBullet* bullet) {
	if (bullet->getAge() < 30) {
		double dir = bullet->getDirectionOfEntity(Game::getPlayer());
		dir -= bullet->rotation();
		if (dir == 180 || dir == -180)
			dir = 0;
		while (dir > 180)
			dir -= 360;
		while (dir < -180)
			dir += 360;
		dir = dir > 2 ? 2 : dir < -2 ? -2 : dir;
		bullet->rotate(dir);
	}
	bullet->moveForward(7);
});
const Bullet Bullet::HOMING8([](EntityBullet* bullet) {
	if (bullet->getAge() < 30) {
		double dir = bullet->getDirectionOfEntity(Game::getPlayer());
		dir -= bullet->rotation();
		if (dir == 180 || dir == -180)
			dir = 0;
		while (dir > 180)
			dir -= 360;
		while (dir < -180)
			dir += 360;
		dir = dir > 2 ? 2 : dir < -2 ? -2 : dir;
		bullet->rotate(dir);
	}
	bullet->moveForward(8);
});
const Bullet Bullet::FLOWER([](EntityBullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->collisionCheck = false;
	if (bullet->getAge() == 30)
		bullet->collisionCheck = true;
	if (bullet->getAge() < 30) {
		bullet->rotate(6);
		bullet->moveForward(3);
	} else {
		bullet->rotate(0.2);
		bullet->moveForward(6);
	}
});
const Bullet Bullet::FLOWERREV([](EntityBullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->collisionCheck = false;
	if (bullet->getAge() == 30)
		bullet->collisionCheck = true;
	if (bullet->getAge() < 30) {
		bullet->rotate(-6);
		bullet->moveForward(3);
	} else {
		bullet->rotate(-0.2);
		bullet->moveForward(6);
	}
});

const List<SpawnInfo> operator<<(const List<SpawnInfo>& list1,
                                 const SpawnInfo& info) {
  List<SpawnInfo> list;
  for (const SpawnInfo& info : list1)
    list.push_back(info);
  list.push_back(info);
  return list;
};
const List<SpawnInfo> operator<<(const List<SpawnInfo>& list1,
                                 const List<SpawnInfo>& list2) {
  List<SpawnInfo> list;
  for (const SpawnInfo& info : list1)
    list.push_back(info);
  for (const SpawnInfo& info : list2)
    list.push_back(info);
  return list;
};
const List<SpawnInfo> operator+(const List<SpawnInfo>& list, double deg) {
	List<SpawnInfo> newPattern;
	for (SpawnInfo info : list)
		newPattern.push_back(SpawnInfo(info.rot + deg, info.loc));
	return newPattern;
}
const List<SpawnInfo> operator*(const List<SpawnInfo>& list, int count) {
	List<SpawnInfo> newPattern;
	for (int i = 0; i < count; i++)
		for (SpawnInfo info : list)
			newPattern.push_back(SpawnInfo(info.rot + (360.0 / count) * i, info.loc));
	return newPattern;
}

const Pattern Pattern::CIRCLE3(SpawnInfo() << SpawnInfo(120) << SpawnInfo(240));
const Pattern Pattern::CIRCLE4(SpawnInfo() << SpawnInfo(90) << SpawnInfo(180)
                                           << SpawnInfo(270));
const Pattern Pattern::CIRCLE6(CIRCLE3 << CIRCLE3 + 60);
const Pattern Pattern::CIRCLE8(CIRCLE4 << CIRCLE4 + 45);
const Pattern Pattern::CIRCLE12(CIRCLE6 << CIRCLE6 + 30);
const Pattern Pattern::CIRCLE16(CIRCLE8 << CIRCLE8 + 22.5);
const Pattern Pattern::CIRCLE32(CIRCLE16 << CIRCLE16 + 11.25);
const Pattern Pattern::SHOTGUN3(SpawnInfo() << SpawnInfo(-20) << SpawnInfo(20));
const Pattern Pattern::SHOTGUN5(SpawnInfo(-40) << SpawnInfo(40) << SHOTGUN3);

const List<BulletInfo> operator<<(const List<BulletInfo>& list1,
                                  const BulletInfo& info) {
  List<BulletInfo> list;
  for (const BulletInfo& info : list1)
    list.push_back(info);
  list.push_back(info);
  return list;
};
const List<BulletInfo> operator<<(const List<BulletInfo>& list1,
                                  const List<BulletInfo>& list2) {
  List<BulletInfo> list;
  for (const BulletInfo& info : list1)
    list.push_back(info);
  for (const BulletInfo& info : list2)
    list.push_back(info);
  return list;
};
