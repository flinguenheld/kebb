#ifndef KEBB_H
#define KEBB_H

// clang-format off
namespace kebb {

  enum class GameMode {
    M_Survival = 10,
    M_Timer = 11,
  };

  enum class GameStatus {
    S_Win = 10,
    S_Loose = 11,
    S_TimeUp = 12,
    S_Quit = 13,
  };

  enum class SurvivalDifficulty {
    D_VeryEasy = 10,
    D_Easy = 20,
    D_Normal = 30,
    D_Hard = 40,
    D_VeryHard = 50,
    D_Impossible = 60,
  };

  enum class WindowName  {
    W_None = 0,
    W_Quit = 1,

    W_About = 100,
    W_GameOver = 101,
    W_GameSurvival = 102,
    W_GameTimer = 103,
    W_Option = 104,
    W_Record = 105,
    W_Welcome = 106,
    W_WelcomeTimer = 107,
    W_WelcomeSurvival = 108,
  };
} // namespace kebb

#endif // !KEBB_H
