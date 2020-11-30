#!/bin/bash
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S0 L56.7459 R23.4 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S0 L56.7459 R23.4 1>out_mycell.txt 2>err_mycell.txt 
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

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S0 L56.7459 R23.4 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S0 L56.7459 R23.4 1>out.txt 2>err.txt
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





./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S1 L56.7459 R23.4 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S1 L56.7459 R23.4 1>out_mycell.txt 2>err_mycell.txt 
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

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S1 L56.7459 R23.4 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S1 L56.7459 R23.4 1>out.txt 2>err.txt
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




./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S2 L56.7459 R23.4 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S2 L56.7459 R23.4 1>out_mycell.txt 2>err_mycell.txt 
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

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S2 L56.7459 R23.4 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S2 L56.7459 R23.4 1>out.txt 2>err.txt
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





./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S3 L56.7459 R23.4 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S3 L56.7459 R23.4 1>out_mycell.txt 2>err_mycell.txt 
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

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C2 S3 L56.7459 R23.4 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C2 S3 L56.7459 R23.4 1>out.txt 2>err.txt
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





./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S200 L56.7459 R23.4 1>myout_mycell.txt 2>myerr_mycell.txt 
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S200 L56.7459 R23.4 1>out_mycell.txt 2>err_mycell.txt 
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

./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./lswip C50 S200 L56.7459 R23.4 1>myout.txt 2>myerr.txt
./SafeRun </dev/null -o400000 -t700 -T6000 -p1000 ./LinearSim C50 S200 L56.7459 R23.4 1>out.txt 2>err.txt
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
