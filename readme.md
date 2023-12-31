<h1 align="center">Kebb</h1>

Kebb is a game for keyboard enthusiasts which allows you to test and improve your typing skills. :rocket:  
Go to options to select the amount of letters, the speed and try to press all of the letters !

It currently works with QWERTY, AZERTY, BÉPO and optimot layouts.

<div align="center">
   <img src="./image/example_timer_1.gif" width="250" />
   <img src="./image/example_timer_2.gif" width="250" />
</div>
<div align="center">
   <img src="./image/example_survival_1.gif" width="250" />
   <img src="./image/example_survival_2.gif" width="250" />
</div>

---

#### Install from package

Pre-built packages for Debian & Arch based distributions are available on the [Releases](https://github.com/flinguenheld/kebb/releases) page.

---

#### Manual install

##### Dependencies

- Make
- CMake >= 3.24
- g++

##### Build

1. Clone this repo: `git clone https://github.com/flinguenheld/kebb`
2. Create a _build_ directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake -DRELEASE_LINUX=ON .. && make`
   > :bulb: The flag RELEASE_LINUX=OFF allows to use the fonts and option files in the build folder.
4. Run: `./kebb`

---

#### Thanks

Colors come from the [Catppuccin](https://github.com/catppuccin/catppuccin) Mocha theme. 😸  
Fonts come from [1001 fonts](https://www.1001fonts.com/monospaced-fonts.html)  
[Udacity snake game](https://github.com/udacity/CppND-Capstone-Snake-Game) that I used to start.
