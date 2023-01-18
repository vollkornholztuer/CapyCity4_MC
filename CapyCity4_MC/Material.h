#pragma once
class Material
{
protected:
	double price;
	char materialLabel;

public:
	char getMaterialLabel();
	double getMaterialPrice() const { return price; };
	Material(double price) : price(price) {};
};

bool operator<(const Material& lhs, const Material& rhs);


class Wood : public Material {
public:
	Wood() : Material(420.69) {
		materialLabel = 'W';
	}
};

class Metal : public Material {
public:
	Metal() : Material(694.20) {
		materialLabel = 'M';
	}
};

class Plastic : public Material {
public:
	Plastic() : Material(133.7) {
		materialLabel = 'P';
	}
};

#pragma once
