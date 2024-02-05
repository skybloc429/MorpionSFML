
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Input.h"
#include "Morpion.h"
#include "Player.h"
#include "Defines.h"

//

#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

bool turn(Render render, Morpion* morpion, int turnCounter) {
    int placeState = morpion->placeSymbol(render);
    if (placeState == 1) {
        std::cout << "Erreur de placement du symbole. Impossible de placer à cet emplacement." << std::endl;
        return false;
    }

    std::cout << "Tour " << turnCounter << ": ";
    std::cout << "Joueur actuel : " << morpion->currentPlayer->name << ", Symbole : " << static_cast<char>(morpion->currentPlayer->symbol) << std::endl;

    morpion->drawBoard(render);

    return true;
}


int main(int argc, char** argv)
{
    std::cout << "SERVER" << std::endl;
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsaerr != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return 0;
    }
    else {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET listenSocket;
    listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (listenSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else {
        std::cout << "Socket is OK!" << std::endl;
    }

    // Configuration de l'adresse et du port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Utilisez INADDR_ANY pour accepter les connexions de n'importe quelle adresse
    serverAddress.sin_port = htons(80);  // Choisissez un numéro de port

    // Liage du socket à l'adresse et au port
    if (bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la liaison du socket à l'adresse et au port." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Mettez le socket en mode écoute
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la mise en écoute du socket." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    SOCKET acceptSocket;
    acceptSocket = accept(listenSocket, nullptr, nullptr);

    // Check for successful connection
    if (acceptSocket == INVALID_SOCKET) {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return -1;
    }
    else {
        std::cout << "accept() is OK!" << std::endl;
    }

    // Envoyer un message au client
    const char* message = "Bienvenue sur le serveur!";
    if (send(acceptSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }

    while (1);
    // Fermer le socket d'écoute
    closesocket(listenSocket);

    // Fermer le socket accepté
    closesocket(acceptSocket);

    // Libérer Winsock
    WSACleanup();
    ////Création d'une fenêtre
    //Render myRenderer{new sf::RenderWindow(sf::VideoMode(640, 480), "SFML"), new sf::Event, 640, 480};
    //Morpion* myMorpion;
    //myMorpion = new Morpion;

    //Player* player1 = nullptr;
    //player1 = new Player{ "William", Symbol::X, 0};

    //Player* player2 = nullptr;
    //player2 = new Player{ "Bot", Symbol::O, 0 };


    ////GameLoop
    //myMorpion->drawBoard(myRenderer);
    //myMorpion->currentPlayer = player1;
    //int turnCounter = 0;
    //while (myRenderer.pWindow->isOpen())
    //{

    //    


    //    //EVENT
    //    int inputState = updateInput(myRenderer);
    //    //PRINT(myMorpion.currentPlayer->name)
    //    if (inputState == 0) {
    //        //PRINT("Pas d'Input")
    //        continue;
    //    }
    //    else if(inputState == 1) {
    //        if (!turn(myRenderer, myMorpion, turnCounter))
    //        {
    //            continue;
    //        };
    //    }




   



    //    //PRINT("Action")

    //    //UPDATE

    //    //DRAW
    //    if (myMorpion->checkEnd(Symbol::X) || myMorpion->checkEnd(Symbol::O)) {
    //        PRINT("Partie terminé, joueur gagnant :")
    //        PRINT(myMorpion->currentPlayer->name);
    //        //break;
    //    }

    //    // Transition next it
    //    myMorpion->currentPlayer = (turnCounter % 2 == 0) ? player2 : player1;
    //    turnCounter++;


    //}

    return 0;
}

//#include <iostream>
//#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
//#include <WinSock2.h>
// 
// 
//
//#pragma comment(lib, "ws2_32.lib")
//
//struct ConnectionData {
//    WSADATA wsaData;
//    SOCKET clientSocket;
//    sockaddr_in serverAddress;
//    const char* getRequest;
//};
//
//// Init Connexion
//bool InitializeConnection(ConnectionData& connectionData) {
//    // Init Winsock
//    if (WSAStartup(MAKEWORD(2, 2), &connectionData.wsaData) != 0) {
//        std::cerr << "Erreur lors de l'initialisation de Winsock." << std::endl;
//        return false;
//    }
//
//    // Init Client Socket
//    connectionData.clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (connectionData.clientSocket == INVALID_SOCKET) {
//        std::cerr << "Erreur lors de la création du socket." << std::endl;
//        WSACleanup();
//        return false;
//    }
//
//    // Config Server Address
//    inet_pton(AF_INET, "172.217.169.78", &(connectionData.serverAddress.sin_addr));
//    connectionData.serverAddress.sin_family = AF_INET; // IP V4
//    connectionData.serverAddress.sin_port = htons(80); // Port 80
//
//    // Connect Client Socket to server address
//    if (connect(connectionData.clientSocket, reinterpret_cast<sockaddr*>(&connectionData.serverAddress), sizeof(connectionData.serverAddress)) == SOCKET_ERROR) {
//        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
//        closesocket(connectionData.clientSocket);
//        WSACleanup();
//        return false;
//    }
//
//    std::cout << "Connexion établie ..." << std::endl;
//    return true;
//}
//
//// Send Request
//bool SendRequest(ConnectionData& connectionData) {
//    if (send(connectionData.clientSocket, connectionData.getRequest, strlen(connectionData.getRequest), 0) == SOCKET_ERROR) {
//        std::cerr << "Erreur lors de l'envoi de la requête." << std::endl;
//        closesocket(connectionData.clientSocket);
//        WSACleanup();
//        return false;
//    }
//
//    return true;
//}
//
//
//void ReceiveAndDisplayResponse(ConnectionData& connectionData) {
//    char buffer[4096];
//    int bytesRead;
//    while ((bytesRead = recv(connectionData.clientSocket, buffer, sizeof(buffer), 0)) > 0) {
//        std::cout.write(buffer, bytesRead);
//    }
//}
//
//
//void CloseConnection(ConnectionData& connectionData) {
//    closesocket(connectionData.clientSocket);
//    WSACleanup();
//}
//
//int main() {
//    ConnectionData connectionData;
//    connectionData.getRequest = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
//
//    if (InitializeConnection(connectionData)) {
//        if (SendRequest(connectionData)) {
//            ReceiveAndDisplayResponse(connectionData);
//        }
//        CloseConnection(connectionData);
//    }
//
//    while (1) {
//    }
//
//    return 0;
//}
