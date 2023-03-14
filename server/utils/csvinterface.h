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
    static void afterTurn(int matchid, int playerid, int fieldno);
    static void afterMatch(int playerid1, int playerid2,
                           int winnerid, long matchTime);
};

#endif // CSVINTERFACE_H
