#include "csvinterface.h"
#include "qdebug.h"


CSVInterface::CSVInterface() {}


QFile playersDB("./db/players.csv");
QFile matchDB("./db/match.csv");
QFile turnsDB("./db/turns.csv");

/**
 * @brief CSVInterface::getPlayerID Gets the PlayerID with the given name
 *                                  If not exits, a new player will be created
 * @param name of the Player
 * @return PlayerID
 */
int CSVInterface::getPlayerID(QString name) {
    int id = -1;
    int lastID = -1;

    if (playersDB.open(QIODevice::ReadOnly)) {
       QTextStream is(&playersDB);

       while (!is.atEnd()) {
           QString line = is.readLine();
           if (line.startsWith("#")) continue; // Skipping Header
           QStringList lineData = line.split(',');

           int lineid;
           if ((lineid = lineData.at(0).toInt()) > lastID) lastID = lineid;
           if (name.toLower() == lineData.at(1).toLower()) id = lineid;
       }
       playersDB.close();
    }

    if (id == -1 && playersDB.open(QIODevice::Append)) {
        QTextStream os(&playersDB);
        id = lastID +1;
        os <<       QString::number(id) +
              "," + name + ",0,0\n";
        os.flush();
        playersDB.close();
    }

    return id;
}

/**
 * @brief CSVInterface::getPlayerScore Gets the 'TotalPlayCount' and 'TotalWinCount'
 * @param playerid      Id of the Player
 * @param totalPlayed   Pointer to the variable that stores the 'TotalPlayCount'
 * @param totalWins     Pointer to the variable that stores the 'TotalWinCount'
 * @returns true if the player score could be obtained, false when not
 */
bool CSVInterface::getPlayerScore(int playerid, int *totalPlayed, int *totalWins) {
    if (playersDB.open(QIODevice::ReadOnly)) {
        QTextStream is(&playersDB);

        while (!is.atEnd()) {
            QString line = is.readLine();
            if (line.startsWith('#')) continue; // Skipping Header
            QStringList lineData = line.split(',');

            if (lineData.at(0).toInt() == playerid) {
                *totalPlayed = lineData.at(2).toInt();
                *totalWins = lineData.at(3).toInt();
                return true;
            }
        }
        playersDB.close();
    }
    return false;
}


/**
 * @brief CSVInterface::afterTurn should be executed after every turn to save all informations in the csv
 * @param matchid   ID of the Match
 * @param playerid  ID of the player
 * @param fieldno   Fieldnumber
 */
void CSVInterface::afterTurn(int matchid, int playerid, int fieldno) {
    int lastTurn = -1;
    QString turnDataRaw = "#turnno,matchid,playerid,fieldno\n";
    if (turnsDB.open(QIODevice::ReadOnly)) {
        QTextStream is(&turnsDB);

        while (!is.atEnd()) {
            QString line = is.readLine();
            if (line.startsWith('#')) continue; // Skipping Header

            QStringList lineData = line.split(',');
            if (lineData.at(1).toInt() == matchid )
                lastTurn = lineData.at(0).toInt();

            turnDataRaw += line+"\n";
        }
        turnsDB.close();
    }

    turnDataRaw +=
                   QString::number(++lastTurn) +
            ","  + QString::number(matchid) +
            ","  + QString::number(playerid) +
            ","  + QString::number(fieldno) + "\n";

    // Writing the turn information to the turns.csv
    if (turnsDB.open(QIODevice::WriteOnly)) {
        QTextStream os(&turnsDB);
        os << turnDataRaw;
        os.flush();
        turnsDB.close();
    }
}


void CSVInterface::afterMatch(int playerid1, int playerid2,
                              int winnerid, long matchTime) {
    // Writing matchdata to the match.csv
    if (matchDB.open(QIODevice::Append)) {
        QTextStream os(&matchDB);
        os <<        QString::number(playerid1) +
              "," + QString::number(playerid2) +
              "," + QString::number(matchTime) +
              "," + QString::number(winnerid) + "\n";
        os.flush();
        matchDB.close();
    }

    QString playerDataRaw = "#id,name,totalPlays,totalWins\n";

    // Reading all Playerdatas and increment the 'totalPlayed' count for every
    // Player played in this Match
    // also increment the 'totalWins' for the winner
    if (playersDB.open(QIODevice::ReadOnly)) {
        QTextStream is(&playersDB);
        while(!is.atEnd()) {
            QString line = is.readLine();
            if (line.startsWith('#')) continue; // Skipping Header

            QStringList lineData = line.split(',');

            int id          = lineData.at(0).toInt();
            QString name    = lineData.at(1);
            int totalPlayed = lineData.at(2).toInt();
            int totalWins   = lineData.at(3).toInt();

            if (id == winnerid) totalWins ++;
            if (id == playerid1 || id == playerid2) totalPlayed++;

            line =       QString::number(id) +
                   "," + name +
                   "," + QString::number(totalPlayed) +
                   "," + QString::number(totalWins) +"\n";


            playerDataRaw += line;
        }
        playersDB.close();
    }

    // Rewriting the playerdatabase with the modified dataset
    if (playersDB.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream os(&playersDB);
        os << playerDataRaw;
        os.flush();
        playersDB.close();
    }
}

