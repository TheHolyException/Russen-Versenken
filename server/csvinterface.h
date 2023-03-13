#ifndef CSVINTERFACE_H
#define CSVINTERFACE_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <QFile>

class CSVInterface : public QObject {
public:
    CSVInterface();
    static void init();
    static void debug();
    static void afterTurn(int turnno, int matchid, int playerid, int fieldno);
    static void afterMatch(int playerid1, int playerid2,
                           int winnerid, long matchTime);
};

#endif // CSVINTERFACE_H
