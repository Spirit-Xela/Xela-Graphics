# XelaGraphics Changelog

### Version 1.2.0
#### tl;dr
Xela Graphics was changed so that all classes are now structs. All class functions are now statis functions. This was to allow building Xela Graphics as a DLL on Windows.

XelaImage was added to load/store textures

#### General:
* Changed XELA_DEBUG_* definitions to either 1 or 0 for true or false
* Changed #ifdef for debug definitions in all files to #if
* Moved #include statements to source files instead of header files wherever possible
* Removed all function overloads
* Removed all C++ objects/structs from function definitions and replaced with C equivalents

#### Created XelaImage.h/.cpp
* Added struct XelaImage to load/store textures
* Added function genImage to create a new XelaImage struct
* Added function delImage to delete a XelaImage struct
* Added void loadImage to load textures from a file using stb_image
* Added void setImage to set a XelaImage's texture's id and name
* Added void setName to set a XelaImage's texture's name
* Added void setID to set a XelaImage's texture's id

#### XelaDefinitions.h/.cpp >> XelaGraphics.h/.cpp
* Renamed files XelaDefinitions.h/.cpp to XelaGraphics.h/.cpp
* Added int width, int height, and int numChannels to struct ImageInfo to store more information about textures
* Added function xelaGetTime() to replace getTime functions removed from XelaWindow

#### XelaInit.h/.cpp >> XelaGraphicsInit.h/.cpp
* Renamed files XelaInit.h/.cpp to XelaGraphicsInit.h/.cpp
* Renamed void xelaInit to xelaGraphicsInit
* Renamed void xelaInitGLEW to xelaGraphicsInitGLEW
* Renamed void xelaTerminate to xelaGraphicsTerminate

#### XelaWindow.h/.cpp
* Changed class XelaWindow to struct XelaWindow
* Added function genWindow to create a new XelaWindow struct
* Set all XelaWindow functions to statis, which now take a pointer to a XelaWindow struct as their first argument
* Removed XelaWindow constructor, use function genWindow instead
* Removed function getTime, replaced with function xelaGetTime in XelaGraphics.h/.cpp

#### XelaShader.h/.cpp
* Changed class XelaShader to struct XelaShader
* Added function genShader to create a new XelaShader struct
* Added function copyShader to create a new XelaShader struct sharing a program with another XelaShader struct
* Added function addUniform to add a pointer to data that is to be sent as a float uniform to GLSL whenever a XelaShader struct is used
* Added functions addUniformVec2, addUniformVec3, and addUniformVec4, to do the same thing as addUniform but with vec2, vec3, and vec4 uniforms respectively.
* Set all XelaShader functions to static, which now take a pointer to a XelaShader struct as their first argument
* Removed XelaShader constructor, use function genShader or copyShader instead
* Removed function getTexList, as the member texList can now be accessed directly instead
* Updated addImage to create a new XelaImage struct for loading/storing textures
* Updated adTexture to create a new XelaImage struct for loading/storing textures
* Updated texList to store XelaImage structs instead of ImageInfo structs

#### XelaObject.h/.cpp
* Changed class XelaObject to struct XelaObject
* Added function genObject to create a new XelaObject struct
* Removed XelaObject constructor, use function genObject instead

#### XelaFont.h/.cpp
* Changed class XelaFont to struct XelaFont
* Added function genFont to create a new XelaFont struct
* Removed XelaFont constructor, use function genFont instead

#### XelaText.h/.cpp
* Changed class XelaText to struct XelaText
* Added function genText to create a new XelaText struct
* Removed XelaText constructor, use function genText instead

#### XelaEvents.h/.cpp
* Added typedef XelaWindowSizeCallback for storing callback functions for window size updates
* Added void XelaSetWindowSizeCallback to set the callback function for window size updayes
* Added stuct XelaWindowSizeInfo to store information about window size updates
* Added void xelaUpdateWindowSize to call the proper callback function for window size updates

#### XelaCallbacks.h/.cpp
* Updated windowSizeCallback to call new function updateWindowSize in XelaEvents.h/.cpp
* Removed xelaFramebufSizeCallback
* Renamed void xelaInitCallbacks to xelaGraphicsInitCallbacks