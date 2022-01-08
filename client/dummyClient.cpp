//
// Created by stefan on 08.01.2022.
//

#include "include.h"
#include "../common/Socket.h"

class RequestHandler {

    static auto makeLoginRequest(String const &, String const &) -> bool;
    static auto makeCreateRequest(String const &, String const &) -> bool;
    static auto makeBooksRequest(String const &) -> bool;


};

static auto filter(String const & filterString ) noexcept -> String;

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

    auto makeBooksRequest = [] (String const & filters){

        UniquePointer <Socket> clientSocket = new Socket;
        clientSocket->connect(IP, PORT);


    };

    auto test = JSON :: load ( Path().parent() / "server/test.json" );
//
//    std::cout << test.toString().cStr() << '\n';
    auto j = JSON::parse( test.getArray("filter").toString() );

//    std :: cout << j.toString() << '\n';
//
//    std::cout << j.getString("title");


    std::cout << filter(j.toString()) <<'\n';


//
//    for(auto const & filter : test.getArray("filter")){
//        std::cout << filter.getJSON().getString("title") << '\n';
//        std::cout << filter.getJSON().getString("author") << '\n';
//        std::cout << filter.getJSON().getInt("after") << '\n';
//        std::cout << filter.getJSON().getInt("before") << '\n';
//        std::cout << filter.getJSON().getInt("rating") << '\n';
//        std::cout << filter.getJSON().getArray("genre") << '\n';
//        for(auto const & gen : filter.getJSON().getArray("genre"))
//            std::cout << gen.toString() << '\n';
//    }

}


static auto filter(String const & filterString ) noexcept -> String{

    auto lib = JSON :: load ( Path().parent() / "server/data/lib.json" );


    auto filter = JSON :: parse (filterString);

    JSON::Array results;
    Index nrBooks = 0;

    for(auto const & book : lib.getArray("books")){
        std::cout << book.getJSON().getInt("ISBN") << '\n';
    }

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
                                result.put("ISBN", book.getJSON().getInt("ISBN"));
                                result.put("title", book.getJSON().getString("title"));
                                result.put("author", book.getJSON().getString("author"));
                                result.put("genre", book.getJSON().getString("genre"));
                                result.put("year", book.getJSON().getInt("year"));
                                result.put("rating", book.getJSON().getInt("rating"));
                                result.put("diskPath", book.getJSON().getString("diskPath"));
                                results.put(nrBooks, result);
                            }
                        }
                    }
                }
            }
        }

    }

    return results.toString();

}