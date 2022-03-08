#include "InputSystem.h"

#include "../Application/Application.h"

#include <SDL2/SDL.h>

namespace OrbEngine
{
	/* Keyboard Constants */
	const int InputSystem::KEYBOARD_A = SDL_SCANCODE_A;
	const int InputSystem::KEYBOARD_B = SDL_SCANCODE_B;
	const int InputSystem::KEYBOARD_C = SDL_SCANCODE_C;
	const int InputSystem::KEYBOARD_D = SDL_SCANCODE_D;
	const int InputSystem::KEYBOARD_E = SDL_SCANCODE_E;
	const int InputSystem::KEYBOARD_F = SDL_SCANCODE_F;
	const int InputSystem::KEYBOARD_G = SDL_SCANCODE_G;
	const int InputSystem::KEYBOARD_H = SDL_SCANCODE_H;
	const int InputSystem::KEYBOARD_I = SDL_SCANCODE_I;
	const int InputSystem::KEYBOARD_J = SDL_SCANCODE_J;
	const int InputSystem::KEYBOARD_K = SDL_SCANCODE_K;
	const int InputSystem::KEYBOARD_L = SDL_SCANCODE_L;
	const int InputSystem::KEYBOARD_M = SDL_SCANCODE_M;
	const int InputSystem::KEYBOARD_N = SDL_SCANCODE_N;
	const int InputSystem::KEYBOARD_O = SDL_SCANCODE_O;
	const int InputSystem::KEYBOARD_P = SDL_SCANCODE_P;
	const int InputSystem::KEYBOARD_Q = SDL_SCANCODE_Q;
	const int InputSystem::KEYBOARD_R = SDL_SCANCODE_R;
	const int InputSystem::KEYBOARD_S = SDL_SCANCODE_S;
	const int InputSystem::KEYBOARD_T = SDL_SCANCODE_T;
	const int InputSystem::KEYBOARD_U = SDL_SCANCODE_U;
	const int InputSystem::KEYBOARD_V = SDL_SCANCODE_V;
	const int InputSystem::KEYBOARD_W = SDL_SCANCODE_W;
	const int InputSystem::KEYBOARD_X = SDL_SCANCODE_X;
	const int InputSystem::KEYBOARD_Y = SDL_SCANCODE_Y;
	const int InputSystem::KEYBOARD_Z = SDL_SCANCODE_Z;
	const int InputSystem::KEYBOARD_0 = SDL_SCANCODE_0;
	const int InputSystem::KEYBOARD_1 = SDL_SCANCODE_1;
	const int InputSystem::KEYBOARD_2 = SDL_SCANCODE_2;
	const int InputSystem::KEYBOARD_3 = SDL_SCANCODE_3;
	const int InputSystem::KEYBOARD_4 = SDL_SCANCODE_4;
	const int InputSystem::KEYBOARD_5 = SDL_SCANCODE_5;
	const int InputSystem::KEYBOARD_6 = SDL_SCANCODE_6;
	const int InputSystem::KEYBOARD_7 = SDL_SCANCODE_7;
	const int InputSystem::KEYBOARD_8 = SDL_SCANCODE_8;
	const int InputSystem::KEYBOARD_9 = SDL_SCANCODE_9;
	const int InputSystem::KEYBOARD_RETURN = SDL_SCANCODE_RETURN;
	const int InputSystem::KEYBOARD_ESCAPE = SDL_SCANCODE_ESCAPE;
	const int InputSystem::KEYBOARD_BACKSPACE = SDL_SCANCODE_BACKSPACE;
	const int InputSystem::KEYBOARD_TAB = SDL_SCANCODE_TAB;
	const int InputSystem::KEYBOARD_SPACE = SDL_SCANCODE_SPACE;
	const int InputSystem::KEYBOARD_MINUS = SDL_SCANCODE_MINUS;
	const int InputSystem::KEYBOARD_EQUALS = SDL_SCANCODE_EQUALS;
	const int InputSystem::KEYBOARD_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET;
	const int InputSystem::KEYBOARD_RIGHTBACKET = SDL_SCANCODE_RIGHTBRACKET;
	const int InputSystem::KEYBOARD_BACKSLASH = SDL_SCANCODE_BACKSLASH;
	const int InputSystem::KEYBOARD_SEMICOLON = SDL_SCANCODE_SEMICOLON;
	const int InputSystem::KEYBOARD_APOSTROPHE = SDL_SCANCODE_APOSTROPHE;
	const int InputSystem::KEYBOARD_GRAVE = SDL_SCANCODE_GRAVE;
	const int InputSystem::KEYBOARD_COMMA = SDL_SCANCODE_COMMA;
	const int InputSystem::KEYBOARD_PERIOD = SDL_SCANCODE_PERIOD;
	const int InputSystem::KEYBOARD_SLASH = SDL_SCANCODE_SLASH;
	const int InputSystem::KEYBOARD_CAPSLOCK = SDL_SCANCODE_CAPSLOCK;
	const int InputSystem::KEYBOARD_F1 = SDL_SCANCODE_F1;
	const int InputSystem::KEYBOARD_F2 = SDL_SCANCODE_F2;
	const int InputSystem::KEYBOARD_F3 = SDL_SCANCODE_F3;
	const int InputSystem::KEYBOARD_F4 = SDL_SCANCODE_F4;
	const int InputSystem::KEYBOARD_F5 = SDL_SCANCODE_F5;
	const int InputSystem::KEYBOARD_F6 = SDL_SCANCODE_F6;
	const int InputSystem::KEYBOARD_F7 = SDL_SCANCODE_F7;
	const int InputSystem::KEYBOARD_F8 = SDL_SCANCODE_F8;
	const int InputSystem::KEYBOARD_F9 = SDL_SCANCODE_F9;
	const int InputSystem::KEYBOARD_F10 = SDL_SCANCODE_F10;
	const int InputSystem::KEYBOARD_F11 = SDL_SCANCODE_F11;
	const int InputSystem::KEYBOARD_F12 = SDL_SCANCODE_F12;
	const int InputSystem::KEYBOARD_RIGHT = SDL_SCANCODE_RIGHT;
	const int InputSystem::KEYBOARD_LEFT = SDL_SCANCODE_LEFT;
	const int InputSystem::KEYBOARD_DOWN = SDL_SCANCODE_DOWN;
	const int InputSystem::KEYBOARD_UP = SDL_SCANCODE_UP;
	const int InputSystem::KEYBOARD_LCTRL = SDL_SCANCODE_LCTRL;
	const int InputSystem::KEYBOARD_LSHIFT = SDL_SCANCODE_LSHIFT;
	const int InputSystem::KEYBOARD_LALT = SDL_SCANCODE_LALT;
	const int InputSystem::KEYBOARD_RCTRL = SDL_SCANCODE_RCTRL;
	const int InputSystem::KEYBOARD_RSHIFT = SDL_SCANCODE_RSHIFT;
	const int InputSystem::KEYBOARD_RALT = SDL_SCANCODE_RALT;
	/*----------------------*/

	InputSystem::InputSystem(Application* application) :
		m_Application(application), m_MousePosition(Vector2::Zero)
	{
		m_KeyState[KEYBOARD_A] = KeyButtonState();
		m_KeyState[KEYBOARD_B] = KeyButtonState();
		m_KeyState[KEYBOARD_C] = KeyButtonState();
		m_KeyState[KEYBOARD_D] = KeyButtonState();
		m_KeyState[KEYBOARD_E] = KeyButtonState();
		m_KeyState[KEYBOARD_F] = KeyButtonState();
		m_KeyState[KEYBOARD_G] = KeyButtonState();
		m_KeyState[KEYBOARD_H] = KeyButtonState();
		m_KeyState[KEYBOARD_I] = KeyButtonState();
		m_KeyState[KEYBOARD_J] = KeyButtonState();
		m_KeyState[KEYBOARD_K] = KeyButtonState();
		m_KeyState[KEYBOARD_L] = KeyButtonState();
		m_KeyState[KEYBOARD_M] = KeyButtonState();
		m_KeyState[KEYBOARD_N] = KeyButtonState();
		m_KeyState[KEYBOARD_O] = KeyButtonState();
		m_KeyState[KEYBOARD_P] = KeyButtonState();
		m_KeyState[KEYBOARD_Q] = KeyButtonState();
		m_KeyState[KEYBOARD_R] = KeyButtonState();
		m_KeyState[KEYBOARD_S] = KeyButtonState();
		m_KeyState[KEYBOARD_T] = KeyButtonState();
		m_KeyState[KEYBOARD_U] = KeyButtonState();
		m_KeyState[KEYBOARD_V] = KeyButtonState();
		m_KeyState[KEYBOARD_W] = KeyButtonState();
		m_KeyState[KEYBOARD_X] = KeyButtonState();
		m_KeyState[KEYBOARD_Y] = KeyButtonState();
		m_KeyState[KEYBOARD_Z] = KeyButtonState();
		m_KeyState[KEYBOARD_0] = KeyButtonState();
		m_KeyState[KEYBOARD_1] = KeyButtonState();
		m_KeyState[KEYBOARD_2] = KeyButtonState();
		m_KeyState[KEYBOARD_3] = KeyButtonState();
		m_KeyState[KEYBOARD_4] = KeyButtonState();
		m_KeyState[KEYBOARD_5] = KeyButtonState();
		m_KeyState[KEYBOARD_6] = KeyButtonState();
		m_KeyState[KEYBOARD_7] = KeyButtonState();
		m_KeyState[KEYBOARD_8] = KeyButtonState();
		m_KeyState[KEYBOARD_9] = KeyButtonState();
		m_KeyState[KEYBOARD_RETURN] = KeyButtonState();
		m_KeyState[KEYBOARD_ESCAPE] = KeyButtonState();
		m_KeyState[KEYBOARD_BACKSPACE] = KeyButtonState();
		m_KeyState[KEYBOARD_TAB] = KeyButtonState();
		m_KeyState[KEYBOARD_SPACE] = KeyButtonState();
		m_KeyState[KEYBOARD_MINUS] = KeyButtonState();
		m_KeyState[KEYBOARD_EQUALS] = KeyButtonState();
		m_KeyState[KEYBOARD_LEFTBRACKET] = KeyButtonState();
		m_KeyState[KEYBOARD_RIGHTBACKET] = KeyButtonState();
		m_KeyState[KEYBOARD_BACKSLASH] = KeyButtonState();
		m_KeyState[KEYBOARD_SEMICOLON] = KeyButtonState();
		m_KeyState[KEYBOARD_APOSTROPHE] = KeyButtonState();
		m_KeyState[KEYBOARD_GRAVE] = KeyButtonState();
		m_KeyState[KEYBOARD_COMMA] = KeyButtonState();
		m_KeyState[KEYBOARD_PERIOD] = KeyButtonState();
		m_KeyState[KEYBOARD_SLASH] = KeyButtonState();
		m_KeyState[KEYBOARD_CAPSLOCK] = KeyButtonState();
		m_KeyState[KEYBOARD_F1] = KeyButtonState();
		m_KeyState[KEYBOARD_F2] = KeyButtonState();
		m_KeyState[KEYBOARD_F3] = KeyButtonState();
		m_KeyState[KEYBOARD_F4] = KeyButtonState();
		m_KeyState[KEYBOARD_F5] = KeyButtonState();
		m_KeyState[KEYBOARD_F6] = KeyButtonState();
		m_KeyState[KEYBOARD_F7] = KeyButtonState();
		m_KeyState[KEYBOARD_F8] = KeyButtonState();
		m_KeyState[KEYBOARD_F9] = KeyButtonState();
		m_KeyState[KEYBOARD_F10] = KeyButtonState();
		m_KeyState[KEYBOARD_F11] = KeyButtonState();
		m_KeyState[KEYBOARD_F12] = KeyButtonState();
		m_KeyState[KEYBOARD_RIGHT] = KeyButtonState();
		m_KeyState[KEYBOARD_LEFT] = KeyButtonState();
		m_KeyState[KEYBOARD_DOWN] = KeyButtonState();
		m_KeyState[KEYBOARD_UP] = KeyButtonState();
		m_KeyState[KEYBOARD_LCTRL] = KeyButtonState();
		m_KeyState[KEYBOARD_LSHIFT] = KeyButtonState();
		m_KeyState[KEYBOARD_LALT] = KeyButtonState();
		m_KeyState[KEYBOARD_RCTRL] = KeyButtonState();
		m_KeyState[KEYBOARD_RSHIFT] = KeyButtonState();
		m_KeyState[KEYBOARD_RALT] = KeyButtonState();

		//DisableCursor();
	}

	InputSystem::~InputSystem()
	{

	}

	void InputSystem::EnableCursor()
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		m_MouseState.m_IsCursorEnabled = true;
		return;
	}

	void InputSystem::DisableCursor()
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		m_MouseState.m_IsCursorEnabled = false;
		return;
	}

	Vector2 InputSystem::GetMousePosition() const
	{
		//if (!m_MouseState.m_IsCursorEnabled) return Vector2::Zero;
		
		return m_MouseState.m_MousePosition;
	}

	Vector2 InputSystem::GetDeltaMousePosition() const
	{
		return m_MouseState.m_DeltaMousePosition;
	}

	Vector2 InputSystem::GetDeltaMousePositionIfMouseEnabled() const
	{
		if (m_MouseState.m_IsCursorEnabled) return Vector2::Zero;

		return m_MouseState.m_DeltaMousePosition;
	}

	bool InputSystem::GetKey(int keycode) const
	{
		auto key = m_KeyState.find(keycode);

		if (key != m_KeyState.end())
		{
			return key->second.m_IsPressed;
		}

		return false;
	}

	bool InputSystem::GetKeyDown(int keycode) const
	{
		auto key = m_KeyState.find(keycode);

		if (key != m_KeyState.end())
		{
			return key->second.m_IsPressedThisFrame;
		}

		return false;
	}

	bool InputSystem::GetKeyUp(int keycode) const
	{
		auto key = m_KeyState.find(keycode);

		if (key != m_KeyState.end())
		{
			return key->second.m_IsReleasedThisFrame;
		}

		return false;
	}

	bool InputSystem::GetMouse(int keycode) const
	{
		if (keycode < 0) keycode = 0;
		if (keycode > 2) keycode = 2;

		return m_MouseState.m_MouseButtonState[keycode].m_IsPressed;
	}

	bool InputSystem::GetMouseDown(int keycode) const
	{
		if (keycode < 0) keycode = 0;
		if (keycode > 2) keycode = 2;

		return m_MouseState.m_MouseButtonState[keycode].m_IsPressedThisFrame;
	}

	bool InputSystem::GetMouseUp(int keycode) const
	{
		if (keycode < 0) keycode = 0;
		if (keycode > 2) keycode = 2;

		return m_MouseState.m_MouseButtonState[keycode].m_IsReleasedThisFrame;
	}

	void InputSystem::HandleKeyOnPress(int keycode)
	{
		auto key = m_KeyState.find(keycode);
		
		if (!key->second.m_IsHeldDown && !key->second.m_IsPressed)
		{
			key->second.m_IsPressedThisFrame = true;
		}
		else if (key->second.m_IsPressed)
		{
			key->second.m_IsHeldDown = true;
			key->second.m_IsPressedThisFrame = false;
		}

		key->second.m_IsPressed = true;
	}

	void InputSystem::HandleKeyOnUp(int keycode)
	{
		auto key = m_KeyState.find(keycode);

		if (!key->second.m_IsReleasedThisFrame && key->second.m_IsPressed)
		{
			key->second.m_IsReleasedThisFrame = true;
		}
		else if (!key->second.m_IsPressed)
		{
			key->second.m_IsReleasedThisFrame = false;
		}

		key->second.m_IsPressed = false;
		key->second.m_IsHeldDown = false;
		key->second.m_IsPressedThisFrame = false;
	}

	void InputSystem::ProcessInput()
	{
		const uint8_t* state = SDL_GetKeyboardState(NULL);
		for (const auto &[keycode, buttonState]: m_KeyState)
		{
			if (state[keycode] == SDL_PRESSED)
			{
				HandleKeyOnPress(keycode);
			}
			else
			{
				HandleKeyOnUp(keycode);
			}
		}

		int x, y;
		const uint32_t buttonState = SDL_GetMouseState(&x, &y);

		float screenPosX = static_cast<float>(x);
		float screenPosY = static_cast<float>(y);
		screenPosX -= m_Application->GetScreenWidth() / 2.0f;
		screenPosY = m_Application->GetScreenHeight() / 2.0f - screenPosY;
		m_MouseState.m_MousePosition = Vector2(screenPosX, screenPosY);

		SDL_GetRelativeMouseState(&x, &y);
		m_MouseState.m_DeltaMousePosition = Vector2(static_cast<float>(x), static_cast<float>(y));

		for (int i = 0; i < NUM_MOUSE_BUTTON_STATES; ++i)
		{
			bool buttonPressedState = (buttonState & (SDL_BUTTON(SDL_BUTTON_LEFT + i)));

			if (buttonPressedState == SDL_PRESSED)
			{
				if (!m_MouseState.m_MouseButtonState[i].m_IsHeldDown && !m_MouseState.m_MouseButtonState[i].m_IsPressed)
				{
					m_MouseState.m_MouseButtonState[i].m_IsPressedThisFrame = true;
				}
				else if (m_MouseState.m_MouseButtonState[i].m_IsPressed)
				{
					m_MouseState.m_MouseButtonState[i].m_IsHeldDown = true;
					m_MouseState.m_MouseButtonState[i].m_IsPressedThisFrame = false;
				}

				m_MouseState.m_MouseButtonState[i].m_IsPressed = true;
			}

			else if (buttonPressedState == SDL_RELEASED)
			{
				if (!m_MouseState.m_MouseButtonState[i].m_IsReleasedThisFrame && m_MouseState.m_MouseButtonState[i].m_IsPressed)
				{
					m_MouseState.m_MouseButtonState[i].m_IsReleasedThisFrame = true;
				}
				else if (!m_MouseState.m_MouseButtonState[i].m_IsPressed)
				{
					m_MouseState.m_MouseButtonState[i].m_IsReleasedThisFrame = false;
				}

				m_MouseState.m_MouseButtonState[i].m_IsPressed = false;
				m_MouseState.m_MouseButtonState[i].m_IsHeldDown = false;
				m_MouseState.m_MouseButtonState[i].m_IsPressedThisFrame = false;
			}
		}
	}


	bool InputSystem::KeyExists(int keycode) const
	{
		auto key = m_KeyState.find(keycode);
		
		if (key != m_KeyState.end()) return true;

		return false;
	}

	void InputSystem::ToggleCursor()
	{
		if (m_MouseState.m_IsCursorEnabled) DisableCursor();
		else EnableCursor();
	}
}