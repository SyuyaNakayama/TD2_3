#pragma once
#include "Sprite.h"
#include "BaseScene.h"

class TitleScene : public BaseScene
{
private:

public:
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};