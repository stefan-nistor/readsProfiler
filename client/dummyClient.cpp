//
// Created by stefan on 08.01.2022.
//

#include "include.h"
#include "../common/Socket.h"


#include <filesystem>

int main(){

    auto makeLoginRequest           = [] ( String const & username, String const & password ) {

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

    auto makeCreateRequest          = [] ( String const & username, String const & password ) {
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

    auto makeFilterBooksRequest     = [] ( String const & filterString ) {

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

    auto makeReadRequest            = [] (int bookID) {

        UniquePointer < Socket > clientSocket = new Socket;
        clientSocket->connect(IP, PORT);

        JSON requestedBook;
        requestedBook.put("reqID", READ);
        requestedBook.put("ISBN", bookID);

        clientSocket->writeString(requestedBook.toString());

        auto response = clientSocket -> readString();

        return response;
    };

    auto makeDownloadRequest        = [] (int bookID) {

        UniquePointer < Socket > clientSocket = new Socket;
        clientSocket -> connect(IP, PORT);

        JSON requestedBook;
        requestedBook.put("reqID", DOWNLOAD);
        requestedBook.put("ISBN", bookID);

        clientSocket->writeString(requestedBook.toString());

        auto response = clientSocket -> readString();

        mkdir("../client/download", 0777);

        String filePath = ".txt";
        filePath.prepend(bookID);
        filePath.prepend("../client/download/");

        std::ofstream out ("../client/download/0.txt");
        out << response;
        out.close();

        return response;

    };

    auto makeRecommendRequest       = [] {

        UniquePointer < Socket > clientSocket = new Socket;
        clientSocket -> connect(IP, PORT);

        JSON requestRecommend;
        requestRecommend.put("reqID", RECOMMEND);


    };

    String filePath = ".txt";
    filePath.prepend(1);
    filePath.prepend("../client/download/");

    std::cout << filePath;


    Array < int > dls;
    dls.resize(6);

    return 0;
}

