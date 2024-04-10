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
#include <random>
#include <mutex>

#include <Windows.h>
#include <cstring>
#include <mmsystem.h>
#include <time.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

#define WIN32_LEAN_AND_MEAN


class OpenGLWindow;
class MainWindow;
class VertexBufferObject2D;
class Texture2D;
class Transform2D;

class Game;
class ObjectBase;
class SceneBase;


// opengl
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include <ft2build.h>
#include FT_FREETYPE_H  
#pragma comment(lib,"freetype.lib")

//fmod
#include "fmod.hpp"
#include <conio.h>

#pragma comment(lib, "fmod_vc.lib")

// user include
#include <OpenGL/Window/OpenGLWindow.h>
#include <OpenGL/Window/MainWindow.h>
#include <OpenGL/Shader/Shader.h>
#include <OpenGL/TextRender/TextRendering.h>

#include <OpenGL/Camera/Camera.h>

#include <Game/Event/Dispatcher.h>

#include <OpenGL/Sprite/Sprite.h>
#include <Game/QuadTree/QuadTree.h>


// user utill
#include <utill/string_utils.h>
#include <utill/stb_image.h>

#include <Macro/delete_macro.h>


#endif // !PCH_H
