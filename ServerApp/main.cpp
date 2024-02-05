#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur lors de l'initialisation de Winsock." << std::endl;
        return 1;
    }

    // Cr�ation du socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la cr�ation du socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuration de l'adresse et du port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345);

    // Liaison du socket � l'adresse et au port
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la liaison du socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Mise en mode �coute
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la mise en mode �coute." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Serveur en attente de connexions..." << std::endl;

    // Accepter une connexion entrante
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Envoyer une variable au client
    int variableAEnvoyer = 42;
    send(clientSocket, (char*)&variableAEnvoyer, sizeof(variableAEnvoyer), 0);

    // Fermer les sockets
    closesocket(clientSocket);
    closesocket(serverSocket);

    // Lib�rer Winsock
    WSACleanup();

    return 0;
}