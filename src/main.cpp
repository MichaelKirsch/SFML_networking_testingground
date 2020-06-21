#include <iostream>
#include <SFML/Network.hpp>

const unsigned short PORT = 5000;
const std::string IPADDRESS("127.0.0.1");//change to suit your needs

std::string msgSend;

sf::TcpSocket l_socket;
sf::Mutex globalMutex;
bool quit = false;

void DoStuff(void)
{
    static std::string oldMsg;
    while(!quit)
    {
        std::string msg;
        sf::Packet packetReceive;

        l_socket.receive(packetReceive);
        if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
        {
            std::cout << msg << std::endl;
            oldMsg = msg;
        }
    }
}

void Server(void)
{
    sf::TcpListener listener;
    listener.listen(PORT);
    listener.accept(l_socket);
    std::cout << "New client connected: " << l_socket.getRemoteAddress() << std::endl;
}


void GetInput(void)
{
    std::string s;
    if(s == "exit")
        quit = true;
    globalMutex.lock();
    globalMutex.unlock();
}


int main(int argc, char* argv[])
{
    sf::Thread* thread = 0;

    Server();

    thread = new sf::Thread(&DoStuff);
    thread->launch();

    while(!quit)
    {
        GetInput();
    }

    if(thread)
    {
        thread->wait();
        delete thread;
    }
    return 0;
}