#include "ClearScene.h"
#include "GameScene.h"
#include "Quaternion.h"

void ClearScene::Initialize()
{
	*GameScene::GetStage() = 5;
	gameScene = GameScene::GetInstance();
	viewProjection->target = {};
	viewProjection->eye = { 0,-1200,0 };
	viewProjection->up = upVector;
	BlockManager::GetInstance()->Initialize();
}

void ClearScene::Update()
{
	Quaternion rotaQ = { std::cos(cameraUpAngle / 2.0f) ,Vector3(0,1,0) * std::sin(cameraUpAngle / 2.0f) };
	viewProjection->up = RotateVector(Vector3(-1, 0, 0), rotaQ);
	cameraUpAngle += upRotSpd;
	if (input->TriggerKey(DIK_SPACE))
	{
		isNextScene = true;
		upRotSpd = 0.075f;
	}
	if (!isNextScene) { return; }
	if (timer.CountDown()) { gameScene->SetNextScene(Scene::Title); }
}

void ClearScene::Draw()
{
	Model::PreDraw(cmdList);
	blockManager->Draw();
	Model::PostDraw();
}