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
