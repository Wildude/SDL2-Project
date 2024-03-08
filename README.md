# SDL2-Project
## Preface
### <i>PREVIEW</i>
![AAU_intro](https://github.com/Wildude/SDL2-Project/blob/main/Images/AAU_intro.gif)
![CS_intro](https://github.com/Wildude/SDL2-Project/blob/main/Images/CS_intro.gif)
<br>
<bold>source code: <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/AAU_intro.cpp">`AAU_intro.cpp`</a> </bold> <br> 
## <underline>
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
### These headers helped in the implementation of the following source codes:
1. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/angle_finder.cpp">`angle_finder.cpp`</a>
  - finds the angle between two points on the 2D plane.
2. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/center_finder.cpp">`center_finder.cpp`</a>
  - finds the center of a polygon on the 2D plane.
3. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/center_finder_iy.cpp">`center_finder_iy.cpp`</a>
  - same as 3.
4. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/center_finder_SDL.cpp">`center_finder_SDL.cpp`</a>
  - same as 3.
5. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/class_making.cpp">`class_making.cpp`</a>
  - tests whether a font drawing class works or not.
6. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/collision_detection.cpp">`collision_detection.cpp`</a>
  - tests collision detection and also resolution algorithm between two polygons on the 2D plane.
7. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/gun_animation.cpp">`gun_animation.cpp`</a>
  - does a simple semi-automatic gun animation (shooting, reloading and empty magazine).
8. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/intersection_sim.cpp">`intersection_sim.cpp`</a>
  - tests the intersection between lines on the 2D plane.
9. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Ipolygon_rotator.cpp">`Ipolygon_rotator.cpp`</a>
  - tests the rotation of a polygon on the 2D plane.
10. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/main.cpp">`main.cpp`</a>
  - tests the detection of mouth inside a polygon on the 2D plane.
11. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/physx1_1.cpp">`physx1_1.cpp`</a>
  - tests simple 2D linear kinematics.
12. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/physx1.cpp">`physx1.cpp`</a>
  - tests simple 2D linear kinematics with airdrag and gravity.
13. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/point_joiner.cpp">`point_joiner.cpp`</a>
  - Joins two user-defined points on the 2D plane into a line.
14. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Polygon_collision1.cpp">`Polygon_collision1.cpp`</a>
  - same as 6. but also with others in it.
15. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Polygon_drawer.cpp">`Polygon_drawer.cpp`</a>
  - simple regular polygon drawer.
16. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Polygon_drawer1_1.cpp">`Polygon_drawer1_1.cpp`</a>
  - same as 15. but with others in it.
17. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/Polygon_drawer2_0.cpp">`Polygon_drawer2_0.cpp`</a>
  - Irregular polygon drawer.
18. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/polygon_point.cpp">`polygon_point.cpp`</a>
  - same as 10. 
19. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/pP_detector.cpp">`pP_detector.cpp`</a>
  - same as 10.
20. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/rotator_demo.cpp">`rotator_demo.cpp`</a>
  - continuously rotates a line along it's initial point with a user-defined speed.
21. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/rotator.cpp">`rotator.cpp`</a>
  - control the length and angle of a line.
22. <a href = "https://github.com/Wildude/SDL2-Project/blob/main/source_codes/SDL2_main.cpp">`SDL2_main.cpp`</a>
  - simple SDL2 test.
### Of all 21 source codes, only 13, 15 and 17 were submitted in the form of control flow in a single CPP code.
The shortcuts of the executables are found in the repo's home directory/page.
here are the executables: <br>
<a href = "https://github.com/Wildude/SDL2-Project/blob/main/Polygon_drawer.exe%20-%20Shortcut.lnk">`Polygon_drawer`</a> <br>
<a href = "https://github.com/Wildude/SDL2-Project/blob/main/Polygon_drawer2_0.exe%20-%20Shortcut.lnk">`Polygon_drawer2_0`</a> <br>
<a href = "https://github.com/Wildude/SDL2-Project/blob/main/point_joiner.exe%20-%20Shortcut.lnk">`point_joiner`</a> <br>
Here's a demo for two of them: <br>
Compiling code using terminal 😢💀: <br>
https://github.com/Wildude/SDL2-Project/assets/122345410/63028f1f-ad0f-4e7c-b880-19e0c5259f5a <br>
point_joiner.exe: <br>
https://github.com/Wildude/SDL2-Project/assets/122345410/5a22740b-db12-451f-865e-baf25415adc1 <br>
Polygon_drawer2_0.exe: <br>
https://github.com/Wildude/SDL2-Project/assets/122345410/da971d40-32d6-47e9-ab47-d2f9719ef8ca <br>
### this repository is out of date and will be updated as soon as this project is continued.
