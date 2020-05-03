# Xela Graphics
A small OpenGL library using glew and glfw to make graphics programming in C++ easier.
Handles window creation, objects, shaders, and text rendering.

#### Current version: 1.2.1

### Table of Contents
* [Installation](#installation)
* [Getting Started](#getting-started)
* [Credits](#credits)
* [License](#license)

### Installation
<details>
  <summary>Windows</summary>
 
* Go to releases and download the latest release of XelaGraphics.
* Unzip the file in it's own folder.
* Link XelaGraphics, Glfw, Glew, and Freetype to your project.
  * The version of glfw, glew, and freetype that I used when compiling that version of XelaGraphics is included in the release for convenience, but if you would like a more updated version of any of these libraries you will have to install them yourself. Links to their websites is [here](#libraries-used)
  
  * The following instructions explain how to set this up with Visual Studio 2019, but similar steps would be used for any IDE. If you're unsure what to do, try searching for how to install libraries with your IDE of choice using Google.
    * When you're in your project on Visual Studio, on the right side should be Solution Explorer. Under the Solution (name) should be the name of your project.
    * Right click the name of your project and select Properties.
    * In the properties window, select C/C++ -> General.
    * Click Additional Include Directories, then click the down arrow on the right side and select edit.
      * Add the path to xelagraphics_(version)_(x86/x64)/xelagraphics/include
        * If you're targeting 32-bit systems, use the folder with x86. If you're targeting 64-bit systems, use the folder with x64.
      * Add the path to xelagraphics_(version)_(x86/x64)/glfw_(version)/include
        * If you've downloaded a different version of glfw, use that folder's path instead.
      * Add the path to xelagraphics_(version)_(x86/x64)/glew_(version)/include
        * If you've downloaded a different version of glew, use that folder's path instead.
      * Add the path to xelagraphics_(version)_(x84/x64)/freetype_(version)/include
        * If you've downloaded a different version of freetype, use that folder's path instead.
      * Select OK.
    * Go to Linker -> General.
    * Click Additional Library Directories, then click the down arrow on the right side and select edit.
      * Add the path to xelagraphics_(version)_(x86/x64)/xelagraphics/lib
      * Add the path to xelagraphics_(version)_(x86/x64)/glfw_(version)/lib-vc2019
      * Add the path to xelagraphics_(version)_(x86/x64)/glew_(version)/(x86/x64)
      * Add the path to xelagraphics_(version)_(x86/x64)/freetype_(version)/(win32/win64)
      * Select OK.
    * Go to Linker -> Input
    * Click Additional Dependencies, then click the down arrow on the right side and select edit.
      * Add the following library names to the list:
        * opengl32.lib
        * glew32.lib
        * glfw3.lib
        * freetype.lib
        * xelagraphics.lib
      * Select OK.
    * Make sure all the DLLs are copied to the same folder your program's EXE file will be located in
      * xelagraphics.dll: xelagraphics_(version)_(x86,x64)/xelagraphics/lib
      * glfw3.dll: xelagraphics_(version)_(x86/x64)/glfw_(version)/lib-vc2019
      * glew32.dll: xelagraphics_(version)_(x86/x64)/glew_(version)/(x86/x64)
      * freetype.dll: xelagraphics_(version)_(x86/x64)/freetype_(version)/(win32/win64)
    * Click apply.
* You're done! You can now use Xela Graphics in your project.
* When including header files from XelaGraphics in your project, be sure to prefix header file names with xela/graphics/
  * Such as `#include <xela/graphics/XelaGraphics.h>`
</details>

<details>
  <summary>Linux</summary>
 
  * Open a terminal in a new folder.
  * Make sure glfw, glew, and freetype2 are all installed on your computer.
  * `git clone https://github.com/XelaSpirit/Xela-Graphics.git`
  * `cd Xela-Graphics`
  * `sudo ./install`
    * This will compile XelaGraphics and put the proper files for XelaGraphics in /usr/lib and /usr/include.
    * Header files will be in /usr/include/xela/graphics, so in your programs make sure to prefix header includes with xela/graphics.
      * Such as `#include <xela/graphics/XelaGraphics.h>`
  * When compiling a program that uses XelaGraphics, link XelaGraphics and its dependencies.
    * With G++, this would look like `g++ -lxelagraphics -lglfw -lGLEW -lfreetype -I/usr/include/freetype2 <Source files>`

</details>

### Getting Started
If you haven't already installed Xela Graphics, make sure you read the [Installation](#installation) instructions to find out how.

The [documentation](Doc.md) contains information on every function in Xela Graphics you might need to use while writing a program.

There's also some [sample code](sample) showing some of the features of the library.

### Credits
**Author - Alex Morse:** morse.alex.j@gmail.com

#### Libraries used

##### GLFW 3.3: https://www.glfw.org/

##### GLEW 2.1.0: http://glew.sourceforge.net/

##### FreeType 2.10.1: https://www.freetype.org/

##### stb_image.h: https://github.com/nothings/stb/blob/master/stb_image.h

### License
Xela Graphics is under the terms of the MIT license, available [here](LICENSE.md).

This library's dependencies also have the following licenses:

GLFW: https://www.glfw.org/license.html

GLEW: https://github.com/nigels-com/glew#copyright-and-licensing

FreeType: https://www.freetype.org/license.html

stb_image: https://github.com/nothings/stb/blob/master/LICENSE
