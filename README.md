# 오목 AI RnE 활동 보조

### REQUIREMENT
Windows:
```bash
1. Visual C++
2. Visual Studio 2019
3. CMake 3.16.0
4. vcpkg
  - freeglut
  - glew
```

Unix:
```bash
1. CMake 3.16.0
2. glut
3. glew
```

### How to Build

Windows:
```bash
git clone --recurse-submodules https://github.com/Piorosen/gomoku-ai-rne.git
cd gomoku-ai-rne/Gomoku
cmake -G "Visual Studio 16 2019" -A Win32
```

Unix: 
``` 
git clone --recurse-submodules https://github.com/Piorosen/gomoku-ai-rne.git
cd gomoku-ai-rne/Gomoku
cmake .
make
```
