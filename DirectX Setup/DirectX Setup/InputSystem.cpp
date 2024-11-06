#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem() {
    memset(m_keys_state, 0, sizeof(m_keys_state));
    memset(m_old_keys_state, 0, sizeof(m_old_keys_state));
}

InputSystem::~InputSystem() {

}

void InputSystem::Update() {
    POINT current_mouse_pos = {};
    ::GetCursorPos(&current_mouse_pos);

    if (m_first_time) {
        m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
        m_first_time = false;
    }



    // Check for mouse movement
    if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y) {
        // Only notify listeners if the right mouse button is pressed
        if (m_keys_state[VK_RBUTTON] & 0x80) {
            std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
            while (it != m_set_listeners.end()) {
                (*it)->OnMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
                ++it;
            }
        }
    }

    m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

    if (::GetKeyboardState(m_keys_state)) {
    for (unsigned int i = 0; i < 256; i++) {
        if (m_keys_state[i] & 0x80) {
            std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

            while (it != m_set_listeners.end()) {

                if (i == VK_LBUTTON) {
                    if (m_keys_state[i] != m_old_keys_state[i]) {
                        (*it)->OnLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                }
                else if (i == VK_RBUTTON) {
                    if (m_keys_state[i] != m_old_keys_state[i]) {
                        (*it)->OnRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                }
                else
                    (*it)->OnKeyDown(i);
                
                ++it;
            }   
        }
        else {
            if (m_keys_state[i] != m_old_keys_state[i]) {
                std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

                while (it != m_set_listeners.end()) {
                    if (i == VK_LBUTTON) {
                        (*it)->OnLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else if (i == VK_RBUTTON) {
                        (*it)->OnRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
                    }
                    else
                        (*it)->OnKeyUp(i);
                    ++it;
                }
            }
        }
    }
    ::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
    }
}

void InputSystem::AddListener(InputListener* listener) {
    m_set_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener* listener) {
    m_set_listeners.erase(listener);
}

void InputSystem::SetCursorPos(const Point& pos) {
    ::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::ShowCursor(bool show) {
    ::ShowCursor(show);
}

bool InputSystem::IsKeyDown(int key) {
    return (m_keys_state[key] & 0x80) != 0;
}

bool InputSystem::IsKeyUp(int key) {
    return (m_old_keys_state[key] & 0x80) != 0 && (m_keys_state[key] & 0x80) == 0;
}

InputSystem* InputSystem::get() {
    static InputSystem system;
    return &system; 
}
