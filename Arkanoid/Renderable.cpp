#include "Renderable.h"

Renderable::Renderable(int id)
	:id(id)
{
}

const int& Renderable::getId() const
{
	return id;
}
