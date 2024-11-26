#pragma once
#include "Piece.hpp"
#include "InputSystem.hpp"
#include <vector>
#include <string>
using std::vector;

class Checkboard {
public:
    Checkboard();
    ~Checkboard();
public:
    void printBoard() const;
    void play();
    void print_rest() const;
    bool get_checkmate() const;
    bool get_stalemate() const;
    std::string get_board_data() const;
private:
    InputSystem input_system;
    vector <Piece*> pieces;
    int pieces_amount;
    const int len;
    char board[8][8];
    bool white_castling; // for whites castling done
    bool black_castling; // for blacks castling done
    bool castling_done; // for doing alternative movement like castling 
    bool under_check; // checking beeing under check
    bool cant_castle; // if the king is under check, he can't canstle
    bool checkmate;
    bool stalemate;
    bool pawn_to_queen; // for becoming the pawn the better piece

    Type _pick_for_pawn (char pick) const;
    int _finding_king (Color color) const ;
    int _find_piece(int row, int col) const ;
    void _pawn_to_queen (int index);
    void _doMove(int i, int fromCol, int fromRow, int toCol, int toRow);
    void _getMove();
    void _setPiece(int index);
    void _setEmpty(int row, int col);
    void _setPieces();
    void _setEmpties();
    void _castling_done();
    bool _castling_CFEKP(int kings_index, int toRow, int toCol, int tmp_row, int tmp_col);
    bool _castling(int index);
    bool _check_checking (Color color);
    bool _moveCheck(int index, int fromCol, int fromRow, int toCol, int toRow, bool checker_mode);
    bool _checkEmpty(int row, int col) const ;
    bool _moving_horizontally_vertically(int fromRow, int toRow, int fromCol, int toCol) const ;
    bool _moving_diagonally(int fromRow, int toRow, int fromCol, int toCol) const ;
    bool _checking_right_eaten_piece(int toCol, int toRow) const ;
    bool _checkmate(Color color);
    bool _for_checkmate_checking_beeing_under_check(int i, int fromCol, int fromRow, int toCol, int toRow);
    bool _check_checking_for_checkmate(Color color);
};