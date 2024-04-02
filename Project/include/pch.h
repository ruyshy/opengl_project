#pragma once

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <stddef.h>

#include <Windows.h>
#include <cstring>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

#define WIN32_LEAN_AND_MEAN


class OpenGLWindow;
class MainWindow;

class GObjectBase;
class GSceneBase;
class MainScene;

class Shader;

class Camera;

class VertexBufferObject2D;
class Texture2D;
class Sprite;

// opengl
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

#include <ft2build.h>
#include FT_FREETYPE_H  
#pragma comment(lib,"freetype.lib")

//fmod
#include "fmod.hpp"
#include <conio.h>

#pragma comment(lib, "fmod_vc.lib")

// user include
#include <OpenGL/Window/MainWindow.h>

// user utill
#include <Macro/delete_macro.h>
#include <Macro/Transform2D_Macro.h>


#endif // !PCH_H
