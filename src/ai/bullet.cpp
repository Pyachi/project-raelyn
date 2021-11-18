#include "bullet.h"
#include "entitybullet.h"

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

const Pattern Pattern::CIRCLE3(SpawnInfo() << SpawnInfo(120) << SpawnInfo(240));
const Pattern Pattern::CIRCLE4(SpawnInfo() << SpawnInfo(90) << SpawnInfo(180)
                                           << SpawnInfo(270));
const Pattern Pattern::CIRCLE6(SpawnInfo(60)
															 << SpawnInfo(180) << SpawnInfo(300) << CIRCLE3);
const Pattern Pattern::CIRCLE8(SpawnInfo(45) << SpawnInfo(135) << SpawnInfo(225)
                                             << SpawnInfo(315) << CIRCLE4);
const Pattern Pattern::CIRCLE12(SpawnInfo(30)
																<< SpawnInfo(90) << SpawnInfo(150)
																<< SpawnInfo(210) << SpawnInfo(270)
																<< SpawnInfo(330) << CIRCLE6);
const Pattern Pattern::CIRCLE16(SpawnInfo(22.5)
                                << SpawnInfo(67.5) << SpawnInfo(112.5)
                                << SpawnInfo(157.5) << SpawnInfo(202.5)
                                << SpawnInfo(247.5) << SpawnInfo(292.5)
                                << SpawnInfo(337.5) << CIRCLE8);
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
