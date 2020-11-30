__kernel void gaussian_blur(__global const unsigned char *image, __global const float* G, 
 const int W, const int H, const int size, __global unsigned char *newImg) { 
   const int col = get_global_id(0);    	
   const int row = get_global_id(1);
          
   if (col < W && row < H) {
      float pixVal= 0;
      int pixels = 0;

      for (int blurrow = -(size/2); blurrow < (size/2 + 1); ++blurrow) {
         for (int blurcol = -(size/2); blurcol < (size/2 + 1); ++blurcol) {
             int currow = row + blurrow;
             int curcol = col + blurcol;
             if (currow > -1 && currow < H && curcol > -1 && curcol < W) {
                pixVal += image[currow * W + curcol] * G[blurrow * size + blurcol];
                pixels++;
             }
         }
      }
      newImg[row * W + col] = (unsigned char)(pixVal / pixels);
   }
}
