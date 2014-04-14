#pragma once
#include "Board.h"


// TODO ���� ����� �������� ������� (�������� ����� AI ���� ������ � ������)
class Game{
public:
    enum Type{
        VS_AI,
        VS_HUMAN,
        WRONG_TYPE
    };
	
    enum Screen{
        GAME_SCREEN,
        PAUSE_SCREEN,
        TUTORIAL_SCREEN,
        MENU_SCREEN
    };
    
    static Game& current();

    void starNewGame(Player* player1, Player* player2, bool restart = false);
    void restartGame();
    // call this when need to end game without actual letting one player win/loose
    void endGame();
    
    Game::Type getCurrentGameType();
    
	void setCurrentBoard(Board* board);
	Board* getBoard();
    
    void addPlayer(Player* player);
    std::vector<Player*>& getPlayers();
    void clearPlayers();
    
    void checkEndGame();
    
    
    float artScale();
    void setArtScale(float scale);
    
    void pauseGame(bool showLayer = true);
    void resumeGame();
    
    Screen getCurrentScreen();
    void setCurrentScreen(Screen screen);

private:
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);

	Board* currentBoard;
    
    std::vector<Player*> players;
    
    float _artScale;
    
    CCSet* pausedTargets;
    
    Screen currentScreen;
    Game::Type currentGameType;
};