#include "Display.h"
#include <GL\glew.h>

#include <iostream>

int Display::m_keyDownkey;
std::vector<int> Display::m_keyDownkeys;
std::vector<int> Display::m_mouseDownButtons;
long Display::m_lastFrame;
float Display::m_delta;
glm::vec2 Display::m_mouseDelta;

Display::Display(int width, int heigth, const std::string title) {
	SDL_Init (SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow (title.c_str (), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, heigth, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext (m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Glew initialize FAIL!" << std::endl;
	}

	m_isClosed = false;

	glEnable (GL_DEPTH_TEST);
	Display::m_lastFrame = GetCurrentTime();
}


Display::~Display() {
	SDL_GL_DeleteContext (m_glContext);
	SDL_DestroyWindow (m_window);
	SDL_Quit ();
}

bool Display::IsClosed () {
	return m_isClosed;
}

void Display::Clear (float r, float g, float b, float a) {
	glClearColor (r, g, b, a);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update () {
	SDL_GL_SwapWindow (m_window);
	long currentFrameTime = GetCurrentTime();
	Display::m_delta = (currentFrameTime - Display::m_lastFrame)/1000.0f;
	Display::m_lastFrame = currentFrameTime;

	while (SDL_PollEvent (&m_event)) {
		switch (m_event.type) {
		case SDL_QUIT:
			m_isClosed = true;
			break;
		case SDL_KEYDOWN:
			Display::m_keyDownkey = m_event.key.keysym.sym;
			if(Display::m_keyDownkeys.size() <= 0) Display::m_keyDownkeys.push_back(m_event.key.keysym.sym);
			else {
				bool isFound = false;
				for (size_t i = 0; i < Display::m_keyDownkeys.size(); i++) {
					if (Display::m_keyDownkeys[i] == m_event.key.keysym.sym)
						isFound = true;
				}
				if(!isFound) Display::m_keyDownkeys.push_back(m_event.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			Display::m_keyDownkey = 0;
			for (size_t i = 0; i < Display::m_keyDownkeys.size(); i++) {
				if (Display::m_keyDownkeys[i] == m_event.key.keysym.sym) {
					Display::m_keyDownkeys.erase(Display::m_keyDownkeys.begin() + i);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (Display::m_mouseDownButtons.size() <= 0) Display::m_mouseDownButtons.push_back(m_event.button.button);
			else {
				bool isFound = false;
				for (size_t i = 0; i < Display::m_mouseDownButtons.size(); i++) {
					if (Display::m_mouseDownButtons[i] == m_event.button.button)
						isFound = true;
				}
				if (!isFound) Display::m_mouseDownButtons.push_back(m_event.button.button);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			for (size_t i = 0; i < Display::m_mouseDownButtons.size(); i++) {
				if (Display::m_mouseDownButtons[i] == m_event.button.button) {
					Display::m_mouseDownButtons.erase(Display::m_mouseDownButtons.begin() + i);
				}
			}
			break;
		case SDL_MOUSEMOTION:
			Display::m_mouseDelta.x = m_event.button.x - m_mouseLastPos.x;
			Display::m_mouseDelta.y = m_event.button.y - m_mouseLastPos.y;
			Display::m_mouseLastPos.x = (float)m_event.button.x;
			Display::m_mouseLastPos.y = (float)m_event.button.y;
			break;
		default:
			break;
		}
	}
}
