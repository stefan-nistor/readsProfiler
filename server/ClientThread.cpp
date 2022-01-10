//
// Created by stefan on 08.01.2022.
//

#include "ClientThread.h"
#include "Server.h"
auto ClientThread::run() noexcept(false) -> void {

    auto requestData = JSON::parse(sock.readString());

    switch ( static_cast<RequestType> (requestData.getInt("reqID"))){
        case CREATE_ACCOUNT:    create(requestData); break;
        case LOGIN:             login(requestData); break;
        case FILTER_BOOKS:      filterBooks(requestData); break;
        case READ:              readBook(requestData); break;
        case DOWNLOAD:          downloadBook(requestData); break;
        case RECOMMEND:         recommendBook(requestData); break;
    }

    this->_callback(this);
}

auto ClientThread::login(JSON const & user) noexcept -> void {

    auto username = user.getString("username");
    auto password = user.getString("password");

    auto retVal = pServer->login(username, password);

    sock.writeInt((int) retVal);

}

auto ClientThread::create(JSON const & user) noexcept -> void {

    auto username = user.getString("username");
    auto password = user.getString("password");

    auto retVal = pServer->create(username, password);

    sock.writeInt((int) retVal);

}

auto ClientThread::filterBooks(JSON const & filterReq ) noexcept -> void {

    auto  filterString = filterReq.getJSON("filter").toString();

    auto retVal = pServer->filterBooks(filterString);

    sock.writeString(retVal);
}

auto ClientThread::readBook(const JSON & reqBook) noexcept -> void {

    auto isbn = reqBook.getInt("ISBN");

    auto retVal = pServer ->readBook(isbn);

    sock.writeString(retVal);
}

auto ClientThread::downloadBook(const JSON & reqBook) noexcept -> void {

    auto isbn = reqBook.getInt("ISBN");

    auto retVal = pServer->downloadBook(isbn);

    sock.writeString(retVal);

}

auto ClientThread::recommendBook(const JSON &) noexcept -> void {

    auto retVal = pServer->recommendBooks();

    sock.writeString(retVal);
}
