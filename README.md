# glut-computer-graphics-3d-primitives-and-basics

This project demonstrates a basic 3D graphics scene using OpenGL and GLUT (OpenGL Utility Toolkit) in C. The scene includes a cube that can be manipulated using keyboard inputs to move, scale, and rotate. The project utilizes lighting effects, including ambient light and a spotlight.

![3dbasicglut](https://github.com/kodiidok/glut-computer-graphics-3d-primitives-and-basics/assets/88420631/cd33e05d-cf35-4950-a9c7-0b4e0cb7d1be)

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
- [Controls](#controls)
- [Libraries Used](#libraries-used)
- [License](#license)

## Features
- 3D cube rendering with various transformations (translation, rotation, scaling).
- User-controlled camera with movement in different directions.
- Lighting effects, including ambient light and a spotlight.
- Information display on keypress events.
- Simple and intuitive keyboard controls.

## Getting Started
Follow the steps below to compile and run the project:

1. Ensure you have the necessary dependencies installed:
   - OpenGL
   - GLUT (OpenGL Utility Toolkit)
   - SOIL2 (Simple OpenGL Image Library)

2. Clone the repository:
   ```bash
   git clone <repository-url>
   ```

3. Navigate to the project directory:
   ```bash
   cd 3D-Graphics-Project
   ```

4. Compile the project using a C compiler (e.g., GCC):
   ```bash
   gcc -o 3DGraphicsProject main.c -lGL -lGLU -lglut -lSOIL2 -lm
   ```

5. Run the compiled executable:
   ```bash
   ./3DGraphicsProject
   ```

## Controls
- **Up Arrow:** Move the cube up (with different effects based on modifiers).
- **Down Arrow:** Move the cube down (with different effects based on modifiers).
- **Left Arrow:** Move the cube to the left.
- **Right Arrow:** Move the cube to the right.
- **W:** Move the cube up.
- **A:** Move the cube to the left.
- **S:** Move the cube down.
- **D:** Move the cube to the right.
- **Alt + Up Arrow/Down Arrow/Left Arrow/Right Arrow:** Rotate the camera (with different effects based on modifiers).
- **Shift + Up Arrow/Down Arrow:** Zoom in/out (affecting camera position or cube scaling).
- **Ctrl + Up Arrow/Down Arrow:** Scale up/down the cube.

## Libraries Used
- OpenGL: Cross-platform 3D graphics API.
- GLUT (OpenGL Utility Toolkit): Toolkit for creating OpenGL applications.
- SOIL2 (Simple OpenGL Image Library): Library for loading image files.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
