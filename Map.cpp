//
// Created by Gentoo Huentoo on 2019-05-12.
//

#include "Map.h"

Map::Map(int w, int h) : _w(w), _h(h) {
    _map = new int *[w];
    for (int i = 0; i < w; ++i) {
        _map[i] = new int[h];
        for (int j = 0; j < h; ++j) {
            _map[i][j] = 0;
        }
    }
}

void Map::set(int x, int y) {
    if (x < 0 || x >= _w || y < 0 || y >= _h)
        throw std::out_of_range("x and y is out of map range");

    _map[x][y] = 1;
}

void Map::update() {
    int **temp = new int *[_w];
    for (int i = 0; i < _w; ++i) {
        temp[i] = new int[_h];
        for (int j = 0; j < _h; ++j) {
            temp[i][j] = rule(i, j);
        }
    }

    for (int i = 0; i < _w; ++i)
        delete[] _map[i];
    delete[] _map;

    _map = temp;
}

void Map::reset(int x, int y) {
    if (x < 0 || x >= _w || y < 0 || y >= _h)
        throw std::out_of_range("x and y is out of map range");

    _map[x][y] = 0;
}

int Map::rule(int x, int y) {
    if (_map[x][y])
        return rule_alive(x, y);
    else
        return rule_dead(x, y);
}

int Map::rule_dead(int _x, int _y) {
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int x = _x + i;
            int y = _y + j;
            if (x < 0 || x >= _w || y < 0 || y >= _h)
                continue;

            count += _map[x][y];
        }
    }

    return count == 3;
}

int Map::rule_alive(int _x, int _y) {
    int count = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int x = _x + i;
            int y = _y + j;
            if (x < 0 || x >= _w || y < 0 || y >= _h || (x == _x && y == _y))
                continue;

            count += _map[x][y];
        }
    }

    return count == 2 || count == 3;
}

std::string Map::print() {
    std::stringstream res;
    for (int i = 0; i < _h; ++i) {
        for (int j = 0; j < _w; ++j) {
            res << _map[j][i];
        }
        res << '\n';
    }

    return res.str();
}

int Map::get_w() const {
    return _w;
}

int Map::get_h() const {
    return _h;
}

void Map::random_fill() {
    for (int i = 0; i < _w; ++i) {
        for (int j = 0; j < _h; ++j)
            _map[i][j] = rand() % 2;
    }
}

void Map::switch_cell(int x, int y) {
    _map[x][y] = !_map[x][y];
}
