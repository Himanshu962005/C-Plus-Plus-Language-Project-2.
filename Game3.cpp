#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <climits>
#include <fstream>
#include <windows.h>
using namespace std;

int HumanWins = 0, AIwins = 0, Draws = 0;
vector<pair<int, int>> winningCells;

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

void clearScreen()
{
    system("cls");
}

void beepWin() { Beep(1000, 500); }
void beepDraw() { Beep(500, 300); }

void saveScore()
{
    ofstream fout("score.txt");
    fout << HumanWins << " " << AIwins << " " << Draws;
}

void loadScore()
{
    ifstream fin("score.txt");
    if (fin)
        fin >> HumanWins >> AIwins >> Draws;
}

void printBoard(const vector<vector<char>> &board)
{
    int n = board.size();
    cout << "\n  ";
    for (int j = 0; j < n; j++)
        cout << j + 1 << " ";
    cout << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < n; j++)
        {
            bool isWinCell = false;
            for (auto &p : winningCells)
                if (p.first == i && p.second == j)
                    isWinCell = true;

            char c = board[i][j];
            string color = (c == 'X') ? BLUE : (c == 'O') ? RED
                                                          : "";
            if (isWinCell)
                color = GREEN;
            cout << color << (c == ' ' ? '.' : c) << RESET << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

bool checkWin(const vector<vector<char>> &board, char player, int k)
{
    winningCells.clear();
    int n = board.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != player)
                continue;

            // Horizontal
            if (j + k <= n)
            {
                bool win = true;
                vector<pair<int, int>> cells;
                for (int x = 0; x < k; x++)
                {
                    if (board[i][j + x] != player)
                    {
                        win = false;
                        break;
                    }
                    cells.emplace_back(i, j + x);
                }
                if (win)
                {
                    winningCells = cells;
                    return true;
                }
            }

            // Vertical
            if (i + k <= n)
            {
                bool win = true;
                vector<pair<int, int>> cells;
                for (int x = 0; x < k; x++)
                {
                    if (board[i + x][j] != player)
                    {
                        win = false;
                        break;
                    }
                    cells.emplace_back(i + x, j);
                }
                if (win)
                {
                    winningCells = cells;
                    return true;
                }
            }

            // Diagonal down-right
            if (i + k <= n && j + k <= n)
            {
                bool win = true;
                vector<pair<int, int>> cells;
                for (int x = 0; x < k; x++)
                {
                    if (board[i + x][j + x] != player)
                    {
                        win = false;
                        break;
                    }
                    cells.emplace_back(i + x, j + x);
                }
                if (win)
                {
                    winningCells = cells;
                    return true;
                }
            }

            // Diagonal up-right
            if (i - k + 1 >= 0 && j + k <= n)
            {
                bool win = true;
                vector<pair<int, int>> cells;
                for (int x = 0; x < k; x++)
                {
                    if (board[i - x][j + x] != player)
                    {
                        win = false;
                        break;
                    }
                    cells.emplace_back(i - x, j + x);
                }
                if (win)
                {
                    winningCells = cells;
                    return true;
                }
            }
        }
    }
    return false;
}

bool isMovesLeft(const vector<vector<char>> &board)
{
    for (auto &row : board)
        for (char c : row)
            if (c == ' ')
                return true;
    return false;
}

int minimax(vector<vector<char>> &board, int depth, bool isMaximizing, int k)
{
    if (checkWin(board, 'O', k))
        return 10 - depth;
    if (checkWin(board, 'X', k))
        return -10 + depth;
    if (!isMovesLeft(board))
        return 0;

    if (isMaximizing)
    {
        int bestVal = INT_MIN;
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board.size(); j++)
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    bestVal = max(bestVal, minimax(board, depth + 1, false, k));
                    board[i][j] = ' ';
                }
        return bestVal;
    }
    else
    {
        int bestVal = INT_MAX;
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board.size(); j++)
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    bestVal = min(bestVal, minimax(board, depth + 1, true, k));
                    board[i][j] = ' ';
                }
        return bestVal;
    }
}

pair<int, int> findBestMove(vector<vector<char>> &board, int k)
{
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board.size(); j++)
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int moveVal = minimax(board, 0, false, k);
                board[i][j] = ' ';
                if (moveVal > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
    return bestMove;
}

pair<int, int> getRandomMove(const vector<vector<char>> &board)
{
    vector<pair<int, int>> moves;
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board.size(); j++)
            if (board[i][j] == ' ')
                moves.emplace_back(i, j);
    if (!moves.empty())
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, moves.size() - 1);
        return moves[dist(gen)];
    }
    return {-1, -1};
}

void playGame(int n, int k, bool aiHardMode)
{
    vector<vector<char>> board(n, vector<char>(n, ' '));
    bool humanTurn = true;

    while (true)
    {
        clearScreen(); // ✅ Clear screen before every move
        printBoard(board);

        if (humanTurn)
        {
            int r, c;
            cout << "Your move (row col) : ";
            cin >> r >> c;
            r--;
            c--;
            if (r < 0 || r >= n || c < 0 || c >= n || board[r][c] != ' ')
            {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[r][c] = 'X';
        }
        else
        {
            pair<int, int> move = aiHardMode ? findBestMove(board, k) : getRandomMove(board);
            if (move.first != -1)
            {
                board[move.first][move.second] = 'O';
                cout << "AI plays: " << (move.first + 1) << " " << (move.second + 1) << "\n";
            }
        }

        if (checkWin(board, humanTurn ? 'X' : 'O', k))
        {
            clearScreen(); // ✅ Clear before win message
            printBoard(board);
            if (humanTurn)
            {
                cout << "You win!\n";
                HumanWins++;
                beepWin();
            }
            else
            {
                cout << "AI wins!\n";
                AIwins++;
                beepWin();
            }
            saveScore();
            cout << "Scoreboard - You (X) : " << HumanWins
                 << " | AI (O) : " << AIwins
                 << " | Draws : " << Draws << "\n\n";
            break;
        }
        else if (!isMovesLeft(board))
        {
            clearScreen(); // ✅ Clear before draw message
            printBoard(board);
            cout << "It's a draw.\n";
            Draws++;
            beepDraw();
            saveScore();
            cout << "Scoreboard - You (X) : " << HumanWins
                 << " | AI (O) : " << AIwins
                 << " | Draws : " << Draws << "\n\n";
            break;
        }

        humanTurn = !humanTurn;
    }
}

int main()
{
    system("cls");
    loadScore();
    cout << "Tic Tac Toe (Console Edition)";
    while (true)
    {
        int n, k;
        cout << "\nBoard size (N > 2) : ";
        cin >> n;
        cout << "Win condition (K in a row, K <= N) : ";
        cin >> k;
        if (n <= 2 || k < 1 || k > n)
        {
            cout << "Invalid settings. Please try again.\n";
            continue;
        }
        cout << "AI difficulty (1 = Easy, 2 = Hard) : ";
        int diff;
        cin >> diff;
        bool aiHard = (diff == 2);
        while (true)
        {
            playGame(n, k, aiHard);
            int choice;
            cout << "1 = Play again, 2 = Change settings, 3 = Exit : ";
            cin >> choice;
            clearScreen();
            if (choice == 1)
                continue;
            else if (choice == 2)
                break;
            else
            {
                cout << "\nFinal Scoreboard - You (X) : " << HumanWins
                     << " | AI (O) : " << AIwins
                     << " | Draws : " << Draws << "\n";
                return 0;
            }
        }
    }
    saveScore();
    getch();
    return 0;
}