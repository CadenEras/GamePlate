# 🐸 GamePlate 🐸

GamePlate is written in C and is a simple multiplayer game application. It is designed to be used as a base for other games.

</br>


# 🔌 Install SDL2 and Cmake Linux 

</br>

```
sudo apt-get update
sudo apr-get upgrade
sudo apt-get install build-essential
sudo apt-get install cmake
```

</br>

<h3> In a separate folder </h3>

```
git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install
```

</br>

<h3> Same thing for SDL2_image by going back in the folder and as many times as necessary for all SDL2 libraries </h3>

```
git clone https://github.com/libsdl-org/SDL_image.git -b SDL2_image
cd SDL
mkdir build
cd build
../configure
make
sudo make install
```

</br>



# ⏳ Compilation 

<h5>For VScode : </h5>

ctrl + maj + p
</br>
cmake configure
</br>
cmake build

</br>

<h5>commandline(terminal) :</h5>

```
mkdir build && cd build
export CC=gcc
cmake ..
make
```
