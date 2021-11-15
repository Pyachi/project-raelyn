#ifndef USER_H
#define USER_H

#include "character.h"
#include "util.h"

class UID;

namespace User {
extern int character;
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
