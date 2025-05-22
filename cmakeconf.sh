#!/bin/bash

rm -rf ./build
rm -f ./CMakeLists.txt
rm -f ./src/gui/ui/ui_logwindow.h
rm -f ./src/gui/ui/ui_mainwindow.h

/usr/lib/qt6/bin/qt-cmake-create

sed -i -e '1i set(CMAKE_EXPORT_COMPILE_COMMANDS ON)' ./CMakeLists.txt
echo '' >> ./CMakeLists.txt
echo '# !!! cmakeconf.sh !!!' >> ./CMakeLists.txt
echo 'find_package(Qt6 REQUIRED COMPONENTS Sql)' >> ./CMakeLists.txt
echo 'find_package(QuaZip-Qt6)' >> ./CMakeLists.txt
echo 'target_include_directories(HLib PUBLIC ${CMAKE_SOURCE_DIR}/src)' >> ./CMakeLists.txt
echo 'target_link_libraries(HLib PRIVATE Qt::Sql QuaZip::QuaZip)' >> ./CMakeLists.txt

mkdir -p ./build
cd ./build
cmake ..

if [ "$1" == "--compile" ]; then
    cmake --build . --config Release -j 12
    cp -f HLib_autogen/include/ui/ui_logwindow.h ../src/gui/ui/
    cp -f HLib_autogen/include/ui/ui_mainwindow.h ../src/gui/ui/
fi
