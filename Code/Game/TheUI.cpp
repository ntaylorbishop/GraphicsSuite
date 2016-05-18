#include "Game/TheUI.hpp"

TheUI* g_theUI = nullptr;

//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
TheUI::TheUI() {
	m_squirrelFont = BitmapFont::CreateOrGetFont("SquirrelFixedFont");
}
TheUI::~TheUI() {

}

//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::Update(float deltaSeconds) {
	deltaSeconds = 0;
}
void TheUI::Render() const {
	g_theRenderer->SetOrtho2D(Vector2(0.f, 0.f), Vector2(1600.f, 900.f));

	RenderHUD();
	//RenderDebugText();
	RenderCrosshair();
}

//HUD
//---------------------------------------------------------------------------------------------------------------------------
void TheUI::RenderHUD() const {
	//Does nothing for right now
}
void TheUI::RenderDebugText() const {
	std::string velocity = StringUtils::Stringf("Position: (%3.2f, %3.2f, %3.2f)", g_theCamera->m_position.x, g_theCamera->m_position.y, g_theCamera->m_position.z);
	std::string rotation = StringUtils::Stringf("Roll: %3.2f Pitch: %3.2f Yaw: %3.2f", g_theCamera->m_rollAboutY, g_theCamera->m_pitchAboutX, g_theCamera->m_yawAboutZ);
	std::string help1 = StringUtils::Stringf("PULSING RED LOCAL CONE LIGHT IN BETWEEN BOXES");
	std::string help2 = StringUtils::Stringf("GREEN LOCAL POINT LIGHT IN BETWEEN BOXES");
	std::string help3 = StringUtils::Stringf("GLOBAL YELLOW POINT LIGHT IN SKY");
	std::string help4 = StringUtils::Stringf("GLOBAL BLUE CONE LIGHT IN SKY");

	m_squirrelFont->DrawText2D(Vector2(10.f, 850.f), velocity, 10.f, RGBA::YELLOW, NULL);
	m_squirrelFont->DrawText2D(Vector2(10.f, 880.f), rotation, 10.f, RGBA::YELLOW, NULL);
	m_squirrelFont->DrawText2D(Vector2(10.f, 700.f), help1, 12.f, RGBA::YELLOW, NULL);
	m_squirrelFont->DrawText2D(Vector2(10.f, 720.f), help2, 12.f, RGBA::YELLOW, NULL);
	m_squirrelFont->DrawText2D(Vector2(10.f, 740.f), help3, 12.f, RGBA::YELLOW, NULL);
	m_squirrelFont->DrawText2D(Vector2(10.f, 760.f), help4, 12.f, RGBA::YELLOW, NULL);

}
void TheUI::RenderCrosshair() const {
	g_theRenderer->BlendMode(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	g_theRenderer->DrawLine(Vector3(800.f, 440.f, 0.f), Vector3(800.f, 460.f, 0.f), RGBA::WHITE);
	g_theRenderer->DrawLine(Vector3(790.f, 450.f, 0.f), Vector3(810.f, 450.f, 0.f), RGBA::WHITE);
	g_theRenderer->BlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}