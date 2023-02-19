# 🐸 GamePlate 🐸

GamePlate is written in C and is a simple multiplayer game application. It is designed to be used as a base for other games.

</br>


# 🔌 Install SDL2 and Cmake Linux 

sudo apt-get update
</br>
sudo apr-get upgrade
</br>
sudo apt-get install build-essential
</br>
sudo apt-get install cmake
</br>
</br>

<h3> In a separate folder </h3>

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

<h3> Same thing for SDL2_image by going back in the folder and as many times as necessary for all SDL2 libraries </h3>

git clone https://github.com/libsdl-org/SDL_image.git -b SDL2_image
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



# ⏳ Compilation 

<h5>For VScode : </h5>

ctrl + maj + p
cmake configure 
cmake build

</br>

<h5>commandline(terminal) :</h5>

mkdir build && cd build
</br>
export CC=gcc
</br>
cmake ..
</br>
make
