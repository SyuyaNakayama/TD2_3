#pragma once
#include "Block.h"
#include <list>
#include <array>
#include <memory>

class BlockManager
{
private:
	enum class BlockType { None, Normal, Move, Copy, Destroy, Ladder, Goal, NonCollisionNormal };
	static const UINT16 STAGE_SIZE = 40;

	std::list<std::unique_ptr<BaseBlock>> blocks;
	std::array<std::array<BlockType, STAGE_SIZE>, STAGE_SIZE> map{};

	void LoadMap(const std::string& fileName);
	BlockManager() = default;
	void CreateBlock(Vector3 pos, BlockType type);
	void CreateBlocks();
	BlockType IntToBlockType(int num);
public:
	BlockManager(const BlockManager& obj) = delete;
	static BlockManager* GetInstance();

	void Initialize(UINT16 stage);
	void Update();
	void Draw();
};