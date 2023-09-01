#include<bits/stdc++.h>
using namespace std;

enum pieces{Empty, WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing, BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing, Passant};

pieces board[8][8];
int evaluation = 0;

int calcEval(int n)
{
    if(n == 1) return 1;
    if(n == 2) return 3;
    if(n == 3) return 3;
    if(n == 4) return 5;
    if(n == 5) return 9;
}

int LtoN(char c)
{
    if(c == 'a') return 0;
    if(c == 'b') return 1;
    if(c == 'c') return 2;
    if(c == 'd') return 3;
    if(c == 'e') return 4;
    if(c == 'f') return 5;
    if(c == 'g') return 6;
    if(c == 'h') return 7;
}

void print()
{
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            cout<<board[j][i]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void setupBoard()
{
    board[0][0] = WhiteRook;
    board[1][0] = WhiteKnight;
    board[2][0] = WhiteBishop;
    board[3][0] = WhiteQueen;
    board[4][0] = WhiteKing;
    board[5][0] = WhiteBishop;
    board[6][0] = WhiteKnight;
    board[7][0] = WhiteRook;

    for(int i = 0; i < 8; i++)
    {
        board[i][1] = WhitePawn;
    }

    board[0][7] = BlackRook;
    board[1][7] = BlackKnight;
    board[2][7] = BlackBishop;
    board[3][7] = BlackQueen;
    board[4][7] = BlackKing;
    board[5][7] = BlackBishop;
    board[6][7] = BlackKnight;
    board[7][7] = BlackRook;

    for(int i = 0; i < 8; i++)
    {
        board[i][6] = BlackPawn;
    }
}

int main()
{
    bool iswhite = true;

    setupBoard();

    print();

    pair<int, int> EnPassant = {-1, -1};

    string s;
    while(cin>>s)
    {
        if(s == "O-O")
        {
            if(iswhite)
            {
                board[4][0] = Empty;
                board[6][0] = WhiteKing;
                board[7][0] = Empty;
                board[5][0] = WhiteRook;
            }
            else
            {
                board[4][7] = Empty;
                board[6][7] = BlackKing;
                board[7][7] = Empty;
                board[5][7] = BlackRook;
            }
        }
        else if(s == "O-O-O")
        {
            if(iswhite)
            {
                board[4][0] = Empty;
                board[2][0] = WhiteKing;
                board[0][0] = Empty;
                board[3][0] = WhiteRook;
            }
            else
            {
                board[4][7] = Empty;
                board[2][7] = BlackKing;
                board[0][7] = Empty;
                board[3][7] = BlackRook;
            }
        }
        else
        {
            int sp1 = LtoN(s[0]);
            int sp2 = s[1]-'0'-1;
            int fp1 = LtoN(s[2]);
            int fp2 = s[3]-'0'-1;
            if(board[fp1][fp2] != Empty)
            {
                board[fp1][fp2] = board[sp1][sp2];
                board[sp1][sp2] = Empty;
                if(board[fp1][fp2] == Passant)
                {
                    if(fp2 == 5) board[fp1][fp2-1] = Empty;
                    else board[fp1][fp2+1] = Empty;
                }
            }
            else
            {
                if((board[sp1][sp2] == WhitePawn || board[sp1][sp2] == BlackPawn) && abs(fp2-sp2) == 2)
                {
                    board[sp1][sp2+1] = Passant;
                    EnPassant = {sp1, sp2+1};
                }
                board[fp1][fp2] = board[sp1][sp2];
                board[sp1][sp2] = Empty;
            }
        }

        print();
        iswhite = !iswhite;
    }
    return 0;
}
