make a build directory
cd into build
then execute cmake in teh directory above
then run make to compile the code

for example, run:
mkdir build
cd build
cmake ..
make

The code expects that you will specify a png file on the command line, e.g.:
./readImg ../Texture_output.png

(where the file "Texture_output.png" will be one directory above the build directory)

This will produce a modified png file (ImageOut.png) in the same directory where the code was run.
Then use gimp or any other image viewing program to view the output, i.e.

gimp ImageOut.png
