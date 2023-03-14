#include "csvinterface.h"
#include "qdebug.h"


CSVInterface::CSVInterface() {}


QFile playersDB("./db/players.csv");
QFile matchDB("./db/match.csv");
QFile turnsDB("./db/turns.csv");

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
        //is.readLine();

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
            "" + QString::number(++lastTurn) +
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
        os << ""   + QString::number(playerid1) +
              ","  + QString::number(playerid2) +
              ","  + QString::number(matchTime) +
              ","  + QString::number(winnerid) + "\n";
        os.flush();
        matchDB.close();
    }



    QString playerDataRaw = "#id,name,totalPlays,totalWins\n";
    // Reading all Playerdatas and increment the 'totalPlayed' count for every
    // Player played in this Match
    // also increment the 'totalWins' for the winner
    if (playersDB.open(QIODevice::ReadOnly)) {
        QTextStream is(&playersDB);
        is.readLine(); // read first line to skip the header
        while(!is.atEnd()) {
            //qDebug() << is.readLine();v
            QString line = is.readLine();
            int id = line.split(",")[0].toInt();
            QString name = line.split(",")[1];
            int totalPlayed = line.split(",")[2].toInt();
            int totalWins = line.split(",")[3].toInt();


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

