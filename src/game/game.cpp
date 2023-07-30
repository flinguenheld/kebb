#include "game.h"

Game::Game(GameMod mod) : _mod(mod) {}

GameMod Game::mod() const { return _mod; }
