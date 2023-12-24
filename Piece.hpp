#pragma once

enum Type {PAWN, ROCK, KNIGHT, BISHOP, QUEEN, KING};
enum Color {WHITE, BLACK};

class Piece{
public:
    Piece();
    Piece(const Piece& other);
    Piece(int row, int col, Type t, Color c);
    ~Piece();
public:
    void setTurn(int toRow, int toCol);
    void setTypeColor(Type type, Color c);
    void setType(Type type);
    int getCol() const;
    int getRow() const;
    Type getType() const;
    Color getColor() const;
    Piece operator= (const Piece& other) ;
private:
    int m_col;
    int m_row;
    Type piece;
    Color color;
};