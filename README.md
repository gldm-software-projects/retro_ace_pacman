# retro Ace PacMan

## My version of pac-man for the Jupiter Ace


this game is developed in C using Z88DK 

## pre-requisites

*please install the following applications:*
+ Compiler Z88DK : get a nightly build at http://nightly.z88dk.org/   
+ EightyOne emulator: get it at https://www.jupiter-ace.co.uk/emulators_win.html  

## build notes

Use the build scripts. The compiler **zcc.exe** must be reachable (i.e. its path should be in the environment variable PATH).  
- The **build_no_joy.cmd** script generates **pacman_k.tap** and **pacman_k.wav** (without joystick support).
- The **build_w_joy.cmd** script generates **pacman_j.tap** and **pacman_j.wav** (with joystick support).

PS: the wav file is useful if you want to load the game in a real Jupiter Ace or a Minstrel 4.

---------------------------------------------------------------------
