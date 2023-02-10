# GamePlate

GamePlate is written in C and is a simple multiplayer game application. It is designed to be used as a base for other games.


** Installation SDL2 et Cmake Linux **

sudo apt-get update
sudo apr-get upgrade
sudo apt-get install build-essential
sudo apt-get install cmake

# Dans un dossier séparé
git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install
# Same pour SDL2_image en revant en arrière dans le dossier et autant de fois que necessaire pour toutes les librairies SDL
git clone https://github.com/libsdl-org/SDL_image.git -b SDL2_image
cd SDL
mkdir build
cd build
../configure
make
sudo make install





** Cmake for Linux **
-> pour l'utiliser 

ctrl + maj + p ( pour vs code)


en ligne de comandes :
mkdir build && cd build
export CC=gcc
cmake ..
make
