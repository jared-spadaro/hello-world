#!/bin/sh
echo "Running test suite...\n"
./a.out < adjtest.txt
./a.out < primetest.txt
./a.out < ranktest.txt
./a.out < suitstest.txt
./a.out < test.txt
./a.out < test2.txt
./a.out < finalTest.txt
