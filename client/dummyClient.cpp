//
// Created by stefan on 08.01.2022.
//

#include "include.h"
#include "../common/Socket.h"

class RequestHandler {

    static auto makeLoginRequest(String const &, String const &) -> bool;
    static auto makeCreateRequest(String const &, String const &) -> bool;
    static auto makeBooksRequest(String const &) -> void;


};

int main(){

    auto makeLoginRequest = [] (
            String const & username,
            String const & password
    ) {

        UniquePointer<Socket> clientSocket = new Socket();
        clientSocket->connect(IP, PORT);

        JSON user;
        user.put("reqID", LOGIN);
        user.put("username", username);
        user.put("password", password);

        clientSocket->writeString(user.toString());

        int response = clientSocket->readInt();
        std::cout << response;

    };

    auto makeCreateRequest = [] (
            String const & username,
            String const & password
            ){
        UniquePointer<Socket> clientSocket = new Socket();
        clientSocket->connect(IP, PORT);

        JSON user;
        user.put("reqID", CREATE_ACCOUNT);
        user.put("username", username);
        user.put("password", password);

        clientSocket->writeString(user.toString());

        int response = clientSocket->readInt();
        std::cout << response;
    };

    auto makeFilterBooksRequest = [] (String const & filterString){

        UniquePointer <Socket> clientSocket = new Socket;
        clientSocket->connect(IP, PORT);

        auto clientFilter = JSON :: parse( filterString );

        JSON filterReq;
        filterReq.put("reqID", FILTER_BOOKS);
        filterReq.put("filter", clientFilter.getJSON("filter") );

        auto filter = filterReq.getJSON("filter");

        clientSocket->writeString(filterReq.toString());

        auto response = clientSocket->readString();

        return response;
    };


    /// filter json data from client
    auto test = JSON :: load ( Path().parent() / "server/test.json" ).toString();

    auto clientFilter = JSON :: parse( test );

    makeFilterBooksRequest(test);


    return 0;
}

