#pragma once
#include "Board.h"


// TODO сюда можно закинуть игроков (например чтобы AI имел доступ к игроку)
class Game{
public:
    enum Type{
        VS_AI,
        VS_HUMAN
    };
	
    static Game& current();

    void starNewGame(Game::Type type = VS_AI);
    
	void setCurrentBoard(Board* board);
	Board* getBoard();
    
    void addPlayer(Player* player);
    std::vector<Player*> getPlayers();
    void clearPlayers();
    
    void checkEndGame();
    
    
    float artScale();
    void setArtScale(float scale);

private:
	Game();
	Game(const Game& other);
	Game& operator=(const Game& other);

	Board* currentBoard;
    
    std::vector<Player*> players;
    
    float _artScale;
};