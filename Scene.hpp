#pragma once
#include <vector>
#include "Entity.hpp"
#include "Ui.hpp"

class Scene {
public:
	Scene() = default;
	virtual void Update() {};
};