#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include <chrono>
#include <cmath>

void TestScene::onStart()
{
	//input system is not necessary for the assessment but could be a good coding practice to make an input class and some wrapper functions 
	//GameEngine::Entity* player1;
	//1 make an entity*
	//2 make shapecomponent*
	//3 add shapecomponent* to entity*
	//4 add entity to the scene

	m_entity = new GameEngine::Entity();
	m_entity->getTransform()->setLocalScale({ 100,100 });
	m_entity->getTransform()->setLocalPosition({ 400, 400 });

	GameGraphics::ShapeComponent* shapeComponent = new GameGraphics::ShapeComponent();
	shapeComponent->setShapeType(GameGraphics::ShapeType::CIRCLE);
	shapeComponent->setColor(0xFF00FFFF);
	m_entity->addComponent(shapeComponent);
	
	addEntity(m_entity);
}

void TestScene::onUpdate(double DeltaTime)
{
	m_accumulatedTime += DeltaTime;

	float currentTime =
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	float circleRadius = 100;
	GameMath::Vector2 newPosition = {
		sin(currentTime) * circleRadius + 400,
		cos(currentTime) * circleRadius + 400};

	m_entity->getTransform()->setLocalPosition(newPosition);
}
