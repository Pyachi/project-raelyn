#ifndef USER_H
#define USER_H

#include <QString>

class UUID;

namespace User {
extern const QString getName();
extern const QString getIp();
extern const UUID getUUID();
};

#endif  // USER_H
