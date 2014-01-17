#pragma once
#include "Board.h"


class Game{
public:
	static Game& current();

	void setCurrentBoard(Board* board);
	Board* getBoard();

private:
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);

	Board* currentBoard;
};