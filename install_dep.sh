#!/usr/bin/env bash

# Install all the dependencies needed to build MAVSDK from source.
   
apt update
apt -y install build-essential cmake git ruby-dev python3-pip || exit 1
apt -y install cmake curl libjsoncpp-dev libtinyxml2-6 zlib1g libcurl-dev

gem install fpm
pip3 install --upgrade cloudsmith-cli
pip3 install future


