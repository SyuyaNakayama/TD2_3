#include "Player.h"
#include "ImGuiManager.h"
#include "CollisionManager.h"
#include <imgui.h>

void Player::Initialize()
{
	//モデル読み込み
	model_ = Model::Create();							// 大元
	modelBody_ = Model::CreateFromOBJ("player_body");	// 体
	modelLegL_ = Model::CreateFromOBJ("player_legL");	// 左足
	modelLegR_ = Model::CreateFromOBJ("player_legR");	// 右足

	worldTransform.Initialize();
	worldTransform.scale_.x = 0.9999f;
	worldTransform.translation_ = { 76.0f ,-76.0f + epsilon,0 };
	jump.SetGravity(0.08f);
	SetCollisionAttribute(CollisionAttribute::Player);
	SetCollisionMask(CollisionMask::Player);
}

void Player::Move()
{
	worldTransform.translation_.x += spdX;
}

void Player::Update()
{
	// 落下チェック(ジャンプ中でないとき)
	if (!jump.IsJump())
	{
		worldTransform.translation_.y -= epsilon;
		worldTransform.Update();
		isFallCheck = true;
		CollisionManager::CheckBoxCollisions();
		worldTransform.translation_.y += epsilon;

		// 下に地面がなかったら落下
		if (isFallCheck)
		{
			jump.StartFall();
			isFallCheck = false;
			jump.UpdateFall(worldTransform.translation_.y);
		}
	}
	if (!jump.IsFall())
	{
		Move();
		jump.UpdateJump(worldTransform.translation_.y);
	}
	worldTransform.Update();
}

void Player::Draw()
{
	model_->Draw(worldTransform, *ViewProjection::GetInstance());
}

void Player::OnCollision(BoxCollider* boxCollider)
{
	if (isFallCheck)
	{
		// 落下チェックのときは終了
		isFallCheck = false;
		return;
	}

	float blockTopPosition = boxCollider->GetWorldPosition().y + boxCollider->GetRadius().y;
	if (jump.IsFall())
	{
		// 落下中に地面に当たったら落下終了
		jump.EndFall();
		worldTransform.translation_.y = blockTopPosition + epsilon + GetRadius().y;
		return;
	}

	float playerTopPosition = GetWorldPosition().y + GetRadius().y;

	if (blockTopPosition - playerTopPosition <= epsilon)
	{
		// 高さ1マスならジャンプ
		jump.StartJump(0.5f, blockTopPosition + epsilon + GetRadius().y);
		return;
	}

	// それ以外なら撥ね返る
	spdX = -spdX;
}