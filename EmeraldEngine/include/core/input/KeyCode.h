#pragma once


namespace EmeraldEngine {
	enum KeyAction : int {
		release = 0,
		press = 1,
		repeat = 2
	};

	enum Key : int {
		undefined = -1,

		//--- Default keys ---
		space = 32,
		apostrophe = 39,  /* ' */
		comma = 44, /* , */
		minus = 45, /* - */
		period = 46, /* . */
		slash = 47, /* / */

		num_0 = 48,
		num_1 = 49,
		num_2 = 50,
		num_3 = 51,
		num_4 = 52,
		num_5 = 53,
		num_6 = 54,
		num_7 = 55,
		num_8 = 56,
		num_9 = 57,

		semicolon = 59, /* ; */
		equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		left_bracket = 91, /* [ */
		backslash = 92, /* \ */
		right_bracket = 93, /* ] */
		grave_accent = 96, /* ` */


		// --- Function keys ---
		escape = 256,
		enter = 257,
		tab = 258,
		backspace = 259,
		insert = 260,
		del = 261,

		right = 262,
		left = 263,
		down = 264,
		up = 265,

		page_up = 266,
		page_down = 267,
		home = 268,
		end = 269,

		caps_lock = 280,
		scroll_lock = 281,
		num_lock = 282,

		print_screen = 283,
		pause = 284,

		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		left_shift = 340,
		left_control = 341,
		left_alt = 342,
		left_super = 343,
		right_shift = 344,
		right_control = 345,
		right_alt = 346,
		right_super = 347,
		menu = 348,


		// --- Numpad keys ---
		numpad_0 = 320,
		numpad_1 = 321,
		numpad_2 = 322,
		numpad_3 = 323,
		numpad_4 = 324,
		numpad_5 = 325,
		numpad_6 = 326,
		numpad_7 = 327,
		numpad_8 = 328,
		numpad_9 = 329,

		numpad_decimal = 330,
		numpad_divide = 331,
		numpad_multiply = 332,
		numpad_subtract = 333,
		numpad_add = 334,
		numpad_enter = 335,
		numpad_equal = 336
	};

	enum MouseButton : int {
		mouse_button_1 = 0,
		mouse_button_2 = 1,
		mouse_button_3 = 2,
		mouse_button_4 = 3,
		mouse_button_5 = 4,
		mouse_button_6 = 5,
		mouse_button_7 = 6,
		mouse_button_8 = 7,

		mouse_button_left = mouse_button_1,
		mouse_button_right = mouse_button_2,
		mouse_button_middle = mouse_button_3,

		mouse_button_last = mouse_button_8
	};
}
