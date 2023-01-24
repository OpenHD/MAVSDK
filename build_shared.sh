#bin/bash
# Note: openhd custom mavlink flavour is directly baked in by modifying the cmake
cmake -Bbuild/default -H.
cmake --build build/default -j4
