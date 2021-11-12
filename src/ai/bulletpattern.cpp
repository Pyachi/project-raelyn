#include "bulletpattern.h"
#include "bullet.h"
#include "src/assets/texture.h"

namespace Patterns {
List<BulletInfo> get(Pattern pattern) {
  switch (pattern) {
    // BulletInfo{AI, ROTATION, POSITION, DAMAGE};
    case PATTERN_PLAYERBASIC:
      return List<BulletInfo>() << BulletInfo{AI_PLAYERBASIC};

    case PATTERN_PLAYERBASICX2:
      return BulletInfo{AI_PLAYERBASIC, 0, {20, 0}}
      << BulletInfo{AI_PLAYERBASIC, 0, {-20, 0}};

    case PATTERN_PLAYERBASICX2C:
      return BulletInfo{AI_PLAYERBASIC, 0, {10, 0}}
      << BulletInfo{AI_PLAYERBASIC, 0, {-10, 0}};

    case PATTERN_PLAYERBASICX3:
      return PATTERN_PLAYERBASIC << PATTERN_PLAYERBASICX2;

    case PATTERN_PLAYERBASICX3C:
      return PATTERN_PLAYERBASIC << PATTERN_PLAYERBASICX2C;

    case PATTERN_PLAYERBASICX5:
      return PATTERN_PLAYERBASICX3 << PATTERN_PLAYERBASICX2C;

    case PATTERN_PLAYERBASICX5C:
      return PATTERN_PLAYERBASICX3C << BulletInfo{AI_PLAYERBASIC, 0, {5, 0}}
      << BulletInfo{AI_PLAYERBASIC, 0, {-5, 0}};

    case PATTERN_PLAYERHOMINGX2:
      return BulletInfo{AI_PLAYERHOMING, 0, {-50, 0}}
      << BulletInfo{AI_PLAYERHOMING, 0, {50, 0}};

    case PATTERN_PLAYERHOMINGX2C:
      return BulletInfo{AI_PLAYERHOMING, 0, {-25, -25}}
      << BulletInfo{AI_PLAYERHOMING, 0, {25, -25}};
    case PATTERN_SINGLE2:
      return BulletInfo{AI_BASIC2}
      << BulletInfo{AI_BASIC2, 0};
    case PATTERN_SINGLE4:
      return BulletInfo{AI_BASIC4}
      << BulletInfo{AI_BASIC4, 0};
    case PATTERN_SINGLE6:
      return BulletInfo{AI_BASIC6}
      << BulletInfo{AI_BASIC6, 0};

    case PATTERN_SINGLE8:
      return BulletInfo{AI_BASIC8}
      << BulletInfo{AI_BASIC8, 0};

    case PATTERN_SHOTGUN2X3:
      return BulletInfo{AI_BASIC2}
      << BulletInfo{AI_BASIC2, 20} << BulletInfo{AI_BASIC2, -20};

    case PATTERN_SHOTGUN4X3:
      return BulletInfo{AI_BASIC4}
      << BulletInfo{AI_BASIC4, 20} << BulletInfo{AI_BASIC4, -20};

    case PATTERN_SHOTGUN6X3:
      return BulletInfo{AI_BASIC6}
      << BulletInfo{AI_BASIC6, 20} << BulletInfo{AI_BASIC6, -20};

    case PATTERN_SHOTGUN8X3:
      return BulletInfo{AI_BASIC8}
      << BulletInfo{AI_BASIC8, 20} << BulletInfo{AI_BASIC8, -20};

    case PATTERN_SHOTGUN10X3:
      return BulletInfo{AI_BASIC10}
      << BulletInfo{AI_BASIC10, 20} << BulletInfo{AI_BASIC10, -20};

    case PATTERN_SHOTGUN12X3:
      return BulletInfo{AI_BASIC12}
      << BulletInfo{AI_BASIC12, 20} << BulletInfo{AI_BASIC12, -20};

    case PATTERN_SHOTGUN4X5:
      return PATTERN_SHOTGUN4X3 << BulletInfo{AI_BASIC4, 40}
      << BulletInfo{AI_BASIC4, -40};

    case PATTERN_SHOTGUN6X5:
      return PATTERN_SHOTGUN6X3 << BulletInfo{AI_BASIC6, 40}
      << BulletInfo{AI_BASIC6, -40};

    case PATTERN_SHOTGUN8X5:
      return PATTERN_SHOTGUN8X3 << BulletInfo{AI_BASIC8, 40}
      << BulletInfo{AI_BASIC8, -40};

    case PATTERN_SHOTGUN10X5:
      return PATTERN_SHOTGUN10X3 << BulletInfo{AI_BASIC10, 40}
      << BulletInfo{AI_BASIC10, -40};

    case PATTERN_SHOTGUN12X5:
      return PATTERN_SHOTGUN12X3 << BulletInfo{AI_BASIC12, 40}
      << BulletInfo{AI_BASIC12, -40};

    case PATTERN_TRIPLESHOTGUNX3:
      return PATTERN_SHOTGUN8X3 << PATTERN_SHOTGUN10X3 << PATTERN_SHOTGUN12X3;

    case PATTERN_TRIPLESHOTGUNX5:
      return PATTERN_SHOTGUN8X5 << PATTERN_SHOTGUN10X5 << PATTERN_SHOTGUN12X5;
  }
}

List<BulletInfo> operator<<(const BulletInfo& info1, const BulletInfo& info2) {
  return List<BulletInfo>() << info1 << info2;
}

List<BulletInfo> operator<<(Pattern pattern, const BulletInfo& info) {
  return get(pattern) << info;
}

List<BulletInfo> operator<<(Pattern pattern1, Pattern pattern2) {
  return get(pattern1) << get(pattern2);
}

List<BulletInfo> operator<<(List<BulletInfo> list, Pattern pattern) {
  return list << get(pattern);
}

List<BulletInfo> operator<<(List<BulletInfo> list, const BulletInfo& info) {
  list.emplace_back(info);
  return list;
}

List<BulletInfo> operator<<(List<BulletInfo> list,
                            const List<BulletInfo>& other) {
  for (BulletInfo info : other) {
    list.emplace_back(info);
  }
  return list;
}
}  // namespace Patterns
