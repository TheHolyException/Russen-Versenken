#include "csvinterface.h"
#include "qdebug.h"


CSVInterface::CSVInterface() {}


QFile playersDB("./db/players.csv");
QFile matchDB("./db/match.csv");
QFile turnsDB("./db/turns.csv");

void CSVInterface::init() {
    //dbMatch.open("./db/matchs.csv");
    //dbPlayer.open("./db/players.csv");
    //dbTurns.open("./db/turns.csv");
}

void CSVInterface::afterTurn(int turnno, int matchid, int playerid, int fieldno) {
    // Writing the turn information to the turns.csv
    if (turnsDB.open(QIODevice::WriteOnly)) {
        QTextStream os(&turnsDB);
        os << "\n" + QString::number(turnno) +
              ","  + QString::number(matchid) +
              ","  + QString::number(playerid) +
              ","  + QString::number(fieldno);
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



    QString playerDataRaw = "id,name,totalPlays,totalWins\n";
    // Reading all Playerdatas and increment the 'totalPlayed' count for every
    // Player played in this Match
    // also increment the 'totalWins' for the winner
    if (playersDB.open(QIODevice::ReadOnly)) {
        qDebug() << "Reading";
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




void CSVInterface::debug() {
    std::ofstream out;
    //out.open("C:\\Users\\Patrick\\Documents\\Git\\Russen-Versenken\\server\\database.csv");
    out.open("./data.csv");
    out.write("asdf", 4);
    out.flush();
    //qDebug() << QString::fromStdString(out);
    out.close();
}


