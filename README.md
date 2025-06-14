# SDL2-Project
## Recent changes
- Added a docs and design folder for clean system design.
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
### Running/Walking animation
![ProjectionGPT](https://github.com/user-attachments/assets/ee35a0d5-60f9-4c76-beab-d5b42c19cc44)
![ProjectionMine](https://github.com/user-attachments/assets/53918aca-7d63-454a-a6cf-933e6f3294f7)
- a 3rd update to the walking/running animation based on a concept of math not expected to be used in the game.
- 3D illusion using 2D projection
- Using help of GPT, a projection algorithm was obtained and implemented.
- The green trapezium controlled by a slider is from GPTs code.
- The other one is from the project's code.
## How to use?
open up executables folder and run the programs.
