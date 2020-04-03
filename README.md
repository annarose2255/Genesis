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



*4.3 Updates* 
Scene Transitions: First scene, run into the enemy to enter a battle scene; from the battle scene
run into the enemy again to go back to the previous scene. In the first scene, move the character up to 
enter a different area. Move down to go back to the first scene. 