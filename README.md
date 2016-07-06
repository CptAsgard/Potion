# Potion
A bootstrapping project for real-time applications. Is meant as a base to avoid direct OpenGL. Potion has the following features.

- Stateless rendering architecture for minimalizing state changes
- Build process to integrate an 'Assets' folder into the build
- Support for render textures and image effects
- Support for switching materials and shaders intuitively
   - Automatically reassigns any assignments done to a material, such as textures, if the shader is changed

Potion uses ASSIMP for model loading, and integrates this support directly. It is extremely easy in Potion to create new models from a file, create a procedurally generated mesh, or create an empty dummy object. These can then all be added to the scene graph, or not, allowing you full control over how you want to run your project.

# How to Use
Currently, Potion is not ready for use in a project. However, the project is being actively developed. If the project comes to a usable state, I will describe how to use Potion in your projects.
