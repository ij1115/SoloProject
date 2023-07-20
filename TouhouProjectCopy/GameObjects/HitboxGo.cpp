#include "stdafx.h"
#include "HitboxGo.h"

HitboxGo::HitboxGo(const std::string& n)
	: GameObject(n)
{
}

HitboxGo::~HitboxGo()
{
}

void HitboxGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(p);
}

void HitboxGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	shape.setPosition(position);
}

void HitboxGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(shape, origin);
	}
}

void HitboxGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	shape.setOrigin(x, y);
}

void HitboxGo::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void HitboxGo::Init()
{
}

void HitboxGo::Reset()
{
}

void HitboxGo::Update(float dt)
{
}

void HitboxGo::SetPool(ObjectPool<HitboxGo>* hitBoxPool)
{
	this->pool = hitBoxPool;
}

sf::FloatRect HitboxGo::GetCollider()
{
	return this->shape.getGlobalBounds();
}
