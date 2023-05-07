#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

int main() {
  try {
    io_service io_service;

    // Create a socket to connect to the server
    tcp::socket socket(io_service);

    // Connect to the server
    socket.connect(tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));

    // Send the message to the server

    while (true) {
        std::string message = "8=FIX.4.4|9=110|35=D|34=1|49=CLIENT1|52=20130204-22:44:16.468|56=CME|11=ORDER0001|21=1|55=AAPL|54=1|38=100|40=2|44=123.45|59=0|10=1360028651|\n";
        boost::asio::write(socket, boost::asio::buffer(message));

        // Wait for a response from the server
        char response[1024];
        size_t length = socket.read_some(boost::asio::buffer(response));

        // Print the response from the server
        std::cout << "Response: " << std::string(response, response + length) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(10));
        

    }
    


  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
