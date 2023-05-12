#include "ElementarElement.h"



ElementarElement::ElementarElement(float a, float b, float UpdateFrame)
{
	x = a;
	y = b;

	dt = 1.0 / UpdateFrame;

	image.setPosition(x, y);
}


void ElementarElement::Draw(sf::RenderWindow* field)
{
	field->draw(image);
}

void ElementarElement::Starting_conditions_for_W()
{
	Wx = 0;
	Wy = 0;
}

void ElementarElement::Starting_conditions_for_V(float v, float u)
{
	Vx = v;
	Vy = u;
}

void ElementarElement::Starting_conditions_for_M(float m)
{
	M = m;
	R = R0 * pow(m / M0, 1.0 / 3);
	image.setRadius(round(R));
}

void ElementarElement::SpawnPoint(float x, float y)
{
	image.setPosition(x, y);
}

void ElementarElement::Move()
{
	Vx += Wx * dt;
	Vy += Wy * dt;
	x += Vx * dt;
	y += Vy * dt;
	image.setPosition(x, y);
}
void ElementarElement::GravitationalForce(ElementarElement* element)
{
	float r = pow(pow((x - element->x), 2) + pow((y - element->y), 2), 3.0 / 2);

	Wx += G * element->M * (element->x - x) / r;
	Wy += G * element->M * (element->y - y) / r;

	element->Wx -= G * M * (element->x - x) / r;
	element->Wy -= G * M * (element->y - y) / r;
}

bool ElementarElement::ClashReporter(ElementarElement& element)
{
	if (pow((x - element.x), 2) + pow((y - element.y), 2) < pow((R + element.R), 2)) {
		return true;
	}
	return false;
}

void ElementarElement::InelasticClashForce(ElementarElement* element)
{
	float Sum_M = M + element->M;
	if (element->M < M) {
		Vx = (M * Vx + element->M * element->Vx) / Sum_M;
		Vy = (M * Vy + element->M * element->Vy) / Sum_M;

		R = pow(pow(R, 3) + pow(element->R, 3), 1.0 / 3);

		M = Sum_M;
		image.setRadius(round(R));


	}
	else {
		element->Vx = (M * Vx + element->M * element->Vx) / Sum_M;
		element->Vy = (M * Vy + element->M * element->Vy) / Sum_M;

		element->R = pow(pow(R, 3) + pow(element->R, 3), 1.0 / 3);

		element->M = Sum_M;
		image.setRadius(round(element->R));

	}
}
