#include "InputManager.h"

namespace helix
{
	InputManager::InputManager()
		: m_mouse_coords{ 0.0f }
	{
	}

	void InputManager::KeyPress(keyID_t key_ID)
	{
		m_key_map[key_ID] = true;
	}


	void InputManager::KeyRelease(keyID_t key_ID)
	{
		m_key_map[key_ID] = false;
	}

	bool InputManager::IsKeyDown(Event::Key key_ID)
	{
		auto found{ m_key_map.find(static_cast<keyID_t>(key_ID)) };
		if (found != m_key_map.end())
			return found->second;
		return false;
	}

	bool InputManager::IsKeyDown(Event::Mouse mouse_ID)
	{
		auto found{ m_key_map.find(static_cast<keyID_t>(mouse_ID)) };
		if (found != m_key_map.end())
			return found->second;
		return false;
	}

	bool InputManager::IsKeyPressed(Event::Key key_ID)
	{
		return false;
	}

	bool InputManager::IsKeyPressed(Event::Mouse key_ID)
	{
		return false;
	}


	void InputManager::SetMouseCoords(float x, float y)
	{
		m_mouse_coords.x = x;
		m_mouse_coords.y = y;
	}
}
