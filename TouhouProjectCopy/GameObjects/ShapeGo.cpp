#include "stdafx.h"
#include "ShapeGo.h"

ShapeGo::ShapeGo(const std::string& n)
{
}

ShapeGo::~ShapeGo()
{
}

void ShapeGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(p);
}

void ShapeGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	shape.setPosition(position);
}

void ShapeGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(shape, origin);
	}
}

void ShapeGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	shape.setOrigin(x, y);
}

void ShapeGo::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void ShapeGo::Init()
{
}

void ShapeGo::Reset()
{
}

void ShapeGo::Update(float dt)
{
}
