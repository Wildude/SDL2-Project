# SDL2-Project
## Recent changes
![environment](https://github.com/user-attachments/assets/7eb32976-d0de-4c2e-ab44-e02aff645b03)
![environment2](https://github.com/user-attachments/assets/34e71d5f-7b0a-4f0f-8666-4ce9664a883b)
![armed_man](https://github.com/user-attachments/assets/7c7f268f-0b4c-4edb-8327-253146f96e1a)
![environment3](https://github.com/user-attachments/assets/85514eaf-6bf5-4141-a924-a169c7ca1b5f)
## How to use?
open up executables folder and run the programs.
## Preface
### This project was submitted on freshman second semester, to Mr. Mohammed, our Computer programming-I instructor of the time. Comprising 20% of the grade, the submission date was set a few days after the final exam.
### Being the least absurd and the only one with a valid SDLC research of all 10 project ideas proposed by all 10 members, it was chosen as the group's project. It was initially planned to be a 2D video game/engine, but having feared potential denial of collaboration from group members who would take difficulty of the operation and feasibility as an excuse, it was modified. After some well deserved thoughts, it was named "Hybrid-designs". This is because it combines both console (regular terminal usage) with Graphical user interface (GUI usage). However, noone in the group could understand the main purpose or the meaning of the project. It was explained repeatedly both in person and online to all group members, but failed to get the appropriate attention. Thus, the project was forced to be done alone and the flexibility of the project was used to pursue on the initial plan. Because of lack of support from the group, difficulty of the implementations and final exam preparations, the initial plan failed and the project was submitted as cluster of simple programs that use the hybrid designs concept.
### The project was submitted in compressed rar form via email. Days after submission, a phone call from the representative explained that the group was given a 0/20 as the file was corrupt and that a physical meeting with the instructor and presentation of the project was urgent. The project was then presented to the instructor in his office and was graded 19/20 for which he stated was because of lack of collaboration 😑. Perhaps, the greatest achievement was it being the highest graded project of the class, but who cares anyway 😒.
### This project teaches a lesson about the inequality and incompatibility of energy and attitude between group members as well as the fruit of balance and keeping things simple especially if it's not that worth it.
## Introduction
### The project contains 5 core headers:
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/Basic.h">`Basic.h`</a>
  - This contains namespaces for the most basic data manipulations like character and integer data conversions.
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/BSDLF.h">`BSDLF.h`</a>
  - This is for using functions from <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/SDL2_namespace.h">`SDL2_namespace.h`</a> to do important GUI tasks like opening a window or drawing an image on it.
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/physics.h">`physics.h`</a>
  - This is for implementation of simple 2D mechanics like gravity, movement and collisions.
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/SDL2_namespace.h">`SDL2_namespace.h`</a>
  - This contains namespaces to hold various functions from SDL2 library in order to make them more memorable and easy.
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Files/Headers/vector2D.h">`vector2D.h`</a>
  - This contains 2D math implementations like line and polygon construction, intersection and collision detection and rotation.
### Project's source codes (Updated)
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/UnicodeTrial.cpp">`UnicodeTrial.cpp`</a>
  - This is the source code that tests for the display of unicode characters using SDL_TTF.
  - https://github.com/Wildude/SDL2-Project/assets/122345410/7c89478f-d892-4ce8-ad3e-901efd9367fb
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/SurfaceDrawingTrial.cpp">`SurfaceDrawingTrial.cpp`</a>
  - This is the source code that tests if a surface can be manipulated.
  - ![SurfaceEditor](https://github.com/Wildude/SDL2-Project/assets/122345410/5ea825ad-2712-4e34-8d5c-147fc4284d35)
  - ![SurfaceEditor2](https://github.com/Wildude/SDL2-Project/assets/122345410/aee43dfa-0174-47b6-8657-ea557a854b83)
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/GraphDrawer.cpp">`GraphDrawer.cpp`</a>
  - This is the source code that draws the graphs of different mathematical functions.
  - It also draws the area.
  - https://github.com/Wildude/SDL2-Project/assets/122345410/bdbc4fd8-3f98-4e41-bca0-65f3370c0ae7
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/AK47test.cpp">`AK47test.cpp`</a>
  - This source code is for an automatic rifle shooting animation.
  - it contains shooting sound so be not surprized.
  - press "Enter" to reposition the rifle, use mouse for aim and left click for shoot.
  - Your shots won't keep going if you don't move your mouse (still trying to fix that).
  - You can also use "space" for a more smooth shooting but you can't aim if you hold it (also trying to fix that).
  - use this executable to test it <a href = "https://github.com/Wildude/SDL2-Project/blob/main/Executables/AK47test.exe">`AK47test.exe`</a>
  - ![AK47test](https://github.com/user-attachments/assets/d0195a88-ee2f-4e77-bd4a-e18709065052)
  - https://github.com/user-attachments/assets/19aff586-493d-43e2-bd65-8a3b980b9f53
- <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Rigid_body.cpp">`Rigid_body.cpp`</a>
  - This source code contains a 2D rag doll animation.
  - It's an improved version that shows the body from a slightly angled front (rather than the side as in older version).
  - The algorithm used is a little more complex than before.
  - And while it works for when the body is static, it shows clear abnormalities for when it's repositioned and/or rotated.
  - It uses a rectangle polygon whose center is the geometric center and whose vertices are the vertices of the particular image.
  - Other body parts are repositioned relative to the center by inputing an angle which is a ray casted until the edge of the rectangle.
  - The angle is compensated for when the image is rotated.
  - This involves the rather erroneous `rotate_C()` function, which is assumed to be the reason for the abnormality.
  - https://github.com/user-attachments/assets/248677c9-9a7b-4908-a524-6554671a8c1a

