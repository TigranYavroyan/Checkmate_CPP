#include "InputSystem.hpp"
#include <iostream>
#include <limits> // Add this line to include the <limits> header

InputSystem::InputSystem(): real_from_row{0}, real_to_row{0}, real_from_col{0}, real_to_col{0}, board_size{8}, currentPlayer{WHITE} {}
InputSystem::~InputSystem() = default;

void InputSystem::setCurrentPlayer(Color change) {
    currentPlayer = change;
}

void InputSystem::input_move() {
    int fromRow = 0;
    int toRow = 0;
    char fromCol = ' ';
    char toCol = ' ';
    while (true) {
        std::cout << "Input the move: ";
        if (!(std::cin >> fromCol >> fromRow >> toCol >> toRow) || !_input_checks(fromRow, fromCol, toRow, toCol)) {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please try again." << std::endl;
        } 
        else
            break;
    }
    _change(fromRow, toRow, fromCol, toCol);
}
int InputSystem::get_from_row() const {
    return real_from_row;
}
int InputSystem::get_to_row() const {
    return real_to_row;
}
int InputSystem::get_from_col() const {
    return real_from_col;
}
int InputSystem::get_to_col() const {
    return real_to_col;
}
void InputSystem::print() const {
    std::cout << real_from_col << real_from_row << ' ' << real_to_col << real_to_row;
}
Color InputSystem::get_currentPlayer () const {
    return currentPlayer;
}

void InputSystem::_change(int fromRow, int toRow, char fromCol, char toCol){
    real_from_col = static_cast<int>(fromCol - 'a');
    real_to_col = static_cast<int>(toCol - 'a');
    real_from_row = board_size - fromRow;
    real_to_row = board_size - toRow;
}

void InputSystem::set_from_move(int fromCol, int fromRow) {
    real_from_col = fromCol;
    real_from_row = fromRow;
}

void InputSystem::set_to_move(int toCol, int toRow) {
    real_to_col = toCol;
    real_to_row = toRow;
}

bool InputSystem::_input_checks(int fromRow, int fromCol, int toRow, int toCol) const {
    return ((fromCol >= 'a' && fromCol <= 'h') && (toCol >= 'a' && toCol <= 'h') && (fromRow >= 1 && fromRow <= 8) && (toRow >= 1 && toRow <= 8));
}