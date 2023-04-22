#pragma once

#include "EngineNode.h"

// Booleans are set to 0 or 1,
// Code generation (by index):
// General values:
// 0: whiteLeftRookMoved, 1: whiteRightRookMoved, 2: blackLeftRookMoved, 3: blackRightRookMoved 
// 4: whiteCanCastle, 5: blackCanCastle, 6: gameWon, 7: whiteTurn
// Piece values follow same as Enums found in DefaultValues.h

struct CodeHandler
{
    public:
    // Interprets board into code and stores it
    CodeHandler() = default;
    ~CodeHandler() = default;

    // Takes ChessGame object and converts relevant values to numbers to be read later
    std::string generateCode(ChessGame &cg)
    {
        std::string code;
        if (!cg.whiteLeftRookMoved) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.whiteRightRookMoved) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.blackLeftRookMoved) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.blackRightRookMoved) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.whiteCanCastle) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.blackCanCastle) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.gameWon) { code.push_back('0'); } else { code.push_back('1'); }
        if (!cg.whiteTurn) { code.push_back('0'); } else { code.push_back('1'); }
        code += std::to_string(cg.gameState);
        this->generateBoardCode(*cg.board, code);
        return code;
    }

    // Generates Evaluation->dataSet string for EngineAI to parse
    // Code is Evaluation->currentEval separated by period, followed by encoded version of <int, string> map
    std::string generateEvaluationCode(Evaluation &eval)
    {
        std::string code = eval.currentEval;
        code.push_back('.');
        auto it = eval.dataSet->begin();
        while (it != eval.dataSet->end())
        {
            code.push_back(it->first);
            code.push_back('.');
            code += it->second;
            code.push_back('.');
        }
        return code;
    }

    // Takes code and ChessGame as input, adjusts ChessGame based on values from code
    // if Code is not the same size as intended (265) no changes are made
    // Unexpectaed behavior will occur if string passed in is of same size but not same format. Try to avoid.
    void generateBoard(std::string &code, ChessGame &newGame)
    {
        if (code.size() == CODE_SIZE)
        {
            if (code[0]) { newGame.whiteLeftRookMoved = true; }
            if (code[1]) { newGame.whiteRightRookMoved = true; }
            if (code[2]) { newGame.blackLeftRookMoved = true; }
            if (code[3]) { newGame.blackRightRookMoved = true; }
            if (code[4]) { newGame.whiteCanCastle = true; }
            if (code[5]) { newGame.blackCanCastle = true; }
            if (code[6]) { newGame.gameWon = true; }
            if (code[7]) { newGame.whiteTurn = true; }
            newGame.gameState = code[8];
            this->codeToBoard(code, newGame);

        }
        else
        {
            std::cout << "Error generating board" << "\n";
        }

    }

    protected:
    // Loops through code and places pieces on board based on code
    void codeToBoard(std::string &code, ChessGame &cg)
    {
        std::cout << "in codetoboard function" << code << "\n";
        int_fast8_t y = 0;
        int_fast8_t x = 0;
        std::string pieceCode;
        // Parses code in chunks of 4 (9 * (4 * 64) = 265 (CODE_SIZE))
        for (int i = 9; i < CODE_SIZE; i += 4)
        {
            pieceCode.clear();
            y = toDigit(code[i]);
            x = toDigit(code[i + 1]);
            pieceCode.push_back(code[i + 2]);
            pieceCode.push_back(code[i + 3]);
            switch (std::stoi(pieceCode))
            {
                    case EmptySpace:
                    (*cg.board)[y][x] = EmptySpace;
                    break;

                    case WhitePawn:
                    (*cg.board)[y][x] = WhitePawn;
                    break;

                    case UnmovedWhitePawn:
                    (*cg.board)[y][x] = UnmovedWhitePawn;
                    break;

                    case WhiteRook:
                    (*cg.board)[y][x] = WhiteRook;
                    break;

                    case WhiteKnight:
                    (*cg.board)[y][x] = WhiteKnight;
                    break;

                    case WhiteBishop:
                    (*cg.board)[y][x] = WhiteBishop;
                    break;

                    case WhiteQueen:
                    (*cg.board)[y][x] = WhiteQueen;
                    break;

                    case WhiteKing:
                    (*cg.board)[y][x] = WhiteKing;
                    break;

                    case BlackPawn:
                    (*cg.board)[y][x] = BlackPawn;
                    break;

                    case UnmovedBlackPawn:
                    (*cg.board)[y][x] = UnmovedBlackPawn;
                    break;

                    case BlackRook:
                    (*cg.board)[y][x] = BlackRook;
                    break;

                    case BlackKnight:
                    (*cg.board)[y][x] = BlackKnight;
                    break;

                    case BlackBishop:
                    (*cg.board)[y][x] = BlackBishop;
                    break;

                    case BlackQueen:
                    (*cg.board)[y][x] = BlackQueen;
                    break;

                    case BlackKing:
                    (*cg.board)[y][x] = BlackQueen;
                    break;

                    default:
                    std::cout << "Invalid input passed into code converter" << "\n";
                    break;
            }
        }
    }

    // Takes Board and adds Board data onto original code string
    void generateBoardCode(std::array<std::array<int_fast8_t, ROWS>, COLUMNS> &board, std::string& code)
    {
        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLUMNS; x++)
            {
                code += std::to_string(y);
                code += std::to_string(x);
                switch (board[y][x])
                {
                    case EmptySpace:
                    code += "00";
                    break;

                    case WhitePawn:
                    code += "01";
                    break;

                    case UnmovedWhitePawn:
                    code += "02";
                    break;

                    case WhiteRook:
                    code += "03";
                    break;

                    case WhiteKnight:
                    code += "04";
                    break;

                    case WhiteBishop:
                    code += "05";
                    break;

                    case WhiteQueen:
                    code += "06";
                    break;

                    case WhiteKing:
                    code += "07";
                    break;

                    case BlackPawn:
                    code += "08";
                    break;

                    case UnmovedBlackPawn:
                    code += "09";
                    break;

                    case BlackRook:
                    code += "10";
                    break;

                    case BlackKnight:
                    code += "11";
                    break;

                    case BlackBishop:
                    code += "12";
                    break;

                    case BlackQueen:
                    code += "13";
                    break;

                    case BlackKing:
                    code += "14";
                    break;
                }
            }
        }
    }
};