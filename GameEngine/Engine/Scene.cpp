#include "Scene.h"
#include "Entity.h"

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
	for (Entity* entity : m_entities)
	{
		if (!entity->getStarted())
			entity->start();

		entity->fixedUpdate(FixedDeltatime);
	}
	onFixedUpdate(FixedDeltatime);
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
