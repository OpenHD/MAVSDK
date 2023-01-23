#!/usr/bin/env bash

set -e

# Match hash from configure step
REPO="https://github.com/OpenHD/mavlink"
TAG="f5ed2eac5780d9165aad08e2abaee1888ab59bf4"
MAVLINK_DIALECT=openhd

MAVLINK_PATH=mavlink
MAVLINK_HEADERS_PATH=mavlink-headers

if [ ! -d $MAVLINK_PATH ]
then
    git clone --recursive $REPO $MAVLINK_PATH
else
    (cd $MAVLINK_PATH && git fetch)
fi

(cd $MAVLINK_PATH && git checkout $TAG && git submodule update --init --recursive)

OUTPUT_PATH="$MAVLINK_HEADERS_PATH/include/mavlink/v2.0/"
mkdir -p "$OUTPUT_PATH"
OUTPUT_PATH=$(realpath $OUTPUT_PATH)

echo "Installing dependencies"
(cd $MAVLINK_PATH && \
    python3 \
        -m pip install -r pymavlink/requirements.txt)

echo "Generating headers"
(cd $MAVLINK_PATH && \
    python3 \
        -m pymavlink.tools.mavgen \
        --lang=C \
        --wire-protocol=2.0 \
        --output=$OUTPUT_PATH \
        message_definitions/v1.0/$MAVLINK_DIALECT.xml)

echo ""
echo "Now run cmake with -DMAVLINK_HEADERS=\"$MAVLINK_HEADERS_PATH/include\""
