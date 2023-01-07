#!/bin/bash

if [ ! -d "build/" ];then
    echo "-- Check files has no exit.."
    mkdir build && cd build && make clear && cmake ../ && make -j4 && make install && cd python && sh setup.sh
else
    echo "-- Check files has exit.."
    cd build && cmake ../ && make -j4 && make install && cd python && sh setup.sh
fi
