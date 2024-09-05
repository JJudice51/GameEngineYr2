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
