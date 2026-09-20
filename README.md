The README will contain random notes for now.

First off, how GLFW's window coordinates and OpenGL's Normalized Device Coordinates (NDC) are structured:

<img width="746" height="669" alt="image" src="https://github.com/user-attachments/assets/e413e105-1324-45cc-b865-7d6cf0026fcd" />

Luckily you can convert between them (OpenGL Doc: https://registry.khronos.org/OpenGL-Refpages/gl4/):
Let $$(x_nd, y_nd)$$


