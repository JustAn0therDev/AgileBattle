#pragma once

class Move {
private:
	float m_Damage;
	float m_Healing;
	const char* m_Name;
	const char* m_Details;
public:
	Move(float damage, float healing, const char* name, const char* details);

	float GetDamage() const;

	float GetHealing() const;

	const char* GetName() const;

	const char* GetDetails() const;
};