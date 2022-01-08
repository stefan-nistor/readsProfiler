//
// Created by stefan on 05.01.2022.
//

#include "Server.h"
#include "include.h"

int main (){

    Server server;
    server.init(PORT);
    server.run();

    return 0;
}

auto Server::login(String const & username, String const & password) noexcept -> bool {

    usersFileLock.lock();
    auto users = JSON :: load ( Path().parent() / "server/data/accounts.json" );
    usersFileLock.unlock();

    for(auto const & user : users.getArray("users")){
        if(
                username == user.getJSON().getString("username") &&
                password == user.getJSON().getString("password")
        )
            return true;
    }

    return false;
}

auto Server::create(String const & username, String const & password) noexcept -> bool {

    usersFileLock.lock();
    auto users = JSON :: load ( Path().parent() / "server/data/accounts.json");
    usersFileLock.unlock();

    for(auto const & user : users.getArray("users")){
        if(username == user.getJSON().getString("username"))
            return false;
    }

    JSON newUser;
    newUser.put("username", username);
    newUser.put("password", password);

    users.getArray("users").put(users.getArray("users").size(), newUser);

    usersFileLock.lock();

    std::ofstream out ((Path().parent() / "server/data/accounts.json").toString().cStr());
    out << users.dump();
    out.close();

    usersFileLock.unlock();

    return true;
}
