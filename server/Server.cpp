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

auto Server::filterBooks( String const & filterString) noexcept -> String {

    auto lib = JSON :: load ( Path().parent() / "server/data/lib.json" );

    auto filter = JSON :: parse (filterString);

    JSON::Array results;
    Index nrBooks = 0;

    for(auto const & book : lib.getArray("books")) {
        if (book.getJSON().getString("title").contains(filter.getString("title"))) {
            if (book.getJSON().getString("author").contains(filter.getString("author"))) {
                if (book.getJSON().getInt("year") <= filter.getInt("before") &&
                    book.getJSON().getInt("year") >= filter.getInt("after")) {
                    if (book.getJSON().getInt("rating") >= filter.getInt("rating")) {
                        for (auto const &gen: filter.getArray("genre")) {
                            if (book.getJSON().getString("genre").contains(gen.getString())) {

                                JSON result;
                                nrBooks++;

                                filterFileLock.lock();

                                result.put("ISBN", book.getJSON().getInt("ISBN"));
                                result.put("title", book.getJSON().getString("title"));
                                result.put("author", book.getJSON().getString("author"));
                                result.put("genre", book.getJSON().getString("genre"));
                                result.put("year", book.getJSON().getInt("year"));
                                result.put("rating", book.getJSON().getInt("rating"));
                                result.put("diskPath", book.getJSON().getString("diskPath"));
                                results.put(nrBooks, result);

                                filterFileLock.unlock();
                            }
                        }
                    }
                }
            }
        }
    }
    return results.toString();
}
