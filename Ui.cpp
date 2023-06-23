#include "Ui.hpp"
#include "Animation.hpp"
#include "Constants.hpp"
#include <string>
#include <raymath.h>
#include <vector>


void Ui::DrawDamageAnimation()
{
	m_CurrentDrawDamagePos.y = Lerp(m_CurrentDrawDamagePos.y, m_DesiredDrawDamagePos.y, 0.03f);
	
	if (floorf(m_CurrentDrawDamagePos.y) == floorf(m_DesiredDrawDamagePos.y)) {
		m_RunningDamageAnimation = false;
	}

	DrawTextEx(m_Font, 
		std::to_string(m_DamageDrawValue).c_str(),
        m_CurrentDrawDamagePos, 
		m_DefaultFontSize, 
		m_DefaultFontSpacing, 
		WHITE);
}

void Ui::DrawContextMenu()
{
	std::string arrowBuffer = "->";

	if (m_ActiveUiState == ActiveUiState::MOVE) {
		std::vector<Move*> entityMovements = m_SelectedEntity->GetMoves();

		Vector2 moveOptionPos = m_MoveTextPos;

		int moveOptionY = 0;

		for (const auto& move : entityMovements) {
			moveOptionPos.y += moveOptionY;

			const char* name = move->GetName();
			const char* details = move->GetDetails();

			Vector2 nameTextSize = MeasureTextEx(m_Font, name, m_DefaultFontSize, m_DefaultFontSpacing);
			Vector2 detailsTextSize = MeasureTextEx(m_Font, details, m_DefaultFontSize, m_DefaultFontSpacing);

			Rectangle nameRec = { 0.0f, 0.0f, nameTextSize.x, nameTextSize.y - 25 };
			Rectangle detailsRec = { 0.0f, 0.0f, detailsTextSize.x, detailsTextSize.y - 25 };

			if (IsCursorOn(moveOptionPos, nameRec)) {
				DrawTextEx(m_Font, arrowBuffer.append(name).c_str(), moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					m_SelectedMove = move;
					m_ActiveUiState = ActiveUiState::SELECTING_TARGET;
				}
			}
			else {
				DrawTextEx(m_Font, name, moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
			}

			Vector2 moveDescriptionPos = { moveOptionPos.x + 400, moveOptionPos.y };

			DrawTextEx(m_Font, details, moveDescriptionPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);

			moveOptionY += 50;
		}
	}
	else if (m_ActiveUiState == ActiveUiState::SELECTING_TARGET) {
		DrawTextEx(m_Font, "Escolha um alvo para usar seu movimento!", m_MoveTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
	}
}

Ui::Ui() : m_CursorPosition({ 0.0f, 0.0f })
{
	m_DefaultFontSize = 72.0f;
	m_DefaultFontSpacing = 2.0f;
	m_Font = LoadFontEx(
		"Assets\\Fonts\\Cloude_Regular_Bold_1.03.otf",
		static_cast<int>(m_DefaultFontSize),
		0,
		256);
	m_SelectedEntity = NULL;
	m_HoveringEntity = NULL;
	m_SelectedTarget = NULL;
	
	m_UpperTextBoxHeightLimit = 590.0f;
	m_LowerTextBoxHeightLimit = 794.0f;
	m_TextBoxWidthLimit = 35.0f;
	
	m_HealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\health_bar.png");
	m_EmptyHealthBarTexture2D = LoadTexture("Assets\\Images\\Health\\empty_bar.png");
	
	m_MoveTextPos = { m_TextBoxWidthLimit, m_UpperTextBoxHeightLimit };
	
	m_ActiveUiState = ActiveUiState::IDLE;
	m_SelectedMove = NULL;

	m_RunningDamageAnimation = false;
}

const Font& Ui::GetFont() {
	return m_Font;
}

bool Ui::IsCursorOn(Vector2 pos, Rectangle entityAreaRec)
{
	return m_CursorPosition.x >= pos.x &&
		   m_CursorPosition.x <= (pos.x + entityAreaRec.width) &&
		   m_CursorPosition.y >= pos.y &&
		   m_CursorPosition.y <= (pos.y + entityAreaRec.height);
}

bool Ui::IsCursorOn(Vector2 pos) {
	return m_CursorPosition.x >= pos.x &&
		  m_CursorPosition.x <= pos.x &&
		  m_CursorPosition.y >= pos.y &&
		  m_CursorPosition.y <= pos.y;
}

Vector2 Ui::GetCursorPosition()
{
	return m_CursorPosition;
}

void Ui::Update(Entity* entity) {
	// TODO: Input should be managed here, not in the draw method.
	m_CursorPosition = GetMousePosition();

	if (m_RunningDamageAnimation) {
		DrawDamageAnimation();
	}

	if (entity != NULL) {
		Vector2 entityPos = entity->GetPosition();
		Rectangle rec = entity->GetCurrentAnimation()->GetAnimationRectangle();

		bool isCursorOn = IsCursorOn(entityPos, rec);

		bool isCursorOnMenu = m_UpperTextBoxHeightLimit <= m_CursorPosition.y;

		if (isCursorOn) {
			m_HoveringEntity = entity;
		}
		else if (!isCursorOn && entity == m_HoveringEntity) {
			m_HoveringEntity = NULL;
		}

		if (m_ActiveUiState == ActiveUiState::SELECTING_TARGET) {
			if (isCursorOn && entity->GetEntityType() == EntityType::Enemy && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				m_SelectedTarget = entity;
				m_RunningDamageAnimation = true;

				// TESTING THE DAMAGE SHOW ANIMATION
				Vector2 entityPos = m_SelectedTarget->GetPosition();
				Rectangle rec = m_SelectedTarget->GetCurrentAnimation()->GetAnimationRectangle();

				m_DamageDrawValue = static_cast<int>(m_SelectedMove->GetDamage());

				Vector2 damageTextSize = 
					MeasureTextEx(
						m_Font, 
						std::to_string(m_DamageDrawValue).c_str(), 
						m_DefaultFontSize, 
						m_DefaultFontSpacing);

				m_CurrentDrawDamagePos = { (entityPos.x + (rec.width / 2.0f) - (damageTextSize.x / 2)), entityPos.y - (rec.height / 2.0f) };

				m_DesiredDrawDamagePos = m_CurrentDrawDamagePos;
				m_DesiredDrawDamagePos.y -= 50.0f;
			}
		}
		else {
			if (entity->GetEntityType() == EntityType::TeamMember && !entity->HasAttackedThisTurn()) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					if (isCursorOn) {
						m_SelectedEntity = entity;
						m_ActiveUiState = ActiveUiState::MOVE;
					}
					else if (!isCursorOn && entity == m_SelectedEntity && !isCursorOnMenu) {
						m_SelectedEntity = NULL;
						// The player is not selecting anything, so there is no way to show the character's moves.
						m_ActiveUiState = ActiveUiState::IDLE;
					}
				}
			}
		}
	}

	Draw();
}

void Ui::Draw() {
	// We know that entities have health;
	// so all entities should have their health drawn on screen.
	// But their health should be managed by the battle system, not by the UI.
	// The UI should only reflect the health's current state.
	if (m_SelectedEntity != NULL) {
		Color color = m_SelectedEntity->GetEntityType() == EntityType::Enemy ? RED : GREEN;

		Vector2 entityPos = m_SelectedEntity->GetPosition();
		Rectangle rec = m_SelectedEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, color);
		
		// Draw the entity's name on top of it.
		const char* entityName = m_SelectedEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);
		
		Vector2 entityInfoPos = { 
			(entityPos.x + (rec.width / 2.0f) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityInfoPos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);

		Rectangle emptyBarRectangle = { 
			0.0f,
			0.0f,
			static_cast<float>(m_EmptyHealthBarTexture2D.width),
			static_cast<float>(m_EmptyHealthBarTexture2D.height / 4.0f)
		};

		entityInfoPos.x =
			static_cast<float>(entityPos.x + (rec.width / 2)) - static_cast<float>((m_EmptyHealthBarTexture2D.width / 2));
		entityInfoPos.y -= 10.0f;

		DrawHpBar(m_SelectedEntity, rec, entityInfoPos);

		// We can only have a context menu if an entity has been selected.
		if (m_SelectedEntity->GetEntityType() == EntityType::TeamMember && !m_SelectedEntity->HasAttackedThisTurn()) {
			DrawContextMenu();
		}
	}

	if (m_HoveringEntity != NULL && m_SelectedEntity != m_HoveringEntity) {
		Vector2 entityPos = m_HoveringEntity->GetPosition();
		Rectangle rec = m_HoveringEntity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, BLACK);

		// Draw the entity's name.
		const char* entityName = m_HoveringEntity->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);

		Vector2 entityInfoPos = { 
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityInfoPos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);

		entityInfoPos.x =
			static_cast<float>(entityPos.x + (rec.width / 2)) - static_cast<float>((m_EmptyHealthBarTexture2D.width / 2));
		entityInfoPos.y -= 10.0f;

		DrawHpBar(m_HoveringEntity, rec, entityInfoPos);
	}

	if (m_SelectedTarget != NULL) {
		Vector2 entityPos = m_SelectedTarget->GetPosition();
		Rectangle rec = m_SelectedTarget->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, RED);

		// Draw the entity's name.
		const char* entityName = m_SelectedTarget->GetName();

		Vector2 textSize = MeasureTextEx(m_Font, entityName, m_DefaultFontSize, m_DefaultFontSpacing);

		Vector2 entityInfoPos = {
			static_cast<float>((entityPos.x + (rec.width / 2)) - (textSize.x / 2)),
			entityPos.y - 90.0f };

		DrawTextEx(m_Font,
			entityName,
			entityInfoPos,
			m_DefaultFontSize,
			m_DefaultFontSpacing,
			WHITE);

		entityInfoPos.x =
			static_cast<float>(entityPos.x + (rec.width / 2)) - static_cast<float>((m_EmptyHealthBarTexture2D.width / 2));
		entityInfoPos.y -= 10.0f;

		DrawHpBar(m_SelectedTarget, rec, entityInfoPos);
	}

	// Creating the mouse cursor
	Vector2 mouseCursorTrianglePoint = { m_CursorPosition.x, m_CursorPosition.y };
	Vector2 mouseCursorTrianglePoint2 = { m_CursorPosition.x, m_CursorPosition.y + 15 };
	Vector2 mouseCursorTrianglePoint3 = { m_CursorPosition.x + 10, m_CursorPosition.y + 10 };

	// Drawing mouse cursor. It should be always drawn after everything, so it stays
	// on top of all the game's content.
	DrawTriangle(
		mouseCursorTrianglePoint,
		mouseCursorTrianglePoint2,
		mouseCursorTrianglePoint3,
		BLACK);
}

void Ui::DrawHpBar(Entity* entity, Rectangle entityRectangle, Vector2 position) const {
	Rectangle emptyBarRectangle = {
		0.0f,
		0.0f,
		static_cast<float>(m_EmptyHealthBarTexture2D.width),
		static_cast<float>(m_EmptyHealthBarTexture2D.height / 4)
	};

	Rectangle healthBarRectangle = {
	0.0f,
	0.0f,
	static_cast<float>(Clamp(entity->GetHealthPoints(), 0, 98)),
	static_cast<float>(m_HealthBarTexture2D.height / 4)
	};

	DrawTextureRec(m_EmptyHealthBarTexture2D, emptyBarRectangle, position, WHITE);
	DrawTextureRec(m_HealthBarTexture2D, healthBarRectangle, position, WHITE);
}

Entity* Ui::GetSelectedTarget() const {
	return m_SelectedTarget;
}

Entity* Ui::GetSelectedEntity() const {
	return m_SelectedEntity;
}

const Move* Ui::GetSelectedMove() const {
	return m_SelectedMove;
}

void Ui::SetSelectedEntity(Entity* entity)
{
	m_SelectedEntity = entity;
}

void Ui::SetSelectedTarget(Entity* entity)
{
	m_SelectedTarget = entity;
}

void Ui::RemoveSelectedMove() {
	m_SelectedMove = NULL;
}

void Ui::RemoveSelectedTarget()
{
	m_SelectedTarget = NULL;
}

void Ui::RemoveHoveringEntity()
{
	m_HoveringEntity = NULL;
}

void Ui::RemoveSelectedEntity()
{
	m_SelectedEntity = NULL;
}

void Ui::ChangeUiState(ActiveUiState activeUiState) {
	m_ActiveUiState = activeUiState;
}

void Ui::ResetUiState()
{
	RemoveSelectedEntity();
	RemoveHoveringEntity();
	RemoveSelectedMove();
	RemoveSelectedTarget();
	ChangeUiState(ActiveUiState::IDLE);
}
