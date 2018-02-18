#ifndef CPPPROCESSGAME_H
#define CPPPROCESSGAME_H

#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <stdlib.h>

typedef std::vector<int> ligne;
typedef std::vector<ligne> grid;

using std::map;
using std::string;

class ProcessGame
{

public:

    ProcessGame();
    ProcessGame(int size);

    void NewGame();
    void MoveBlock( string sens );

    grid getGrille() const;
    bool isGameOver() const;



    int getScore() const;
    map< string, grid> getMove() const;

private:

    void creerGrilleJeu(int gridSize);

    void fusionCase(ligne &_ligne);
    void moveZeros(ligne &_ligne);

    void addNumber();
    bool perdu();


protected:

    grid grille;
    int score;
    bool gameOver;

private:
    int numberOfZeros;
    bool blockMoved;
    map< string, grid> i_move;
};

#endif // CPPPROCESSGAME_H
