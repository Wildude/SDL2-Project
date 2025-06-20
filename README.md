# SDL2-Project 🎮

A modular C++ framework built on SDL2 for experimenting with game engine features including GUI systems, physics, vector math, Lua scripting, and multimedia handling. This project serves as a flexible foundation for developing 2D games or interactive applications.

---
## 🧰 Tools and Languages used
<p align="center">
  <img src="Icons/SDL.png" width="100" alt="SDL"/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="Icons/OpenGL.png" width="100" alt="OpenGL"/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="Icons/zlib.png" width="100" alt="zlib"/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="Icons/ffmpeg.png" width="100" alt="ffmpeg"/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <img src="Icons/Lua.png" width="100" alt="lua"/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</p>

---
## 📓 Description
### - SDL - Main driver of engine, allows cross-platform and low-level access to computer multi-media hardware components (audio, keyboard, mouse, joystick, graphics, etc).
### - OpenGL - A popular cross-platform graphics library ([`in OpenGL branch`](https://github.com/Wildude/SDL2-Project/tree/OpenGL))
### - zlib - compression/decompression library (used in decompressing tilemaps)
### - ffmpeg - video encoding/decoding library (helps view videos through program)
### - lua - a general purpose programming language (used for scripting in this context)

<blockquote> Other libraries </blockquote>
<blockquote> tinyxml: for XML parsing (useful in reading tilemaps from XML files) </blockquote>
<blockquote> base64: decoding/encoding library (useful in decoding XML files that has tilemap data) </blockquote>

---
## 📁 Project Structure
<!-- Audio Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Audio">Audio/</a></strong></summary>
  &nbsp &nbsp &nbsp &nbsp <i>Empty (for now)</i> <br>
</details>
<!-- Executables Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Executables">Executables/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Executables/UI_test1.exe">UI_test1.exe</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Executables/UI_test2.exe">UI_test2.exe</a> <br>
  &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Executables/UI_test3.exe">UI_test3.exe</a> <br>
</details>
<!-- Fonts Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Fonts">Fonts/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Fonts/ROCK.ttf">ROCK.ttf</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Fonts/ROCKB.ttf">ROCKB.ttf</a> <br>
</details>
<!-- Icons Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Icons">Icons/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Icons/Addis_Ababa_University_logo.ico">AAU.ico</a>
</details>
<!-- Images Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Images">Images/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Samples">Samples/</a> <br>  
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Samples/AAU.png">AAU.png</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Samples/CS.jpg">CS.jpg</a> <br>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Stages">Stages/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Tilesets">Tilesets/</a>
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Tilesets/tileset_1bit.png">tileset_1bit.png</a> <br>
&nbsp &nbsp &nbsp &nbsp - 
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Weapons">Weapons/</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Weapons/AK 47">AK47/</a>
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Weapons/AK 47/AK_47.png">AK_47.png</a> <br>
  &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Weapons/fire">fire/</a>
  <a href="https://github.com/Wildude/SDL2-Project/blob/master/Images/Weapons/fire/fire.png">fire.png</a> <br>
</details>
<!-- Headers Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/headers">headers/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/Basic.hpp">Basic.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/BSDLF.hpp">BSDLF.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/SDL2_namespace.hpp">SDL2_namespace.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/vector2D.hpp">vector2D.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/command.hpp">command.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/GUI.hpp">GUI.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/physics.hpp">physics.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/rigid_body.hpp">rigid_body.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/Tilemap.hpp">Tilemap.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/headers/scriptProcessor.hpp">scriptProcessor.hpp</a> <br>
</details>
<!-- Sample_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/sample_codes">sample_codes/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <i>Non-functional (and old) sample source codes</i>
</details>
<!-- Source_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/source_codes">source_codes/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/source_codes/UI_test.cpp">UI_test.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/source_codes/UI_test2.cpp">UI_test2.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/source_codes/UI_test3.cpp">UI_test3.cpp</a> <br>
</details>
<!-- SRC Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/src">src/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <i>Where SDL, FFMPEG, LUA and ZLIB reisde (open at your own risk)</i> <br>
</details>
<!-- Design Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/design">design/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/design/sample">sample/</a> <br>
&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/design/sample/game_class.puml">game_class.puml</a> <br>
&nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/design/sample/sample1.uml">sample1.uml</a> <br>
</details>
<!-- Files Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/blob/master/Files">Files/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Files/Data">Data/</a> <i>contains logging info (for monitoring)</i> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Files/scripts">scripts/</a> <i>contains lua scripts (for scripting)</i> <br>
  &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/blob/master/Files/XML">XML/</a> <i>contains XML documents(for tilemap data)</i> <br>
</details>

## 😲❓ Recent changes
- Added a docs and design folder for clean system design.
- Added UI system
- Added command system
- Added scripting system

---
## 🎥 Screen records

![TilemapTest15](https://github.com/user-attachments/assets/53e31a42-5e95-47dd-a227-a7ec776e3935)
![Armed_MeAN](https://github.com/user-attachments/assets/6de1b8ee-4d19-474b-b468-967450f37415)

---
## New concepts
### Rescaling images
![image](https://github.com/user-attachments/assets/189e9e9b-c481-4f18-a270-fda506be3a0b)
- This speeds up image generation process since drawing is not required.
- The above image is an illustration of this concept.
- Initially the large images (The man, The leather jeans and shoes) were downloaded separately from the internet.
- They were then rescaled into a desirable size and stiched to each other via the app <a href ="https://graphicsgale.com/us/">GraphicsGale</a>.
- Then each parts of the now stiched man were partitioned and rescaled again to fit parts of the human body (according to the design needed by <a href = "Headers/rigid_body.hpp">rigid_body.hpp</a>
---
## How to use?
### Windows
open up executables folder and run the programs.
### Linux
🤷compile and run
### MacOS
🤷‍♂️compile and run
