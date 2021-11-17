#include "controls.h"

Array<Ref<Controls>> Controls::list;

const Controls Controls::TRAD("Controls: Traditional",
															{Qt::Key_Up, Qt::Key_Left, Qt::Key_Down,
															 Qt::Key_Right, Qt::Key_Shift, Qt::Key_Z,
															 Qt::Key_X});

const Controls Controls::WASD("Controls: WASD",
															{Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D,
															 Qt::Key_L, Qt::Key_K, Qt::Key_J});

const Controls Controls::IJKL("Controls: IJKL",
															{Qt::Key_I, Qt::Key_J, Qt::Key_K, Qt::Key_L,
															 Qt::Key_A, Qt::Key_S, Qt::Key_D});
