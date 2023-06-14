#pragma once
#include "Entity.hpp"
#include "Move.hpp"

class Action {
private:
	Entity* m_Entity;
	Move* m_Move;
public:
	Action(Entity* entity, Move* move);

};