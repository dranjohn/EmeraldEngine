#pragma once

//--- Interface files ---
#include "core/input/KeyCode.h"


namespace EmeraldEngine {
	struct MousePosition { double x; double y; };
	struct MouseClick { MousePosition position; MouseButton button; KeyAction action; };
	struct KeyStateModified { Key key; KeyAction action; };
}
