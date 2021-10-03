#include "hitbox.h"
#include "src/game/game.h"
#include <type_traits>

Hitbox::Hitbox(Game* game, Entity* owner, QString texture, QPoint spawnLoc, int zValue)
    : Entity(game, texture, spawnLoc, zValue) {
    this->owner = owner;
}

QList<Hitbox*> Hitbox::collidingHitboxes() {
    QList<QGraphicsItem*> collidingList = collidingItems();
    QList<Hitbox*> hitboxList;
    foreach(QGraphicsItem* item, collidingList) {
        if (Hitbox* hitbox = dynamic_cast<Hitbox*>(item))
            if (hitbox->owner != owner && hitbox != owner)
                hitboxList.append(hitbox);
    }
    return hitboxList;
}
