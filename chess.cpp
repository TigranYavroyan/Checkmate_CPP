#include "Checkboard.hpp"
#include <cstdlib> // for system function
#include <iostream>

int main() {
    Checkboard check_board;
    while(1){
        system("clear");
        check_board.printBoard();
        check_board.play();
        if (check_board.get_stalemate()) {
            system("clear");
            check_board.printBoard();
            std::cout << "It is the stalemate" << std::endl;
            break;
        }
        else if (check_board.get_checkmate()) {
            system("clear");
            check_board.printBoard();
            std::cout << "It is the checkmate" << std::endl;
            break;
        }
    }
    std::cout << "The end of the game" << std::endl;
    return 0;
}