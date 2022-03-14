#!/bin/bash

SOURCE_DIR=`pwd`
BUILD_DIR=$SOURCE_DIR/build
CLEAN_UP_OPTION=false
BUILD_LAB_1_UT=false
BUILD_LAB_2_UT=false
CMAKE_OPTIONS=""

if [ $# == 0 ] ; then
  echo "Only building src...."
fi

# check args
TEMP=`getopt -o sertfm --long clean,lab1,lab2 \
      -n 'example.bash' -- "$@"`

if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi
eval set -- "$TEMP"

while true ; do
  case "$1" in
    --clean) echo "Clean up env."; CLEAN_UP_OPTION=true; shift ;;
    --lab1) echo "Build unit tests for lab1."; BUILD_LAB_1_UT=true; shift ;;
    --lab2) echo "Build unit tests for lab2."; BUILD_LAB_2_UT=true; shift ;;
    --) shift ; break ;;
    *) echo "Invalid argument!" ; exit 1 ;;
  esac
done

# set up build dir
if [ "$CLEAN_UP_OPTION"  = "true" ]
then
  rm -rf ${BUILD_DIR}
fi

if [ "$BUILD_LAB_1_UT" = "true" ]
then
  CMAKE_OPTIONS="${CMAKE_OPTIONS} -DBUILD_LAB_1_UT=true"
fi

if [ "$BUILD_LAB_2_UT" = "true" ]
then
  CMAKE_OPTIONS="${CMAKE_OPTIONS} -DBUILD_LAB_2_UT=true"
fi

mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ${SOURCE_DIR} ${CMAKE_OPTIONS} && make -j

if [ $? != 0 ]
then
  echo "Fail to build!"
  exit 1
fi

if [ "$BUILD_LAB_1_UT" = "true" ]
then
  # copy test resources to the build dir
  cp $SOURCE_DIR/test/resources/test.csv $BUILD_DIR/test/lab1/
fi

if [ "$BUILD_LAB_2_UT" = "true" ]
then
  # copy test resources to the build dir
  cp $SOURCE_DIR/test/resources/test.csv $BUILD_DIR/test/lab2/
fi

echo "Success."
exit 0
