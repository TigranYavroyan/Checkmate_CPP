#include "Checkboard.hpp"
#include <iostream>

// CFEKP -> checking for each king position
bool Checkboard::_castling_CFEKP (int kings_index, int toRow, int toCol, int tmp_row, int tmp_col) {
    pieces[kings_index]->setTurn(toRow, toCol); // when do castling and the king is going under check, it is not return invalid move , finish it
    _setPiece(kings_index);
    if (_check_checking(input_system.get_currentPlayer())) {
        pieces[kings_index]->setTurn(tmp_row, tmp_col);
        _setPiece(kings_index);
        board[toRow][toCol] = '.';
        return false;
    }

    return true;
}

void Checkboard::_castling_done() {
    if (white_castling && input_system.get_currentPlayer() == WHITE)
        white_castling = false;
    else if (black_castling && input_system.get_currentPlayer() == BLACK)
        black_castling = false;
}

bool Checkboard::_castling(int index) { // index -> kings index
    if (!cant_castle) {
        if (!white_castling && input_system.get_currentPlayer() == WHITE || !black_castling && input_system.get_currentPlayer() == BLACK) 
            return false;
        int fromCol = input_system.get_from_col();
        int toCol = input_system.get_to_col();
        int fromRow = input_system.get_from_row();
        int toRow = input_system.get_to_row();
        if (fromRow == toRow && toCol - fromCol == 2 && fromCol == 4 && board[toRow][fromCol + 1] == '.' && board[toRow][fromCol + 2] == '.') {
            for (int i = 0; i < pieces_amount; ++i) {
                if (pieces[i] != nullptr && pieces[i]->getRow() == fromRow && pieces[i]->getCol() == toCol + 1 && pieces[i]->getType() == ROCK) {
                    int tmp_col = pieces[index]->getCol();
                    int tmp_row = pieces[index]->getRow();
                    if (!_castling_CFEKP(index, toRow, toCol - 1, tmp_row, tmp_col))
                        return false;
                    board[toRow][toCol - 1] = '.';
                    if (!_castling_CFEKP(index, toRow, toCol, tmp_row, tmp_col))
                        return false;
                    board[fromRow][fromCol] = '.';
                    pieces[i]->setTurn(toRow, fromCol + 1);
                    board[fromRow][toCol + 1] = '.';
                    _setPiece(i);
                    castling_done = true;
                    _castling_done();
                    input_system.setCurrentPlayer(((input_system.get_currentPlayer() == WHITE) ? BLACK : WHITE));
                    return true;
                }
            }
        }
        else if (fromRow == toRow && fromCol - toCol == 2 && fromCol == 4 && board[toRow][fromCol - 1] == '.' && board[toRow][fromCol - 2] == '.' && board[toRow][fromCol - 3] == '.') {
            for (int i = 0; i < pieces_amount; ++i) {
                if (pieces[i] != nullptr && pieces[i]->getRow() == fromRow && pieces[i]->getCol() == toCol - 2 && pieces[i]->getType() == ROCK) {
                    int tmp_col = pieces[index]->getCol();
                    int tmp_row = pieces[index]->getRow();
                    if (!_castling_CFEKP(index, toRow, toCol + 1, tmp_row, tmp_col))
                        return false;
                    board[toRow][toCol + 1] = '.';
                    if (!_castling_CFEKP(index, toRow, toCol, tmp_row, tmp_col))
                        return false;
                    board[fromRow][fromCol] = '.';
                    pieces[index]->setTurn(toRow, toCol);
                    _setPiece(index);
                    pieces[i]->setTurn(toRow, fromCol - 1);
                    board[fromRow][toCol - 2] = '.';
                    _setPiece(i);
                    castling_done = true;
                    _castling_done();
                    input_system.setCurrentPlayer(((input_system.get_currentPlayer() == WHITE) ? BLACK : WHITE));
                    return true;
                }
            }
        }
    }
    return false;
}

Checkboard::Checkboard():len{8}, white_castling{true}, black_castling{true}, castling_done{false}, under_check{false}, cant_castle{false}, checkmate{false}, stalemate{false}, pieces_amount{0}, pawn_to_queen{false} { // creating default position of checkboard
    for(int i = 0; i < 8; ++i)
    {
        pieces.push_back(new Piece(6, i, PAWN, WHITE));
    }
    pieces.push_back(new Piece(7, 0, ROCK, WHITE));
    pieces.push_back(new Piece(7, 7, ROCK, WHITE));
    pieces.push_back(new Piece(7, 1, KNIGHT, WHITE));
    pieces.push_back(new Piece(7, 6, KNIGHT, WHITE));
    pieces.push_back(new Piece(7, 2, BISHOP, WHITE));
    pieces.push_back(new Piece(7, 5, BISHOP, WHITE));
    pieces.push_back(new Piece(7, 3, QUEEN, WHITE));
    pieces.push_back(new Piece(7, 4, KING, WHITE));
    
    for(int i = 0; i < 8; ++i)
    {
        pieces.push_back(new Piece(1, i, PAWN, BLACK));
    }
    pieces.push_back(new Piece(0, 0, ROCK, BLACK));
    pieces.push_back(new Piece(0, 7, ROCK, BLACK));
    pieces.push_back(new Piece(0, 1, KNIGHT, BLACK));
    pieces.push_back(new Piece(0, 6, KNIGHT, BLACK));
    pieces.push_back(new Piece(0, 2, BISHOP, BLACK));
    pieces.push_back(new Piece(0, 5, BISHOP, BLACK));
    pieces.push_back(new Piece(0, 3, QUEEN, BLACK));
    pieces.push_back(new Piece(0, 4, KING, BLACK));

    // pieces.push_back(new Piece(1, 0, KING, WHITE));
    // pieces.push_back(new Piece(1, 7, PAWN, WHITE));
    // pieces.push_back(new Piece(0, 2, KING, BLACK));
    // pieces.push_back(new Piece(4, 1, QUEEN, BLACK));

    pieces_amount = pieces.size();

    _setPieces();
    _setEmpties();
}

Checkboard::~Checkboard() { // dtoring not dtored pieces at the end of the game
    for(int i = 0; i < pieces_amount; ++i){
        if(pieces[i] != nullptr)
            delete pieces[i];
    }
}

bool Checkboard::_checking_right_eaten_piece(int toCol, int toRow) const {
    for (int i = 0; i < pieces_amount; ++i) {
        if (pieces[i] != nullptr && (pieces[i]->getCol() == toCol) && (pieces[i]->getRow() == toRow)) {
            if (input_system.get_currentPlayer() == pieces[i]->getColor())
                return false;
        }
    }
    return true;
}

bool Checkboard::_moving_horizontally_vertically(int fromRow, int toRow, int fromCol, int toCol) const {
    // move vertically or horizontally without jumping over other pieces
    if (toRow != fromRow && fromCol == toCol) {
        int step = (toRow > fromRow) ? +1 : -1;  
        for (int row = fromRow + step;(step < 0) ? row > toRow : row < toRow; row += step) {
            if (board[row][toCol] != '.') 
                return false;  // there's a piece blocking the path
        }   
        return true;
    }
    else if (toRow == fromRow && toCol != fromCol) {
        int step = (toCol > fromCol) ? 1 : -1;
        for (int col = fromCol + step;(step < 0) ? col > toCol : col < toCol; col += step) {
            if (board[toRow][col] != '.') {
                return false;  // there's a piece blocking the path
            }
        }   
        return true;
    }
    return false;
}

bool Checkboard::_moving_diagonally(int fromRow, int toRow, int fromCol, int toCol) const {
    if (abs(fromCol - toCol) == abs(fromRow - toRow)) { // move diagonally
        int stepCol = (fromCol > toCol) ? -1 : 1;
        int stepRow = (fromRow > toRow) ? -1 : 1;
        int col = fromCol + stepCol;
        int row  = fromRow + stepRow;
        while(row != toRow) {
            if(board[row][col] != '.')
                return false; // there's a piece blocking the path
            col += stepCol;
            row += stepRow;
        }
        return true;
    }
    return false;
}

bool Checkboard::_moveCheck(int index, int fromCol = -1, int fromRow = -1, int toCol = -1, int toRow = -1, bool checker_mode = false) {
    if (!checker_mode && input_system.get_currentPlayer() != pieces[index] -> getColor()) // if the current player is not the same color as piece color 
        return false;
    if (fromCol == -1 && fromRow == -1 && toCol == -1 && toRow == -1) { // if there is no input for movement by default it is from input system
        fromCol = input_system.get_from_col();
        toCol = input_system.get_to_col();
        fromRow = input_system.get_from_row();
        toRow = input_system.get_to_row();
    }
    for (int i = 0; i < pieces_amount; ++i) { // find the to-piece and checking not beeing the same color 
        if (pieces[i] != nullptr && (pieces[i]->getCol() == toCol && pieces[i]->getRow() == toRow) && pieces[index]->getColor() == pieces[i]->getColor())
            return false;
    }
    switch (pieces[index] -> getType())
    {
        case KING:
            if (_castling(index))
                return true;
            else if(abs(toCol - pieces[index] -> getCol()) == 1 && abs(toRow - pieces[index] -> getRow()) == 1) {
                _castling_done();
                return true;
            }
            else if(toCol == pieces[index] -> getCol() && abs(toRow - pieces[index] -> getRow()) == 1) {
                _castling_done();
                return true;
            }
            else if(toRow == pieces[index] -> getRow() && abs(toCol - pieces[index] -> getCol()) == 1) {
                _castling_done();
                return true;
            }
            else
                return false;
            break;
        case KNIGHT:
            if(abs(toRow - pieces[index] -> getRow()) == 2 && abs(toCol - pieces[index] -> getCol()) == 1)
                return true;
            else if (abs(toRow - pieces[index] -> getRow()) == 1 && abs(toCol - pieces[index] -> getCol()) == 2)
                return true;
            else
                return false;
            break;  
        case PAWN: // flag avelacnel zinvori koxancik utelu hamar, stugumy koxancik utelu kazmakerpel _doMove() member functioni mej // pawn sideway move
            if (pieces[index]->getColor() == WHITE) {
                if(len - fromRow == 2 && fromRow - toRow == 2 && fromCol == toCol && board[fromRow - 1][toCol] == '.' && board[toRow][toCol] == '.') {
                    return true;
                }
                else if(fromRow - toRow == 1 && abs(toCol - fromCol) == 1 && board[toRow][toCol] != '.')
                    return true;
                else if(fromRow - toRow == 1 && fromCol == toCol) {
                    if (board[toRow][toCol] == '.') {
                        if (toRow == 0)
                            _pawn_to_queen(index);
                        return true;
                    }
                    return false;
                }
            }
            else if (pieces[index]->getColor() == BLACK) {
                if(len - fromRow == 7 && toRow - fromRow == 2 && fromCol == toCol && board[toRow - 1][toCol] == '.' && board[toRow][toCol] == '.')
                    return true;
                else if(toRow - fromRow == 1 && abs(toCol - fromCol) == 1 && board[toRow][toCol] != '.')
                    return true;
                else if(toRow - fromRow == 1 && fromCol == toCol) {
                    if (board[toRow][toCol] == '.') {
                        if (toRow == 7)
                            _pawn_to_queen(index);
                        return true;
                    }
                    return false;
                }
            }
            break;
        case ROCK:
            return _moving_horizontally_vertically(fromRow, toRow, fromCol, toCol);
        case BISHOP:
            return _moving_diagonally(fromRow, toRow, fromCol, toCol);
        case QUEEN:
            return (_moving_horizontally_vertically(fromRow, toRow, fromCol, toCol) || _moving_diagonally(fromRow, toRow, fromCol, toCol));
    }
    return false;
}

void Checkboard::_setPiece(int index){ // creating board with the positions of pieces 
    if(pieces[index] != nullptr) {
        if(pieces[index]->getType() == PAWN && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'P';
        else if(pieces[index]->getType() == PAWN && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'p';
        else if(pieces[index]->getType() == ROCK && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'R';
        else if(pieces[index]->getType() == ROCK && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'r';
        else if(pieces[index]->getType() == KNIGHT && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'N';
        else if(pieces[index]->getType() == KNIGHT && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'n';
        else if(pieces[index]->getType() == BISHOP && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'B';
        else if(pieces[index]->getType() == BISHOP && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'b';
        else if(pieces[index]->getType() == KING && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'K';
        else if(pieces[index]->getType() == KING && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'k';
        else if(pieces[index]->getType() == QUEEN && pieces[index]->getColor() == WHITE)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'Q';
        else if(pieces[index]->getType() == QUEEN && pieces[index]->getColor() == BLACK)
            board[pieces[index]->getRow()][pieces[index]->getCol()] = 'q';
    }
}

void Checkboard::_setEmpty(int row, int col){ // adding empty bars
    if(_checkEmpty(row, col))
        board[row][col] = '.';
}

bool Checkboard::_checkEmpty(int row, int col) const { // cheking is the bar empty
    switch (board[row][col])
    {
        case 'P':
            return false;
        case 'R':
            return false;
        case 'N':
            return false;
        case 'B':
            return false;
        case 'Q':
            return false;
        case 'K':
            return false;
        case 'p':
            return false;
        case 'r':
            return false;
        case 'n':
            return false;
        case 'b':
            return false;
        case 'q':
            return false;
        case 'k':
            return false;
    }
    return true;
}

void Checkboard::_setPieces() { // adding all pieces in board[][]
    for(int i = 0; i < pieces_amount; ++i){
        _setPiece(i);
    }
}

void Checkboard::_setEmpties() { // adding '.' in board[][]
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            _setEmpty(i, j);
        }
    }
}

int Checkboard::_find_piece(int row, int col) const { // dtoring the eaten piece
    if (!_checkEmpty(row, col)) {
        for (int i = 0; i < pieces_amount; ++i) {
            if ((pieces[i] != nullptr) && (pieces[i]->getRow() == row) && (pieces[i]->getCol() == col))
                return i;
        }
    }
    return -1;
}

void Checkboard::play() {
    _getMove();
}

void Checkboard::_getMove() {
    input_system.input_move();
    int fromCol = input_system.get_from_col();
    int fromRow = input_system.get_from_row();
    if (!_checkEmpty(fromRow, fromCol)) {
        int toCol = input_system.get_to_col();
        int toRow = input_system.get_to_row();
        for (int i = 0; i < pieces_amount; ++i) {
            if ((pieces[i] != nullptr) && (pieces[i]->getCol() == fromCol) && (pieces[i]->getRow() == fromRow)) { // trying find the right piece
                if (_moveCheck(i) && _checking_right_eaten_piece(toCol, toRow)) { // checking the right move 
                    if (!castling_done)
                        _doMove(i, fromCol, fromRow, toCol, toRow);
                    else
                        castling_done = false;
                }
            }
        }
    }
}

void Checkboard::printBoard() const { // printing the board
    std::cout << "---------------------------------------------------" << std::endl;
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < len; ++j){
            std::cout << ' ' << board[i][j] << ' ';
        }
        std::cout.put('\n');
    }
    std::cout << "---------------------------------------------------" << std::endl;
    if (input_system.get_currentPlayer() == WHITE)
        std::cout << "White's turn" << std::endl;
    else
        std::cout << "Black's turn" << std::endl;
    if(under_check)
        std::cout << "The king is under check" << std::endl;
}

bool Checkboard::_check_checking(Color color) { // for finding check is pretty good
    int kings_index = 0;
    kings_index = _finding_king(color); // finding the color king
    for (int index = 0; index < pieces_amount; ++index) {
        if (pieces[index] == nullptr)
            continue; //                                                                                                             true for checker_mode
        if (_moveCheck(index, pieces[index]->getCol(), pieces[index]->getRow(), pieces[kings_index]->getCol(), pieces[kings_index]->getRow(), true)) {
            cant_castle = true;
            under_check = true;
            return true;
        }
    }
    cant_castle = false;
    under_check = false;
    return false;
}

bool Checkboard::_checkmate(Color color) { // it is not generic for searching the needed color of pieces , but it works
    if (color == WHITE) {
        for (int i = 0; i < pieces_amount / 2; ++i) {
            for (int row = 0; row < len; ++row) {
                for (int col = 0; col < len; ++col) {
                    if (pieces[i] != nullptr && _for_checkmate_checking_beeing_under_check(i, pieces[i]->getCol(), pieces[i]->getRow(), col, row))
                        return false;
                }
            }
        }
    }
    else {
        for (int i = pieces_amount / 2; i < pieces_amount; ++i) {
            for (int row = 0; row < len; ++row) {
                for (int col = 0; col < len; ++col) {
                    if (pieces[i] != nullptr && _for_checkmate_checking_beeing_under_check(i, pieces[i]->getCol(), pieces[i]->getRow(), col, row))
                        return false;
                }
            }
        }
    }
    if (under_check)
        checkmate = true;
    else
        stalemate = true;
    return true;
}

bool Checkboard::_for_checkmate_checking_beeing_under_check(int i, int fromCol, int fromRow, int toCol, int toRow) {
    if (!_moveCheck(i, fromCol, fromRow, toCol, toRow, true))
        return false;
    Piece tmp_piece; // creating the tmp object for eated pieces under check
    bool to_move_empty = false;
    int index_to_eaten_piece = -1;
    if (_checkEmpty(toRow, toCol))
        to_move_empty = true;
    else {  
        index_to_eaten_piece = _find_piece(toRow, toCol);
        tmp_piece = *(pieces[index_to_eaten_piece]); 
        delete pieces[index_to_eaten_piece]; // eating the piece
        pieces[index_to_eaten_piece] = nullptr;
    }
    int tmp_col = pieces[i]->getCol();
    int tmp_row = pieces[i]->getRow();
    pieces[i]->setTurn(toRow, toCol);
    board[fromRow][fromCol] = '.';
    _setPiece(i);
    if (!_check_checking_for_checkmate(input_system.get_currentPlayer())) {
        pieces[i]->setTurn(tmp_row, tmp_col);
        _setPiece(i);
        if (to_move_empty) 
            board[toRow][toCol] = '.';
        else {
            pieces[index_to_eaten_piece] = new Piece(tmp_piece);
            _setPiece(index_to_eaten_piece);
        }
        return true;
    }
    pieces[i]->setTurn(tmp_row, tmp_col);
    _setPiece(i);
    if (to_move_empty) 
        board[toRow][toCol] = '.';
    else {
        pieces[index_to_eaten_piece] = new Piece(tmp_piece);
        _setPiece(index_to_eaten_piece);
    }
    return false;
}

bool Checkboard::get_checkmate() const {
    return checkmate;
}

bool Checkboard::_check_checking_for_checkmate(Color color) { // for finding check is pretty good
    int kings_index = 0;
    kings_index = _finding_king(color); // finding the color king
    for (int index = 0; index < pieces_amount; ++index) {
        if (pieces[index] == nullptr)
            continue; //                                                                                                             true for checker_mode
        if (_moveCheck(index, pieces[index]->getCol(), pieces[index]->getRow(), pieces[kings_index]->getCol(), pieces[kings_index]->getRow(), true))
            return true;
    }
    return false;
}

int Checkboard::_finding_king(Color color) const {
    for (int i = 0; i < pieces_amount; ++i) {
        if (pieces[i] != nullptr && color == pieces[i]->getColor() && pieces[i]->getType() == KING)
            return i;
    }
    return -1; // It would be the end of the game, bcz there is no king to find
}

void Checkboard::print_rest() const {
    int count = 0;
    int i = 0;
    while (i < pieces_amount) {
        if (pieces[i] != nullptr)
            ++count;
        ++i;
    }
    std::cout << "\n\n count -> " << count << "\n" << std::endl; 
}

void Checkboard::_doMove(int i, int fromCol, int fromRow, int toCol, int toRow) {
    Piece tmp_piece; // creating the tmp object for eated pieces under check
    bool to_move_empty = false;
    int index_to_eaten_piece = -1;
    if (_checkEmpty(toRow, toCol))
        to_move_empty = true;
    else {  
        index_to_eaten_piece = _find_piece(toRow, toCol);
        tmp_piece = *(pieces[index_to_eaten_piece]); 
        delete pieces[index_to_eaten_piece]; // eating the piece
        pieces[index_to_eaten_piece] = nullptr;
    }
    int tmp_col = pieces[i]->getCol();
    int tmp_row = pieces[i]->getRow();
    pieces[i]->setTurn(toRow, toCol);
    board[fromRow][fromCol] = '.';
    _setPiece(i);
    if (!_check_checking(input_system.get_currentPlayer())) {
        input_system.setCurrentPlayer(((input_system.get_currentPlayer() == WHITE) ? BLACK : WHITE));
        _check_checking(input_system.get_currentPlayer());
        _checkmate(input_system.get_currentPlayer());
    }
    else {
        pieces[i]->setTurn(tmp_row, tmp_col);
        _setPiece(i);
        if (to_move_empty) {
            board[toRow][toCol] = '.';
            if (pawn_to_queen){
                pieces[i]->setType(PAWN);
                _setPiece(i);
            }
        }
        else {
            pieces[index_to_eaten_piece] = new Piece(tmp_piece);
            _setPiece(index_to_eaten_piece);
        }
    }
    pawn_to_queen = false;
}

bool Checkboard::get_stalemate() const {
    return stalemate;
}

void upper_to_lower (char* ch) {
    if (*ch >= 'A' && *ch <= 'Z')
        *ch += 32;
}

Type Checkboard::_pick_for_pawn(char pick) const {
    upper_to_lower(&pick);
    switch (pick)
    {
        case 'r':
            return ROCK;
        case 'n':
            return KNIGHT;
        case 'b':
            return BISHOP;
        case 'q':
            return QUEEN;
    }
    return PAWN;
}

void Checkboard::_pawn_to_queen (int index) { // if the king is under check, it is not working well
    char pick;
    Type being;
    do {
        std::cout << "Pick the figure (R, N, B, Q): ";
        std::cin >> pick;
        std::cout << std::endl;
        being = _pick_for_pawn(pick);
    }
    while (being == PAWN);
    pawn_to_queen = true;
    pieces[index]->setType(being);
}
