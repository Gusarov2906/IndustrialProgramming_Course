#pragma once
#include <string>
#include "Track.h"
#include "Data.h"
#include "Car.h"
#include "Train.h"
#include "Plane.h"
#include "CarFactory.h"
#include "PlaneFactory.h"
#include "TrainFactory.h"

enum Type { Turbo, Standart, Economy };

class Order
{
	double cost;
	int volume;
	std::string startPoint;
	std::string finishPoint;
	enum::Type type;
	Track track;
	
	CarFactory carFactory;
	PlaneFactory planeFactory;
	TrainFactory trainFactory;
	
public:
	Order();
	Order(Type, std::string, std::string, int);
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);
};
