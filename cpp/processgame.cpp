#include "processgame.h"
#include <iostream>

using namespace std;

void ProcessGame::NewGame()
{
    grille.clear();
    gameOver = false;
    score = 0;

    srand ( (int)time(NULL)* clock() );
    creerGrilleJeu( 5 );
    for ( int i = 0; i < 2; i++)
    {
        addNumber();
    }
}

ProcessGame::ProcessGame()
    : gameOver (false), score(0)
{
    srand ( (int)time(NULL)* clock() );
    creerGrilleJeu( 5 );
    for ( int i = 0; i < 2; i++)
    {
        addNumber();
    }
}

ProcessGame::ProcessGame( int size = 5 )
    : gameOver (false), score(0)
{
    srand ( (int)time(NULL)* clock() );
    creerGrilleJeu( size );
    for ( int i = 0; i < 2; i++)
    {
        addNumber();
    }
}

void ProcessGame::moveZeros(ligne& _ligne)
{
    //repère les indices des zeros.
    vector <int> i_zeros;
    int i = 0;

    for ( int chiffre : _ligne)
    {

        if ( chiffre == 0 )
            i_zeros.insert( i_zeros.begin(), i);
        i++;
    }
    //supprime les zeros
    for ( int posZero : i_zeros )
    {
        _ligne.erase( _ligne.begin() + posZero );
    }

    //reinsere les zeros au début
    vector<int> nullVector ( i_zeros.size() , 0 );
    _ligne.insert( _ligne.begin(), nullVector.begin(), nullVector.end() );
}

void ProcessGame::addNumber()
{
    int i = 0;
    int j = 0;

    //Repère les indices des zeros
    vector<int> indicesBlocksNulls;
    for (ligne _ligne : grille)
    {
        for ( int block : _ligne )
        {
            if (block == 0)
            {
                int indice = i * (int)grille.size() + j;
                indicesBlocksNulls.push_back( indice );
            }

            j++;
        }
        j = 0;
        i++;
    }

    //selectionne aléatoirement un indice de zeros
    int i_random = ( indicesBlocksNulls.size() < 2 )? 0 : rand() % ( indicesBlocksNulls.size() - 1 );

    int indice = indicesBlocksNulls[ i_random ];
    i = indice / (int)grille.size();
    j = indice % (int)grille.size();

    //insert une nouvelle valeur sur cet indice selectionné
    bool chanceOf4 = (rand() % 100) < 15;
    int valueBlock = 2 * chanceOf4 + 2;

    grille[i][j] = valueBlock;

}

bool ProcessGame::perdu()
{
    struct XY
    {
        int i;
        int j;
    };

    vector<XY> around = { { 1, 0 }, { 0, 1 } };

    int i = 0;

    bool perdu = true;
    //Verifie si des zeros existe ou si 2 cases peuvent fusionner
    for (ligne _ligne : grille )
    {

        int j = 0;
        for ( int block : _ligne)
        {

            for ( XY offset : around )
            {
                int ii = i + offset.i;
                int jj = j + offset.j;
                if ( ii < (int)grille.size() && jj < (int)grille.size() )
                {
                    int neighboorBlock = grille[ ii ][ jj ];

                    if ( block == neighboorBlock || block == 0 || neighboorBlock == 0)
                    {
                        return !perdu;
                    }
                }
            }
            j++;
        }
        i++;
    }

    return perdu;
}

int ProcessGame::getScore() const
{
    return score;
}

bool ProcessGame::isGameOver() const
{
    return gameOver;
}

std::map<std::string, grid> ProcessGame::getMove() const
{
    return i_move;
}

grid ProcessGame::getGrille() const
{
    return grille;
}

void ProcessGame::fusionCase(ligne& _ligne)
{
    for ( int i = (int)_ligne.size() - 1; i >= 1; i -- )
    {
        if ( _ligne[i] == _ligne[i - 1] )
        {
            _ligne[ i ] *= 2;
            score += _ligne[ i ];

            _ligne.erase( _ligne.begin() + i - 1 );
            _ligne.insert( _ligne.begin(), 0);
        }
    }
}

void ProcessGame::MoveBlock( string sens )
{
    if ( !gameOver )
    {
        blockMoved = false;
        numberOfZeros = 0;

        //creer des lignes en fonction de la grille
        //et du mouvememnt pour traiter chaque ligne.

        for ( ligne i_line : i_move[sens] )
        {
            ligne processLine;
            for ( int indice : i_line)
            {
                int i = indice / (int)grille.size();
                int j = indice % (int)grille.size();

                processLine.push_back( grille[ i ][ j ] );
            }

            moveZeros( processLine );
            fusionCase( processLine );

            int jj = 0;

            //restitue les blocks dans la grille
            for ( int numcase : i_line )
            {

                int i = numcase / (int)grille.size();
                int j = numcase % (int)grille.size();


                bool changeCase = ( grille[i][j] != processLine[jj] );
                if ( changeCase )
                {
                    blockMoved = true;
                    grille[i][j] = processLine[jj];
                }

                if (grille[i][j] == 0)
                    numberOfZeros++;
                jj++;
            }
        }

        //verifie si il y a eu un deplacement des cases
        if ( blockMoved )
        {
            addNumber();
            numberOfZeros--;
        }

        //verifie si on peut encore jouer
        if ( numberOfZeros < 1 )
            if ( perdu() )
                gameOver = true;

    }
}

void ProcessGame::creerGrilleJeu( int gridSize )
{
    grille.resize( gridSize, vector<int>( gridSize, 0 )  );

    grid left, up, right, down;

    left.resize( grille.size(), vector<int>( grille.size(), 0 )  );
    right.resize( grille.size(), vector<int>( grille.size(), 0 )  );
    up.resize( grille.size(), vector<int>( grille.size(), 0 )  );
    down.resize( grille.size(), vector<int>( grille.size(), 0 )  );

    //repartie les indices des cases pour les traiter de la même
    //manière quelque soit le sens de déplacement.

    for ( int k = 0; k < int(grille.size() * grille.size() ); k++)
    {
        int i = k / (int)grille.size();
        int j = k % (int)grille.size();

        right[ i ][ j ]                       = k ;
        down [ j ][ i ]                       = k;
        left [ i ][ ( left.size() - 1 ) - j ] = k;
        up   [ j ][ ( up.size() -  1  ) - i ] = k;

    }

    i_move["up"] = up;
    i_move["down"] = down;
    i_move["left"] = left;
    i_move["right"] = right;

}
