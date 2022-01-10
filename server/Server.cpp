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
                        /// for each genre
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
                            } else continue;
                        }

                        /// if no genre - stupid implementation ik but it works
                        if(filter.getArray("genre").toString() == "[]"){
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

                    } else continue;
                } else continue;
            } else continue;
        } else continue;
    }
    return results.toString();
}

auto Server::readBook(int isbn) noexcept -> String {

    readLibLock.lock();
    auto lib = JSON :: load ( Path().parent() / "server/data/lib.json" );
    readLibLock.unlock();

    std::stringstream result;

    for(auto const & book : lib.getArray("books")){
        if(book.getJSON().getInt("ISBN") == isbn){
            readLibLock.lock();
            std::ifstream in ((Path().parent() / book.getJSON().getString("diskPath")).toString().cStr());
            result << in.rdbuf();
            in.close();
            readLibLock.unlock();
        }
    }

    return result.str();
}

auto Server::downloadBook(int isbn) noexcept -> String {

    downloadLock.lock();
    auto lib = JSON :: load ( Path().parent() / "server/data/lib.json" );
    downloadLock.unlock();

    std::stringstream  result;
    this->downloads.resize(7);
    for(auto & book : lib.getArray("books")) {
        if( book.getJSON().getInt("ISBN") == isbn){
            downloadLock.lock();
            auto genre = book.getJSON().getString("genre");

            if(genre == "Drama")    downloads[DRAMA]++;
            if(genre == "Comedy")   downloads[COMEDY]++;
            if(genre == "Horror")   downloads[HORROR]++;
            if(genre == "Novel")    downloads[NOVEL]++;
            if(genre == "Police")   downloads[POLICE]++;
            if(genre == "Theatre")  downloads[THEATRE]++;

            std::ifstream  in ((Path().parent() / book.getJSON().getString("diskPath")).toString().cStr());
            result << in.rdbuf();
            in.close();
            downloadLock.unlock();
        }
    }

    return result.str();
}

auto Server::recommendBooks() noexcept -> String {

    int max = 0, gen;
    for(int i = 0; i < downloads.size(); i++)
        if (downloads[i] > 3)
            gen = i;

    writeStat(gen);

    auto lib = JSON :: load ( Path().parent() / "server/data/lib.json" );
    auto stats = JSON :: load ( Path().parent() / "server/data/stats.json" );

    JSON::Array results;
    Index nrBooks = 0;
    for (const auto & book : lib.getArray("books")){
        for (const auto & stat : stats.getArray("stats")){
            if ( book.getJSON().getString("genre").contains(stat.getJSON().getString("genre")) &&
                !stat.getJSON().getString("genre").empty()){
                JSON result;
                nrBooks++;

                recommendLock.lock();

                result.put("ISBN", book.getJSON().getInt("ISBN"));
                result.put("title", book.getJSON().getString("title"));
                result.put("author", book.getJSON().getString("author"));
                result.put("genre", book.getJSON().getString("genre"));
                result.put("year", book.getJSON().getInt("year"));
                result.put("rating", book.getJSON().getInt("rating"));
                result.put("diskPath", book.getJSON().getString("diskPath"));
                results.put(nrBooks, result);

                recommendLock.unlock();
            }
        }
    }

    return results.toString();
}

auto Server::writeStat(int gen) noexcept -> void {

    JSON newStat;
    recommendLock.lock();
    auto stats = JSON :: load ( Path().parent() / "server/data/stats.json" );
    recommendLock.unlock();

    std::cout << statExists(gen) << '\n';
    if( statExists(gen) )   return;

    newStat.put("genre", getStatFromInt(gen));

    stats.getArray("stats").put(stats.getArray("stats").size(), newStat);

    recommendLock.lock();

    std::ofstream out ((Path().parent() / "server/data/stats.json").toString().cStr());
    out << stats.dump();
    out.close();

    recommendLock.unlock();
}

auto Server::statExists(int gen) noexcept -> bool {
    recommendLock.lock();
    auto stats = JSON :: load (Path().parent() / "server/data/stats.json");
    recommendLock.unlock();

    auto genre = getStatFromInt(gen);

    for (const auto &item : stats.getArray("stats")){
        if(genre == item.getJSON().getString("genre"))
            return true;
    }
    return false;
}

auto Server::getStatFromInt(int gen) noexcept -> String {
    switch (gen) {
        case DRAMA:
            return "Drama";
            break;
        case COMEDY:
            return "Comedy";
            break;
        case HORROR:
            return "Horror";
            break;
        case NOVEL:
            return "Novel";
            break;
        case POLICE:
            return "Police";
            break;
        case THEATRE:
            return "Theatre";
            break;
        default:
            return "";
    }
}
