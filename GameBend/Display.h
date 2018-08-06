#ifndef DISPLAY_H
#define DISPLAY_H

#include <glm\glm.hpp>
#include <sdl\SDL.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>

class Display {
	public:
		Display(int width, int height, const std::string title);
		void Update ();
		void Clear (float r, float g, float b, float a);

		bool IsClosed ();
		virtual ~Display();

		inline SDL_Event GetSDL_Event() { return m_event; }
		
		static bool GetKeyDown() { return (m_keyDownkeys.size() <= 0) ? false : true; }
		static bool GetKeyDown(int key) {
			for (size_t i = 0; i < m_keyDownkeys.size(); i++) {
				if (m_keyDownkeys[i] == key)
					return true;
			}
			return false;
		}
		static bool GetMouseDown() { return (m_mouseDownButtons.size() <= 0) ? false : true; }
		static bool GetMouseDown(int key) {
			for (size_t i = 0; i < m_mouseDownButtons.size(); i++) {
				if (m_mouseDownButtons[i] == key)
					return true;
			}
			return false;
		}
		static int GetKeyDownKey() { return m_keyDownkey; }
		static std::vector<int> GetKeyDownKeys() { return m_keyDownkeys; }
		static float GetDeltaTime() { return m_delta; }
		static glm::vec2 GetMouseDelta() { return m_mouseDelta; }
	protected:
	private:
		Display(const Display &other) {}
		void operator = (const Display &other) {}

		static long GetCurrentTime() {
			const clock_t start = clock();
			return start;
		}

		SDL_Window* m_window;
		SDL_GLContext m_glContext;
		SDL_Event m_event;
		bool m_isClosed;
		glm::vec2 m_mouseLastPos;

		static int m_width;
		static int m_height;
		static int m_keyDownkey;
		static std::vector<int> m_keyDownkeys;
		static std::vector<int> m_mouseDownButtons;
		static long m_lastFrame;
		static float m_delta;
		static glm::vec2 m_mouseDelta;
};

#endif // !DISPLAY_H