#ifndef USER_H
#define USER_H

#include <QString>
#include "src/ai/player.h"

class UUID;

namespace User {
extern PlayerType character;
extern const QString getName();
extern const QString getIp();
extern const UUID getUUID();
};  // namespace User

#endif  // USER_H
