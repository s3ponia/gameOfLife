//
// Created by Gentoo Huentoo on 2019-05-12.
//

#ifndef GAME_LIFE_MAP_H
#define GAME_LIFE_MAP_H

#include <vector>
#include <string>
#include <sstream>

class Map {
    int** _map;
    int _w;
    int _h;
public:
    int get_w() const;

    int get_h() const;

private:

    int rule_dead(int x, int y);

    int rule_alive(int x, int y);

    int rule(int x, int y);
public:
    Map(int w, int h);

    void set(int x, int y);

    void reset(int x, int y);

    void switch_cell(int, int);

    void random_fill();

    void update();

    std::string print();
};


#endif //GAME_LIFE_MAP_H
