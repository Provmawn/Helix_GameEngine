#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "Event.h"

#include <glm/glm.hpp>

#include <unordered_map>


namespace helix {
	class InputManager
	{
	public:
		InputManager();
		using keyID_t = unsigned int;
		void KeyPress(keyID_t key_ID);
		void KeyRelease(keyID_t key_ID);
		bool IsKeyDown(Event::Key key_ID);
		bool IsKeyDown(Event::Mouse key_ID);
		bool IsKeyPressed(Event::Key key_ID);
		bool IsKeyPressed(Event::Mouse key_ID);
		void SetMouseCoords(float x, float y);
		const glm::vec2& GetMouseCoords() const { return m_mouse_coords; }
	private:
		std::unordered_map<keyID_t, bool> m_key_map{};
		std::unordered_map<keyID_t, bool> m_previous_key_map{};
		glm::vec2 m_mouse_coords{};
	};
}
#endif
