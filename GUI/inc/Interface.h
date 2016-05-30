
#ifndef _GUI_H
#define _GUI_H

const int NROBOT = 4;
const int SZ = 20;
const int CN = 20; // #points to draw circle
const double PI = acos(-1);

class PackagesManager {
public:
    char data[SZ][100];
    int head, rail;


public:
    PackagesManager();
    ~PackagesManager();

    int prev(int iter);
    void push(const char *s, int sz);
};

#endif
