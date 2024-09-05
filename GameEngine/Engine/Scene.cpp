#include "Scene.h"
#include "Entity.h"
#include "Physics/ColliderComponent.h"

GameEngine::Scene::Scene()
{
	m_entities = List<Entity*>();
}

void GameEngine::Scene::start()
{
	for (Entity* entity : m_entities)
	{
		entity->start();
	}
}


void GameEngine::Scene::update(double deltaTime)
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();

		entity->update(deltaTime);
	}
}

void GameEngine::Scene::fixedUpdate(float FixedDeltatime)
{
	//Update Entities
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();

		entity->fixedUpdate(FixedDeltatime);
	}
	onFixedUpdate(FixedDeltatime);

	//Update Colliders
	for (auto row = m_activeColliders.begin(); row != m_activeColliders.end(); row++)
	{
		for (auto column = row; column != m_activeColliders.end(); column++)
		{
			if (row == column)
				continue;

			GamePhysics::Collision* collisionData1 = nullptr;
			GamePhysics::Collision* collisionData2 = new GamePhysics::Collision;
			GamePhysics::ColliderComponent* collider1 = *row;
			GamePhysics::ColliderComponent* collider2 = *column;

			if (collisionData1 = collider1->checkCollision(collider2))
			{
				//get collider 1 rigidbody and resolve collision
				collider1->getOwner()->onCollistionEnter(collisionData1);
			

				collisionData2->normal = collisionData1->normal * -1;
				collisionData2->collider = collider1;
				collider2->getOwner()->onCollistionEnter(collisionData2);

			}
		}
	}

}

void GameEngine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		entity->draw();
	}
	onDraw();
}

void GameEngine::Scene::end()
{
	for (Entity* entity : m_entities)
	{
		entity->end();
	}
	onEnd();
}

void GameEngine::Scene::addEntity(Entity* entity)
{
	m_entities.add(entity);
}

void GameEngine::Scene::removeEntity(Entity* entity)
{
	m_entities.remove(entity);
}
