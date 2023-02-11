# 🐸 GamePlate 🐸

GamePlate is written in C and is a simple multiplayer game application. It is designed to be used as a base for other games.

</br>

# 🔌 Installation SDL2 et Cmake Linux 

sudo apt-get update
</br>
sudo apr-get upgrade
</br>
sudo apt-get install build-essential
</br>
sudo apt-get install cmake
</br>
sudo apt install libsdl2-gfx-dev
</br>

</br>

<h3> Dans un dossier séparé </h3>

git clone https://github.com/libsdl-org/SDL.git -b SDL2
</br>
cd SDL
</br>
mkdir build
</br>
cd build
</br>
../configure
</br>
make
</br>
sudo make install
</br>

</br>

<h3> Same pour SDL2_image en revant en arrière dans le dossier et autant de fois que necessaire pour toutes les librairies SDL
git clone https://github.com/libsdl-org/SDL_image.git -b SDL2_image </h3>

cd SDL
</br>
mkdir build
</br>
cd build
</br>
../configure
</br>
make
</br>
sudo make install
</br>

</br>



# 📁 Comment utiliser Cmake for Linux 

<h5>Pour VScode : </h5>
ctrl + maj + p

</br>
</br>

<h5>en ligne de comandes :</h5>
</br>
mkdir build && cd build
</br>
export CC=gcc
</br>
cmake ..
</br>
make
