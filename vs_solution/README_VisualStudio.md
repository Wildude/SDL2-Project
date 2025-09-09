# SDL2 Project - Visual Studio Setup Guide

This guide provides step-by-step instructions to set up and build the SDL2 C++ project using Visual Studio on Windows.

## Prerequisites

### Required Software
1. **Visual Studio 2022** (or 2019) with C++ development workload
2. **SDL2 Development Libraries** for Visual Studio
3. **Git** (for cloning repositories if needed)

### SDL2 Development Libraries Setup

#### Option 1: Using vcpkg (Recommended)
```bash
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat

# Install SDL2 and related libraries
vcpkg install sdl2:x64-windows
vcpkg install sdl2-ttf:x64-windows
vcpkg install sdl2-image:x64-windows
vcpkg install sdl2-mixer:x64-windows
vcpkg install sdl2-net:x64-windows
vcpkg install sdl2-gfx:x64-windows
vcpkg install lua:x64-windows
vcpkg install zlib:x64-windows

# Integrate with Visual Studio
vcpkg integrate install
```

#### Option 2: Manual Download
Download the following from the official SDL2 websites:
- SDL2 Development Libraries
- SDL2_ttf
- SDL2_image
- SDL2_mixer
- SDL2_net
- SDL2_gfx
- Lua 5.1 or 5.4
- zlib

Extract all libraries to a common directory (e.g., `C:\SDL2`).

## Project Structure

```
SDL2-Project/
├── vs_solution/           # Visual Studio project files
│   ├── SDL2_Project.sln   # Main solution file
│   ├── SDL2_Core.vcxproj  # SDL core library
│   ├── SDL2_BAS.vcxproj   # Basic framework library
│   └── SDL2_Framework.vcxproj # Main application
├── core/                  # Framework source code
│   ├── SDL/               # SDL-specific components
│   └── BAS/               # Basic framework components
├── tests/src/             # Test/demo applications
├── src/                   # External libraries and headers
├── Executables/           # Output directory (created by build)
└── [assets]/             # Fonts, Images, Files directories
```

## Build Instructions

### Step 1: Initial Setup
```bash
# Run the setup script to copy DLLs and assets
vs_solution\setup_build.bat
```

### Step 2: Open in Visual Studio
1. Open `vs_solution/SDL2_Project.sln` in Visual Studio
2. The solution contains three projects:
   - **SDL2_Core**: SDL-specific framework library
   - **SDL2_BAS**: Basic framework components
   - **SDL2_Framework**: Main application with all demos

### Step 3: Configure Dependencies (if using manual setup)

If you didn't use vcpkg integration, configure the include and library paths:

1. Right-click on each project → Properties
2. Go to **VC++ Directories**
3. Add to **Include Directories**:
   ```
   $(SolutionDir)..\src\include
   $(SolutionDir)..\src\include\SDL2
   C:\SDL2\include (or your SDL2 path)
   ```
4. Add to **Library Directories**:
   ```
   $(SolutionDir)..\src\lib
   C:\SDL2\lib\x64 (or your SDL2 lib path)
   ```

### Step 4: Build the Solution
1. Select **Release** or **Debug** configuration
2. Select **x64** platform
3. Build → Build Solution (F7)

### Step 5: Run the Applications
1. Navigate to the `Executables/` folder
2. Run any of the generated `.exe` files
3. Each executable demonstrates different features of the framework

## Available Demo Applications

The project builds the following demo applications:

### GUI Components
- `UI_test.exe` - Main UI demonstration
- `UI_test2.exe` - Extended UI components
- `CheckBoxTest.exe` - Checkbox functionality
- `DropDownTest.exe` - Dropdown menus
- `SliderTest.exe` - Slider controls
- `SpinBoxTest.exe` - Spin box controls
- `InputBoxTest.exe` - Text input
- `LabelAreaTest.exe` - Label areas
- `RadioButtonTest.exe` - Radio buttons

### Graphics & Multimedia
- `ImageTest.exe` - Image handling
- `Texture_mapper.exe` - Texture mapping
- `Tilemaptest.exe` - Tile-based graphics
- `video_test.exe` - Video playback

### Physics & Game Logic
- `bounding_box_test.exe` - Physics simulation
- `State_test.exe` - State management
- `State_test2.exe` - Advanced state management

### Scripting & Network
- `script_test.exe` - Lua scripting integration
- `NetworkTrial.exe` - Network functionality
- `xmltest.exe` - XML parsing

## Troubleshooting

### Common Issues

1. **Missing DLLs**
   - Ensure all required DLLs are in the `Executables/` folder
   - Check that the DLLs match your system architecture (x64)

2. **Linker Errors**
   - Verify all library paths are correctly configured
   - Ensure you're using the correct library files (.lib for linking)

3. **Include Path Issues**
   - Double-check include directory paths
   - Ensure SDL2 headers are accessible

4. **Runtime Errors**
   - Make sure all asset files (fonts, images) are copied to `Executables/`
   - Check that the working directory is set correctly

### Build Output
- Libraries: `build/$(Configuration)/SDL2_Core/` and `build/$(Configuration)/SDL2_BAS/`
- Executables: `Executables/` folder
- Intermediate files: `build/$(Configuration)/SDL2_Framework/`

## Advanced Configuration

### Custom Build Settings
You can modify the project properties for:
- Additional compiler flags
- Custom preprocessor definitions
- Specific library configurations

### Adding New Demo Applications
1. Add your `.cpp` file to `tests/src/`
2. Update the `SDL2_Framework.vcxproj` file to include the new source
3. Rebuild the solution

### Library Dependencies
The project links with:
- SDL2 core libraries
- FFmpeg libraries (for video support)
- Lua (for scripting)
- zlib (for compression)
- Windows system libraries

## Support

For issues with:
- **SDL2 setup**: Check official SDL2 documentation
- **Visual Studio**: Microsoft documentation
- **Project-specific**: Check the main project README.md

## License
This project follows the same license as the original SDL2-Project repository.
