# <p align = "center"> SDL2-Project 🎮 </p>

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
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Executables">Executables/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Executables/UI_test.exe">UI_test.exe</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Executables/UI_test2.exe">UI_test2.exe</a> <br>
  &nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Executables/UI_test3.exe">UI_test3.exe</a> <br>
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
<!-- Headers Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers">Headers/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/Basic.hpp">Basic.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/BSDLF.hpp">BSDLF.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/SDL2_namespace.hpp">SDL2_namespace.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/vector2D.hpp">vector2D.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/command.hpp">command.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/GUI.hpp">GUI.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/physics.hpp">physics.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/rigid_body.hpp">rigid_body.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/Tilemap.hpp">Tilemap.hpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/Headers/scriptProcessor.hpp">scriptProcessor.hpp</a> <br>
</details>
<!-- Sample_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/sample_codes">sample_codes/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <i>Non-functional (and old) sample source codes</i>
</details>
<!-- Source_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/Master/source_codes">source_codes/</a></strong></summary>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/source_codes/UI_test.cpp">UI_test.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/source_codes/UI_test2.cpp">UI_test2.cpp</a> <br>
&nbsp &nbsp &nbsp &nbsp - <a href="https://github.com/Wildude/SDL2-Project/tree/Master/source_codes/UI_test3.cpp">UI_test3.cpp</a> <br>
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
- Added a docs and design folder for clean system design.
- Added UI system
- Added command system
- Added scripting system

---
## 🎥 Screen records
<p align="left">
  <a href="source_codes/InputBoxTest.cpp"><img src = "screenshots/UI_inputbox1.gif" width = "800" alt = "InputBox test"/></a> 
  <a href="source_codes/SliderTest.cpp"><img src = "screenshots/UI_slider1.gif" width = "400" alt = "InputBox test"/></a> 
  <a href="source_codes/State_test.cpp"><img src = "screenshots/UI_state1.gif" width = "400" alt = "Menu State test"/></a> 
  <a href="source_codes/CheckBoxTest.cpp"><img src = "screenshots/UI_checkbox1.gif" width = "400" alt = "CheckBox test"/></a> 
  <a href="source_codes/State_test2.cpp"><img src = "screenshots/UI_diffstate1.gif" width = "400" alt = "Difficulty state test"/></a> 
  <a href="source_codes/UItabTest.cpp"><img src = "screenshots/UI_tab1.gif" width = "400" alt = "UITab test"/></a> 
  <a href="source_codes/UI_test3.cpp"><img src = "screenshots/UI_test1.gif" width = "400" alt = "UI test"/></a> 
  <a href="source_codes/TextSwitchTest.cpp"><img src = "screenshots/TextSwitchTest.gif" width = "400" alt = "Textswitch test"/></a> 
  <a href="source_codes/DropDownTest.cpp"><img src = "screenshots/DropDownTest.gif" width = "400" alt = "Dropdown test"/></a> 
  <a href="source_codes/SpinBoxTest.cpp"><img src = "screenshots/SpinBoxTest.gif" width = "400" alt = "Spinbox test"/></a> 
</p>

---
## 📷 Screen shots
<p align="left">
  <a href="source_codes/bounding_box_test.cpp"><img src = "screenshots/Bounding Box Test 7_1_2025 9_22_51 PM.png" width = "400" alt = "bounding box test"/></a> 
    <a href="source_codes/ImageTest.cpp"><img src = "screenshots/GUI Test 7_1_2025 9_25_22 PM.png" width = "400" alt = "ImageUI test"/></a> 
    <a href="source_codes/UI_test.cpp"><img src = "screenshots/GUI Test 7_1_2025 9_25_30 PM.png" width = "400" alt = "UI test1"/></a>
    <a href="source_codes/UIPC_test.cpp"><img src = "screenshots/GUI Test 7_1_2025 9_25_49 PM.png" width = "400" alt = "UI Panel and Container test"/></a> 
  <a href="source_codes/UI_test2.cpp"><img src = "screenshots/UIContainer Test 7_1_2025 9_25_39 PM.png" width = "400" alt = "UI Container test"/></a>
  <a href="source_codes/InputBoxTest.cpp"><img src = "screenshots/InputBox Test 7_3_2025 3_28_58 PM.png" width = "400" alt = "InputBox test"/></a> 
  <a href="source_codes/LabelAreaTest.cpp"><img src = "screenshots/LabelArea Test 7_4_2025 6_18_39 PM.png" width = "400" alt = "Labelarea test"/></a> 
</p>

---
## 👩‍🔬 New concepts
### Rescaling images
![image](https://github.com/user-attachments/assets/189e9e9b-c481-4f18-a270-fda506be3a0b)
- This speeds up image generation process since drawing is not required.
- The above image is an illustration of this concept.
- Initially the large images (The man, The leather jeans and shoes) were downloaded separately from the internet.
- They were then rescaled into a desirable size and stiched to each other via the app <a href ="https://graphicsgale.com/us/">GraphicsGale</a>.
- Then each parts of the now stiched man were partitioned and rescaled again to fit parts of the human body (according to the design needed by <a href = "Headers/rigid_body.hpp">rigid_body.hpp</a>
---
## 🤔 How to use?
### Windows
open up executables folder and run the programs.
### Linux
🤷compile and run
### MacOS
🤷‍♂️compile and run
