# 오목 AI RnE 활동 보조

### 와! 이것은 샌즈!<br>

빌드 : 
윈도우 : 
```bash
git clone --recurse-submodules https://github.com/Piorosen/gomoku-ai-rne.git
cd gomoku-ai-rne/Gomoku
cmake -G "Visual Studio 16 2019" -A Win32
explorer .
# Visual Studio 2019 실행
# All Build
copy ./Resources ./Debug/Resources
./Debug/Gomoku-ai.exe
```

맥 : 
``` 
git clone --recurse-submodules https://github.com/Piorosen/gomoku-ai-rne.git
cd gomoku-ai-rne/Gomoku
cmake .
make
./Gomoku-ai
```
