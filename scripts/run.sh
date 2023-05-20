#!/bin/bash

echo "Program for 4-5 points"
for j in `seq 1 $2`
do
    echo "Test $j"
    ./4-5-points/server.exe 55555 tests/test$j.in &
    ./4-5-points/client-seller.exe 55555 tests/test$j.in &
    ./4-5-points/client-buyers.exe 127.0.0.1 55555 tests/test$j.in
    sleep 10
    echo
done
echo
echo "Program for 6-7 points"
for j in `seq 1 $2`
do
    echo "Test $j"
    ./6-7-points/main.exe tests/test$j.in
    sleep 10
    echo
done
echo
echo "Programs finished"
