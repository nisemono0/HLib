<h1 align="center"> HLib </h1>
<p align="center">Qt app to search/read my local library</p>

# Info
Uses the ```info.json``` tag files inside the archives. <br>
Only searches for ```*.zip``` archives since that's all I use. <br>

# Dependencies (Arch Linux)
```qt5-base``` <br>
```quazip-qt5``` <br>
```sqlite``` <br>

# Compile

### Linux
Install missing dependencies <br>
Make sure that the ```qmakeconf.sh``` points to the right libs and include paths on your system <br>
Run ```qmakeconf.sh``` then ```make release``` <br>
The binary is ```./release/HLib```

### Windows
Theoretically compiling on Windows should work (I wouldn't know, never tested) <br>
Make sure that the libs and include paths are set in the ```qmakeconf.sh``` or the ```.pro``` file <br>
Compile it
