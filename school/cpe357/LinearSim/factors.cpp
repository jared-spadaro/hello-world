#include <iostream>
using namespace std;

int main() {
   int num;
   cout << "Enter number: ";
   cin >> num;
   int i;
   cout << "Factors of " << num << " are: " << endl;
   for (i = 1; i <= num; ++i) {
      if (num % i == 0) {
         cout << i << endl;
      }
   }
   return 0;
}
