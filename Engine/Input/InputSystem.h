#pragma once
#include "../Math/Math.h"

#include <unordered_map>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;
	class Actor;

	struct MouseButtonState
	{
		MouseButtonState() :
			m_IsPressed(false), m_IsPressedThisFrame(false),
			m_IsReleasedThisFrame(false), m_IsHeldDown(false) {}

		bool m_IsPressed;
		bool m_IsPressedThisFrame;
		bool m_IsHeldDown;
		bool m_IsReleasedThisFrame;
	};

	constexpr int NUM_MOUSE_BUTTON_STATES = 3;

	struct MouseState
	{
		MouseState() :
			m_MousePosition(Vector2::Zero), m_DeltaMousePosition(Vector2::Zero),
			m_IsCursorEnabled(false) {}

		MouseButtonState m_MouseButtonState[NUM_MOUSE_BUTTON_STATES];
		Vector2 m_MousePosition;
		Vector2 m_DeltaMousePosition;
		bool m_IsCursorEnabled;
	};

	struct KeyButtonState
	{
	public:
		KeyButtonState() : 
			m_IsPressed(false), m_IsPressedThisFrame(false), 
			m_IsReleasedThisFrame(false), m_IsHeldDown(false) {}
		
		bool m_IsPressed;
		bool m_IsPressedThisFrame;
		bool m_IsHeldDown;
		bool m_IsReleasedThisFrame;
	};

	class InputSystem
	{
	public:
		/* Constructors/destructor */
		InputSystem(Application* application);
		~InputSystem();

		/* Main functions */
		void EnableCursor();
		void DisableCursor();
		Vector2 GetMousePosition() const;
		Vector2 GetDeltaMousePosition() const;
		Vector2 GetDeltaMousePositionIfMouseEnabled() const;
		bool GetKey(int keycode) const;
		bool GetKeyDown(int keycode) const;
		bool GetKeyUp(int keycode) const;
		bool GetMouse(int keycode) const;
		bool GetMouseDown(int keycode) const;
		bool GetMouseUp(int keycode) const;
		void ProcessInput();
		bool KeyExists(int keycode) const;
		void ToggleCursor();

		/* Getters */
		MouseState GetMouseState() const { return m_MouseState; }

		/* Constants */
		static const int KEYBOARD_A;
		static const int KEYBOARD_B;
		static const int KEYBOARD_C;
		static const int KEYBOARD_D;
		static const int KEYBOARD_E;
		static const int KEYBOARD_F;
		static const int KEYBOARD_G;
		static const int KEYBOARD_H;
		static const int KEYBOARD_I;
		static const int KEYBOARD_J;
		static const int KEYBOARD_K;
		static const int KEYBOARD_L;
		static const int KEYBOARD_M;
		static const int KEYBOARD_N;
		static const int KEYBOARD_O;
		static const int KEYBOARD_P;
		static const int KEYBOARD_Q;
		static const int KEYBOARD_R;
		static const int KEYBOARD_S;
		static const int KEYBOARD_T;
		static const int KEYBOARD_U;
		static const int KEYBOARD_V;
		static const int KEYBOARD_W;
		static const int KEYBOARD_X;
		static const int KEYBOARD_Y;
		static const int KEYBOARD_Z;
		static const int KEYBOARD_0;
		static const int KEYBOARD_1;
		static const int KEYBOARD_2;
		static const int KEYBOARD_3;
		static const int KEYBOARD_4;
		static const int KEYBOARD_5;
		static const int KEYBOARD_6;
		static const int KEYBOARD_7;
		static const int KEYBOARD_8;
		static const int KEYBOARD_9;
		static const int KEYBOARD_RETURN;
		static const int KEYBOARD_ESCAPE;
		static const int KEYBOARD_BACKSPACE;
		static const int KEYBOARD_TAB;
		static const int KEYBOARD_SPACE;
		static const int KEYBOARD_MINUS;
		static const int KEYBOARD_EQUALS;
		static const int KEYBOARD_LEFTBRACKET;
		static const int KEYBOARD_RIGHTBACKET;
		static const int KEYBOARD_BACKSLASH;
		static const int KEYBOARD_SEMICOLON;
		static const int KEYBOARD_APOSTROPHE;
		static const int KEYBOARD_GRAVE;
		static const int KEYBOARD_COMMA;
		static const int KEYBOARD_PERIOD;
		static const int KEYBOARD_SLASH;
		static const int KEYBOARD_CAPSLOCK;
		static const int KEYBOARD_F1;
		static const int KEYBOARD_F2;
		static const int KEYBOARD_F3;
		static const int KEYBOARD_F4;
		static const int KEYBOARD_F5;
		static const int KEYBOARD_F6;
		static const int KEYBOARD_F7;
		static const int KEYBOARD_F8;
		static const int KEYBOARD_F9;
		static const int KEYBOARD_F10;
		static const int KEYBOARD_F11;
		static const int KEYBOARD_F12; // ends at value 69 in SDL_scandode.h
		static const int KEYBOARD_RIGHT; // picks up at value 79
		static const int KEYBOARD_LEFT;
		static const int KEYBOARD_DOWN;
		static const int KEYBOARD_UP; // ends at 82
		static const int KEYBOARD_LCTRL; // starts at 224
		static const int KEYBOARD_LSHIFT;
		static const int KEYBOARD_LALT;
		static const int KEYBOARD_RCTRL;
		static const int KEYBOARD_RSHIFT;
		static const int KEYBOARD_RALT;
	private:
		Application* m_Application;
		Vector2 m_MousePosition;
		std::unordered_map<int, KeyButtonState> m_KeyState;
		MouseState m_MouseState;

		/* Internal functions */
		void HandleKeyOnPress(int keycode);
		void HandleKeyOnUp(int keycode);
	};
}