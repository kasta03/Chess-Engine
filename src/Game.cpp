#include "../include/Game.h"

Game::Game() : playerColour(true), GameMode(1), turn(1), isTurn(true) {}

Game::Game(bool playerColour, int GameMode) : playerColour(playerColour), GameMode(GameMode), turn(1), isTurn(true) {}

void Game::StartGame()
{
    std::cout << "Welcome to the Game!" << std::endl;
    PickColour();

    Piece *White_Pawn = new WhitePawn();
    Piece *White_Knight = new WhiteKnight();
    Piece *White_Bishop = new WhiteBishop();
    Piece *White_Rook = new WhiteRook();
    Piece *White_Queen = new WhiteQueen();
    Piece *White_King = new WhiteKing();

    Piece::white_pieces.push_back(White_Pawn);
    Piece::white_pieces.push_back(White_Knight);
    Piece::white_pieces.push_back(White_Bishop);
    Piece::white_pieces.push_back(White_Rook);
    Piece::white_pieces.push_back(White_Queen);
    Piece::white_pieces.push_back(White_King);

    Piece *Black_Pawn = new BlackPawn();
    Piece *Black_Knight = new BlackKnight();
    Piece *Black_Bishop = new BlackBishop();
    Piece *Black_Rook = new BlackRook();
    Piece *Black_Queen = new BlackQueen();
    Piece *Black_King = new BlackKing();

    Piece::black_pieces.push_back(Black_Pawn);
    Piece::black_pieces.push_back(Black_Knight);
    Piece::black_pieces.push_back(Black_Bishop);
    Piece::black_pieces.push_back(Black_Rook);
    Piece::black_pieces.push_back(Black_Queen);
    Piece::black_pieces.push_back(Black_King);

    Piece::InitializeBitboards();

    if(GameMode == 2) AutoPlay();
}

void Game::AutoPlay()
{
    PrintBitboard();
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

void Game::PickColour()
{
    std::cout << "Choose your colour (W/B), (R) to randomize. Choose (A) for autoplay: ";
    char choice;
    std::cin >> choice;
    choice = toupper(choice);
    srand(time(0));

    switch (choice)
    {
        case 'W':
            std::cout << "You play as white" << std::endl;
            playerColour = true;
            break;
        case 'B':
            std::cout << "You play as black" << std::endl;
            playerColour = false;
            break;
        case 'R':
            if (rand() % 2 == 0)
            {
                std::cout << "You play as white" << std::endl;
                playerColour = true;
                break;
            }
            else
            {
                std::cout << "You play as black" << std::endl;
                playerColour = false;
                break;
            }
        case 'A':
            std::cout << "Autoplay mode activated." << std::endl;
            GameMode = 2;
            break;
        default:
            std::cout << "Invalid choice. Please choose W, B, or R." << std::endl;
            PickColour();
            break;
    }
}

void Game::flipTurn()
{
    isTurn = !isTurn;
}

void Game::EndGame() {}
void Game::ResetGame() {}