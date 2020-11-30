#include <stdio.h>
#include "checkit.h"
#include "vehicle.h"

void test_cases(void)
{
	struct vehicle car;
	car = create_vehicle(1, 1.5, 2, 0);
	checkit_double(car.wheels, 1);
	checkit_double(car.fuel, 1.5);
	checkit_double(car.doors, 2);
	checkit_double(car.roof, 0);

}

int main(int argc, char **argv)
{
   test_cases();

   return 0;
}
