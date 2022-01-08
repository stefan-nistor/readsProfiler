//
// Created by stefan on 08.01.2022.
//

#ifndef READSPROFILER_CLIENTTHREAD_H
#define READSPROFILER_CLIENTTHREAD_H
#include "include.h"
#include "../common/Socket.h"

class Server;

class ClientThread : public Thread{
private:

    Socket sock;
    Function < void (ClientThread *) > _callback;

    Server * pServer { nullptr };

public:

    explicit ClientThread ( Socket && s, Server * server ) :
            sock( s ),
            pServer ( server ) {

    }

    auto run () noexcept(false) -> void override;

    template<typename Callback >
    auto onClose ( Callback const & callback ) noexcept -> void {
        this->_callback = callback;
    }

    auto login (JSON const &) noexcept -> void;

    auto create (JSON const &) noexcept -> void;

};


#endif //READSPROFILER_CLIENTTHREAD_H
