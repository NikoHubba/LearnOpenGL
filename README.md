# Random notes

## Tools used to support OpenGL:

- GLFW for OS-specific operations
- GLAD to load correct implementations

I plan on getting

- vcpkg to manage these tools/libraries/packages
- glm to use GLSL-like math expression in source code. Like veci.
- fmt for python-like output formatting
- clang-tidy to start complying with the C++ Core Guidelines: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- Dear imGUI for in-game UI
- Qt for external UI

## How GLFW's window coordinates and OpenGL's Normalized Device Coordinates (NDC) are structured

<img width="746" height="669" alt="image" src="https://github.com/user-attachments/assets/e413e105-1324-45cc-b865-7d6cf0026fcd" />

Where x and y are width and height respectively, set when calling $glViewport()$. Keep in mind the y-axis is positive.

Luckily you can convert between them (OpenGL Doc: https://registry.khronos.org/OpenGL-Refpages/gl4/):

Let $(x_{nd}, y_{nd})$ be NDC. The windows coordinates $(x_w,y_w)$
are computed as follows:

$x_w = (x_{nd} + 1)(\frac{width}{2}) + x$

$y_w = (y_{nd} + 1)(\frac{height}{2}) + y$

As mentioned x and y are set when calling $glViewPort()$. Their initial value is 0, making them insignificant in the equation. Conversely, $(x_{nd},y_{nd})$ can be found by:

$x_{nd} = (\frac{x_w}{width} * 2) - 1$

$y_{nd} = -(\frac{y_w}{height}*2) - 1$

Note how the sign of $y_{nd}$ is flipped; where window coordinates work with a flipped y-axis, NDC does not.
