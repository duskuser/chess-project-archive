#include "BoardHandler.h"

// Checks all possible moves for White and Black pieces, handles checks / illegal
// moves, handles castling 
void BoardHandler::calculateLegalMoves(ChessGame &cg)
{
    // Checks repition first
    if (checkForRepition(*cg.lastMoves))
    {
        cg.gameWon = true;
        cg.gameState = GameDrawn;
    }
    else 
    {
        calculateWhiteMoves(*cg.whiteLegalMoves, *cg.board);
        calculateBlackMoves(*cg.blackLegalMoves, *cg.board);
        // Check for checks // illegal moves 
        handleWhiteCheck(*cg.whiteLegalMoves, *cg.board);
        handleBlackCheck(*cg.blackLegalMoves, *cg.board);
        if (cg.whiteTurn)
        {
            // Check for castling
            if (!checkWhiteCheck(*cg.blackLegalMoves, *cg.board) && cg.whiteCanCastle)
            {
                if (cg.whiteCanCastle)
                {
                    handleWhiteCastling(cg);
                }
            }
    }
    else
    {
        // Check for castling
        if (!checkBlackCheck(*cg.whiteLegalMoves, *cg.board) && cg.blackCanCastle)
        {
            handleBlackCastling(cg);
        }
    }
    }

    if (cg.whiteLegalMoves->size() == 0 && cg.blackLegalMoves->size() == 0)
    {
        cg.gameWon = true;
        cg.gameState = GameDrawn;
    }
    else if (cg.blackLegalMoves->size() == 0)
    {
        cg.gameWon = true;
        cg.gameState = WhiteWon;
    }
    else if (cg.whiteLegalMoves->size() == 0)
    {
        cg.gameWon = true;
        cg.gameState = BlackWon;
    }
}

bool BoardHandler::checkForRepition
(std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>> &lastMoves)
{
    if (lastMoves.size() < REPEATABLE_MOVES) { return false; }
    for (int i = 1; i < lastMoves.size(); i++)
    {
        if (lastMoves[0] != lastMoves[i]) { return false; }
    }
    return true;
}

// Checks all possible moves for White pieces
void BoardHandler::calculateWhiteMoves(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves, 
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    // Initial pass through calculates all possible moves regardless of check / castling status
    
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMNS; x++)
        {
            if (board[y][x] != EmptySpace && board[y][x] <= WhiteKing)
            {
                std::vector<std::pair<int_fast8_t, int_fast8_t>> currentMoves;
                std::pair<int_fast8_t, int_fast8_t> position {y, x};
                switch (board[y][x])
                {

                case WhitePawn:
                currentMoves = handleWhitePawn(board, y, x);
                break;

                case UnmovedWhitePawn:
                currentMoves = handleUnmovedWhitePawn(board, y, x);
                break;

                case WhiteRook:
                currentMoves = handleWhiteRook(board, y, x);
                break;

                case WhiteKnight:
                currentMoves = handleWhiteKnight(board,y, x);
                break;

                case WhiteBishop:
                currentMoves = handleWhiteBishop(board, y, x);
                break;

                case WhiteQueen:
                currentMoves = handleWhiteQueen(board, y, x);
                break;

                case WhiteKing:
                currentMoves = handleWhiteKing(board, y, x);
                break;

                default:
                break;

                }
                if (currentMoves.size() != 0)
                {

                    whiteLegalMoves.insert({position, currentMoves});
                }
            }

        }
    } 
}

// Checks all possible moves for Black pieces
void BoardHandler::calculateBlackMoves(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves, 
std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    // Initial pass through calculates all possible moves regardless of check / castling status
    for (int_fast8_t y = 0; y < ROWS; y++)
    {
        for (int_fast8_t x = 0; x < COLUMNS; x++)
        {
            if (board[y][x] != EmptySpace && board[y][x] >= BlackPawn)
            {
                std::vector<std::pair<int_fast8_t, int_fast8_t>> currentMoves;
                std::pair<int_fast8_t, int_fast8_t> position {y, x};
                switch (board[y][x])
                {

                case BlackPawn:
                currentMoves = handleBlackPawn(board, y, x);
                break;

                case UnmovedBlackPawn:
                currentMoves = handleUnmovedBlackPawn(board, y, x);
                break;

                case BlackRook:
                currentMoves = handleBlackRook(board, y, x);
                break;

                case BlackKnight:
                currentMoves = handleBlackKnight(board, y, x);
                break;

                case BlackBishop:
                currentMoves = handleBlackBishop(board, y, x);
                break;

                case BlackQueen:
                currentMoves = handleBlackQueen(board, y, x);
                break;

                case BlackKing:
                currentMoves = handleBlackKing(board, y, x);
                break;

                default:
                break;

                }
                if (currentMoves.size() != 0)
                {
                    blackLegalMoves.insert({position, currentMoves});
                }
            }

        }
    } 
}

// Returns true if WhiteKing position is found in blacks legal move set
bool BoardHandler::checkWhiteCheck(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves,
std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    for (auto it : blackLegalMoves)
    {
        for (auto position : it.second)
        {
            if (board[position.first][position.second] == WhiteKing)
            {
                return true;
            }   
        }
    }
    return false;
}

// Returns true if BlackKing position is found in whites legal move set
bool BoardHandler::checkBlackCheck(std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves,
std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    for (auto it : whiteLegalMoves)
    {
        for (auto position : it.second)
        {
            if (board[position.first][position.second] == BlackKing)
            {
                return true;
            }   
        }
    }
    return false;
}

// Passes through all moves and removes all scenarios where King is in check
// after moving piece
void BoardHandler::handleWhiteCheck(
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& whiteLegalMoves, 
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> boardCopy = board;
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>> blackMoves;
    std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>> moveSet;
    auto entry = whiteLegalMoves.begin();
    while (entry != whiteLegalMoves.end())
    {
        moveSet.first = entry->first;
        auto it = entry->second.begin();
        while (it != entry->second.end())
        {
            // Resets Board / Moves
            boardCopy = board;
            blackMoves.clear();
            moveSet.second = *it;
            // Moves Piece on board copy
            handleMove(boardCopy, moveSet);
            // Calculates what blacks moves are if piece is moved
            calculateBlackMoves(blackMoves, boardCopy);
            // If in check move is deleted
            if (checkWhiteCheck(blackMoves, boardCopy))
            {
                it = entry->second.erase(it);
            }
            else
            {
                it++;
            }
        }

        // Deletes entry if 0 available moves
        if (entry->second.size() == 0)
        {
            entry = whiteLegalMoves.erase(entry);
        }
        else
        {
            entry++;
        }
    }
}

// Passes through all moves and removes all scenarios where King is in check
// after moving piece
void BoardHandler::handleBlackCheck(
std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>>& blackLegalMoves, 
std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board)
{
    std::array<std::array<int_fast8_t, ROWS>, COLUMNS> boardCopy = board;
    std::map<std::pair<int_fast8_t, int_fast8_t>, std::vector<std::pair<int_fast8_t, int_fast8_t>>> whiteMoves;
    std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>> moveSet;
    
    auto entry = blackLegalMoves.begin();
    while (entry != blackLegalMoves.end())
    {
        moveSet.first = entry->first;
        auto it = entry->second.begin();
        while (it != entry->second.end())
        {
            // Resets Board / Moves
            boardCopy = board;
            whiteMoves.clear();
            moveSet.second = *it;
            // Moves Piece on board copy
            handleMove(boardCopy, moveSet);
            // Calculates what blacks moves are if piece is moved
            calculateWhiteMoves(whiteMoves, boardCopy);
            // If not in check, move is added to updated moves for copy
            if (checkBlackCheck(whiteMoves, boardCopy))
            {
                it = entry->second.erase(it);
            }
            else
            {
                it++;
            }
        }

        // Deletes entry if 0 available moves
        if (entry->second.size() == 0)
        {
            entry = blackLegalMoves.erase(entry);
        }
        else
        {
            entry++;
        }
    }
}

void BoardHandler::handleWhiteCastling(ChessGame &cg)
{
    if (!cg.whiteRightRookMoved)
    {
        if ((*cg.board)[F1.first][F1.second] == EmptySpace &&
        (*cg.board)[G1.first][G1.second] == EmptySpace)
        {
            std::cout << "White can castle short!" << "\n";
            for (auto &it : *cg.whiteLegalMoves)
            {
                if (it.first == E1)
                {
                    it.second.push_back(G1);
                    break;
                }
            }
        }
    }

    if (!cg.whiteLeftRookMoved)
    {
        if ((*cg.board)[D1.first][D1.second] == EmptySpace &&
        (*cg.board)[C1.first][C1.second] == EmptySpace &&
        (*cg.board)[B1.first][B1.second] == EmptySpace)
        {
            for (auto &it : *cg.whiteLegalMoves)
            {
                if (it.first == E1)
                {
                    it.second.push_back(C1);
                    break;
                }
            }
        }
    }
}

void BoardHandler::handleBlackCastling(ChessGame &cg)
{
    if (!cg.blackRightRookMoved)
    {
        if ((*cg.board)[F8.first][F8.second] == EmptySpace &&
        (*cg.board)[G8.first][G8.second] == EmptySpace)
        {
            for (auto &it : *cg.whiteLegalMoves)
            {
                if (it.first == E8)
                {
                    it.second.push_back(G8);
                    break;
                }
            }
        }
    }

    if (!cg.blackLeftRookMoved)
    {
        if ((*cg.board)[D8.first][D8.second] == EmptySpace &&
        (*cg.board)[C8.first][C8.second] == EmptySpace &&
        (*cg.board)[B8.first][B8.second] == EmptySpace)
        {
            for (auto &it : *cg.whiteLegalMoves)
            {
                if (it.first == E8)
                {
                    it.second.push_back(C8);
                    break;
                }
            }
        }
    }
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhitePawn
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    if (y == EIGHTH_ROW)
    {
        board[y][x] = WhiteQueen;
        return handleWhiteQueen(board, y, x);
    }
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;

    if (board[y + WhitePawnForward.first][x + WhitePawnForward.second] == EmptySpace)
    {
        std::pair<int_fast8_t, int_fast8_t> move (y + WhitePawnForward.first, x + WhitePawnForward.second);
        pieceMoves.push_back(move);
    }

    // Additional if to protect from out of range error
    if (x != BOARD_LEFT)
    {
        if (board[y + WhitePawnTakeLeft.first][x + WhitePawnTakeLeft.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t>move (y + WhitePawnTakeLeft.first, x + WhitePawnTakeLeft.second);
            pieceMoves.push_back(move); 
        }
    }

    // Additional if to protect from out of range error
    if (x != BOARD_RIGHT)
    {
        if (board[y + WhitePawnTakeRight.first][x + WhitePawnTakeRight.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + WhitePawnTakeRight.first, x + WhitePawnTakeRight.second);
            pieceMoves.push_back(move); 
        }
    }

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleUnmovedWhitePawn
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    if (y != SECOND_ROW)
    {
        board[y][x] = WhitePawn;
        return handleWhitePawn(board, y, x);
    }
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;

    if (board[y + WhitePawnForward.first][x + WhitePawnForward.second] == EmptySpace)
    {
        std::pair<int_fast8_t, int_fast8_t> move (y + WhitePawnForward.first, x + WhitePawnForward.second);
        pieceMoves.push_back(move);
    }

    if (board[y + UnmovedWhitePawnForward.first][x + UnmovedWhitePawnForward.second] == EmptySpace)
    {
    std::pair<int, int> move (y + UnmovedWhitePawnForward.first, x + UnmovedWhitePawnForward.second);
    pieceMoves.push_back(move);
    }

    // Additional if to protect from out of range error
    if (x != BOARD_LEFT)
    {
        if (board[y + WhitePawnTakeLeft.first][x + WhitePawnTakeLeft.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t>move (y + WhitePawnTakeLeft.first, x + WhitePawnTakeLeft.second);
            pieceMoves.push_back(move); 
        }
    }

    // Additional if to protect from out of range error
    if (x != BOARD_RIGHT)
    {
        if (board[y + WhitePawnTakeRight.first][x + WhitePawnTakeRight.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + WhitePawnTakeRight.first, x + WhitePawnTakeRight.second);
            pieceMoves.push_back(move); 
        }
    }

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhiteRook
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
        // Handle Left
        if (x != BOARD_LEFT)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (x + (i * PieceLeft.second) <= -1)
                {
                    break;
                }
                if (board[y][x + (i * PieceLeft.second)] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y][x + (i * PieceLeft.second)] >= BlackPawn)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }
        // Handle Right
        if (x != BOARD_RIGHT)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (x + (i * PieceRight.second) == 8)
                {
                    break;
                }
                if (board[y][x + (i * PieceRight.second)] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y][x + (i * PieceRight.second)] >= BlackPawn)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }

        // Handle Down
        if (y != BOARD_BOTTOM)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (y + (i * PieceBack.first) >= 8)
                {
                    break;
                }
                if (board[y + (i * PieceBack.first)][x] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y + (i * PieceBack.first)][x] >= BlackPawn)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }

        // Handle Up
        if (y != BOARD_TOP)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (y + (i * PieceForward.first) <= -1)
                {
                    break;
                }
                if (y + (i * PieceForward.first) == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y + (i * PieceForward.first)][x] >= BlackPawn)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }
        return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhiteKnight
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;

    // Handle Left Forward
    if (y + KnightLeftForward.first >= BOARD_TOP &&
     x + KnightLeftForward.second >= BOARD_LEFT)
    {
        if (board[y + KnightLeftForward.first][x + KnightLeftForward.second] == EmptySpace ||
        board[y + KnightLeftForward.first][x + KnightLeftForward.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightLeftForward.first, x + KnightLeftForward.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Right Forward
    if (y + KnightRightForward.first >= BOARD_TOP &&
     x + KnightRightForward.second <= BOARD_RIGHT)
    {
        if (board[y + KnightRightForward.first][x + KnightRightForward.second] == EmptySpace ||
        board[y + KnightRightForward.first][x + KnightRightForward.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightRightForward.first, x + KnightRightForward.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Left Back
    if (y + KnightLeftBack.first <= BOARD_BOTTOM && 
    x + KnightLeftBack.second >= BOARD_LEFT)
    {
        if (board[y + KnightLeftBack.first][x + KnightLeftBack.second] == EmptySpace ||
        board[y + KnightLeftBack.first][x + KnightLeftBack.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightLeftBack.first, x + KnightLeftBack.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Right Back
    if (y + KnightRightBack.first <= BOARD_BOTTOM 
    && x + KnightRightBack.second <= BOARD_RIGHT)
    {
        if (board[y + KnightRightBack.first][x + KnightRightBack.second] == EmptySpace ||
        board[y + KnightRightBack.first][x + KnightRightBack.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightRightBack.first, x + KnightRightBack.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Forward Left
    if (y + KnightForwardLeft.first >= BOARD_TOP &&
     x + KnightForwardLeft.second >= BOARD_LEFT)
    {
        if (board[y + KnightForwardLeft.first][x + KnightForwardLeft.second] == EmptySpace ||
        board[y + KnightForwardLeft.first][x + KnightForwardLeft.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightForwardLeft.first, x + KnightForwardLeft.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Forward Right
    if (y + KnightForwardRight.first >= BOARD_TOP &&
     x + KnightForwardRight.second <= BOARD_RIGHT)
    {
        if (board[y + KnightForwardRight.first][x + KnightForwardRight.second] == EmptySpace ||
        board[y + KnightForwardRight.first][x + KnightForwardRight.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightForwardRight.first, x + KnightForwardRight.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Back Left
    if (y + KnightBackLeft.first <= BOARD_BOTTOM &&
     x + KnightBackLeft.second >= BOARD_LEFT)
    {
        if (board[y + KnightBackLeft.first][x + KnightBackLeft.second] == EmptySpace ||
        board[y + KnightBackLeft.first][x + KnightBackLeft.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightBackLeft.first, x + KnightBackLeft.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Back Right
    if (y + KnightBackRight.first <= BOARD_BOTTOM 
    && x + KnightBackRight.second <= BOARD_RIGHT)
    {
        if (board[y + KnightBackRight.first][x + KnightBackRight.second] == EmptySpace ||
        board[y + KnightBackRight.first][x + KnightBackRight.second] >= BlackPawn)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightBackRight.first, x + KnightBackRight.second);
            pieceMoves.push_back(move);
        }
    }

    

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhiteBishop
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    // Loop iterates 7 times each cycle as maximum of 7 moves in any direction is possible at any given moment
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardLeft.first) <= -1 || x + (i * PieceForwardLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardRight.first) <= -1 || x + (i * PieceForwardRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackLeft.first) >= 8 || x + (i * PieceBackLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && y != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackRight.first) <= -1 || x + (i * PieceBackRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }


    return pieceMoves;
};

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhiteQueen
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Left
    if (x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (x + (i * PieceLeft.second) <= -1)
            {
                break;
            }
            if (board[y][x + (i * PieceLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + (i *PieceLeft.second));
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y][x + (i * PieceLeft.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }
    // Handle Right
    if (x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (x + (i * PieceRight.second) == 8)
            {
                break;
            }
            if (board[y][x + (i * PieceRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y][x + (i * PieceRight.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }

    // Handle Down
    if (y != BOARD_BOTTOM)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBack.first) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceBack.first)][x] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y + (i * PieceBack.first)][x] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }

    // Handle Up
    if (y != BOARD_TOP)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForward.first) <= -1)
            {
                break;
            }
            if (y + (i * PieceForward.first) == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y + (i * PieceForward.first)][x] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }
    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardLeft.first) <= -1 || x + (i * PieceForwardLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardRight.first) <= -1 || x + (i * PieceForwardRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackLeft.first) >= 8 || x + (i * PieceBackLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackRight.first) < BOARD_BOTTOM || x + (i * PieceBackRight.second) >= BOARD_RIGHT)
            {
                break;
            }
            if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] >= BlackPawn)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }


    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleWhiteKing
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
        std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Left
    if (x != BOARD_LEFT)
    {
        if (board[y][x + PieceLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceLeft.second);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y][x + PieceLeft.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceLeft.second);
                pieceMoves.push_back(move);
            }
        }
    }
    // Handle Right
    if (x != BOARD_RIGHT)
    {
        if (board[y][x + PieceRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceRight.second);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y][x + PieceRight.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceRight.second);
                pieceMoves.push_back(move);
            }
        }
    }

    // Handle Down
    if (y != BOARD_BOTTOM)
    {
        if (board[y + PieceBack.first][x] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBack.first, x);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y + PieceBack.first][x] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBack.first, x);
                pieceMoves.push_back(move);
            }
        }
    }

    // Handle Up
    if (y != BOARD_TOP)
    {
        if (y + PieceForward.first == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForward.first, x);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y + PieceForward.first][x] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForward.first, x);
                pieceMoves.push_back(move);
            }
        }
    }
    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        if (board[y + PieceForwardLeft.first][x + PieceForwardLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardLeft.first, x + PieceForwardLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceForwardLeft.first][x + PieceForwardLeft.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardLeft.first, x + PieceForwardLeft.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        if (board[y + PieceForwardRight.first][x + PieceForwardRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardRight.first, x + PieceForwardRight.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceForwardRight.first][x + PieceForwardRight.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardRight.first, x + PieceForwardRight.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        if (board[y + PieceBackLeft.first][x + PieceBackLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackLeft.first, x + PieceBackLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceBackLeft.first][x + PieceBackLeft.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackLeft.first, x + PieceBackLeft.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && x != BOARD_RIGHT)
    {
        if (board[y + PieceBackRight.first][x + PieceBackRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackRight.first, x + PieceBackLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceBackRight.first][x + PieceBackRight.second] >= BlackPawn)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackRight.first, x + PieceBackRight.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackPawn
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    if (y == FIRST_ROW)
    {
        board[y][x] = BlackQueen;
        return handleBlackQueen(board, y, x);
    }
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    if (board[y + BlackPawnForward.first][x + BlackPawnForward.second] == EmptySpace)
    {
        std::pair<int_fast8_t, int_fast8_t> move (y + BlackPawnForward.first, x + BlackPawnForward.second);
        pieceMoves.push_back(move);
    }
    // Additional if to protect from out of range error
    if (x != BOARD_LEFT)
    {
        if (board[y + BlackPawnTakeLeft.first][x + BlackPawnTakeLeft.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t>move (y + BlackPawnTakeLeft.first, x + BlackPawnTakeLeft.second);
            pieceMoves.push_back(move); 
        }
    }

    // Additional if to protect from out of range error
    if (x != BOARD_RIGHT)
    {
        if (board[y + BlackPawnTakeRight.first][x + BlackPawnTakeRight.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + BlackPawnTakeRight.first, x + BlackPawnTakeRight.second);
            pieceMoves.push_back(move); 
        }
    }

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleUnmovedBlackPawn
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    if (y != SEVENTH_ROW)
    {
        board[y][x] = BlackPawn;
        return handleBlackPawn(board, y, x);
    }
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    if (board[y + BlackPawnForward.first][x + BlackPawnForward.second] == EmptySpace)
    {
        std::pair<int_fast8_t, int_fast8_t> move (y + BlackPawnForward.first, x + BlackPawnForward.second);
        pieceMoves.push_back(move);
    }

    if (board[y + UnmovedBlackPawnForward.first][x + UnmovedBlackPawnForward.second] == EmptySpace)
    {
    std::pair<int_fast8_t, int_fast8_t> move (y + UnmovedBlackPawnForward.first, x + UnmovedBlackPawnForward.second);
    pieceMoves.push_back(move);
    }

    // Additional if to protect from out of range error
    if (x != BOARD_LEFT)
    {
        if (board[y + BlackPawnTakeLeft.first][x + BlackPawnTakeLeft.second] <= WhiteKing
        && board[y + BlackPawnTakeLeft.first][x + BlackPawnTakeLeft.second] != EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t>move (y + BlackPawnTakeLeft.first, x + BlackPawnTakeLeft.second);
            pieceMoves.push_back(move); 
        }
    }

    // Additional if to protect from out of range error
    if (x != BOARD_RIGHT)
    {
        if (board[y + BlackPawnTakeRight.first][x + BlackPawnTakeRight.second] <= WhiteKing
        && board[y + BlackPawnTakeLeft.first][x + BlackPawnTakeLeft.second] != EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + BlackPawnTakeRight.first, x + BlackPawnTakeRight.second);
            pieceMoves.push_back(move); 
        }
    }

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackRook
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
        // Handle Left
        if (x != BOARD_LEFT)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (x + (i * PieceLeft.second) <= -1)
                {
                    break;
                }
                if (board[y][x + (i * PieceLeft.second)] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y][x + (i * PieceLeft.second)] <= WhiteKing)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }
        // Handle Right
        if (x != BOARD_RIGHT)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (x + (i * PieceRight.second) == 8)
                {
                    break;
                }
                if (board[y][x + (i * PieceRight.second)] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y][x + (i * PieceRight.second)] <= WhiteKing)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }

        // Handle Down
        if (y != BOARD_BOTTOM)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (y + (i * PieceBack.first) == -1)
                {
                    break;
                }
                if (board[y + (i * PieceBack.first)][x] == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y + (i * PieceBack.first)][x] <= WhiteKing)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }

        // Handle Up
        if (y != BOARD_TOP)
        {
            for (int_fast8_t i = 1; i < MAX_MOVES; i++)
            {
                if (y + (i * PieceForward.first) == 8)
                {
                    break;
                }
                if (y + (i * PieceForward.first) == EmptySpace)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                    pieceMoves.push_back(move);
                }
                else
                {
                    if (board[y + (i * PieceForward.first)][x] <= WhiteKing)
                    {
                        std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                        pieceMoves.push_back(move);
                    }
                    break;
                }
            }
        }
        return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackKnight
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;

    // Handle Left Forward
    if (y + KnightLeftForward.first >= BOARD_TOP &&
     x + KnightLeftForward.second >= BOARD_LEFT)
    {
        if (board[y + KnightLeftForward.first][x + KnightLeftForward.second] == EmptySpace ||
        board[y + KnightLeftForward.first][x + KnightLeftForward.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightLeftForward.first, x + KnightLeftForward.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Right Forward
    if (y + KnightRightForward.first >= BOARD_TOP &&
     x + KnightRightForward.second <= BOARD_RIGHT)
    {
        if (board[y + KnightRightForward.first][x + KnightRightForward.second] == EmptySpace ||
        board[y + KnightRightForward.first][x + KnightRightForward.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightRightForward.first, x + KnightRightForward.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Left Back
    if (y + KnightLeftBack.first <= BOARD_BOTTOM && 
    x + KnightLeftBack.second >= BOARD_LEFT)
    {
        if (board[y + KnightLeftBack.first][x + KnightLeftBack.second] == EmptySpace ||
        board[y + KnightLeftBack.first][x + KnightLeftBack.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightLeftBack.first, x + KnightLeftBack.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Right Back
    if (y + KnightRightBack.first <= BOARD_BOTTOM 
    && x + KnightRightBack.second <= BOARD_RIGHT)
    {
        if (board[y + KnightRightBack.first][x + KnightRightBack.second] == EmptySpace ||
        board[y + KnightRightBack.first][x + KnightRightBack.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightRightBack.first, x + KnightRightBack.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Forward Left
    if (y + KnightForwardLeft.first >= BOARD_TOP &&
     x + KnightForwardLeft.second >= BOARD_LEFT)
    {
        if (board[y + KnightForwardLeft.first][x + KnightForwardLeft.second] == EmptySpace ||
        board[y + KnightForwardLeft.first][x + KnightForwardLeft.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightForwardLeft.first, x + KnightForwardLeft.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Forward Right
    if (y + KnightForwardRight.first >= BOARD_TOP &&
     x + KnightForwardRight.second <= BOARD_RIGHT)
    {
        if (board[y + KnightForwardRight.first][x + KnightForwardRight.second] == EmptySpace ||
        board[y + KnightForwardRight.first][x + KnightForwardRight.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightForwardRight.first, x + KnightForwardRight.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Back Left
    if (y + KnightBackLeft.first <= BOARD_BOTTOM &&
     x + KnightBackLeft.second >= BOARD_LEFT)
    {
        if (board[y + KnightBackLeft.first][x + KnightBackLeft.second] == EmptySpace ||
        board[y + KnightBackLeft.first][x + KnightBackLeft.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightBackLeft.first, x + KnightBackLeft.second);
            pieceMoves.push_back(move);
        }
    }

    // Handle Back Right
    if (y + KnightBackRight.first <= BOARD_BOTTOM 
    && x + KnightBackRight.second <= BOARD_RIGHT)
    {
        if (board[y + KnightBackRight.first][x + KnightBackRight.second] == EmptySpace ||
        board[y + KnightBackRight.first][x + KnightBackRight.second] <= WhiteKing)
        {
            std::pair<int_fast8_t, int_fast8_t> move 
            (y + KnightBackRight.first, x + KnightBackRight.second);
            pieceMoves.push_back(move);
        }
    }

    

    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackBishop
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    // Loop iterates 7 times each cycle as maximum of 7 moves in any direction is possible at any given moment
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardLeft.first) <= -1 || x + (i * PieceForwardLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardRight.first) <= -1 || x + (i * PieceForwardRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackLeft.first) >= 8 || x + (i * PieceBackLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackRight.first) <= -1 || x + (i * PieceBackRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }


    return pieceMoves;
};

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackQueen
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
    std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Left
    if (x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (x + (i * PieceLeft.second) <= -1)
            {
                break;
            }
            if (board[y][x + (i * PieceLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + (i *PieceLeft.second));
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y][x + (i * PieceLeft.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceLeft.second));
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }
    // Handle Right
    if (x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (x + (i * PieceRight.second) == 8)
            {
                break;
            }
            if (board[y][x + (i * PieceRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y][x + (i * PieceRight.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y, x + (i * PieceRight.second));
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }

    // Handle Down
    if (y != BOARD_BOTTOM)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBack.first) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceBack.first)][x] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y + (i * PieceBack.first)][x] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBack.first), x);
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }

    // Handle Up
    if (y != BOARD_TOP)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForward.first) <= 0)
            {
                break;
            }
            if (y + (i * PieceForward.first) == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                pieceMoves.push_back(move);
            }
            else
            {
                if (board[y + (i * PieceForward.first)][x] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForward.first), x);
                    pieceMoves.push_back(move);
                }
                break;
            }
        }
    }

    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardLeft.first) <= -1 || x + (i * PieceForwardLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardLeft.first)][x + (i * PieceForwardLeft.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardLeft.first), x + (i * PieceForwardLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceForwardRight.first) <= -1 || x + (i * PieceForwardRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceForwardRight.first)][x + (i * PieceForwardRight.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceForwardRight.first), x + (i * PieceForwardRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackLeft.first) >= 8 || x + (i * PieceBackLeft.second) <= -1)
            {
                break;
            }
            if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackLeft.first)][x + (i * PieceBackLeft.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackLeft.first), x + (i * PieceBackLeft.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && y != BOARD_RIGHT)
    {
        for (int_fast8_t i = 1; i < MAX_MOVES; i++)
        {
            if (y + (i * PieceBackRight.first) <= -1 || x + (i * PieceBackRight.second) >= 8)
            {
                break;
            }
            if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] == EmptySpace)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackLeft.second));
                pieceMoves.push_back(move); 
            }
            else
            {
                if (board[y + (i * PieceBackRight.first)][x + (i * PieceBackRight.second)] <= WhiteKing)
                {
                    std::pair<int_fast8_t, int_fast8_t> move (y + (i * PieceBackRight.first), x + (i * PieceBackRight.second));
                    pieceMoves.push_back(move); 
                }
                break;
            }
        }
    }


    return pieceMoves;
}

std::vector<std::pair<int_fast8_t, int_fast8_t>> BoardHandler::handleBlackKing
(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, int_fast8_t y, int_fast8_t x)
{
        std::vector<std::pair<int_fast8_t, int_fast8_t>> pieceMoves;
    // Handle Left
    if (x != BOARD_LEFT)
    {
        if (board[y][x + PieceLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceLeft.second);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y][x + PieceLeft.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceLeft.second);
                pieceMoves.push_back(move);
            }
        }
    }
    // Handle Right
    if (x != BOARD_RIGHT)
    {
        if (board[y][x + PieceRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceRight.second);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y][x + PieceRight.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y, x + PieceRight.second);
                pieceMoves.push_back(move);
            }
        }
    }

    // Handle Down
    if (y != BOARD_BOTTOM)
    {
        if (board[y + PieceBack.first][x] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBack.first, x);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y + PieceBack.first][x] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBack.first, x);
                pieceMoves.push_back(move);
            }
        }
    }

    // Handle Up
    if (y != BOARD_TOP)
    {
        if (y + PieceForward.first == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForward.first, x);
            pieceMoves.push_back(move);
        }
        else
        {
            if (board[y + PieceForward.first][x] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForward.first, x);
                pieceMoves.push_back(move);
            }
        }
    }
    // Handle Forward Left
    if (y != BOARD_TOP && x != BOARD_LEFT)
    {
        if (board[y + PieceForwardLeft.first][x + PieceForwardLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardLeft.first, x + PieceForwardLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceForwardLeft.first][x + PieceForwardLeft.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardLeft.first, x + PieceForwardLeft.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Forward Right
    if (y != BOARD_TOP && x != BOARD_RIGHT)
    {
        if (board[y + PieceForwardRight.first][x + PieceForwardRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardRight.first, x + PieceForwardRight.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceForwardRight.first][x + PieceForwardRight.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceForwardRight.first, x + PieceForwardRight.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Back Left
    if (y != BOARD_BOTTOM && x != BOARD_LEFT)
    {
        if (board[y + PieceBackLeft.first][x + PieceBackLeft.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackLeft.first, x + PieceBackLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceBackLeft.first][x + PieceBackLeft.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackLeft.first, x + PieceBackLeft.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    // Handle Back Right
    if (y != BOARD_BOTTOM && x != BOARD_RIGHT)
    {
        if (board[y + PieceBackRight.first][x + PieceBackRight.second] == EmptySpace)
        {
            std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackRight.first, x + PieceBackLeft.second);
            pieceMoves.push_back(move); 
        }
        else
        {
            if (board[y + PieceBackRight.first][x + PieceBackRight.second] <= WhiteKing)
            {
                std::pair<int_fast8_t, int_fast8_t> move (y + PieceBackRight.first, x + PieceBackRight.second);
                pieceMoves.push_back(move); 
            }
        }
    }

    return pieceMoves;
}
// Sets moveset.second to moveset.first, moveset.first to empty space on Board
void BoardHandler::handleMove(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>& moveSet)
{
    // Handles Castling, logic checks have already been completed by this point
    if (board[moveSet.first.first][moveSet.first.second] == WhiteKing
    && moveSet.first == E1)
    {
        if (moveSet.second == C1)
        {
            board[C1.first][C1.second] = WhiteKing;
            board[D1.first][D1.second] = WhiteRook;
            board[E1.first][E1.second] = EmptySpace;
            board[A1.first][A1.second] = EmptySpace;

        }
        else if (moveSet.second == G1)
        {
            board[G1.first][G1.second] = WhiteKing;
            board[F1.first][F1.second] = WhiteRook;
            board[E1.first][E1.second] = EmptySpace;
            board[H1.first][H1.second] = EmptySpace;
        }
        // Normal move, castling privilege will be lost upon generation of next
        // ChessGame object
        else
        {
            board[moveSet.second.first][moveSet.second.second] = board[moveSet.first.first][moveSet.first.second];
            board[moveSet.first.first][moveSet.first.second] = EmptySpace;
        }
    }
    else if (board[moveSet.first.first][moveSet.first.second] == BlackKing
    && moveSet.first == E8)
    {
        if (moveSet.second == C8)
        {
            board[C8.first][C8.second] = WhiteKing;
            board[D8.first][D8.second] = WhiteRook;
            board[E8.first][E8.second] = EmptySpace;
            board[A8.first][A8.second] = EmptySpace;

        }
        else if (moveSet.second == G8)
        {
            board[G8.first][G8.second] = WhiteKing;
            board[F8.first][F8.second] = WhiteRook;
            board[E8.first][E8.second] = EmptySpace;
            board[H8.first][H8.second] = EmptySpace;
        }
        // Normal move, castling privilege will be lost upon generation of next
        // ChessGame object
        else
        {
            board[moveSet.second.first][moveSet.second.second] = board[moveSet.first.first][moveSet.first.second];
            board[moveSet.first.first][moveSet.first.second] = EmptySpace;
        }
    }
        // Handles normal moves
    else
    {
        board[moveSet.second.first][moveSet.second.second] = board[moveSet.first.first][moveSet.first.second];
        board[moveSet.first.first][moveSet.first.second] = EmptySpace;
    }
}

void BoardHandler::updateLastMoves(std::vector<std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>> &lastMoves, 
std::pair<std::pair<int_fast8_t, int_fast8_t>, std::pair<int_fast8_t, int_fast8_t>>& moveSet)
{
    lastMoves.push_back(moveSet);
}

void BoardHandler::printBoard(ChessGame &cg)
{
    for (int y = 0; y < COLUMNS; y++)
    {
        for (int x = 0; x < ROWS; x++)
        {
            if (x == 7)
            {
                std::cout << translateToNotation(y,x) << " " << translateToPiece((*cg.board)[y][x]) << "\n";
            }
            else 
            {
                std::cout << translateToNotation(y,x) << " " << translateToPiece((*cg.board)[y][x]) << " ";
            }

        }
    }
}

void BoardHandler::printTurn (bool whiteTurn)
{
    if (whiteTurn)
    {
        std::cout << "White to play" << "\n";
    }
    else 
    {
        std::cout << "Black to play" << "\n";
    }
}

void BoardHandler::printLegalMoves(ChessGame &cg)
{
    std::cout << "Legal moves ";
    if (cg.whiteTurn)
    {
        std::cout << "(White playing): \n";
        for (auto it : *cg.whiteLegalMoves)
        {
            std::cout << translateToNotation(it.first.first, it.first.second) << ": ";
            for (auto position : it.second)
            {
                std::cout << translateToNotation(position.first, position.second) << " ";
            }
        }
    }
    else 
    {
        std::cout << "(Black playing): \n";
        for (auto it : *cg.blackLegalMoves)
        {
            std::cout << translateToNotation(it.first.first, it.first.second) << ": ";
            for (auto position : it.second)
            {
                std::cout << translateToNotation(position.first, position.second) << " ";
            }
        }
    }
    std::cout << " " << "\n";
}

std::string BoardHandler::translateToNotation(int_fast8_t y, int_fast8_t x)
{
    std::string square;
    switch (x)
    {
        case 0:
        square.push_back('A');
        break;
        case 1:
        square.push_back('B');
        break;
        case 2:
        square.push_back('C');
        break;
        case 3:
        square.push_back('D');
        break;
        case 4:
        square.push_back('E');
        break;
        case 5:
        square.push_back('F');
        break;
        case 6:
        square.push_back('G');
        break;
        case 7:
        square.push_back('H');
        break;
    }
    // Reverses Y for board orientation
    switch (y)
    {
        case 0:
        square.push_back(8 + '0');
        break;

        case 1:
        square.push_back(7 + '0');
        break;

        case 2:
        square.push_back(6 + '0');
        break;

        case 3:
        square.push_back(5 + '0');
        break;

        case 4:
        square.push_back(4 + '0');
        break;

        case 5:
        square.push_back(3 + '0');
        break;

        case 6:
        square.push_back(2 + '0');
        break;

        case 7:
        square.push_back(1 + '0');
        break;
    }
    return square;
}

std::string BoardHandler::translateToPiece(int_fast8_t pieceNum)
{
    std::string pieceName;
    switch (pieceNum)
    {
        case EmptySpace:
        pieceName = "Empty";
        break;
        
        case WhitePawn:
        pieceName = "White Pawn";
        break;

        case UnmovedWhitePawn:
        pieceName = "White Pawn";
        break;

        case WhiteRook:
        pieceName = "White Rook";
        break;

        case WhiteKnight:
        pieceName = "White Knight";
        break;

        case WhiteBishop:
        pieceName = "White Bishop";
        break;

        case WhiteQueen:
        pieceName = "White Queen";
        break;

        case WhiteKing:
        pieceName = "White King";
        break;

        case BlackPawn:
        pieceName = "Black Pawn";
        break;

        case UnmovedBlackPawn:
        pieceName = "Black Pawn";
        break;

        case BlackRook:
        pieceName = "Black Rook";
        break;

        case BlackKnight:
        pieceName = "Black Knight";
        break;

        case BlackBishop:
        pieceName = "Black Bishop";
        break;

        case BlackQueen:
        pieceName = "Black Queen";
        break;

        case BlackKing:
        pieceName = "Black King";
        break;

    }
    return pieceName;
}