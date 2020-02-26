# Xela Graphics Documentation

## Table of Contents
* [Data](#data)
  * [XelaDefinitions.h](#xeladefinitionsh)
    * [XelaVectors](#xelavectors)
    * [Shaders](#shaders)
      * [Data types](#data-types)
      * [Texture definitions](#texture-definitions)
    * [Errors](#errors)
    * [Keys](#keys)
  * [XelaEvents.h](#xelaeventsh)
    * [xelaProcessEvents()](#xelaprocessevents)
    * [xelaSetKeyCallback()](#xelasetkeycallback)
    * [xelaSetMouseButtonCallback()](#xelasetmousebuttoncallback)
    * [xelaSetCursorPosCallback()](#xelasetcursorposcallback)
  * [XelaFont.h](#xelafonth)
    * [Class XelaFont](#class-xelafont)
      * [XelaFont()](#xelafont)
      * [loadFont()](#loadfont)
* [Graphics](#graphics)
  * [XelaWindow.h](#xelawindowh)
    * [Class XelaWindow](#class-xelawindow)
      * [XelaWindow()](#xelawindow)
      * [captureMouse()](#capturemouse)
      * [hideMouse()](#hidemouse)
      * [showMouse()](#showmouse)
      * [update()](#update)
      * [setShouldClose()](#setshouldclose)
      * [setClearColor()](#setclearcolor)
      * [setAlwaysOnTop()](#setalwaysontop)
      * [setOpacity()](#setopacity)
      * [setSize()](#setsize)
      * [maximize()](#maximize)
      * [shouldClose()](#shouldclose)
      * [getSize()](#getsize)
      * [getResolution()](#getresolution)
      * [getTime()](#gettime)
      * [getTitle()](#gettitle)
      * [getGLFWwindow()](#getglfwwindow)
  * [XelaObject.h](#xelaobjecth)
    * [Class XelaObject](#class-xelaobject)
      * [XelaObject()](#xelaobject)
      * [addIndex()](#addindex)
      * [addIndices()](#addindices)
      * [clearIndices()](#clearindices)
      * [setIndices()](#setindices)
      * [clearVertexData()](#clearvertexdata)
      * [addVertexData()](#addvertexdata)
      * [setVertexData()](#setvertexdata)
      * [setDataUpdateFrequency()](#setdataupdatefrequency)
      * [updateData()](#updatedata)
      * [draw()](#draw)
      * [getSize()](#xelaobject-getsize)
  * [XelaShader.h](xelashaderh-)
    * [Class XelaShader](#class-xelashader)
      * [XelaShader()](#xelashader)
      * [setShader()](#setshader)
      * [addImage()](#addimage)
      * [addTexture()](#addtexture)
      * [addShaderCallback()](#addshadercallback)
      * [removeShaderCallback()](#removeshadercallback)
      * [use()](#use)
      * [addUniform()](#adduniform)
      * [addUniformVec2()](#adduniformvec2)
      * [addUniformVec3()](#adduniformvec3)
      * [addUniformVec4()](#adduniformvec4)
      * [getTexList()](#gettexlist)
      * [getProgram()](#getprogram)
  * [XelaText.h](#xelatexth)
    * [Class XelaText](#class-xelatext)
      * [XelaText()](#xelatext)
      * [setFont()](#setfont)
      * [setText()](#settext)
      * [setColor()](#setColor)
      * [setPosition()](#setposition)
      * [setScale()](#setscale)
      * [draw()](#xelatext-draw)
      * [getFont()](#getfont)
      * [getSize()](#xelatext-getsize)

## Data
### XelaDefinitions.h
Contains most definitions and structs used throughout the library
<br><br>

#### XelaVectors

Structures used to store coordinate/color data.
<br><br>

```C++
template<typename T>
struct XelaVec2 {
	T x, y;
};
```C++
Contains 2 variables of type T. Used in various places as an easy means of storing coordinate/color values.
<br><br>

```C++
template<typename T>
struct XelaVec3 {
	T x, y, z;
};
```
Contains 3 variables of type T. Used in various places as an easy means of storing coordinate/color values.
<br><br>

```C++
template<typename T>
struct XelaVec4 {
	T x, y, z, w;
};
```
Contains 4 variables of type T. Used in various places as an easy means of storing coordinate/color values.
<br><br>

#### Shaders
Definitions meant to be used with XelaShaders.
<br><br>

##### Data types
The different data types that can be sent as uniforms to a shader.
<br><br>

```C++
#define XELA_BOOL 0
```
Boolean data type. In glsl: bool, vec2, vec3, etc.
<br><br>

```C++
#define XELA_INT 1
```
Integer data type. In glsl: int, ivec2, ivec3, etc.
<br><br>

```C++
#define XELA_UNSIGNED_INT 2
```
Unsigned integer data type. In glsl: uint, uvec2, uvec3, etc.
<br><br>

```C++
#define XELA_FLOAT 3
```
Float data type. In glsl: float, vec2, vec3, etc.
<br><br>

```C++
#define XELA_DOUBLE 4
```
Double data type. In glsl: double, dvec2, dvec3, etc.
<br><br>

##### Texture definitions
Definitions to describe texture/image data. These are all just redefinitions of things defined by glfw but with the xela prefix.
<br><br>

```C++
#define XELA_R GL_R
```
Used when the image only has a red component.
<br><br>

```C++
#define XELA_RG GL_RG
```
Used when the image has a red and green component.
<br><br>

```C++
#define XELA_RGB GL_RGB
```
Used when the image has a red, green, and blue component.
<br><br>

```C++
#define XELA_RGBA GL_RGBA
```
Used when the image has a red, green, blue, and alpha component.
<br><br>

```C++
#define XELA_SRGB GL_SRGB
```
Used when the image has a red, green, and blue component in the sRGB color space.
<br><br>

```C++
#define XELA_SRGBA GL_SRGB_ALPHA
```
Used when the image has a red, green, blue, and alpha component in the sRGB color space.
<br><br><br><br>

#### Errors
Definitions for errors that Xela Graphics may return.
<br><br>

```C++
#define XELA_ERROR_UNKNOWN 0
```
Returned for generic errors or unknown errors.
<br><br>

```C++
#define XELA_SUCCESS 1
```
Returned if a function is successful
<br><br>

```C++
#define XELA_ERROR_INIT 2
```
Returned if there's an error initializing glfw.
<br><br>

```C++
#define XELA_ERROR_WINDOW 3
```
Returned if there's an error creating a glfwWindow when constructing a XelaWindow object.
<br><br>

```C++
#define XELA_ERROR_INIT_GLEW 4
```
Returned if there's an error initializing glew.
<br><br>

```C++
#define XELA_ERROR_FREETYPE_INIT 5
```
Returned if there's an error initializing FreeType.
<br><br>

```C++
#define XELA_ERROR_FREETYPE_LOAD_CHAR 6
```
Returned if there's an error loading a character with FreeType.
<br><br>

```C++
#define XELA_ERROR_UNKNOWN_FORMAT 7
```
Returned if an input file has an unrecognized format and is unable to be used.
<br><br>

#### Keys
Glfw key definitions have been redefined with the XELA_ prefix. This is mostly for consistency in having everything in the library
start with xela. In some cases, the name of the key was shortened to make typing it a little less tedious.
<details>
  <summary>Full list of key definitions</summary>
  
  ```C++
  #define XELA_PRESS GLFW_PRESS
  #define XELA_RELEASE GLFW_RELEASE
  //=====================================================================
  #define XELA_MOUSE_LEFT GLFW_MOUSE_BUTTON_LEFT
  #define XELA_MOUSE_RIGHT GLFW_MOUSE_BUTTON_RIGHT
  #define XELA_MOUSE_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE
  #define XELA_MOUSE_LAST GLFW_MOUSE_BUTTON_LAST
  #define XELA_MOUSE_1 GLFW_MOUSE_BUTTON_1
  #define XELA_MOUSE_2 GLFW_MOUSE_BUTTON_2
  #define XELA_MOUSE_3 GLFW_MOUSE_BUTTON_3
  #define XELA_MOUSE_4 GLFW_MOUSE_BUTTON_4
  #define XELA_MOUSE_5 GLFW_MOUSE_BUTTON_5
  #define XELA_MOUSE_6 GLFW_MOUSE_BUTTON_6
  #define XELA_MOUSE_7 GLFW_MOUSE_BUTTON_7
  #define XELA_MOUSE_8 GLFW_MOUSE_BUTTON_8
  //=====================================================================
  #define XELA_UNKNOWN GLFW_KEY_UNKNOWN
  #define XELA_SPACE GLFW_KEY_SPACE /*   */
  #define XELA_APOSTROPHE GLFW_KEY_APOSTROPHE /* ' */
  #define XELA_COMMA GLFW_KEY_COMMA/* , */
  #define XELA_MINUS GLFW_KEY_MINUS /* - */
  #define XELA_PERIOD GLFW_KEY_PERIOD /* . */
  #define XELA_SLASH GLFW_KEY_SLASH /* / */
  #define XELA_0 GLFW_KEY_0 /* 0 */
  #define XELA_1 GLFW_KEY_1 /* 1 */
  #define XELA_2 GLFW_KEY_2 /* 2 */
  #define XELA_3 GLFW_KEY_3 /* 3 */
  #define XELA_4 GLFW_KEY_4 /* 4 */
  #define XELA_5 GLFW_KEY_5 /* 5 */
  #define XELA_6 GLFW_KEY_6 /* 6 */
  #define XELA_7 GLFW_KEY_7 /* 7 */
  #define XELA_8 GLFW_KEY_8 /* 8 */
  #define XELA_9 GLFW_KEY_9 /* 8 */
  #define XELA_SEMICOLON GLFW_KEY_SEMICOLON /* ; */
  #define XELA_EQUAL GLFW_KEY_EQUAL /* = */
  #define XELA_A GLFW_KEY_A /* A */
  #define XELA_B GLFW_KEY_B /* B */
  #define XELA_C GLFW_KEY_C /* C */
  #define XELA_D GLFW_KEY_D /* D */
  #define XELA_E GLFW_KEY_E /* E */
  #define XELA_F GLFW_KEY_F /* F */
  #define XELA_G GLFW_KEY_G /* G */
  #define XELA_H GLFW_KEY_H /* H */
  #define XELA_I GLFW_KEY_I /* I */
  #define XELA_J GLFW_KEY_J /* J */
  #define XELA_K GLFW_KEY_K /* K */
  #define XELA_L GLFW_KEY_L /* L */
  #define XELA_M GLFW_KEY_M /* M */
  #define XELA_N GLFW_KEY_N /* N */
  #define XELA_O GLFW_KEY_O /* O */
  #define XELA_P GLFW_KEY_P /* P */
  #define XELA_Q GLFW_KEY_Q /* Q */
  #define XELA_R GLFW_KEY_R /* R */
  #define XELA_S GLFW_KEY_S /* S */
  #define XELA_T GLFW_KEY_T /* T */
  #define XELA_U GLFW_KEY_U /* U */
  #define XELA_V GLFW_KEY_V /* V */
  #define XELA_W GLFW_KEY_W /* W */
  #define XELA_X GLFW_KEY_X /* X */
  #define XELA_Y GLFW_KEY_Y /* Y */
  #define XELA_Z GLFW_KEY_Z /* Z */
  #define XELA_LEFT_BRACKET GLFW_KEY_LEFT_BRACKET /* [ */
  #define XELA_BACKSLASH GLFW_KEY_BACKSLASH /* \ */
  #define XELA_RIGHT_BRACKET GLFW_KEY_RIGHT_BRACKET /* ] */
  #define XELA_GRAVE GLFW_KEY_GRAVE_ACCENT /* ` */
  #define XELA_WORLD_1 GLFW_KEY_WORLD_1 /* non-US #1 */
  #define XELA_WORLD_2 GLFW_KEY_WORLD_2 /* non-US #2 */
  #define XELA_ESCAPE GLFW_KEY_ESCAPE /* Escape */
  #define XELA_ENTER GLFW_KEY_ENTER /* Enter */
  #define XELA_TAB GLFW_KEY_TAB /* Tab */
  #define XELA_BACKSPACE GLFW_KEY_BACKSPACE /* Backspace */
  #define XELA_INSERT GLFW_KEY_INSERT /* Insert */
  #define XELA_DELETE GLFW_KEY_DELETE /* Delete */
  #define XELA_RIGHT GLFW_KEY_RIGHT /* Right Arrow */
  #define XELA_LEFT GLFW_KEY_LEFT /* Left Arrow */
  #define XELA_DOWN GLFW_KEY_DOWN /* Down Arrow */
  #define XELA_UP GLFW_KEY_UP /* Up Arrow */
  #define XELA_PAGE_UP GLFW_KEY_PAGE_UP /* Page Up */
  #define XELA_PAGE_DOWN GLFW_KEY_PAGE_DOWN /* Page Down */
  #define XELA_HOME GLFW_KEY_HOME /* Home */
  #define XELA_END GLFW_KEY_END /* End */
  #define XELA_CAPS_LOCK GLFW_KEY_CAPS_LOCK /* Caps Lock */
  #define XELA_SCROLL_LOCK GLFW_KEY_SCROLL_LOCK /* Scroll Lock */
  #define XELA_NUM_LOCK GLFW_KEY_NUM_LOCK /* Num Lock */
  #define XELA_PRINT_SCREEN GLFW_KEY_PRINT_SCREEN /* Print Screen */
  #define XELA_PAUSE GLFW_KEY_PAUSE /* Pause */
  #define XELA_F1 GLFW_KEY_F1 /* F1 */
  #define XELA_F2 GLFW_KEY_F2 /* F2 */
  #define XELA_F3 GLFW_KEY_F3 /* F3 */
  #define XELA_F4 GLFW_KEY_F4 /* F4 */
  #define XELA_F5 GLFW_KEY_F5 /* F5 */
  #define XELA_F6 GLFW_KEY_F6 /* F6 */
  #define XELA_F7 GLFW_KEY_F7 /* F7 */
  #define XELA_F8 GLFW_KEY_F8 /* F8 */
  #define XELA_F9 GLFW_KEY_F9 /* F9 */
  #define XELA_F10 GLFW_KEY_F10 /* F10 */
  #define XELA_F11 GLFW_KEY_F11 /* F11 */
  #define XELA_F12 GLFW_KEY_F12 /* F12 */
  #define XELA_F13 GLFW_KEY_F13 /* F13 */
  #define XELA_F14 GLFW_KEY_F14 /* F14 */
  #define XELA_F15 GLFW_KEY_F15 /* F15 */
  #define XELA_F16 GLFW_KEY_F16 /* F16 */
  #define XELA_F17 GLFW_KEY_F17 /* F17 */
  #define XELA_F18 GLFW_KEY_F18 /* F18 */
  #define XELA_F19 GLFW_KEY_F19 /* F19 */
  #define XELA_F20 GLFW_KEY_F20 /* F20 */
  #define XELA_F21 GLFW_KEY_F21 /* F21 */
  #define XELA_F22 GLFW_KEY_F22 /* F22 */
  #define XELA_F23 GLFW_KEY_F23 /* F23 */
  #define XELA_F24 GLFW_KEY_F24 /* F24 */
  #define XELA_F25 GLFW_KEY_F25 /* F25 */
  #define XELA_NUMPAD_0 GLFW_KEY_KP_0 /* Numpad 0 */
  #define XELA_NUMPAD_1 GLFW_KEY_KP_1 /* Numpad 1 */
  #define XELA_NUMPAD_2 GLFW_KEY_KP_2 /* Numpad 2 */
  #define XELA_NUMPAD_3 GLFW_KEY_KP_3 /* Numpad 3 */
  #define XELA_NUMPAD_4 GLFW_KEY_KP_4 /* Numpad 4 */
  #define XELA_NUMPAD_5 GLFW_KEY_KP_5 /* Numpad 5 */
  #define XELA_NUMPAD_6 GLFW_KEY_KP_6 /* Numpad 6 */
  #define XELA_NUMPAD_7 GLFW_KEY_KP_7 /* Numpad 7 */
  #define XELA_NUMPAD_8 GLFW_KEY_KP_8 /* Numpad 8 */
  #define XELA_NUMPAD_9 GLFW_KEY_KP_9 /* Numpad 9 */
  #define XELA_NUMPAD_DECIMAL GLFW_KEY_KP_DECIMAL /* Numpad . */
  #define XELA_NUMPAD_DIVIDE GLFW_KEY_KP_DIVIDE /* Numpad / */
  #define XELA_NUMPAD_MULTIPLY GLFW_KEY_KP_MULTIPLY /* Numpad * */
  #define XELA_NUMPAD_SUBTRACT GLFW_KEY_KP_SUBTRACT /* Numpad - */
  #define XELA_NUMPAD_ADD GLFW_KEY_KP_ADD /* Numpad + */
  #define XELA_NUMPAD_ENTER GLFW_KEY_KP_ENTER /* Numpad Enter */
  #define XELA_NUMPAD_EQUAL GLFW_KEY_KP_EQUAL /* Numpad + */
  #define XELA_LEFT_SHIFT GLFW_KEY_LEFT_SHIFT /* Left Shift */
  #define XELA_LEFT_CONTROL GLFW_KEY_LEFT_CONTROL /* Left Control */
  #define XELA_LEFT_ALT GLFW_KEY_LEFT_ALT /* Left Alt */
  #define XELA_LEFT_SUPER GLFW_KEY_LEFT_SUPER /* Left Super */
  #define XELA_RIGHT_SHIFT GLFW_KEY_RIGHT_SHIFT /* Right Shift */
  #define XELA_RIGHT_CONTROL GLFW_KEY_RIGHT_CONTROL /* Right Control */
  #define XELA_RIGHT_ALT GLFW_KEY_RIGHT_ALT /* Right Alt */
  #define XELA_RIGHT_SUPER GLFW_KEY_RIGHT_SUPER /* Right Super */
  #define XELA_MENU GLFW_KEY_MENU /* Right Menu */
  #define XELA_LAST GLFW_KEY_LAST /* GLFW_KEY_MENU */
  ```
  
</details>
<br><br><br><br>

### XelaEvents.h *
Contains functions and definitions for handling events from glfw.
<br><br>

```C++
typedef void(*XelaKeyCallback)(XelaWindow *window, int key, int scancode, int action, int mods);
```
Function template for functions handling key events.
<br><br>

```
typedef void(*XelaMouseButtonCallback)(XelaWindow *window, int button, int action, int mods);
```
Function template for functions handling mouse button events.
<br><br>

```
typedef void(*XelaCursorPosCallback)(XelaWindow *window, double xpos, double ypos);
```
Function template for functions handling cursor position events.
<br><br>

#### xelaProcessEvents()
```C++
void xelaProcessEvents();
```
Processes any events currently listed.
<br><br>

#### xelaSetKeyCallback()
```C++
void xelaSetKeyCallback(XelaKeyCallback cb);
```
Sets a function to be called whenever a key event is processed.
<br><br>

#### xelaSetMouseButtonCallback()
```C++
void xelaSetMouseButtonCallback(XelaMouseButtonCallback cb);
```
Sets a function to be called whenever is mouse button event is processed.
<br><br>

#### xelaSetCursorPosCallback()
```C++
void xelaSetCursorPosCallback(XelaCursorPosCallback cb);
```
Sets a function to be called whenever the cursor position changes.
<br><br><br><br>

### XelaFont.h
Contains struct and class definitions for loading/storing/using fonts with FreeType.
<br><br>

#### Class XelaFont
An object that uses FreeType to load and store font data.
<br><br>

##### XelaFont()
```C++
XelaFont();
```
Creates a new XelaFont object.
<br><br>

##### loadFont()
```C++
int loadFont(std::string ttf, int size);
```
Loads a new font from a file. Size is the size to load the font at and ttf is the path to the font file. Returns one of XELA_SUCCESS, XELA_ERROR_UNKNOWN, XELA_ERROR_FREETYPE_INIT, or XELA_ERROR_UNKNOWN_FORMAT.
<br><br><br><br>

## Graphics

### XelaWindow.h
#### Class XelaWindow
Object representing the window that shows up on the user's screen.
<br><br>

##### XelaWindow()
```C++
XelaWindow(int sizeX, int sizeY, const char* title, bool fullscreen, int* success, XelaWindow* share = nullptr);
XelaWindow(int sizeX, int sizeY, const char* title, bool fullscreen, int* success, bool decorated, XelaWindow *share = nullptr);
```
Creates a new XelaWindow object.

sizeX and sizeY are the resolution of the window. If a value less than 0 is specified for either, that value will be set to the width or height of the primary monitor.

title is the title to display for the window.

fullscreen determines whether or not this window is fullscreen or windowed.

success is set to one of XELA_SUCCESS, XELA_ERROR_INIT, or XELA_ERROR_WINDOW.

Decorated determines whether or not the window border is decorated is fullscreen is false.

Share specifies the XelaWindow object to share a context with, and is set to nullptr by default.
<br><br>

##### captureMouse()
```C++
void captureMouse();
```
Prevents the mouse from leaving the window.
<br><br>

##### hideMouse()
```C++
void hideMouse();
```
Hides the mouse while it is over this window.
<br><br>

##### showMouse()
```C++
void showMouse();
```
Shows the mouse while it is over this window.
<br><br>

##### update()
```C++
void update();
```
Updates the window and processes any events that occurred since the last update. This should be called every frame.
<br><br>

##### setShouldClose()
```C++
void setShouldClose(bool close);
```
Sets whether or not this window should exit. Can be used to forcefully close the program. Automatically set to true if the user clicks the X at the top right of the window.
<br><br>

##### setClearColor()
```C++
void setClearColor(XelaVec4<float> rgba);
```
Sets the background color of the window. Default value is { 0, 0, 0, 1 }.
<br><br>

##### setAlwaysOnTop()
```C++
void setAlwaysOnTop(bool top);
```
Sets whether or not this window should be forced to the foreground of the user's screen. Default is false.
<br><br>

##### setOpacity()
```C++
void setOpactiy(float opa);
```
Sets the opacity of this window.
<br><br>

##### setSize()
```C++
void setSize(int sizeX, int sizeY);
```
Resizes the window to sizeX by sizeY.
<br><br>

##### maximize()
```C++
void maximize();
```
Maximizes the window.
<br><br>

##### shouldClose()
```C++
bool shouldClose();
```
Returns whether or not this window should be closed. This is meant to be used to allow a program to continue looping until the user tries to close it.
<br><br>

##### getSize()
```C++
void getSize(int *width, int*height);
```
Sets width and height to the size of the window.
<br><br>

##### getResolution()
```C++
void getResolution(int *width, int *height);
```
Sets width and height to the resolution the window is rendering at.
<br><br>

##### getTime()
```C++
double getTime();
```
Returns how much time has passed since glfw was first initializes in seconds.
<br><br>

##### getTitle()
```C++
const char *getTitle();
```
Returns the title this window uses.
<br><br>

##### getGLFWwindow()
```C++
GLFWwindow *getGLFWwindow();
```
Returns the glfwWindow this XelaWindow is using. This allows you to use advanced glfw functions not covered by Xela Graphics.
<br><br><br><br>

### XelaObject.h
#### Class XelaObject
Class containing all information about a single object that can be rendered on screen. Handles OpenGL's buffers so you only have to specify vertices and indices and the object can be rendered to the screen.
<br><br>

##### XelaObject()
```C++
XelaObject();
```
Creates a new XelaObject. Generates a new vertex array object, vertex buffer object, and element buffer object for storing vertex data.
<br><br>

##### addIndex()
```C++
void addIndex(XelaVec3<unsigned int> ind);
```
Adds a triangle to this object by specifying 3 indices.
<br><br>

##### addIndices()
```C++
void addIndices(std::vector<XelaVec3<unsigned int>> inds);
void addIndices(XelaVec3<unsigned int> *inds, int count);
```
Adds multiple triangles to this object by specifying a multiple of 3 indices. inds is an array of XelaVec3<unsigned int> and count is how big the array is if a vector isn't used.
<br><br>

##### clearIndices()
```C++
void clearIndices();
```
Removes all indices from this object, effectively erasing the object.
<br><br>

##### setIndices()
```C++
void setIndices(std::vector<XelaVec3<unsigned int>> inds);
void setIndices(XelaVec3<unsigned int> *inds, int count);
```
Clears all indices from this object and replaces them with inds.
<br><br>

##### clearVertexData()
```C++
void clearVertexData(int id);
```
Clears all vertex data with a given id.
<br><br>

##### addVertexData()
```C++
void addVertexData(float vec, int id);
void addVertexData(std::vector<float> vec, int id);
void addVertexData(float *vec, int count, int id);

void addVertexData(XelaVec2<float> vec, int id);
void addVertexData(std::vector<XelaVec2<float>> vec, int id);
void addVertexData(XelaVec2<float>* vec, int count, int id);

void addVertexData(XelaVec3<float> vec, int id);
void addVertexData(std::vector<XelaVec3<float>> vec, int id);
void addVertexData(XelaVec3<float>* vec, int count, int id);

void addVertexData(XelaVec4<float> vec, int id);
void addVertexData(std::vector<XelaVec4<float>> vec, int id);
void addVertexData(XelaVec4<float>* vec, int count, int id);
```
Adds a number of vertices to the object with a specified id. Vertices with the same id must have the same size, meaning you can not pass a XelaVec3<float> and XelaVec4<float> to the same id. If you attempt to do so, the function does nothing. Vertices at location 0 are used for size calculations, meaning those will be used to calculate minX, minY, minZ, maxX, maxY, and maxZ. When writing a shader in GLSL, this data is retrieved with `layout (location = <id>) in vec<size> vert;` where <id> is the id of the vertex data and <size> is the vector size of the data (2, 3, or 4). If the vertex data was sent a floats, not XelaVectors, the size is one and `vec<size>` should be replaces with `float`.
<br><br>

##### setVertexData()
```C++
void setVertexData(float vec, int id);
void setVertexData(std::vector<float> vec, int id);
void setVertexData(float *vec, int count, int id);

void setVertexData(XelaVec2<float> vec, int id);
void setVertexData(std::vector<XelaVec2<float>> vec, int id);
void setVertexData(XelaVec2<float>* vec, int count, int id);

void setVertexData(XelaVec3<float> vec, int id);
void setVertexData(std::vector<XelaVec3<float>> vec, int id);
void setVertexData(XelaVec3<float>* vec, int count, int id);

void setVertexData(XelaVec4<float> vec, int id);
void setVertexData(std::vector<XelaVec4<float>> vec, int id);
void setVertexData(XelaVec4<float>* vec, int count, int id);
```
This is the same as addVertexData except it clears all vertex data with the specified id before replacing it with the new data.
<br><br>

##### setDataUpdateFrequency()
```C++
void setDataUpdateFrequency(int id, int freq);
```
Sets the update frequency of all vertex data with the specified id to freq. By default this is 0, meaning the data updates with every vertex. If freq is set to 1, that id of vertex data will only update with every instance of the object. 2 means every second instance, and so on.
<br><br>

##### updateData()
```C++
void updateData();
```
Updates the object's OpenGL buffers with the current index and vertex data. Should be called once adding/removing indices and vertices is done but before the first draw call is made. So long as the vertex and index data doesn't change after calling this function, there's no need to call this function more than once.

##### draw()
```C++
void draw(unsigned int count);
```
Draws count instances of this object to the screen.
<br><br>

<h6 id="xelaobject-getsize"> getSize()</h6>

```C++
XelaVec3<float> getSize();
```
Returns the size of the object based on vertex data at id 0. Equal to { maxX - minX, maxY - minY, maxZ - minZ }.
<br><br><br><br>

### XelaShader.h
#### Class XelaShader
Class for handling OpenGL shaders and shader information.
<br><br>

##### XelaShader()
```C++
XelaShader(const char *shaderV, const char *shaderG, const char *shaderF);
XelaShader(XelaShader *s);
```
Creates a new XelaShader. If the first constructor is used, this compiles a new GLSL program using the source code provided by shaderV, shaderG, and shaderF. If the second constructor is used, this shares a program with s.

shaderV = Source code for the vertex shader. Required.

shaderG = Source code for the geometry shader. Not required. If set to nullptr no geometry shader will be used.

shaderF = Source code for the fragment shader. Required.
<br><br>

##### setShader()
```C++
void setShader(const char *shaderV, const char *shaderG, const char *shaderF);
```
Compiles a new GLSL program using the source code provided. Deletes the old shader program.

shaderV = Source code for the vertex shader. Required.

shaderG = Source code for the geometry shader. Not required. If set to nullptr no geometry shader will be used.

shaderF = Source code for the fragment shader. Required.
<br><br>

##### addImage()
```C++
void addImage(const char *tPath, const char *name, int *width, int *height, int *numChannels, int inputFormat, int textureFormat);
```
Loads an image from a file located at tPath and stores it. Whenever this shader is used, the loaded image will be sent as a texture to the uniform called name in this shader's fragment shader. Width, height, and numchannels are set to the width, height, and number of channels of the loaded image respectively. InputFormat corresponds to the format the image is saved as and textureFormat specifies the format this image should be stored in. Accepted formats include XELA_R, XELA_RG, XELA_RGB, XELA_RGBA, XELA_SRGB, and XELA_SRGBA. Other formats defined by glfw are acceptable but those should cover almost everything and are therefore the only ones redefined with the XELA_ prefix.

In the fragment shader, this texture would be accessed with `uniform sampler2D <name>` where <name> is replaced with name.
<br><br>

##### addTexture()
```C++
void addTexture(GLuint id, const char *name);
```
Adds a new texture to be sent to the fragment shader to a uniform called name. id is the id of the OpenGL texture. This is meant to be used if for whatever reason you need to manually create your OpenGL textures, as is the case in XelaFont/XelaText.

In the fragment shader, this texture would be accessed with `uniform sampler2D <name>` where <name> is replaced with name.
<br><br>

##### addShaderCallback()
```C++
void addShaderCallback(XelaShaderCallbackFunction func);
```
Adds a function to the list of functions to call whenever this shader is used.
<br><br>

##### removeShaderCallback()
```
void removeShaderCallback(XelaShaderCallbackFunction func);
```
Removes a function from the list of functions to call whenever this shader is used.
<br><br>

##### use()
```
void use();
```
Activates this shader and calls any necessary callback functions. Any draw calls with OpenGL after this will use this shader.
<br><br>

##### addUniform()
```C++
void addUniform(const char *name, int inType, int outType, void *data);
```
Adds a uniform to the list of uniforms to automatically set whenever this shader is called. This saves you the trouble of manually setting uniforms every frame. Name is the name of the uniform in the GLSL shader. InType is the data type of data and outType is the type the data should be when sent to the shader. InType and outType can be one of XELA_BOOL, XELA_INT, XELA_UNSIGNED_INT, XELA_FLOAT, or XELA_DOUBLE.

This is meant to be used when you plan on setting a uniform equal to a single variable every frame. For example, if I have a variable `int scale` and every frame I'm setting a uniform equal to scale, I would use addUniform and have data be a pointer to scale. Every time this shader is used, scale would automatically be sent as a uniform. Any time the variable scale is changed, this change would occur in the shader automatically.

This uniform is accessed in the shader using `uniform <type> <name>` where <type> is one of `bool`, `int`, `uint`, `float`, or `double` and <name> is replaced with name.
<br><br>

##### addUniformVec2()
```C++
void addUniformVec2(const char *name, int inType, int outType, void *data1, void *data2);
```
This is the same as addUniform() but with vec2.

This uniform is accessed in the shader using `uniform <type> <name>` where <type> is one of 'bvec2`, 'ivec2`, `uvec2`, `vec2`, or `dvec2` and <name> is replaced with name.
<br><br>

##### addUniformVec3()
```C++
void addUniformVec3(const char *name int inType, int outType, void *data1, void *data2, void *data3);
```
This is the same as addUniform() but with vec3.

This uniform is accessed in the shader using `uniform <type> <name>` where <type> is one of `bvec3`, `ivec3`, `uvec3`, `vec3`, or `dvec3` and <name> is replaced with name.
<br><br>

##### addUniformVec4()
```C++
void addUniformVec4(const char *name, int inType, int outType, void *data1, void *data2, void *data3, void *data4);
```
This is the same as addUniform() but with vec4.

This uniform is accessed in the shader using `uniform <type> <name>` where <type> is one of `bvec4`, `ivec4`, `uvec4`, `vec4`, or `dvec4` and <name> is replaced with name.
<br><br>

##### getTexList()
```C++
std::vector<XelaImageInfo> getTexList();
```
Returns a vector of XelaImageInfo structs containing information on all images being automatically sent to the shader as uniforms every time this shader is used.
<br><br>

##### getProgram()
```C++
unsigned int getProgram();
```
Returns an unsigned int representing the GLSL program id. Used for some gl functions such as the glUniform functions for doing things with OpenGL not covered by Xela Graphics.
<br><br><br><br>

### XelaText.h
#### Class XelaText
##### XelaText()
```C++
XelaText(std::string fontFilePath, int size);
XelaText(XelaFont *f);
```
Creates a new XelaText object. The first constructor creates a new XelaFont object from the file specified to use with this text and renders it at size size. The second constructor uses a pre-existing XelaFont object for generating text, allowing you to use the same font with multiple text objects.
<br><br>

##### setFont()
```C++
void setFont(std::string fontFilePath, int size);
```
Creates a new XelaFont object for this text from the font file specified to be rendered at size size.
<br><br>

##### setText()
```C++
void setText(std::string t);
```
Updates the text that's rendered with this object.
<br><br>

##### setColor()
```C++
void setColor(XelaVec4<float> c);
```
Sets the color to render this text with.
<br><br>

##### setPosition()
```C++
void setPosition(XelaVec3<float> p);
```
Sets the position on the screen to render this text at. Position should be specified from (0, 0) to (resolution x, resolution y).
<br><br>

##### setScale()
```C++
void setScale(XelaVec2<float> s);
```
Sets how much to scale the size of the text when rendering.
<br><br>

<h6 id="xelatext-draw"> draw()</h6>
```C++
void draw(XelaVec2<int> screenResolution);
```
Draws the text on screen based on a resolution of screenResolution. In order for the text to look correct, make sure screenResolution is equal to the resolution the window is actually rendering at.
<br><br>

##### getFont()
```C++
XelaFont *getFont();
```
Returns a pointer to the XelaFont object being used by this text.
<br><br>

<h6 id="xelatext-getsize> getSize()</h6>
```C++
XelaVec2<float> getSize();
```
Returns the size of this text object before scaling is applied.