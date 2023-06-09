#include "Ui.hpp"
#include "Animation.hpp"
#include "Constants.hpp"
#include <string>
#include <raymath.h>
#include <vector>

void Ui::ExecuteDrawDamageAnimation()
{
	Color color;

	if (m_DamageHasModifier) {
		color = GREEN;
	}
	else {
		color = WHITE;
	}

	m_CurrentDrawDamagePos.y = Lerp(m_CurrentDrawDamagePos.y, m_DesiredDrawDamagePos.y, 0.03f);
	
	if (floorf(m_CurrentDrawDamagePos.y) == floorf(m_DesiredDrawDamagePos.y)) {
		m_RunningDamageAnimation = false;
	}

	DrawTextEx(m_Font,
		std::to_string(m_DamageDrawValue).c_str(),
        m_CurrentDrawDamagePos,
		m_DefaultFontSize,
		m_DefaultFontSpacing,
		color);
}

void Ui::SetupDrawDamageAnimation()
{
	m_RunningDamageAnimation = true;
	Vector2 entityPos = m_SelectedTarget->GetPosition();
	Rectangle rec = m_SelectedTarget->GetCurrentAnimation()->GetAnimationRectangle();

	m_DamageHasModifier = m_SelectedMove->GetMoveType() == m_SelectedTarget->GetWeakness();

	if (m_DamageHasModifier) {
		m_DamageDrawValue = static_cast<int>(m_SelectedMove->GetDamage() * Constants::DAMAGE_MODIFIER);
	}
	else {
		m_DamageDrawValue = static_cast<int>(m_SelectedMove->GetDamage());
	}

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

void Ui::UpdateContextMenu()
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
				DrawTextEx(m_Font, arrowBuffer.append(name).c_str(), moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, YELLOW);

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					m_SelectedMove = move;
					m_ActiveUiState = ActiveUiState::SELECTING_TARGET;
					PlaySound(m_BlinkSound);
				}
			}
			else {
				DrawTextEx(m_Font, name, moveOptionPos, m_DefaultFontSize, m_DefaultFontSpacing, YELLOW);
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

	m_CurrentDrawDamagePos = Vector2Zero();
	m_DesiredDrawDamagePos = Vector2Zero();
	m_DamageDrawValue = 0;
	m_DamageHasModifier = false;
	m_LockedBy = LockContext::NoLocks;

	m_PlayerLost = false;
	m_PlayerWon = false;

	m_BlinkSound = LoadSound("Assets\\Audio\\Sound Effects\\Blink Sound Effect.wav");
	SetSoundVolume(m_BlinkSound, Constants::SOUND_VOLUME);
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
	m_CursorPosition = GetMousePosition();

	if (m_RunningDamageAnimation) {
		ExecuteDrawDamageAnimation();
	}

	if (entity != NULL && m_LockedBy == LockContext::NoLocks && !m_PlayerWon && !m_PlayerLost) {
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
			if (isCursorOn && entity->GetEntityType() == EntityType::Enemy && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && entity->GetHealthPoints() > 0) {
				m_SelectedTarget = entity;
				SetupDrawDamageAnimation();
				PlaySound(m_BlinkSound);
			}
		}
		else {
			if (entity->GetEntityType() == EntityType::TeamMember && 
				entity->GetHealthPoints() > 0.0f) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					if (isCursorOn) {
						m_SelectedEntity = entity;
						m_ActiveUiState = ActiveUiState::MOVE;
						PlaySound(m_BlinkSound);
					}
					else if (!isCursorOn && entity == m_SelectedEntity && !isCursorOnMenu && m_ActiveUiState != ActiveUiState::MOVE) {
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
	// If we have the menu in the IDLE state, we should show a message
	// to the player, indicating that they can act!
	if (m_ActiveUiState == ActiveUiState::IDLE) {
		DrawTextEx(m_Font, "Selecione um membro do time para agir!", m_MoveTextPos, m_DefaultFontSize, m_DefaultFontSpacing, WHITE);
	}

	// We know that entities have health;
	// so all entities should have their health drawn on screen.
	// But their health should be managed by the battle system, not by the UI.
	// The UI should only reflect the health's current state.
	if (m_SelectedEntity != NULL) {
		DrawEntityInformation(m_SelectedEntity);

		// We can only have a context menu if an entity has been selected.
		if (m_SelectedEntity->GetEntityType() == EntityType::TeamMember) {
			UpdateContextMenu();
		}
	}

	if (m_HoveringEntity != NULL && m_SelectedEntity != m_HoveringEntity && m_ActiveUiState != ActiveUiState::MOVE) {
		DrawEntityInformation(m_HoveringEntity);
	}

	if (m_SelectedTarget != NULL) {
		DrawEntityInformation(m_SelectedTarget);
	}

	if (m_PlayerWon) {
		DrawWinText();
	}
	else if (m_PlayerLost) {
		DrawLoseText();
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

void Ui::DrawEntityInformation(Entity* entity) const
{
	if (entity != NULL) {
		Color color = entity->GetEntityType() == EntityType::Enemy ? RED : GREEN;

		Vector2 entityPos = entity->GetPosition();
		Rectangle rec = entity->GetCurrentAnimation()->GetAnimationRectangle();

		Vector2 trianglePoint1 = { entityPos.x + (rec.width / 2) + 15, entityPos.y - 25 };
		Vector2 trianglePoint2 = { entityPos.x + (rec.width / 2) - 15, entityPos.y - 25 };
		Vector2 trianglePoint3 = { entityPos.x + (rec.width / 2), entityPos.y - 10 };

		DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, color);

		// Draw the entity's name on top of it.
		const char* entityName = entity->GetName();

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

		DrawHpBar(entity, rec, entityInfoPos);
	}
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

void Ui::SetSelectedMove(Move* move)
{
	m_SelectedMove = move;
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

void Ui::Lock(LockContext lockContext)
{
	m_LockedBy = lockContext;
}

void Ui::ReleaseLock() 
{
	m_LockedBy = LockContext::NoLocks;
}

const LockContext Ui::GetLockContext() const
{
	return m_LockedBy;
}

void Ui::SetPlayerWon()
{
	m_PlayerWon = true;
}

void Ui::SetPlayerLost()
{
	m_PlayerLost = true;
}

const float Ui::GetFontSize() const
{
	return m_DefaultFontSize;
}

const float Ui::GetFontSpacing() const
{
	return m_DefaultFontSpacing;
}

Ui::~Ui()
{
	UnloadSound(m_BlinkSound);

	UnloadFont(m_Font);
}

void Ui::DrawWinText() const
{
	const char* winText = "VOCE VENCEU!";
	
	Vector2 textSize = MeasureTextEx(m_Font, winText, m_DefaultFontSize, m_DefaultFontSpacing);

	Vector2 textPos = { (Constants::DEFAULT_WIDTH / 2) - (textSize.x / 2), (Constants::DEFAULT_HEIGHT / 2) - (textSize.y / 2) };

	DrawTextEx(m_Font, winText, textPos, m_DefaultFontSize, m_DefaultFontSpacing, GREEN);
}

void Ui::DrawLoseText() const
{
	const char* loseText = "VOCE PERDEU!";

	Vector2 textSize = MeasureTextEx(m_Font, loseText, m_DefaultFontSize, m_DefaultFontSpacing);

	Vector2 textPos = { (Constants::DEFAULT_WIDTH / 2) - (textSize.x / 2), (Constants::DEFAULT_HEIGHT / 2) - (textSize.y / 2) };

	DrawTextEx(m_Font, loseText, textPos, m_DefaultFontSize, m_DefaultFontSpacing, RED);
}
