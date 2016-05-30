#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdio>

#include "../inc/Interface.h"

PackagesManager::PackagesManager()
{
    this->head = this->rail = 0;
}

PackagesManager::~PackagesManager()
{
    //add code here.

}

int PackagesManager::prev(int iter) {
    iter = (iter + SZ - 1) % SZ;
    return iter;
}

void PackagesManager::push(const char *s, int sz) {
    for (int i = 0; i < sz; ++ i) {
        data[rail][i] = s[i];
    }
    data[rail][sz] = 0;
    rail = (rail + 1) % SZ;
    if (rail == head) head = (head + 1) % SZ;
}

