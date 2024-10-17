#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include <chrono>
#include <cmath>
#include <iostream>

void TestScene::onStart()
{
	//input system is not necessary for the assessment but could be a good coding practice to make an input class and some wrapper functions 
	//GameEngine::Entity* player1;
	//1 make an entity*
	//2 make shapecomponent*
	//3 add shapecomponent* to entity*
	//4 add entity to the scene

	//add circle1
	m_circle1 = new GameEngine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40,40 });
	m_circle1->getTransform()->setLocalPosition({ 100, 100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new GamePhysics::CircleColliderComponent(50));
	addEntity(m_circle1);

	//add circle2
	m_circle2 = new GameEngine::Entity();
	m_circle2->getTransform()->setLocalScale({ 40,40 });
	m_circle2->getTransform()->setLocalPosition({ 600, 100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new GamePhysics::CircleColliderComponent(50));
	addEntity(m_circle2);
	
	
}

void TestScene::onUpdate(double DeltaTime)
{

	
	GameMath::Vector2 position = m_circle1->getTransform()->getLocalPosition();
	GameMath::Vector2 deltaPosition = { 40,0 };



	float currentTime =
		std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	float circleRadius = 100;
	GameMath::Vector2 newPosition = {
		sin(currentTime) * circleRadius + 400,
		cos(currentTime) * circleRadius + 400};

	
}
