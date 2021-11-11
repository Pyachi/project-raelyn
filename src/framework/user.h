#ifndef USER_H
#define USER_H

#include <QString>
#include "src/ai/player.h"

class UID;

namespace User {
extern PlayerType character;
extern Array<int> keys;
extern int getKeyUp(void);
extern int getKeyLeft(void);
extern int getKeyDown(void);
extern int getKeyRight(void);
extern int getKeyFocus(void);
extern int getKeyShoot(void);
extern int getKeyBomb(void);
extern const QString getName(void);
extern const QString getIp(void);
extern const UID getUUID(void);
};  // namespace User

#endif  // USER_H
