#pragma once

#include "libraries.h"
#include "FundamentalConstants.h"

class ElementarElement
{
private:
    float M = 10;
    float M0 = 10;

    float Vx = 0;
    float Vy = 0;

    float Wx = 0;
    float Wy = 0;

    float R = 2;
    float R0 = 2;

    float x = 0;
    float y = 0;

    float dt = 1.0 / 16;

    

private:
    sf::CircleShape image = sf::CircleShape(R, 10);

public:

    ElementarElement(float x, float y, float UpdateFrames);

    void Draw(sf::RenderWindow* field);

    void Starting_conditions_for_W();

    void Starting_conditions_for_V(float v, float u);

    void Starting_conditions_for_M(float m);

    void SpawnPoint(float x, float y);

    void Move();

    void GravitationalForce(ElementarElement* element);

    void Cout();

    bool ClashReporter(ElementarElement& element);

    void InelasticClashForce(ElementarElement* element);

};

