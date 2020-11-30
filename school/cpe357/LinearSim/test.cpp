#include <iostream>
using namespace std;

class Rectangle {
   int height, width;
   public:
     void set_values(int,int);
     int area() {return width * height;}
};

void Rectangle::set_values(int x, int y) {
   width = x;
   height = y;
}

int main() {
   Rectangle rect;
   rect.set_values(4,3);
   int a = rect.area();
   return 0;
}
