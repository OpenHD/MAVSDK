#bin/bash
cmake -Bbuild/default -DMAVLINK_DIALECT=openhd -DMAVLINK_HEADERS=mavlink-headers -DBUILD_SHARED_LIBS=OFF -H.
cmake --build build/default -j4