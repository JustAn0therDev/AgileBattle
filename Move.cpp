#include "Move.hpp"

Move::Move(float damage, float healing, const char* name, const char* details)
{
	m_Damage = damage;
	m_Healing = healing;
	m_Name = name;
	m_Details = details;
}