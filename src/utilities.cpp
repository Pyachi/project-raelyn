#include "utilities.h"
#include "entityinfo.h"
#include "entitytypes.h"
#include "game.h"

bool Util::confineToPlayableArea(QPointF& pos, QSizeF size) {
	QPointF old(pos);
	pos.setX(qBound(double(playBorder), pos.x(),
									gameHeight - playBorder - size.width()));
	pos.setY(qBound(double(playBorder), pos.y(),
									gameHeight - playBorder - size.height()));
	return (old.x() != pos.x() || old.y() != pos.y());
}

void Util::bulletCircle(BaseEntity* shooter,
												BulletInfo& info,
												int count,
												double startRot) {
	double rot = startRot;
	for (int i = 0; i < count; i++) {
		shooter->fireBullet(info, QPointF(0, 0), rot);
		rot += 360 / double(count);
	}
}
