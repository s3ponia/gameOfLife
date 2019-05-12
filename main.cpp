#include <iostream>
#include <ncurses.h>
#include "Map.h"

void initMap(Map map) {
    int x = 0;
    int y = 0;

    bool runnable = true;
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    raw();
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    //INFO
    {
        int w, h;
        getmaxyx(stdscr, h, w);
        mvaddstr(h/2-8,w/2-10,"\'s\': switch cell\n");
        mvaddstr(h/2-7,w/2-10,"\'1\': set cell alive\n");
        mvaddstr(h/2-6,w/2-10,"\'0\': set cell dead\n");
        mvaddstr(h/2-5,w/2-10,"KEY_LEFT: move left\n");
        mvaddstr(h/2-4,w/2-10,"KEY_UP: move up\n");
        mvaddstr(h/2-3,w/2-10,"KEY_DOWN: move dodwn\n");
        mvaddstr(h/2-2,w/2-10,"KEY_RIGHT: move right\n");
        mvaddstr(h/2-1,w/2-10,"\'q\': exit initialization map mode\n");
        refresh();
        getchar();
    }

    while (runnable) {
        int temp_y = 0;
        int temp_x = 0;
        move(0, 0);
        move(0, 0);
        const char *string = map.print().data();
        size_t len = strlen(string);
        for (size_t i = 0; i < len; ++i) {
            if (string[i] == '\n') {
                addch('\n');
                ++temp_y;
                temp_x = 0;
            } else {
                if (y == temp_y && x == temp_x) {
                    if (string[i] == '1') {
                        attron(COLOR_PAIR(1));
                        addch('*' | A_BLINK);
                        attroff(COLOR_PAIR(1));
                    } else {
                        attron(COLOR_PAIR(0));
                        addch('0' | A_BLINK);
                        attroff(COLOR_PAIR(0));
                    }
                } else if (string[i] == '1') {
                    attron(COLOR_PAIR(1));
                    addch('*');
                    attroff(COLOR_PAIR(1));
                } else {
                    attron(COLOR_PAIR(0));
                    addch('0');
                    attroff(COLOR_PAIR(0));
                }
                ++temp_x;
            }
        }
        switch (getch()) {
            case 's':
                map.switch_cell(x,y);
                break;
            case '1':
                map.set(x, y);
                break;
            case '0':
                map.reset(x, y);
                break;
            case KEY_LEFT:
                if (x)
                    --x;
                break;
            case KEY_RIGHT:
                if (x < map.get_w())
                    ++x;
                break;
            case KEY_DOWN:
                if (y < map.get_h())
                    ++y;
                break;
            case KEY_UP:
                if (y)
                    --y;
                break;
            case 'q':
                runnable = false;
                break;
            default:
                break;
        }
    }
}

int main() {
    initscr();
    int w, h;
    getmaxyx(stdscr, h, w);
    Map map(w - 1, h - 1);
    //map.random_fill();

    initMap(map);
    clear();
    refresh();

    start_color();
    curs_set(0);
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    halfdelay(5);
    while (getch() != 'q') {
        move(0, 0);
        const char *string = map.print().data();
        size_t len = strlen(string);
        for (size_t i = 0; i < len; ++i) {
            if (string[i] == '\n')
                addch('\n');
            else {
                if (string[i] == '1') {
                    attron(COLOR_PAIR(1));
                    addch('*');
                    attroff(COLOR_PAIR(1));
                } else {
                    attron(COLOR_PAIR(0));
                    addch('0');
                    attroff(COLOR_PAIR(0));
                }
            }
        }
        refresh();
        map.update();
    }

    endwin();

    return 0;
}