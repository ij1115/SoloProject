#pragma once
#include "GameObject.h"
class ShapeGo : public GameObject
{
public:
	sf::RectangleShape shape;

	ShapeGo(const std::string& n="");
	virtual ~ShapeGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};

