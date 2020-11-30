#!/bin/bash
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S0 L-56.7459427 R-23.4111223254 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S0 L-56.7459427 R-23.4111223254 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S0 L-56.7459427 R-23.4111223254 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S0 L-56.7459427 R-23.4111223254 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln





./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S1 L-100000 R-2000000 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S1 L-100000 R-2000000 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S1 L-100000 R-2000000 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S1 L-100000 R-2000000 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln




./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S2 L-1.00001 R-0.53459 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S2 L-1.00001 R-0.53459 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S2 L-1.00001 R-0.53459 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S2 L-1.00001 R-0.53459 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln





./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S3 L-.000052349 R-.5529 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S3 L-.000052349 R-.5529 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S3 L-.00052349 R-.5529 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S3 L-.00052349 R-.5529 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln




./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S50 L-123456789 R-123456789 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S50 L-123456789 R-123456789 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S50 L-123456789 R-123456789 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S50 L-123456789 R-123456789 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln






./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S100 L-0 R-0.1 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S100 L-0 R-0.1 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S100 L-0 R-0.1 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S100 L-0 R-0.1 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt





mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S220 L-1.00000001 R-0.0000000059 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S220 L-1.00000001 R-0.0000000059 1>out_mycell.txt 2>err_mycell.txt 
sort < myout_mycell.txt > Smyout_mycell.txt
sort < myerr_mycell.txt > Smyerr_mycell.txt
sort < out_mycell.txt > Sout_mycell.txt
sort < err_mycell.txt > Serr_mycell.txt
diff -bw Smyout_mycell.txt Sout_mycell.txt
diff -bw Smyerr_mycell.txt Serr_mycell.txt

rm Cell
cd ..
mv Cell lssoln
cd lssoln

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S220 L-1.00000001 R-0.0000000059 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S220 L-1.00000001 R-0.0000000059 1>out.txt 2>err.txt
sort < myout.txt > Smyout.txt
sort < myerr.txt > Smyerr.txt
sort < out.txt > Sout.txt
sort < err.txt > Serr.txt
diff -bw Smyout.txt Sout.txt
diff -bw Smyerr.txt Serr.txt

mv Cell ..
cd ../lsturnin
cp Cell ../lssoln
cd ../lssoln
