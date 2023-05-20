#!/bin/bash

gcc ./4-5-points/client-buyers.c -lpthread -o ./4-5-points/client-buyers
gcc ./4-5-points/client-seller.c -lpthread -o ./4-5-points/client-seller
gcc ./4-5-points/server.c -lpthread -o ./4-5-points/server
# gcc ./6-7-points/main.c -o ./6-7-points/main.exe
echo "Programs compiled"
