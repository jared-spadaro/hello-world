//The Gaussian blur function that runs on the gpu
__kernel void gaussian_blur(__global const unsigned char *image, __global const float* G, 
 const int W, const int H, const int size, __global unsigned char *newImg) { 
	//Inputs: Image, original image; G is the ImageBlur filter, W is the width and H is the hight
	//Output: newImg , image blurred	
	//Get the index of the current element being processed
        const int ndx = get_global_id(0);    	
        float PValue = 0;
        int N_start_point = ndx - (5/2);
        for (int j = 0; j < 5; j++) {
           if (N_start_point + j >= 0 && N_start_point + j < W) {
              PValue += image[N_start_point + j] * G[j];
           }
        }          
        newImg[ndx] = PValue/5; 
}

