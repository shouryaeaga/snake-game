emcc -o web_build/game.html main.cpp Game.cpp Fruit.cpp Player.cpp -Os -Wall /home/shourya/github/raylib/src/libraylib.a -I/home/shourya/github/raylib/src -s USE_GLFW=3 -s ASYNCIFY --shell-file /home/shourya/github/raylib/src/minshell.html --preload-file assets -s TOTAL_MEMORY=67108864