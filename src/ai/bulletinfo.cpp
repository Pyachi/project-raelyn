#include "bulletinfo.h"
#include "src/entity/bullet.h"

BulletInfo::BulletInfo(const Texture& texture,
											 const BulletAI& ai,
											 double relRot,
											 const QPointF& relPos)
		: texture(texture), ai(ai), relRot(relRot), relPos(relPos) {}

Bullet* BulletInfo::spawn(Entity* owner,
													const QPointF& spawn,
													double rotation) const {
	return new Bullet(this, owner, spawn + relPos, rotation + relRot);
}
