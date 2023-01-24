#bin/bash
# Note: openhd custom mavlink flavour is directly baked in by modifying the cmake
cmake -Bbuild/default -DBUILD_SHARED_LIBS=OFF -H.
cmake --build build/default -j4