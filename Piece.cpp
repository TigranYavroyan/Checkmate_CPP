#include "Piece.hpp"

Piece::Piece() {
    setTurn(-1, -1);
    setTypeColor(PAWN, WHITE);
}
Piece::Piece(int row, int col, Type t, Color c){
    setTurn(row, col);
    setTypeColor(t, c);
}
Piece::~Piece() = default;

void Piece::setTurn(int toRow, int toCol){
    m_col = toCol;
    m_row = toRow;
}
void Piece::setTypeColor(Type type, Color c){
    piece = type;
    color = c;
}
void Piece::setType(Type type){
    piece = type;
}
int Piece::getCol() const {
    return m_col;
}
int Piece::getRow() const {
    return m_row;
}
Type Piece::getType() const {
    return piece;
}
Color Piece::getColor() const {
    return color;
}
Piece::Piece(const Piece& other) {
    setTurn(other.getRow(), other.getCol());
    setTypeColor(other.getType(), other.getColor());
}
Piece Piece::operator= (const Piece& other) {
    setTurn(other.getRow(), other.getCol());
    setTypeColor(other.getType(), other.getColor());
    return other;
}