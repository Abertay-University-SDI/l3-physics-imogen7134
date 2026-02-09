#include "Sheep.h"
#include <iostream>

Sheep::Sheep()
{
	
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	
	sf::Vector2f inputDir ({ 0,0 });

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A)) inputDir.x -= 1;

	
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D)) inputDir.x += 1;
	

	if (m_input->isKeyDown(sf::Keyboard::Scancode::W)) inputDir.y -= 1;
	

	if (m_input->isKeyDown(sf::Keyboard::Scancode::S)) inputDir.y += 1;
	
	// prevents player from moving faster than normal while moving diagonally
	if (inputDir.length() > 0) inputDir = inputDir.normalized();
	
	m_acceleration = inputDir * ACCELERATION;

}


void Sheep::update(float dt)
{
	m_velocity += (m_acceleration * dt);
	m_velocity *= DRAG_FACTOR;
	checkWallAndBounce();
	move(m_velocity);
	sf::Vector2f position;
	position = getPosition();
	
}

void Sheep::setWorldSize(float x, float y)
{
	m_worldSize = { x, y };
}

void Sheep::checkWallAndBounce()
{
	sf::Vector2f pos = getPosition();
	if ((pos.x < 0 && m_velocity.x < 0) || (pos.x + getSize().x > m_worldSize.x && m_velocity.x > 0))
		m_velocity.x *= -COEFF_OF_RESTITUTION;
	if ((pos.y < 0 && m_velocity.y < 0) || (pos.y + getSize().y > m_worldSize.y && m_velocity.y > 0))
		m_velocity.y *= -COEFF_OF_RESTITUTION;

}

void Sheep::collisionResponse(GameObject& collider)
{
	m_velocity *= -COEFF_OF_RESTITUTION;
	if (m_velocity.lengthSquared() < 200)
		move(m_velocity * 0.5f);
	else move(m_velocity * 0.05f);

}
