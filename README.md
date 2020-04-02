# Genesis
*Movement*
WASD to move Sprite
Up/Down/Left/Right to move camera 

*To Set Up*
Using tmxlite library: https://github.com/fallahn/tmxlite 
In the event that it doesn't compile: 
-Delete build folder under tmxlite-master/tmxlite
-Run the following commands: 
-mkdir build 
-cd build
-cmake ..
-sudo make install 
Also if you get an error about the library not linking then run: sudo ldconfig (that's an L in ldconfig)

*3.27 Updates* 
So far, no working demo :( 
* Worked on implementing Tween files from last hw; implemented some.
* In the main folder, added an events folder with first attempts at making a SceneManager and scene transition events
* Since the dev tool wasn't available to use, we started to parse in tmx files through a parsing library in Scene, but nothing is completely parsed yet.
