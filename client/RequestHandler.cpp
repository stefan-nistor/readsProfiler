//
// Created by stefan on 09.01.2022.
//

#include "RequestHandler.h"

auto RequestHandler::login(String const & username, String const & password ) noexcept -> bool {

    UniquePointer<Socket> clientSocket = new Socket();
    clientSocket->connect(IP, PORT);

    JSON user;
    user.put("reqID", LOGIN);
    user.put("username", username);
    user.put("password", password);

    clientSocket->writeString(user.toString());

    return clientSocket->readInt();

}

auto RequestHandler::create(const String &username, const String &password) noexcept -> bool {

    UniquePointer<Socket> clientSocket = new Socket();
    clientSocket->connect(IP, PORT);

    JSON user;
    user.put("reqID", CREATE_ACCOUNT);
    user.put("username", username);
    user.put("password", password);

    clientSocket->writeString(user.toString());

    return clientSocket->readInt();

}

auto RequestHandler::makeFilterBooksRequest(const String &filterString) noexcept -> String {
    UniquePointer <Socket> clientSocket = new Socket;
    clientSocket->connect(IP, PORT);

    auto clientFilter = JSON :: parse( filterString );

    JSON filterReq;
    filterReq.put("reqID", FILTER_BOOKS);
    filterReq.put("filter", clientFilter.getJSON("filter") );

    auto filter = filterReq.getJSON("filter");

    clientSocket->writeString(filterReq.toString());

    return clientSocket->readString();
}

auto RequestHandler::makeReadRequest(int bookID) noexcept -> String {

    UniquePointer < Socket > clientSocket = new Socket;
    clientSocket->connect(IP, PORT);

    JSON requestedBook;
    requestedBook.put("reqID", READ);
    requestedBook.put("ISBN", bookID);

    clientSocket->writeString(requestedBook.toString());

   return clientSocket -> readString();

}

auto RequestHandler::makeDownloadRequest(int bookID) noexcept -> String {
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

    std::ofstream out (filePath.toStdString());
    out << response;
    out.close();

    return response;
}

auto RequestHandler::makeRecommendRequest() noexcept -> String {
    UniquePointer < Socket > clientSocket = new Socket;
    clientSocket -> connect(IP, PORT);

    JSON recommendReq;
    recommendReq.put("reqID", RECOMMEND);

    clientSocket->writeString(recommendReq.toString());

    return clientSocket->readString();
}
