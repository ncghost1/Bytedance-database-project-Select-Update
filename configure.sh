#!/bin/bash

TMP_DOWNLOAD_DIR="/tmp/tmp_download"
LIB_GTEST="/usr/local/lib/libgtest.a"
LIB_GTEST_MAIN="/usr/local/lib/libgtest_main.a"

# check if we need to configure gtest
if [ -f "$LIB_GTEST" ] && [ -f "$LIB_GTEST_MAIN" ]
then
  echo "There is nothing to be configured, just skip."
  echo "You are safe to run build.sh now."
  exit 0
fi

# download googletest
if [ ! -d "$TMP_DOWNLOAD_DIR" ]
then
  mkdir -p $TMP_DOWNLOAD_DIR
else
  rm -rf $TMP_DOWNLOAD_DIR
fi

# set up
cd $TMP_DOWNLOAD_DIR && git clone https://github.com/google/googletest.git
cd googletest && mkdir -p build && cd build && cmake .. && make -j

# install with root access
sudo make install

# check if gtest binary files exist
if [ ! -f "$LIB_GTEST" ]
then
  echo "Fail to configure gtest, fail to find the target binary file: ${LIB_GTEST}"
  exit 1
fi

if [ ! -f "$LIB_GTEST_MAIN" ]
then
  echo "Fail to configure gtest, fail to find the target binary file: ${LIB_GTEST_MAIN}"
  exit 1
fi

echo "Success."
rm -rf $TMP_DOWNLOAD_DIR
