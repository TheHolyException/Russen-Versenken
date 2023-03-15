#include "russenversenken_server.h"
#include "qtimer.h"
#include "utils\csvinterface.h"

RussenVersenken_Server::RussenVersenken_Server()
{
    player1 = Player();
    player2 = Player();;
    phase =0;

    QTimer *m_timer;

    m_timer = new QTimer(this);
    m_timer->setInterval(10); // (100 TPS)
    QObject::connect(m_timer, &QTimer::timeout, this, &RussenVersenken_Server::Game);
    m_timer->start();
}

void RussenVersenken_Server::sendGrid(Hexagon grid[10][10], Player *player) {
    std::map<std::string, JSONUtils::Value> gridMap;
    int pos = 0;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            Hexagon hex = grid[j][i];
            gridMap.insert({std::to_string(pos) , std::to_string(hex.isShipPart) + "#"+std::to_string(hex.isHit)});
            pos++;
        }
    }
    QString message = QString::fromStdString(JSONUtils::generateJSON(gridMap));
    player->sendPacket(151, message);
}

bool RussenVersenken_Server::AreAllShipsDown(Hexagon grid[10][10]){

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(grid[i][j].isShipPart && !grid[i][j].isHit){
                return false;
            }
        }
    }

    return true;
}

void RussenVersenken_Server::Game(){
     QString m;
    if(phase==0){
        if(player1.name!="" && player2.name!=""){
            phase=1;
            qDebug() << "phase 1";
        }

    }else if(phase==1){

        if(player1.isReady&&player2.isReady){
            phase=2;
            m ="2";
            player1.sendPacket(301,m) ;
            player2.sendPacket(301,m) ;
            qDebug() << "phase 2";
            player1.isReady=false;
            player2.isReady=false;
            matchId=CSVInterface::createMatch();
        }
    }else if(phase==2){
        if(activePlayer==nullptr){
            activePlayer=&player1;
            m ="";
            sendGrid(player2.grid,&player1);
            player1.sendPacket(801,m) ;
        }else if(activePlayer==&player1){
            if(player1.isReady && player2.isReady ){

               activePlayer=&player2;
               player1.isReady=false;
               player2.isReady=false;
               sendGrid(player1.grid,&player2);
               waitingForOtherPlayer=false;

               m ="";
               player2.sendPacket(801,m) ;
            }else if(activePlayer->isReady&&!waitingForOtherPlayer){
                sendGrid(player2.grid,&player2);
                m = player1.name +" hat auf das Feld "+(QString)((char)(65+hit.x()))+(QString)((char)(49+hit.y()))+" geschossen";
                player2.sendPacket(602,m);
                waitingForOtherPlayer=true;

                if(AreAllShipsDown(player2.grid)){
                    gameWon(&player1);
                }
            }

        }else if(activePlayer==&player2){
            if(player1.isReady && player2.isReady ){
               activePlayer=&player1;
               player1.isReady=false;
               player2.isReady=false;
               sendGrid(player2.grid,&player1);
               waitingForOtherPlayer=false;

               m ="";
               player1.sendPacket(801,m) ;
            }else if(activePlayer->isReady&&!waitingForOtherPlayer){
                sendGrid(player1.grid,&player1);
                QString m = player2.name +" hat auf das Feld "+(QString)((char)(65+hit.x()))+(QString)((char)(49+hit.y()))+" geschossen";
                player1.sendPacket(602,m);
                waitingForOtherPlayer=true;

                if(AreAllShipsDown(player1.grid)){
                    gameWon(&player2);
                }
            }
        }
    }else if(phase==3){
        if(player1.isReady&&player2.isReady){
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    player1.grid[i][j].isHit=false;
                    player1.grid[i][j].isShipPart=false;
                    player2.grid[i][j].isHit=false;
                    player2.grid[i][j].isShipPart=false;
                }
            }
            sendGrid(player1.grid,&player1);
            sendGrid(player2.grid,&player2);
            activePlayer=nullptr;

            phase=1;
            m ="1";
            player1.sendPacket(301,m) ;
            player2.sendPacket(301,m) ;
            player1.sendPacket(801,m) ;
            player2.sendPacket(801,m) ;
            player1.isReady=false;
            player2.isReady=false;
        }
    }
}

void RussenVersenken_Server::gameWon(Player *player){
    QString m = player->name +" hat das Spiel gewonnen!!\n Wenn du noch ein Spielspielen willst, drücke den \"Bereit\"-Knopf.";
    player1.sendPacket(602,m);
    player2.sendPacket(602,m);

    phase = 3;
    m ="3";
    player1.sendPacket(301,m) ;
    player2.sendPacket(301,m) ;
    player1.isReady=false;
    player2.isReady=false;

    int player1Id=CSVInterface::getPlayerID(player1.name);
    int player2Id=CSVInterface::getPlayerID(player2.name);
    int winnerId =CSVInterface::getPlayerID(player->name);

    CSVInterface::afterMatch(matchId,player1Id,player2Id,winnerId);
}
