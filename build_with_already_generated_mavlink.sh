#bin/bash
cmake -Bbuild/default -DMAVLINK_DIALECT=openhd -DMAVLINK_HEADERS=mavlink-headers -H.
cmake --build build/default -j4
