#include "MoveNode.h"

MoveNode::MoveNode() : currentBoard(new ChessGame()), next(NULL)
{
    handler.printBoard(*this->currentBoard);
}

MoveNode::MoveNode(ChessGame &cg)
{
    this->currentBoard = new ChessGame(cg);
    this->currentBoard->whiteLegalMoves->clear();
    this->currentBoard->blackLegalMoves->clear();
    handler.calculateLegalMoves(*this->currentBoard);
    handler.printBoard(*this->currentBoard);
    handler.printTurn(this->currentBoard->whiteTurn);
}

MoveNode::~MoveNode()
{
    delete this->currentBoard;
}