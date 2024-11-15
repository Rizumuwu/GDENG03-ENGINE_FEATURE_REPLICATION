#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void Update();
	void AddListener(InputListener* listener);
	void RemoveListener(InputListener* listener);

	void SetCursorPos(const Point& pos);
	void ShowCursor(bool show);

	bool IsKeyDown(int key);
	bool IsKeyUp(int key);

public:
	static InputSystem* get();

private:
	std::unordered_set<InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;
};

