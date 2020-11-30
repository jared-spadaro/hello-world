/* Release code for reading image into a unsigned char array - also writes it out, slightly shifted */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main(int argc, char **argv)
{
   int w, h, ncomps;
	string filename;
	
	if(argc < 2) {
      cout << "Usage: loadImg imagefile" << endl;
      cout << "For example: ./readImg ../Texture_output.png" << endl;
      return 0;
   }
	filename = argv[1];

   //stbi_set_flip_vertically_on_load(true);
   unsigned char *data = stbi_load(filename.c_str(), &w, &h, &ncomps, 0);
   if(!data) {
      cerr << argv[1] << " not found" << endl;
   }
   if(ncomps != 3) {
      cerr << argv[1] << " must have 3 components (RGB)" << endl;
   }

	//example of iterating through the data and shifting it - replace with OpenCL blur
	for (int y=0; y < h; y++) {
		for (int x=0; x < w; x++) {
			if (x%20 < 10 && y < h-10)	{
				//shift the red
				data[ncomps*(x+y*w)+ 0] = data[ncomps*(x+(y+9)*w)+0]; 
				//shift the green
				data[ncomps*(x+y*w)+ 1] = data[ncomps*(x+(y+9)*w)+1]; 
				//shift the blue 
				data[ncomps*(x+y*w)+ 2] = data[ncomps*(x+(y+9)*w)+2]; 
			}
		}
	}

	cout << "writing out file named: ImageOut.png, use gimp to view it" << endl;
 	stbi_write_png("ImageOut.png",  w, h, ncomps, data, w*ncomps);

	stbi_image_free(data);
	return 0;
}
