#include "Tetris.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace chrono;
typedef vector<vector<int>> Shape;
const vector<Shape> SHAPES = {
    {{1, 1, 1, 1}},                          // I-shape
    {{1, 1}, {1, 1}},                        // O-shape
    {{0, 1, 0}, {1, 1, 1}},                  // T-shape
    {{1, 1, 0}, {0, 1, 1}},                  // S-shape
    {{0, 1, 1}, {1, 1, 0}},                  // Z-shape
    {{1, 0, 0}, {1, 1, 1}},                  // J-shape
    {{0, 0, 1}, {1, 1, 1}},                  // L-shape
};


Tetris::Tetris() : currentBlock(SHAPES[rand() % SHAPES.size()]), gameOver(false), score(0), dropSpeed(0.5) {
    srand((time(0)));
    lastUpdate = steady_clock::now();
}

//Policzenie zdobytych punktów na podstawie wyczyszczonych na raz linii
int Tetris::scorePerLines(int linesCleared){
    if(linesCleared==0){
        return 0;
    }else if(linesCleared==1){
        return 1;
    }else {
        return linesCleared * scorePerLines(linesCleared-1);
    }
}

//Potwierdzenie opusczenia gry
void Tetris::quit() {
    while (1) {
        cout << "Czy napewno chcesz wyjsc? [T/N]\n";
        char choice;
        cin >> choice;
        if (choice == 'T') {
            gameOver = true;
            break;
        } else if (choice == 'N') {
            break;
        } else {
            cout << "Nieprawidlowe dane\n";
        }
    }
}

//Stworzenie nowego bloku
void Tetris::spawnBlock() {
    currentBlock = Block(SHAPES[rand() % SHAPES.size()]);
    if (!board.canPlace(currentBlock)) {
        gameOver = true;
    }
}

//Przesunięcie bloku w wyznaczone miejsce oraz sprawdzenie czy jest taka możliwość i czy linia została zapełniona
void Tetris::moveBlock(int dx, int dy) {
    currentBlock.x += dx;
    currentBlock.y += dy;
    if (!board.canPlace(currentBlock)) {
        currentBlock.x -= dx;
        currentBlock.y -= dy;
        if (dy > 0) {
            board.place(currentBlock);
            int linesCleared = board.clearLines();
            score += scorePerLines(linesCleared);
            if(endlessMode){
                dropSpeed-=0.01;
            }
            spawnBlock();
        }
    }
}

//Obrócenie bloku i sprawdzenie czy można go w tej formie umieścić
void Tetris::rotateBlock() {
    currentBlock.rotate();
    if (!board.canPlace(currentBlock)) {
        for (int i = 0; i < 3; ++i) {
            currentBlock.rotate();
        }
    }
}

//Ustawienie poziomu trudności/szybkości opadania bloków
void Tetris::setDifficulty() {
    bool correct;
    endlessMode = false;
    do{
    correct=true;
    char choice;
    cout << "Wybierz poziom trudnosci:\n";
    cout << "1. Latwy\n2. Sredni\n3. Trudny\n4. Endless\n";
    cin >> choice;

    switch (choice) {
        case '1': dropSpeed = 0.8; break; 
        case '2': dropSpeed = 0.5; break;
        case '3': dropSpeed = 0.3; break;
        case '4': dropSpeed = 0.8; endlessMode=true; break;
        default: cout << "Nieprawidlowy wybor.\n"; correct = false; break; 
    }
    }while(!correct);
}

//Wypisanie tabeli wyników, posortowanie wyników od najlepszego
void Tetris::showHighScores() {
    ifstream file("highscores.txt");
    string line;
    vector<tuple<string, int, string>> scores;

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int score;
        string date;
        
        ss >> name >> score >> ws;
        getline(ss, date);  
        scores.push_back({name, score, date});
    }

    sort(scores.begin(), scores.end(), [](const tuple<string, int, string>& a, const tuple<string, int, string>& b) {
        return get<1>(a) > get<1>(b);
    });

    cout << "Tabela wynikow:\n";
    for (int i = 0; i < min(10, static_cast<int>(scores.size())); ++i) {
        cout << get<0>(scores[i]) << " " << get<1>(scores[i]) << " " << get<2>(scores[i]) << '\n';
    }
}

//Zapisanie wyniku do tabeli, pod warunkiem że gracz nie ma już takiego wyniku
void Tetris::saveHighScore() {
    ifstream file("highscores.txt");
    string line;
    vector<pair<string, int>> scores;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int score;
        string date;
        ss >> name >> score >> date;
        scores.push_back({name, score});

        if (name == playerName && score == this->score) {
            found = true;
            break;
        }
    }

    if (!found && score) {
        auto now = system_clock::now();
        auto time = system_clock::to_time_t(now);
        tm* tm_ptr = localtime(&time);

        char dateStr[20];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", tm_ptr);

        ofstream file("highscores.txt", ios::app);
        file << playerName << " " << score << " " << dateStr << '\n';
    }
    score=0;
}

//Obsługa gry, wyśweitlanie menu, główna pętla
void Tetris::run() {
    int choice;
    cout << "Podaj swoj nick: ";
    cin >> playerName;

    while (!gameOver) {
        cout << "Menu:\n";
        cout << "1. Graj\n";
        cout << "2. Ustawienia\n";
        cout << "3. Tabela wynikow\n";
        cout << "4. Wyjdz\n";
        cin >> choice;

        switch (choice) {
            case 1:
                spawnBlock();
                while (!gameOver) {
                    steady_clock::time_point now = steady_clock::now();
                    duration<double> elapsed_seconds = duration_cast<duration<double>>(now - lastUpdate);

                    if (elapsed_seconds.count() >= dropSpeed) {
                        moveBlock(0, 1);
                        lastUpdate = steady_clock::now();
                        cout << "Score: " << score << '\n';
                        cout << string(20, '-') << '\n';
                        board.print(&currentBlock);
                        cout << "Przyciski: a (lewo), d (prawo), s (w dol), w (obroc), q (wyjdz)\n";
                    }

                    if (kbhit()) {
                        char command = _getch();
                        switch (command) {
                            case 'a': moveBlock(-1, 0); break;
                            case 'd': moveBlock(1, 0); break;
                            case 's': moveBlock(0, 1); break;
                            case 'w': rotateBlock(); break;
                            case 'q': quit(); break;
                            default: cout << "Nieprawidlowy ruch!\n";
                        }
                    }
                }
                board.clearGrid();
                saveHighScore();
                gameOver = false;
                endlessMode = false;
                break;
            case 2:
                setDifficulty();
                break;
            case 3:
                showHighScores();
                break;
            case 4:
                gameOver = true;
                break;
            default:
                cout << "Nieprawidlowy wybor.\n";
        }
    }
}
