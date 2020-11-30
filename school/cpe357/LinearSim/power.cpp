#include <iostream>
using namespace std;

int calculatePower(int, int);

int main() {
   int base, power, result;
   cout << "Enter base number: ";
   cin >> base;

   cout << "Enter exponent: ";
   cin >> power;

   result = calculatePower(base, power);
   cout << base << "^" << power << " = " << result << endl;
   return 0;
}

int calculatePower(int base, int power) {
   if (power) {
      return base * calculatePower(base, power-1);
   }
   else {
      return 1;
   }
}
