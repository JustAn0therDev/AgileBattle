#include "Move.hpp"
#include "MoveType.hpp"

Move::Move(float damage, float healing, const char* name, const char* details, MoveType moveType)
{
	m_Damage = damage;
	m_Healing = healing;
	m_Name = name;
	m_Details = details;
	m_MoveType = moveType;
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

MoveType Move::GetMoveType() const
{
	return m_MoveType;
}
