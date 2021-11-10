#ifndef USER_H
#define USER_H

#include <QString>
#include "src/ai/player.h"

class UUID;

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
extern const UUID getUUID(void);
};  // namespace User

#endif  // USER_H
