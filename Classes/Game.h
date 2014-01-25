#pragma once
#include "Board.h"

// TODO ���� ����� �������� ������� (�������� ����� AI ���� ������ � ������)
class Game{
public:
	static Game& current();

    void starNewGame();
    
	void setCurrentBoard(Board* board);
	Board* getBoard();

private:
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);

	Board* currentBoard;
};