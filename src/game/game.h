#ifndef GAME_H
#define GAME_H

enum class GameMod {
  M_Timer,
  M_Survival,
};

class Game {
public:
  Game(GameMod mod);
  GameMod mod() const;

private:
  GameMod _mod;
};

#endif // !GAME_H
