#pragma once
#include "Engine/Scene.h"

class TestScene : public GameEngine::Scene
{
public:
	void onStart() override;
	void onUpdate(double DeltaTime) override;

private:
	GameEngine::Entity* m_entity;
	float m_accumulatedTime;


};