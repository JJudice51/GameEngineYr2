#pragma once
#include "Engine/Scene.h"

class GameEngine::Entity;

class TestScene : public GameEngine::Scene
{
public:
	void onStart() override;
	void onUpdate(double DeltaTime) override;

private:
	GameEngine::Entity* m_circle1;
	GameEngine::Entity* m_circle2;


};