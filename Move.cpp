#include "Move.hpp"

Move::Move(float damage, float healing, const char* name, const char* details)
{
	m_Damage = damage;
	m_Healing = healing;
	m_Name = name;
	m_Details = details;
}

float Move::GetDamage() const
{
	return m_Damage;
}

float Move::GetHealing() const
{
	return m_Healing;
}

const char* Move::GetName() const
{
	return m_Name;
}

const char* Move::GetDetails() const
{
	return m_Details;
}
