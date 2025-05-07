// GUI of game
/* Note
* This is a simplified version of the GUI class.
* The actual version has scripting and ECS features.
*/
class GUI
{
public:
    GUI() {}
    GUI(const GUI& gui) {
        // Copy constructor implementation
    }
    GUI& operator=(const GUI& gui) {
        // Assignment operator implementation
        if (this != &gui) {
            // Copy the data members from gui to this object
        }
        return *this;
    }
    ~GUI() {
        // Destructor implementation
        // Clean up any resources if needed
    }
    // GUI related methods and members go here
    SDL_Rect box; // 16 bytes
    SDL_Color col1, col2; // 2 * 4 bytes
    string text; // 24 bytes
    FONT font; // 12 bytes
    // total = 66 bytes
    // GUI related methods and members go here

    /*  
    * This class is used to represent the GUI of the game.
    * It contains all the information about the GUI,
    * buttons, text boxes, text lists, etc.
    * features:
    * 1. Hover (animation, sound)
    * 2. click (animation, sound)
    * 3. drag (animation, sound)
    * 4. drop (animation, sound)
    * 5. scroll (animation, sound)
    * 6. resize (animation, sound)
    */
};
