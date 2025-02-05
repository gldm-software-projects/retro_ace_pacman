del pacman.tap
del pacman.wav
zcc +ace -lndos -O2 --opt-code-speed=inlineints -pragma-define:CLIB_EXIT_STACK_SIZE=0 -UUSEJOYSTICK -create-app -Cz--audio --generic-console pacman.c -opacman
move pacman.tap pacman_k.tap
move pacman.wav pacman_k.wav
