<h1 align="center">Kebb</h1>

Kebb is a game for keyboard enthusiasts which allows you to test and improve your typing skills. :rocket:  
Go to options to select the amount of letters, the speed and try to press all of the letters !

<div align="center">
   <img src="./image/example_slow_1.gif" width="250" />
   <img src="./image/example_slow_2.gif" width="250" />
</div>
<div align="center">
   <img src="./image/example_fast_1.gif" width="250" />
   <img src="./image/example_fast_2.gif" width="250" />
</div>

#### Dependencies

- **CMake >= 3.7**:
  - [CMake install](https://cmake.org/install/)
  - Debian: `apt install cmake`
- **g++:**
  - Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  - Windows: [Click here for installation instructions](https://gnuwin32.sourceforge.net/packages/make.htm)
  - Debian: `apt install build-essential`
- **SDL (>= 2.0.12):**
  - All OSes: [SDL install](https://wiki.libsdl.org/SDL2/Installation)
- **SDL TTF (>= 2.0.15):**
  - Find the package name or see the [github repository](https://github.com/libsdl-org/SDL_ttf)
  - debian: `apt install libsdl2-2.0-0 libsdl2-ttf-2.0-0`

#### Build

1. Clone this repo: `git clone https://github.com/flinguenheld/kebb`
2. Create a _build_ directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake -DRELEASE_LINUX=ON .. && make`  
   _:bulb: The flag RELEASE_LINUX allows to use the fonts and option files in the build folder._
4. Run: `./kebb`

#### Thanks

Colors come from the [Catppuccin](https://github.com/catppuccin/catppuccin) Mocha theme. 😸  
Fonts come from [1001 fonts](https://www.1001fonts.com/monospaced-fonts.html)  
[SDL2 CMake modules](https://github.com/aminosbh/sdl2-cmake-modules) 🙏
