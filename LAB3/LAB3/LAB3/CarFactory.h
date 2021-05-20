#pragma once
#include "VehicleFactory.h"
#include "Car.h"

class CarFactory : public VehicleFactory
{
public:
	Vehicle* createVehicle() override;
	Vehicle* createVehicle(std::tuple<int, int, double>, int dist) override;
};

