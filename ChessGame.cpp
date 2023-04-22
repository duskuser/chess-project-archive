#include "ChessGame.h"

ChessGame::ChessGame() : board(new std::array<std::array<int_fast8_t, ROWS>, COLUMNS>), 
whiteLegalMoves(new std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>),
blackLegalMoves(new std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>),
lastMoves(new std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>>),
whiteCanCastle(true), blackCanCastle(true), whiteLeftRookMoved(false), whiteRightRookMoved(false),
gameWon(false), gameState(PlayingGame), whiteTurn(true), currentMove(0)
{
    std::copy(std::begin(defaultBoard), std::end(defaultBoard), std::begin(*this->board));
    *this->whiteLegalMoves = defaultWhiteLegalMoves;
    *this->blackLegalMoves = defaultBlackLegalMoves;
}

ChessGame::ChessGame(const ChessGame &source)
 : board(new std::array<std::array<int_fast8_t, ROWS>, COLUMNS>),
whiteLegalMoves(new std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>),
blackLegalMoves(new std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>),
whiteCanCastle(source.whiteCanCastle), blackCanCastle(source.blackCanCastle), whiteLeftRookMoved(), 
whiteRightRookMoved(source.whiteRightRookMoved),
gameWon(source.gameWon), whiteTurn(!source.whiteTurn), currentMove(source.currentMove + 1), 
lastMoves(source.lastMoves)
{
    // Removes old moves when size gets to correct variable, checks for repitions
    if (this->lastMoves->size() >= REPEATABLE_MOVES)
    {
        this->lastMoves->erase(this->lastMoves->begin());
    }
    // Copies board
    this->board = source.board;
    // Keeps track of castling ability on board construction
    if (this->whiteTurn)
    {
        if (this->whiteCanCastle)
        {
            if ((*this->board)[E1.first][E1.second] != WhiteKing)
            {
                this->whiteCanCastle = false;
            }
            else
            {
                if ((*this->board)[H1.first][H1.second] != WhiteRook)
                {
                    this->whiteRightRookMoved = true;
                }
                if ((*this->board)[A1.first][A1.second] != WhiteRook)
                {
                    this->whiteLeftRookMoved = true;
                }
                if (this->whiteRightRookMoved && this->whiteRightRookMoved)
                {
                    this->whiteCanCastle = false;
                }
            }

        }
    }
    else
    {
        if (this->blackCanCastle)
        {
            if ((*this->board)[E8.first][E8.second] != BlackKing)
            {
                this->blackCanCastle = false;
            }
            else
            {
                if ((*this->board)[H8.first][H8.second] != BlackRook)
                {
                    this->blackRightRookMoved = true;
                }
                if ((*this->board)[A8.first][A8.second] != BlackRook)
                {
                    this->blackLeftRookMoved = true;
                }
                if (this->blackRightRookMoved && this->blackRightRookMoved)
                {
                    this->blackCanCastle = false;
                }
            }

        }
    }

}

ChessGame::~ChessGame()
{
    std::cout << "Calling Game destructor" << "\n";
    delete this->board;
    delete this->whiteLegalMoves;
    delete this->blackLegalMoves;
    delete this->lastMoves;
}