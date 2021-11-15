#include "collectable.h"
#include "entitycollectable.h"
#include "entityplayer.h"
#include "sfx.h"
#include "texture.h"

EntityCollectable* Collectable::spawn(const QPointF& loc) const {
  EntityCollectable* col = new EntityCollectable(tex, ai);
  col->setPos(loc);
  return col;
}

const Collectable Collectable::POWER(Texture::POWER, [](EntityPlayer* player) {
  player->addPower();
  SFX::COLLECT1.play(10);
});

const Collectable Collectable::POINTS(Texture::POINTS,
                                      [](EntityPlayer* player) {
                                        SFX::COLLECT3.play(10);
                                      });

const Collectable Collectable::HEALTH(Texture::ENEMYTEMP,
                                      [](EntityPlayer* player) {
                                        SFX::COLLECT3.play(10);
                                      });

const Collectable Collectable::BOMB(Texture::ENEMYTEMP,
                                    [](EntityPlayer* player) {
                                      SFX::COLLECT3.play(10);
                                    });
