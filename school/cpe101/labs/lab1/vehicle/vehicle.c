#include "vehicle.h"

struct vehicle create_vehicle(int wheels, double fuel, int doors, int roof)
{
	struct vehicle car;
	car.wheels = wheels;
	car.fuel = fuel;
	car.doors = doors;
	car.roof = roof;
	return car;
}
