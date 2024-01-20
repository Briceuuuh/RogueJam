/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Server.cpp
*/

#include "../include/Server.hpp"

/**
 * @brief Default constructor for the Server class.
 *
 * This constructor initializes the server with default values and starts the server.
 */
Server::Server()
{
    this->listener.listen(std::stoi("4242"));
    this->selector.add(this->listener);
    this->udp = new sf::UdpSocket();
    this->code = new Code();
    this->running = false;
    this->clients_ready = 0;
    this->LogFile.open("LogFile.txt");
    if (this->udp->bind(4242) == sf::Socket::Done) {
        std::cout << "/*----------------------------------------------------*/\n" << std::endl;
        std::cout << "/*                 GTR TYPE - SERVER                  */\n" << std::endl;
        std::cout << "/*____________________________________________________*/\n" << std::endl;
        std::cout << "/* @ All right reserved to                            */\n" << std::endl;
        std::cout << "/*                        - Maël POMPILIUS            */\n" << std::endl;
        std::cout << "/*                        - Florian ETHEVE            */\n" << std::endl;
        std::cout << "/*                        - Ethan GUILLOUX            */\n" << std::endl;
        std::cout << "/*                        - Brice HUET                */\n" << std::endl;
        std::cout << "/*                        - Noémie MAILLOT            */\n" << std::endl;
        std::cout << "/*____________________________________________________*/\n" << std::endl;
        std::cout << "/* Here's the log of the game, all the sended message */\n" << std::endl;
        std::cout << "/* is displayed on the terminal.                      */\n" << std::endl;
        std::cout << "/*                                                    */\n" << std::endl;
        std::cout << "/* Refer to the protocol documentation to know the    */\n" << std::endl;
        std::cout << "/* logs.                                              */\n" << std::endl;
        std::cout << "/*----------------------------------------------------*/\n" << std::endl;
        this->LogFile << "/*----------------------------------------------------*/\n"
                        "/*                 GTR TYPE - SERVER                  */\n"
                        "/*____________________________________________________*/\n"
                        "/* @ All right reserved to                            */\n"
                        "/*                        - Maël POMPILIUS            */\n"
                        "/*                        - Florian ETHEVE            */\n"
                        "/*                        - Ethan GUILLOUX            */\n"
                        "/*                        - Brice HUET                */\n"
                        "/*                        - Noémie MAILLOT            */\n"
                        "/*____________________________________________________*/\n"
                        "/* Here's the log of the game, all the sended message */\n"
                        "/* is displayed on the terminal.                      */\n"
                        "/*                                                    */\n"
                        "/* Refer to the protocol documentation to know the    */\n"
                        "/* logs.                                              */\n"
                        "/*----------------------------------------------------*/\n";
        this->LogFile.flush();
        this->LogFile << "Served Launched\n";
        this->LogFile.flush();
        this->selector.add(*this->udp);
    }
    this->state = Waiting;
    this->udp->setBlocking(false);
    
    this->run();
}

/**
 * @brief Constructor for the Server class with a custom port.
 *
 * This constructor initializes the server with a specified port and starts the server.
 *
 * @param port The port number for the server to listen on.
 */
Server::Server(const std::string &port)
{
    this->listener.listen(std::stoi(port));
    this->selector.add(this->listener);
    this->udp = new sf::UdpSocket();
    this->code = new Code();
    this->running = false;
    this->clients_ready = 0;
    this->LogFile.open("LogFile.txt");
    if (this->udp->bind(std::stoi(port)) == sf::Socket::Done) {
        // std::cout << "udp connect" << std::endl;
        // std::string log = "game id [";
        // log << this->hash_id(this->identifier) << "]\n";
        std::cout << "/*----------------------------------------------------*/" << std::endl;
        std::cout << "/*                 GTR TYPE - SERVER                  */" << std::endl;
        std::cout << "/*____________________________________________________*/" << std::endl;
        std::cout << "/* @ All right reserved to - GTR Team                 */" << std::endl;
        std::cout << "/*____________________________________________________*/" << std::endl;
        std::cout << "/* Here's the log of the game, all the sended message */" << std::endl;
        std::cout << "/* is displayed on the terminal.                      */" << std::endl;
        std::cout << "/*                                                    */" << std::endl;
        std::cout << "/* Refer to the protocol documentation to know the    */" << std::endl;
        std::cout << "/* logs.                                              */" << std::endl;
        std::cout << "/*----------------------------------------------------*/\n" << std::endl;
        this->LogFile << "/*----------------------------------------------------*/\n"
                        "/*                 GTR TYPE - SERVER                  */\n"
                        "/*____________________________________________________*/\n"
                        "/* @ All right reserved to                            */\n"
                        "/*                        - Maël POMPILIUS            */\n"
                        "/*                        - Florian ETHEVE            */\n"
                        "/*                        - Ethan GUILLOUX            */\n"
                        "/*                        - Brice HUET                */\n"
                        "/*                        - Noémie MAILLOT            */\n"
                        "/*____________________________________________________*/\n"
                        "/* Here's the log of the game, all the sended message */\n"
                        "/* is displayed on the terminal.                      */\n"
                        "/*                                                    */\n"
                        "/* Refer to the protocol documentation to know the    */\n"
                        "/* logs.                                              */\n"
                        "/*----------------------------------------------------*/\n";
        this->LogFile.flush();
        this->LogFile << "Served Launched\n";
        this->LogFile.flush();
        this->selector.add(*this->udp);
    }
    this->state = Waiting;
    this->udp->setBlocking(false);
    this->run();
}

/**
 * @brief Add a client to the server.
 *
 * This function creates and adds a new client to the server, accepting the client's connection on the TCP socket.
 *
 * @param id The unique identifier for the new client.
 */
void Server::addClient(size_t id)
{
    ClientManager *cli = new ClientManager(id);
    sf::TcpSocket *tcpSocket = cli->getTcp()->getSocket();

    if (this->listener.accept(*tcpSocket) != sf::Socket::Done) {
        std::cout << "error to accept" << std::endl;
        this->LogFile << "error to accept\n";
        this->LogFile.flush();
    }
    this->selector.add(*tcpSocket);
    cli->setConnect(true);

    this->clients.push_back(cli);
    std::cout << "client accepted" << std::endl;
    this->LogFile << "Client accepted\n";
    this->LogFile.flush();
}

/**
 * @brief Perform TCP action for a client.
 *
 * This function handles the TCP actions for a given client. It can be used to send initial messages to the client or perform other actions after the client has connected.
 *
 * @param client The client for which to perform TCP actions.
 */
void Server::actionTcp(ClientManager *client)
{
    if (client->getFirst() != true) {
        client->getTcp()->send(std::to_string(client->getId()) + ",1");
        client->setFirst();
    } else {
        
    }
}

/**
 * @brief Check for incoming data on TCP connections.
 *
 * This function iterates through the list of connected clients and checks for incoming data on their TCP connections. If there is incoming data, it reads and processes it, typically by invoking the 'actionTcp' function for each client.
 */
void Server::onLineTcp()
{
    for (size_t i = 0; i < this->clients.size() ; i++) {
        if (this->selector.isReady(*this->clients.at(i)->getTcp()->getSocket())) {
            this->clients.at(i)->getTcp()->read();
            this->actionTcp(this->clients.at(i));
        }
    }
}

/**
 * @brief Inject UDP data to other clients.
 *
 * This function injects previously saved UDP data to other clients except the specified client.
 *
 * @param client The client to exclude from data injection.
 * @return `true` if data injection was successful; `false` otherwise.
 */
bool Server::injectReady(ClientManager *client)
{
    bool alright = false;
    Code *decrypt = new Code();

    for (size_t i = 0; i < this->saveUdp.size(); i++) {
        decrypt->getReceivePackage(this->saveUdp.at(i));
        sf::IpAddress new_ip = client->getIp();
        unsigned short new_port = client->getPort();
        if (client->getId() != (size_t)decrypt->getId()) {
            this->udp->send(this->saveUdp.at(i).c_str(), this->saveUdp.at(i).size(), new_ip, new_port);
            alright = true;
        }
    }
    return alright;
}

/**
 * @brief Convert ASCII text to binary string.
 *
 * This function takes an ASCII text as input and converts it into a binary string, where each character in the text is represented as an 8-bit binary sequence.
 *
 * @param ascii The ASCII text to be converted to binary.
 * @return The binary representation of the input ASCII text.
 */
std::string switchToBinary(std::string ascii)
{
    std::string tmp;
    for (size_t i = 0; i != ascii.size(); i++) {
        std::bitset<8> binaire(ascii.at(i));
        tmp += binaire.to_string();
    }
    return tmp;
}

/**
 * @brief Send a UDP message to all connected clients except the sender.
 *
 * This method sends a UDP message to all connected clients except the sender. It uses the provided
 * UDP socket to send the message. The sender's ID is checked to exclude sending the message back to them.
 *
 * @param response The message to be sent to clients.
 * @param socket The UDP socket for sending the message.
 */
bool Server::sendToAllUdp(std::string str, size_t id)
{
    for (size_t i = 0; i < this->clients.size(); i++) {
        sf::IpAddress new_ip = this->clients.at(i)->getIp();
        unsigned short new_port = this->clients.at(i)->getPort();
        if (this->clients.at(i)->getId() != id &&
        (this->udp->send(str.c_str(), str.size(), new_ip, new_port) == sf::Socket::Done)) {
            this->LogFile << "[[UDP]] ~ send {" << switchToBinary(str) << "} from [" << id << "] to [" << this->clients.at(i)->getId() << "]\n";
            this->LogFile.flush();
            // std::cout << "message envoyé UDP => " << switchToBinary(str) << ": [" << id  << "] de port [" << new_port << "] destiné à [" << this->clients.at(i)->getId() << "]" << std::endl; 
        }
    }
    return true;
}

/**
 * @brief Process incoming UDP data.
 *
 * This function processes incoming UDP data, including injecting saved UDP data to other clients, handling new clients, and sending data to clients when the server is in a 'Ready' state.
 */
void Server::onLineUdp()
{
    sf::IpAddress clientAddress;
    unsigned short clientPort;
    std::size_t received;
    char buffer[3];

    if (this->clients_ready == 0 && this->saveUdp.size() < 2) {
        // do nothing
        clients_ready += 1;
    } else if (this->clients_ready < 2 && this->saveUdp.size() == 2) {
        // std::cout << "je suis pret pour envoyer a tout le monde" << std::endl;
        this->clients_ready += 1;
    } else if (this->clients_ready == 2) {
        // std::cout << "inject" << std::endl;
        this->LogFile << "the 2 clients are loged\n";
        this->LogFile.flush();
        for (size_t i = 0; i < clients.size(); i++) {
            this->injectReady(this->clients.at(i));
        }
        this->clients_ready += 1;
    }
    if (this->udp->receive(buffer, sizeof(buffer), received, clientAddress, clientPort) == sf::Socket::Done) {
        std::string message(buffer, received);
        this->code->getReceivePackage(message);

        if (this->clients_ready > 2) {
            size_t id_client = this->code->getId();
            this->sendToAllUdp(this->code->getSendPackage(), id_client);
        }
        for (size_t i = 0; this->clients_ready < 2 && i < this->clients.size(); i++) {
            if (this->clients.at(i)->addInfo(clientAddress, clientPort, i + 1) == true) {
                this->code->changeId(this->clients.at(i)->getId());
                std::string msg = this->code->getSendPackage();
                this->saveUdp.push_back(msg);
            }
        }
    }
}

/**
 * @brief Start the server and run the main loop.
 *
 * This function starts the server and enters the main event loop. The server goes through different states ('Waiting' and 'Ready') and continuously checks for incoming connections and data. It handles TCP and UDP data processing.
 */
void Server::run()
{
    size_t index_client = 1;
    this->running = true;
    // sf::Time timeout = sf::microseconds(10);

    while (this->running == true) {
        if (this->state == Waiting) {
            if (this->selector.wait()) {
                if (this->selector.isReady(this->listener)) {
                    this->addClient(index_client);
                    index_client += 1;
                } else {
                    this->onLineTcp();
                    this->onLineUdp();
                    if (index_client == 3) {
                        this->state = Ready;
                    }
                }
            }
        } else if (this->state == Ready) {
            // if (this->selector.wait(timeout)) {
                this->onLineUdp();
            // }
        }
    }
}

/**
 * @brief Destructor for the Server class.
 *
 * This function cleans up resources and performs cleanup tasks when the Server instance is destroyed.
 */
Server::~Server()
{
    this->LogFile.close();
    delete (this->udp);
    delete (this->code);
}
