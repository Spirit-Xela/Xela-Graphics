# Xela Graphics
A small OpenGL library using glew and glfw to make graphics programming in C++ easier.
Handles window creation, objects, shaders, and text rendering.

### Table of Contents
* [Installation](#installation)
* [Getting Started](#getting-started)
* [Credits](#credits)
* [License](#license)

### Installation
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
      * Add the path to xelagraphics_(version)_(x86/x64)/xelagraphics/(debug/release)
        * Xela Graphics is currently a static library, meaning there's both a debug and release version. In visual studio, in the debug configuration you have to use the debug folder. In the release configuration, you have to use the release folder.
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
    * Click apply.
* You're done! You can now use Xela Graphics in your project.

### Getting Started
If you haven't already installed Xela Graphics, make sure you read the [Installation](#installation) instructions to find out how.

The [full documentation](Docs/Full%20Doc.md) is available in docs and contains information on every function in Xela Graphics.

The [condensed documentation](Docs/Condensed%20Doc.md) is available in docs and contains information on every function that someone using this library may need.

There's also some [sample code](sample) showing simple programs using the library.

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