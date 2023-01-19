#!/usr/bin/env bash

set -e

# Match hash from configure step
REPO="https://github.com/OpenHD/mavlink.git"
TAG="2.2.x-evo"
MAVLINK_DIALECT=common

MAVLINK_PATH=mavlink
MAVLINK_HEADERS_PATH=mavlink-headers

mkdir $MAVLINK_PATH
cd $MAVLINK_PATH && git clone $REPO && git checkout $TAG && git submodule update --init --recursive

OUTPUT_PATH="$MAVLINK_HEADERS_PATH/include/mavlink/v2.0/"
mkdir -p "$OUTPUT_PATH"
OUTPUT_PATH=$(realpath $OUTPUT_PATH)

tree

(cd $MAVLINK_PATH && \
    python3 \
        -m pymavlink.tools.mavgen \
        --lang=C \
        --wire-protocol=2.0 \
        --output=$OUTPUT_PATH \
        message_definitions/v1.0/$MAVLINK_DIALECT.xml)

echo ""
echo "Now run cmake with -DMAVLINK_HEADERS=\"$MAVLINK_HEADERS_PATH/include\""
