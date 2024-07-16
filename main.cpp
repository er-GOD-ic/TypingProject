#include <curses.h>
#include <stdlib.h>
#include <cstring>
#include <cctype>
#include <chrono>
#include <thread>
#include <time.h>
#include "game.h"
#include "gm.h"

int main() {
    // rand の時刻初期化
    srand(static_cast<unsigned int>(time(nullptr)));
    Start();
    return 0;
}

void Start() {
    // ゲーム開始
    isPlaying = true;

    // cursesの初期化
    initscr();
    // カーソルを非表示
    curs_set(0);
    // エコーを削除
    noecho();
    // ボードの描画
    drawBoard();
    setSubjects();
    // 画面を更新して待機
    refresh();
    Update();
}

void End(bool quickEnd) {
    isPlaying = false;
    nodelay(stdscr, false);
    curs_set(1);
    
    if(quickEnd)
        end();
    else {
        mvprintw(1, colSize + 4, "END GAME??   y/n : ");
        // ユーザ入力の待機
        if(getch() == 'y'){
            end();
        }
        else 
            cancel();
    }
    return;
}

void Update() {
    nodelay(stdscr, true);
    while (isPlaying) {
        refresh();
        input = getch();
        if(input != lastInput);
            mvprintw(2, colSize + 4, "%d", input);
            switch (input) {
                // quit game
                case Keycode.esc:
                    End();
                    break;
                // set new subject
                case Keycode.tab:
                    setSubjects();
                    break;
                default : 
                    if(input != -1)
                        playerInOut(input);
                    break;
            }
        lastInput = input;
        std::this_thread::sleep_for(std::chrono::seconds(1/fps));
        //show current fps
        if(currentFrame > 99999999) {
            currentFrame = 0;
            currentFrameUpward++;
        }
        else
            currentFrame++;
        mvprintw(6, colSize + 4, "%d", currentFrameUpward);
        printw(" : %d", currentFrame);
    }
}


/*
    game code
*/

void playerInOut(int input) {
    setcsa :
        // this means current subject alphabet
        char csa = *(subjects[cs] + charactor);
        mvprintw(3, colSize + 4, "next charactor : %c", csa);
    
    // draw player input
    if(isalpha(input)) {
        inputAlpha = static_cast<int>(input);
        mvprintw(4, colSize + 4, "your iput : %c", inputAlpha);
        if(csa == inputAlpha) {
            mvprintw(3, 2 + charactor, "%c", csa);
            charactor++;
            goto setcsa;
        }
        if(charactor == charactorSize) {
            setSubjects();
        }
    }
    return;
}

void drawBoard() {
    // draw main board
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            if(board[row][col] == 1) 
                drawSqare(row, col);
            else 
                mvprintw(row, col," ");
        }
    }
    
    // draw user infomation
    mvprintw(1, colSize + 4, "ESC : end game");

    // dev infomation
    move(rowSize + 3, 0);
    printw("///this is alpha test///\n");
    printw("Ver.%s\n", version);
    printw("---------------------------------------------\n");
    printw("///BUG LEPORT///\n");
    printw("-when input same characters, you can enter them all at once");
}

void drawSqare(int row ,int col){
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    attron((COLOR_PAIR(1)));
    mvprintw(row, col, " ");
    attroff(COLOR_PAIR(1));
}

void setSubjects() {
    drawBoard();
    lastcs = cs;
    charactor = 0;
    recreate :
        cs = rand() % sizeof(subjects) / sizeof(subjects[0]);
    if (lastcs == cs)
        goto recreate;
    charactorSize = strlen(subjects[cs]);
    mvprintw(5, colSize + 4, "charactorSize : %d", charactorSize);
    mvprintw(1,2,"%s", subjects[cs]);
}