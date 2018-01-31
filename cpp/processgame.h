#ifndef CPPPROCESSGAME_H
#define CPPPROCESSGAME_H
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <stdlib.h>

typedef std::vector<int> ligne;
typedef std::vector<ligne> grid;

class ProcessGame
{

public:
    void NewGame();
    ProcessGame();
    ProcessGame(int size);
    void MoveBlock( std::string sens );
    grid getGrille() const;

    std::map<std::string, grid> getMove() const;

    bool isGameOver() const;

    int getScore() const;

private:
    void creerGrilleJeu(int gridSize);

    void fusionCase(ligne &_ligne);
    void moveZeros(ligne &_ligne);

    void addNumber();
    bool perdu();


protected:
    grid grille;
    std::map< std::string, grid> i_move;
    bool gameOver;
    int numberOfZeros;
    int score;
    bool blockMoved;
};

#endif // CPPPROCESSGAME_H
