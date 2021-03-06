//
// Created by stefan on 05.01.2022.
//

#ifndef READSPROFILER_SERVER_H
#define READSPROFILER_SERVER_H
#include <CDS/Thread>
#include "include.h"
#include "../common/Socket.h"
#include "ClientThread.h"

enum GENRES {
    DRAMA, COMEDY, HORROR, NOVEL, POLICE, THEATRE
};


class Server {
private:
    UniquePointer < Socket > serverSocket = new Socket();
    HashSet < Thread * > threads;
    Array < int > downloads;
    Mutex threadLock;
    Mutex usersFileLock;
    Mutex filterFileLock;
    Mutex readLibLock;
    Mutex downloadLock;
    Mutex recommendLock;
    bool initialized {false};

public:

    auto init(uint16 port) noexcept(false) -> void {
        try {
            serverSocket->open().bind(port).listen(1024);
            initialized = true;
        } catch (Exception const & e ){
            std::cerr << "Server initialized failed. Reason: " << e << '\n';
        }
    }

    __CDS_NoReturn auto run() noexcept (false) -> void {

        auto callback = [&] ( ClientThread * pThread) {
            threadLock.lock();
            threads.removeFirst( pThread );
            threadLock.unlock();

            delete pThread;
        };

        while ( true ){

            try{
                auto newThread = new ClientThread (serverSocket->accept(), this);

                newThread->onClose( callback );

                threadLock.lock();
                threads.add( newThread );
                threadLock.unlock();

                newThread->start();

            } catch ( Exception const & e ){
                std::cerr << " Accept/ClientThread error:  " << e << '\n';
            }
        }
    }

    auto login(String const & , String const &) noexcept -> bool;
    auto create(String const & , String const &) noexcept -> bool;
    auto filterBooks( String const &) noexcept -> String;
    auto readBook ( int ) noexcept -> String;
    auto recommendBooks () noexcept -> String;
    auto downloadBook (int isbn) noexcept -> String;


    auto writeStat(int gen) noexcept -> void;
    auto statExists (int gen) noexcept -> bool;
    static auto getStatFromInt (int gen) noexcept -> String;
};


#endif //READSPROFILER_SERVER_H

