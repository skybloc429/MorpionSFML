#include <Ws2tcpip.h>  // Ajout de l'en-tête pour inet_pton
#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")


int main() {
    // Initialize WSA variables
    std::cout << "CLIENT" << std::endl;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsaerr != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return 0;
    } else {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (clientSocket == INVALID_SOCKET) {
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

    // Utilisation de inet_pton pour convertir l'adresse IP
    if (inet_pton(AF_INET, "172.217.169.78", &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    serverAddress.sin_port = htons(80);  // Choisissez un numéro de port

    // Connexion au serveur
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Connexion réussie" << std::endl;
    }

    char buffer[4096];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    // Vérifier si la réception a été réussie
    if (bytesRead == SOCKET_ERROR || bytesRead == 0) {
        std::cerr << "Erreur lors de la réception du message du serveur." << std::endl;
    }
    else {
        // Afficher le message
        std::cout << "Message du serveur : " << buffer << std::endl;
    }


    // Fermer le socket
    closesocket(clientSocket);

    // Libérer Winsock
    WSACleanup();

    while (1);

    return 0;
}
