#ifndef CONTEXTE_H
#define CONTEXTE_H

#include "processgame.h"
#include "iostream"
#include <QObject>
#include <QQmlContext>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QQmlApplicationEngine>


class Contexte : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList game2048 READ game2048 WRITE setGame2048 NOTIFY game2048Changed)
    Q_PROPERTY(QString direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(QString newGame READ newGame WRITE setNewGame NOTIFY newGameChanged)
    Q_PROPERTY(QString score READ score WRITE setScore NOTIFY scoreChanged)
    QStringList m_game2048;




public:
    explicit Contexte(QObject *parent = nullptr);

    QStringList game2048() const;
    void start();
    void updateGrid ();
    void getGridForQML();

    void setContext(QQmlContext *context);
    void updateContext();
    QString direction() const;

    QString newGame() const;

    QString score() const
    {
        return m_score;
    }

public slots:
    void setGame2048(QStringList game2048);
    void setDirection(QString direction);

    void setNewGame(QString newGame);

    void setScore(QString score);

signals:
    void game2048Changed(QStringList game2048);

    void directionChanged(QString direction);

    void newGameChanged(QString newGame);

    void scoreChanged(QString score);

private:
    QQmlContext* m_context;
    QString m_direction;
    ProcessGame* jeux;
    QString m_newGame;
    QString m_score;
};

#endif // CONTEXTE_H
