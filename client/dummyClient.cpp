//
// Created by stefan on 08.01.2022.
//

#include "include.h"
#include "../common/Socket.h"

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

    makeCreateRequest("admin", "admin");
    makeCreateRequest("admin1", "admin");
    makeCreateRequest("admin2", "admin1");
    makeCreateRequest("nistor", "nistor");
    makeCreateRequest("nistor", "admin");
    makeCreateRequest("admin3", "nistor");
}