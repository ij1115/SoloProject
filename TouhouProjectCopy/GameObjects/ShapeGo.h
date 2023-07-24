#pragma once
#include "GameObject.h"
class ShapeGo :  public GameObject
{
protected:
	sf::RectangleShape shape;

public:

	ShapeGo(const std::string& n = "");
	virtual ~ShapeGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetSize(sf::Vector2f size) { shape.setSize(size); }
};

