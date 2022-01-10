//
// Created by stefan on 09.01.2022.
//

#ifndef READSPROFILER_REQUESTHANDLER_H
#define READSPROFILER_REQUESTHANDLER_H

#include "../common/Socket.h"

class RequestHandler : public QObject{
    Q_OBJECT

private:
    Socket socket;

public:

    inline auto getSocket() noexcept -> Socket const & {return socket;}

    RequestHandler() noexcept = default;

    explicit RequestHandler (Socket const & sock) noexcept(false){
        if (!sock.isOpen())
            throw Exception("No open socket");
        this->socket = sock;
    }

    RequestHandler ( RequestHandler const & req)  noexcept : socket(req.socket) {}

    static auto login (String const & username, String const & password) noexcept -> bool;
    static auto create (String const & username, String const & password) noexcept -> bool;
    static auto makeFilterBooksRequest  ( String const & filterString ) noexcept -> String;
    static auto makeReadRequest ( int bookID ) noexcept -> String;
    static auto makeDownloadRequest ( int bookID ) noexcept -> String;

};


#endif //READSPROFILER_REQUESTHANDLER_H
