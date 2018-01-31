#include "contexte.h"
#include <iostream>

using namespace std;

Contexte::Contexte( QObject *parent ) : QObject( parent ), m_context( nullptr ), jeux(new ProcessGame)
{}


QStringList Contexte::game2048() const
{
    return m_game2048;
}

void Contexte::start()
{

    //    ProcessGame jeux(5);
    //    setScore("0");
    updateGrid();
    updateContext();
}

void Contexte::updateGrid()
{
    jeux->NewGame();
    QStringList maListe;
    maListe.clear();
    grid grille = jeux->getGrille();
    for ( ligne _ligne : grille)
    {
        for ( int block : _ligne)
        {

            maListe << QString::number( block );
        }
    }

    setGame2048(maListe);


}

void Contexte::getGridForQML()
{
    m_game2048.clear();
    grid grille = jeux->getGrille();
    for ( ligne _ligne : grille)
    {
        for ( int block : _ligne)
        {
            m_game2048 << QString::number( block );
        }
    }

}

void Contexte::setContext(QQmlContext *context)
{
    std::cout << "setContext" <<endl << std::endl;
    m_context = context;
    m_context->setContextProperty("Context", this);
}

//int getScore() const;
void Contexte::updateContext()
{
    // Send the data to Qml
    QString myScore = QString::number( jeux->getScore() );
    setScore(myScore);

    if( m_context!= nullptr )
        m_context->setContextProperty("modele2048", QVariant::fromValue( m_game2048 ));
    else
        qDebug() << "Context non instancié";
}

QString Contexte::direction() const
{
    return m_direction;
}

QString Contexte::newGame() const
{
    return m_newGame;
}

void Contexte::setGame2048(QStringList game2048)
{
    std::cout << "set2048" <<endl << std::endl;
    if (m_game2048 == game2048)
        return;

    m_game2048 = game2048;
    emit game2048Changed(m_game2048);
}

void Contexte::setDirection(QString direction)
{
    //    ------------
    jeux->MoveBlock(direction.toStdString());
    getGridForQML();
    //            updateGrid();
    updateContext();
    //    ----------
    if (m_direction == direction)
        return;

    m_direction = direction;
    emit directionChanged(m_direction);
}

void Contexte::setNewGame(QString newGame)
{
    //setContext( ctx );

    //        QQmlApplicationEngine engine;
    //        QQmlContext* ctx = engine.rootContext();


    // Set le ctx
    //        setContext( ctx );
    start();



    if (m_newGame == newGame)
        return;

    m_newGame = newGame;
    //    emit game2048Changed(m_game2048 );
    emit newGameChanged(m_newGame);
}

void Contexte::setScore(QString score)
{
    //    if (m_score == score)
    //        return;

    m_score = score;
    emit scoreChanged(m_score);
}


