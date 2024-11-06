#pragma once
#include "Point.h"

class InputListener {
public:
	InputListener() {

	}

	~InputListener() {

	}

	// KEYBOARD pure virtual callback functions
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	// MOUSE pure virtual callback functions
	virtual void OnMouseMove(const Point& mouse_pos) = 0;
	virtual void OnLeftMouseDown(const Point& mouse_pos) = 0;
	virtual void OnLeftMouseUp(const Point& mouse_pos) = 0;
	virtual void OnRightMouseDown(const Point& mouse_pos) = 0;
	virtual void OnRightMouseUp(const Point& mouse_pos) = 0;
};