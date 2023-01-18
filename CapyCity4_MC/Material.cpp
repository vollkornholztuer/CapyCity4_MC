#include "Material.h"

char Material::getMaterialLabel()
{
	return materialLabel;
}

bool operator<(const Material& lhs, const Material& rhs)
{
	return lhs.getMaterialPrice() < rhs.getMaterialPrice();
}
