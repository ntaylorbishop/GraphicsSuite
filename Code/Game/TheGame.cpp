#include "Game/TheGame.hpp"

TheGame* g_theGame = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS AND INITIALIZATION
//---------------------------------------------------------------------------------------------------------------------------
TheGame::TheGame() {
	g_theCamera = new TheCamera(Vector3(0.f, -1.f, 0.f), 0.f, 0.f, 0.f);
	g_theApparatusEngine->BindKeyToConsole(VK_F1);

	g_theLightSystem = new LightSystem();

	RegisterCommands();

	m_cubes.reserve(32);

	for (unsigned int x = 0; x < 4; x++) {
		for (unsigned int y = 0; y < 4; y++) {
			m_cubes.push_back(Cube(Vector3(x * 5.f, y * 5.f, 0.f)));
			m_cubes.push_back(Cube(Vector3(x * 5.f, y * 5.f, 8.f)));
		}
	}

	m_cubes.push_back(Cube(Vector3(-5.f, -0.f, 0.f)));
}
TheGame::~TheGame() {
	delete g_theLightSystem;
	g_theLightSystem = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);

	g_theCamera->Update(deltaSeconds);

	if (g_theApp->HasFocus()) {
		HandlePlayerLook();
		HandlePlayerMovement(deltaSeconds);
	}


	g_theLightSystem->Update(deltaSeconds);
	g_theDebugRenderer->DrawDebugAxis(Vector3::ZERO, 10.f, DEBUG_DRAW_DEPTH_TEST_ON);

	//UpdateMaterials();
	for (unsigned int i = 0; i < m_cubes.size(); i++) {
		m_cubes[i].Update(deltaSeconds);
	}
}

void TheGame::UpdateMaterials() const {
	std::vector<Light3D> lights = g_theLightSystem->GetLights();
	int lightCount = lights.size();

	Material* brick = g_theMaterialManager->GetMaterial("Brick");
	
	Uniform_INT* gLightCount = static_cast<Uniform_INT*>(brick->GetUniform("gLightCount"));
	Uniform_VECTOR3* gCameraPosition = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gCameraPosition"));
	Uniform_MAT4* gView = static_cast<Uniform_MAT4*>(brick->GetUniform("gView"));
	Uniform_MAT4* gProj = static_cast<Uniform_MAT4*>(brick->GetUniform("gProj"));

	gLightCount->SetData(lightCount);
	gCameraPosition->SetData(g_theCamera->m_position);
	gView->SetData(g_theRenderer->GetViewMatrix());
	gProj->SetData(g_theRenderer->GetProjectionMatrix());
	
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightCount);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gCameraPosition);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gView);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gProj);

	Uniform_VECTOR3* gLightPosition = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gLightPosition"));
	Uniform_VECTOR3* gLightDirection = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gLightDirection"));
	Uniform_RGBA* gLightColor = static_cast<Uniform_RGBA*>(brick->GetUniform("gLightColor"));
	Uniform_FLOAT* gMinLightDistance = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMinLightDistance"));
	Uniform_FLOAT* gMaxLightDistance = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMaxLightDistance"));
	Uniform_FLOAT* gMinLightPower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMinLightPower"));
	Uniform_FLOAT* gMaxLightPower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMaxLightPower"));
	Uniform_FLOAT* gInterpolateAttenuation = static_cast<Uniform_FLOAT*>(brick->GetUniform("gInterpolateAttenuation"));
	Uniform_FLOAT* gThetaInner = static_cast<Uniform_FLOAT*>(brick->GetUniform("gThetaInner"));
	Uniform_FLOAT* gThetaOuter = static_cast<Uniform_FLOAT*>(brick->GetUniform("gThetaOuter"));
	Uniform_FLOAT* gLightInsidePower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gLightInsidePower"));
	Uniform_FLOAT* gLightOutsidePower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gLightOutsidePower"));

	std::vector<Vector3> lightPositions;
	std::vector<Vector3> lightDirections;
	std::vector<RGBA> lightColors;
	std::vector<float> minLightDists;
	std::vector<float> maxLightDists;
	std::vector<float> minLightPowers;
	std::vector<float> maxLightPowers;
	std::vector<float> dirInterps;
	std::vector<float> thetaInners;
	std::vector<float> thetaOuters;
	std::vector<float> lightInsidePowers;
	std::vector<float> lightOutsidePowers;

	for (unsigned int i = 0; i < lightCount; i++) {
		lightPositions.push_back(lights[i].GetPosition());
		lightDirections.push_back(lights[i].GetDirection());
		lightColors.push_back(lights[i].GetColor());
		minLightDists.push_back(lights[i].GetMinLightDistance());
		maxLightDists.push_back(lights[i].GetMaxLightDistance());
		minLightPowers.push_back(lights[i].GetPowerAtMin());
		maxLightPowers.push_back(lights[i].GetPowerAtMax());
		dirInterps.push_back(lights[i].GetIsDirectionInterpolated());
		thetaInners.push_back(lights[i].GetInnerTheta());
		thetaOuters.push_back(lights[i].GetOuterTheta());
		lightInsidePowers.push_back(lights[i].GetThetaInnerPower());
		lightOutsidePowers.push_back(lights[i].GetThetaOuterPower());
	}
		

	gLightPosition->SetData(lightPositions);
	gLightDirection->SetData(lightDirections);
	gLightColor->SetData(lightColors);
	gMinLightDistance->SetData(minLightDists);
	gMaxLightDistance->SetData(maxLightDists);
	gMinLightPower->SetData(minLightPowers);
	gMaxLightPower->SetData(maxLightPowers);
	gInterpolateAttenuation->SetData(dirInterps);
	gThetaInner->SetData(thetaInners);
	gThetaOuter->SetData(thetaOuters);
	gLightInsidePower->SetData(lightInsidePowers);
	gLightOutsidePower->SetData(lightOutsidePowers);

	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightPosition);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightDirection);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightColor);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMinLightDistance);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMaxLightDistance);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMinLightPower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMaxLightPower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gInterpolateAttenuation);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gThetaInner);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gThetaOuter);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightInsidePower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightOutsidePower);

}

//---------------------------------------------------------------------------------------------------------------------------
//RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::SetUpPerspectiveProjection() const {
	float aspect = 16.f / 9.f;
	float fovDegreesVertical = 90.f;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 100.f;

	g_theRenderer->SetPerspective(fovDegreesVertical, aspect, nearClippingPlane, farClippingPlane);

	g_theRenderer->EnableDepthTesting();
	g_theRenderer->EnableBackfaceCulling();
	g_theRenderer->EnableAlphaTesting();

	//NEW WAY
	Vector3 cameraRotation = Vector3(g_theCamera->m_pitchAboutX, g_theCamera->m_rollAboutY, g_theCamera->m_yawAboutZ);
	g_theRenderer->SetCamera3D(Vector3(cameraRotation), g_theCamera->m_position);

	//OLD WAY
	g_theRenderer->RotateViewMatrix(-90.f, Vector3(1.f, 0.f, 0.f)); //Put z up
	g_theRenderer->RotateViewMatrix(-g_theCamera->m_rollAboutY, Vector3(1.f, 0.f, 0.f));
	g_theRenderer->RotateViewMatrix(-g_theCamera->m_pitchAboutX, Vector3(0.f, 1.f, 0.f));
	g_theRenderer->RotateViewMatrix(g_theCamera->m_yawAboutZ, Vector3(0.f, 0.f, 1.f));
	g_theRenderer->TranslateViewMatrix(Vector3(-g_theCamera->m_position.x, -g_theCamera->m_position.y, -g_theCamera->m_position.z));
}
void TheGame::Render() const {

	//Render 3D
	SetUpPerspectiveProjection();

	UpdateMaterials();

	g_theLightSystem->Render();

	for (unsigned int i = 0; i < m_cubes.size(); i++) {
		m_cubes[i].Render();
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//USER INPUT
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::HandlePlayerLook() {
	IntVector2 cursorDelta = g_theApp->GetCursorDelta();
	g_theInputSystem->HideMouseCursor();

	if (g_theCamera->m_rollAboutY <= 89.f && cursorDelta.y < 0.f) {
		g_theCamera->m_rollAboutY -= (float)cursorDelta.y * MOUSE_SENSITIVITY;
	}
	else if(g_theCamera->m_rollAboutY >= -89.f && cursorDelta.y > 0.f) {
		g_theCamera->m_rollAboutY -= (float)cursorDelta.y * MOUSE_SENSITIVITY;
	}

	g_theCamera->m_yawAboutZ += (float)cursorDelta.x * MOUSE_SENSITIVITY;
}
void TheGame::HandlePlayerMovement(float deltaSeconds) {
	float moveSpeed = PLAYER_MOVE_SPEED * deltaSeconds;

	//g_theDebugRenderer->DrawDebugSphere(Vector3(10.f, 10.f, 0.f), 2.f, RGBA::WHITE, DEBUG_DRAW_DEPTH_TEST_DUAL);

	//FORWARD BACKWARD
	if (g_theInputSystem->GetKey('D')) {
		g_theCamera->m_position += g_theCamera->GetForwardXY() * moveSpeed; //Forward
	}
	else if (g_theInputSystem->GetKey('A')) {
		g_theCamera->m_position += g_theCamera->GetForwardXY() * -moveSpeed; //Backward
	}
	//LEFT RIGHT
	if (g_theInputSystem->GetKey('W')) {
		g_theCamera->m_position += g_theCamera->GetLeftXY() * moveSpeed; //Left
	}
	else if (g_theInputSystem->GetKey('S')) {
		g_theCamera->m_position += g_theCamera->GetLeftXY() * -moveSpeed; //Right
	}

	//UP DOWN
	if (g_theInputSystem->GetKey(VK_SPACE)) {
		g_theCamera->m_position += Vector3(0.f, 0.f, moveSpeed); //Up
	}
	else if (g_theInputSystem->GetKey('C')) {
		g_theCamera->m_position += Vector3(0.f, 0.f, -moveSpeed); //Down
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//CONSOLE SETUP
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::RegisterCommands() {
	g_theApparatusEngine->RegisterCommandToConsole("add", Add);
}

//---------------------------------------------------------------------------------------------------------------------------
//COMMANDS
//---------------------------------------------------------------------------------------------------------------------------
void Add(Command& args) {
	int arg0, arg1, arg2;

	args.GetNextInt(arg0);
	args.GetNextInt(arg1);
	args.GetNextInt(arg2);

	int sum = arg0 + arg1 + arg2;

	std::string strToPrint = StringUtils::Stringf("%i + %i + %i = %i", arg0, arg1, arg2, sum);

	g_theApparatusEngine->PrintOutputToConsole(strToPrint, CONSOLE_VERIFY);
}

//YOU CAN STILL USE GL_LINES

