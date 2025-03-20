#pragma once
#include "pch.h"

class Game
{
public:
    bool playerColour;
    int GameMode;
    bool isTurn = true;
    bool isPlayerTurn;
    int turn = 1;

    Game();
    Game(bool playerColour, int GameMode);
    ~Game() = default;

    void StartGame();
    void AutoPlay();
    void PickColour();
    void EndGame();
    void ResetGame();
    void flipTurn();
};