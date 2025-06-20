# SDL2-Project 🎮

A modular C++ framework built on SDL2 for experimenting with game engine features including GUI systems, physics, vector math, Lua scripting, and multimedia handling. This project serves as a flexible foundation for developing 2D games or interactive applications.

---
## 📁 Project Structure
<!-- Audio Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Audio">Audio/</a></strong></summary>
- Holds audio assets
</details>
<!-- Executables Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Executables">Executables/</a></strong></summary>
- Holds executable files <br>
- [game.exe](https://github.com/Wildude/SDL2-Project/blob/main/Executables/game.exe)  
- [SDL2.dll](https://github.com/Wildude/SDL2-Project/blob/main/Executables/SDL2.dll)
</details>
<!-- Fonts Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Fonts">Fonts/</a></strong></summary>
- [arial.ttf](https://github.com/Wildude/SDL2-Project/blob/main/Fonts/arial.ttf)
</details>
<!-- Icons Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Icons">Icons/</a></strong></summary>
- [icon.png](https://github.com/Wildude/SDL2-Project/blob/main/Icons/icon.png)
</details>
<!-- Images Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Images">Images/</a></strong></summary>
- [player.png](https://github.com/Wildude/SDL2-Project/blob/main/Images/player.png)  
- [enemy.png](https://github.com/Wildude/SDL2-Project/blob/main/Images/enemy.png)
</details>
<!-- Headers Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/headers">headers/</a></strong></summary>
- [gui.hpp](https://github.com/Wildude/SDL2-Project/blob/main/headers/gui.hpp)  
- [vector2d.hpp](https://github.com/Wildude/SDL2-Project/blob/main/headers/vector2d.hpp)  
- [physics.hpp](https://github.com/Wildude/SDL2-Project/blob/main/headers/physics.hpp)  
- [script.hpp](https://github.com/Wildude/SDL2-Project/blob/main/headers/script.hpp)
</details>
<!-- Sample_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/sample_codes">sample_codes/</a></strong></summary>
- [notes.txt](https://github.com/Wildude/SDL2-Project/blob/main/sample_codes/notes.txt)  
- [ui_experiment.txt](https://github.com/Wildude/SDL2-Project/blob/main/sample_codes/ui_experiment.txt)
</details>
<!-- Source_codes Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/source_codes">source_codes/</a></strong></summary>
- [test_gui.cpp](https://github.com/Wildude/SDL2-Project/blob/main/source_codes/test_gui.cpp)  
- [test_vector2d.cpp](https://github.com/Wildude/SDL2-Project/blob/main/source_codes/test_vector2d.cpp)  
- [test_physics.cpp](https://github.com/Wildude/SDL2-Project/blob/main/source_codes/test_physics.cpp)
</details>
<!-- SRC Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/src">src/</a></strong></summary>
- [external_library.hpp](https://github.com/Wildude/SDL2-Project/blob/main/src/external_library.hpp)  
- [lua_bindings.cpp](https://github.com/Wildude/SDL2-Project/blob/main/src/lua_bindings.cpp)
</details>
<!-- Design Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/design">design/</a></strong></summary>
- [external_library.hpp](https://github.com/Wildude/SDL2-Project/blob/main/design/external_library.hpp)  
- [lua_bindings.cpp](https://github.com/Wildude/SDL2-Project/blob/main/design/lua_bindings.cpp)
</details>
<!-- Files Files -->
<details>
<summary><strong><a href="https://github.com/Wildude/SDL2-Project/tree/main/Files">Files/</a></strong></summary>
- [external_library.hpp](https://github.com/Wildude/SDL2-Project/blob/main/Files/external_library.hpp)  
- [lua_bindings.cpp](https://github.com/Wildude/SDL2-Project/blob/main/Files/lua_bindings.cpp)
</details>
<br>
## Recent changes
- Added a docs and design folder for clean system design.
- Added UI system
- Added command system
- Added scripting system
![TilemapTest15](https://github.com/user-attachments/assets/53e31a42-5e95-47dd-a227-a7ec776e3935)
![Armed_MeAN](https://github.com/user-attachments/assets/6de1b8ee-4d19-474b-b468-967450f37415)
## New concepts
### Rescaling images
![image](https://github.com/user-attachments/assets/189e9e9b-c481-4f18-a270-fda506be3a0b)
- This speeds up image generation process since drawing is not required.
- The above image is an illustration of this concept.
- Initially the large images (The man, The leather jeans and shoes) were downloaded separately from the internet.
- They were then rescaled into a desirable size and stiched to each other via the app <a href ="https://graphicsgale.com/us/">GraphicsGale</a>.
- Then each parts of the now stiched man were partitioned and rescaled again to fit parts of the human body (according to the design needed by <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Headers/rigid_body.hpp">rigid_body.hpp</a>
## How to use?
open up executables folder and run the programs.
