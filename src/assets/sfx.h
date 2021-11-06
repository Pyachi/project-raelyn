#ifndef SFX_H
#define SFX_H

#include <QString>

namespace SFX {
extern const QString COLLECT_1;
extern const QString COLLECT_2;
extern const QString COLLECT_3;
extern const QString EXPL_HEAVY_1;
extern const QString EXPL_HEAVY_2;
extern const QString EXPL_HEAVY_3;
extern const QString EXPL_HEAVY_4;
extern const QString EXPL_LIGHT_1;
extern const QString EXPL_LIGHT_2;
extern const QString EXPL_LIGHT_3;
extern const QString EXPL_MED_1;
extern const QString EXPL_MED_2;
extern const QString EXPL_MED_3;
extern const QString EXPL_SUPERHEAVY_1;
extern const QString EXPL_SUPERHEAVY_2;
extern const QString HIT_1;
extern const QString HIT_2;
extern const QString HIT_3;
extern const QString LASER_1;
extern const QString MISSILE_1;
extern const QString MISSILE_2;
extern const QString MISSILE_3;
extern const QString POWERUP_1;
extern const QString POWERUP_2;
extern const QString POWERUP_3;
extern const QString SELECT_1;
extern const QString SELECT_2;

extern void playSound(const QString&, qreal = 0);
};

#endif  // SFX_H
