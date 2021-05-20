#pragma once
#include "Vehicle.h"

class Train : public Vehicle
{
public:
	Train();
	Train(std::tuple<int, int, double>, int);
};
