# !bin/base

if [  -z  "$(ls -A $(pwd)/pybind11)" ] ;  then
    git clone https://github.com/pybind/pybind11
else
    echo "-- Check pybind11 has exit "
fi

rm -rf build && mkdir build && cd build && cmake .. && make -j4