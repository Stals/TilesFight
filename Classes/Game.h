#pragma once
#include "Board.h"

// TODO ���� ����� �������� ������� (�������� ����� AI ���� ������ � ������)
class Game{
public:
	static Game& current();

    void starNewGame();
    
	void setCurrentBoard(Board* board);
	Board* getBoard();
    
    void addPlayer(Player* player);
    std::vector<Player*> getPlayers();
    void clearPlayers();
    
    void checkEndGame();

private:
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);

	Board* currentBoard;
    
    std::vector<Player*> players;
};