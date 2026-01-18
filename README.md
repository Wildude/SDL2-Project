# <p align = "center"> SDL2-Project (for Linux 🐧) 🎮 </p>

A modular C++ framework built on SDL2 for experimenting with game engine features including GUI systems, physics, vector math, Lua scripting, and multimedia handling. This project serves as a flexible foundation for developing 2D games or interactive applications.

---
## 🧰 Tools and Languages used
<p align="center">
  <a href="https://www.libsdl.org/"><img src="Icons/SDL.png" width="100" alt="SDL"/></a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://zlib.net/"><img src="Icons/zlib.png" width="100" alt="zlib"/></a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://www.lua.org/"><img src="Icons/Lua.png" width="100" alt="lua"/></a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</p>

---
## 📓 Description
<i> "All trademarks and logos are property of their respective owners. <br> some logos like OpenGL's and ffmpeg's were removed because of usage restrictions." </i>
### - [SDL](https://www.libsdl.org/) - Main driver of engine, allows cross-platform and low-level access to computer multi-media hardware components (audio, keyboard, mouse, joystick, graphics, etc).
### - [OpenGL](https://www.opengl.org/) - A popular cross-platform graphics library ([`in OpenGL branch`](https://github.com/Wildude/SDL2-Project/tree/OpenGL))
### - [zlib](https://zlib.net/) - compression/decompression library (used in decompressing tilemaps)
### - [ffmpeg](https://ffmpeg.org/) - video encoding/decoding library (helps view videos through program)
### - [lua](https://www.lua.org/) - a general purpose programming language (used for scripting in this context)
### 📚 Other libraries
### - [tinyxml](https://github.com/leethomason/tinyxml2): for XML parsing (useful in reading tilemaps from XML files) 
### - [base64](https://github.com/ReneNyffenegger/cpp-base64): decoding/encoding library (useful in decoding XML files that has tilemap data)

---
## 📁 Project Structure
<!-- Audio Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/">Audio/</a></strong></summary>
  &nbsp &nbsp &nbsp &nbsp <i>Empty (for now)</i> <br>
</details>
<!-- Executables Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/bin">bin/</a></strong></summary>
  None so far
</details>
<!-- Fonts Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Fonts">Fonts/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Fonts/ROCK.TTF">ROCK.ttf</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Fonts/ROCKB.TTF">ROCKB.ttf</a> <br>
</details>
<!-- Icons Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Icons">Icons/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Icons/Addis_Ababa_University_logo.ico">AAU.ico</a>
</details>
<!-- Images Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images">Images/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Samples">Samples/</a> <br>  
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Samples/AAU.png">AAU.png</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Samples/CS.jpg">CS.jpg</a> <br>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Stages">Stages/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Stages/Tilesets">Tilesets/</a>
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Stages/Tilesets/tileset_1bit.png">tileset_1bit.png</a> <br>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Weapons">Weapons/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Weapons/AK 47">AK47/</a>
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Weapons/AK 47/AK_47.png">AK_47.png</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Weapons/fire">fire/</a>
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Images/Weapons/fire/fire.png">fire.png</a> <br>
</details>
<!-- core Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/core">core/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/BAS">BAS/</a> <br>  
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/BAS/include">include/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/BAS/src">src/</a> <br>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/SDL">SDL/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/SDL/include">include/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/core/SDL/src">src/</a> <br>
</details>
<!-- Sample_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/sample_codes">sample_codes/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <i>Non-functional (and old) sample source codes</i>
</details>
<!-- Source_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/tests/src">tests/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/tests/src/UI_test.cpp">UI_test.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/tests/src/UI_test2.cpp">UI_test2.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/tests/src/UI_test3.cpp">UI_test3.cpp</a> <br>
</details>
<!-- SRC Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/src">src/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <i>Where SDL, FFMPEG, LUA and ZLIB reisde (open at your own risk)</i> <br>
</details>
<!-- Design Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/design">design/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/design/sample">sample/</a> <br>
&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/design/sample/game_class.puml">game_class.puml</a> <br>
&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/design/sample/sample1.uml">sample1.uml</a> <br>
</details>
<!-- Files Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Files">Files/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Files/Data">Data/</a> <i>contains logging info (for monitoring)</i> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Files/scripts">scripts/</a> <i>contains lua scripts (for scripting)</i> <br>
  &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Files/XML">XML/</a> <i>contains XML documents(for tilemap data)</i> <br>
</details>

## 😲❓ Recent changes
- separated declaration and definition (implementation)
- Added batch and makefiles to automate build tasks
- These make compilation fast and efficient

---
## 🎥 Screen records
<p align="left">
  None so far
</p>

---
## 📷 Screen shots
<p align="left">
  None so far
</p>

---
## 👩‍🔬 New concepts
- project in renovation
---
## 🤔 How to use?
Notice: For the time being, it's presumed these packages are locally installed and are in pkg-config: SDL2, ffmpeg, lua, zlib
install with 
```sh
sudo apt install sdl2 ffmpeg lua zlib sdl2-devel
```
open up executables folder and run the programs.
in case there are no programs navigate to project root and run:
```sh
bash build.sh
```
To rebuild, run:
```sh
bash clean.sh help
```
or simply 
```sh
bash clean.sh
```
which cleans everything

