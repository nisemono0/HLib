<h1 align="center"> HLib </h1>
<p align="center">Qt app to search/read my local library</p>

# Info
Uses the ```info.json``` tag files inside the archives. <br>
Only searches for ```*.zip``` archives since that's all I use. <br>

# Dependencies (Arch Linux)
```qt6-base``` <br>
```quazip-qt6``` <br>
```cmake (compile)``` <br>

# Compile

### Linux
Install missing dependencies <br>
```mkdir build ; cd build``` <br>
```cmake -DCMAKE_BUILD_TYPE=Release ..``` <br>
```cmake --build .``` <br>
The binary is in ```./build/HLib``` <br>

### Windows
Theoretically compiling on Windows should work (I wouldn't know, never tested)
