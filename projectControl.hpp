#pragma once
#include "windowControl.hpp"
#include "object.hpp"

class projectControl {
public:
	projectControl();

	void run();

private:
	void render();
	void update();

	windowControl window_control;
	object object_control;
};