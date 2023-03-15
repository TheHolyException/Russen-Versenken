#ifndef CSVINTERFACE_H
#define CSVINTERFACE_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <QFile>

class CSVInterface : public QObject {
private:
    CSVInterface();
public:
    static int  getPlayerID(QString name);
    static bool getPlayerScore(int playerid, int* totalPlayed, int* totalWins);
    static int  createMatch();
    static void afterTurn(int matchid, int playerid, int fieldno, long timestamp);
    static void afterMatch(int matchid, int playerid1, int playerid2,
                           int winnerid);
};

#endif // CSVINTERFACE_H
