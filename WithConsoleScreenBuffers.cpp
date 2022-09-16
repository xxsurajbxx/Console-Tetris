#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
using namespace chrono;
using namespace chrono_literals;

char screen[120*18] = {' '};
auto start = high_resolution_clock::now();
int score=0;
int lvl=0;
char map[17][13] = {
    {'+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '+'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

class tetromino {
    private:
    int orientation;
    char type;
    bool cleared;
    public:
    int x, y;
    tetromino() {
        orientation=0;
        x=5;
        y=1;
        srand(time(0));
        switch(rand()%7) {
            case 0:
                type = 's';
                break;
            case 1:
                type = 'l';
                break;
            case 2:
                type = 'T';
                break;
            case 3:
                type = 'L';
                break;
            case 4:
                type = 'J';
                break;
            case 5:
                type = 'S';
                break;
            case 6:
                type = 'Z';
                break;
        }
    }
    ~tetromino() {
        orientation=0;
        x=5;
        y=1;
    }
    bool collision() {
        if(type=='Z') {
            if(orientation==0||orientation==2) {
                if(map[y+2][x]!=' '||map[y+1][x-1]!=' '||map[y+2][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1||orientation==3) {
                if(map[y+1][x]!=' '||map[y+2][x-1]!=' ') {
                    return true;
                }
                return false;
            }
        }
        if(type=='S') {
            if(orientation==0||orientation==2) {
                if(map[y+1][x-1]!=' '||map[y+1][x]!=' '||map[y][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1||orientation==3) {
                if(map[y+1][x-1]!=' '||map[y+2][x]!=' ') {
                    return true;
                }
                return false;
            }
        }
        if(type=='J') {
            if(orientation==0) {
                if(map[y+2][x]!=' '||map[y+2][x-1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1) {
                if(map[y+1][x]!=' '||map[y+1][x+1]!=' '||map[y+1][x-1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==2) {
                if(map[y+2][x]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==3) {
                if(map[y+2][x+1]!=' ') {
                    return true;
                }
                return false;
            }
        }
        if(type=='L') {
            if(orientation==0) {
                if(map[y+2][x]!=' '||map[y+2][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1){
                if(map[y+2][x-1]!=' '||map[y+1][x]!=' '||map[y+1][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==2){
                if(map[y+2][x]!=' '||map[y][x-1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==3){
                if(map[y+1][x]!=' '||map[y+1][x-1]!=' '||map[y+1][x+1]!=' ') {
                    return true;
                }
                return false;
            }
        }
        if(type=='T') {
            if(orientation==0) {
                if(map[y+1][x]!=' '||map[y+1][x-1]!=' '||map[y+1][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1) {
                if(map[y+2][x]!=' '||map[y+1][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==2) {
                if(map[y+2][x]!=' '||map[y+1][x+1]!=' '||map[y+1][x-1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==3) {
                if(map[y+2][x]!=' '||map[y+1][x-1]!=' ') {
                    return true;
                }
                return false;
            }
        }
        if(type=='s') {
            if(map[y+1][x]!=' '||map[y+1][x-1]!=' ') {
                return true;
            }
            return false;
        }
        if(type=='l') {
            if(orientation==0 || orientation==2) {
                if(map[y+1][x]!=' '||map[y+1][x-1]!=' '||map[y+1][x-2]!=' '||map[y+1][x+1]!=' ') {
                    return true;
                }
                return false;
            }
            if(orientation==1 || orientation==3) {
                if(map[y+3][x]!=' ') {
                    return true;
                }
                return false;
            }
        }
    }
    void turnRight() {
        if(type=='Z') {
            if(((orientation==0||orientation==2)&&(map[y-1][x]==' '&&map[y+1][x-1]==' '))||((orientation==1||orientation==3)&&(map[y+1][x]==' '&&map[y+1][x+1]==' '))) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
        if(type=='S') {
            if(((orientation==0||orientation==2)&&(map[y-1][x-1]==' '&&map[y+1][x]==' '))||((orientation==1||orientation==3)&&(map[y-1][x]==' '&&map[y-1][x+1]==' '))) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
        if(type=='J') {
            if((orientation==0&&map[y][x-1]==' '&&map[y][x+1]==' '&&map[y-1][x-1]==' ')||(orientation==1&&map[y+1][x]==' '&&map[y-1][x]==' '&&map[y-1][x+1]==' ')||(orientation==2&&map[y][x+1]==' '&&map[y][x-1]==' '&&map[y+1][x+1]==' ')||(orientation==3&&map[y-1][x]==' '&&map[y+1][x]==' '&&map[y+1][x-1]==' ')) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
        if(type=='L') {
            if((orientation==0&&map[y+1][x-1]==' '&&map[y][x-1]==' '&&map[y][x+1]==' ')||(orientation==1&&map[y-1][x-1]==' '&&map[y-1][x]==' '&&map[y+1][x]==' ')||(orientation==2&&map[y-1][x+1]==' '&&map[y][x+1]==' '&&map[y][x-1]==' ')||(orientation==3&&map[y+1][x+1]==' '&&map[y+1][x]==' '&&map[y-1][x]==' ')) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
        if(type=='T') {
            if((orientation==0&&map[y+1][x]==' ')||(orientation==1&&map[y][x-1]==' ')||(orientation==2&&map[y-1][x]==' ')||(orientation==3&&map[y][x+1]==' ')) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
        if(type=='s') {
            return;
        }
        if(type=='l') {
            if(((orientation==0||orientation==2)&&map[y+2][x]==' '&&map[y-1][x]==' '&&map[y+1][x]==' ')||((orientation==1||orientation==3)&&map[y][x-1]==' '&&map[y][x-2]==' '&&map[y][x+1]==' ')) {
                clear();
                if(orientation==3) {
                    orientation=0;
                }
                else {
                    orientation++;
                }
                return;
            }
        }
    }
    void turnLeft() {
        if(type=='Z') {
            turnRight();
        }
        if(type=='S') {
            turnRight();
        }
        if(type=='J') {
            if((orientation==0&&map[y][x+1]==' '&&map[y][x-1]==' '&&map[y+1][x+1]==' ')||(orientation==1&&map[y-1][x]==' '&&map[y+1][x]==' '&&map[y+1][x-1]==' ')||(orientation==2&&map[y][x-1]==' '&&map[y][x+1]==' '&&map[y-1][x-1]==' ')||(orientation==3&&map[y+1][x]==' '&&map[y-1][x]==' '&&map[y-1][x+1]==' ')) {
                clear();
                if(orientation==0) {
                    orientation=3;
                }
                else {
                    orientation--;
                }
                return;
            }
        }
        if(type=='L') {
            if((orientation==0&&map[y-1][x+1]==' '&&map[y][x+1]==' '&&map[y][x-1]==' ')||(orientation==1&&map[y+1][x+1]==' '&&map[y+1][x]==' '&&map[y-1][x]==' ')||(orientation==2&&map[y+1][x-1]==' '&&map[y][x-1]==' '&&map[y][x+1]==' ')||(orientation==3&&map[y-1][x]==' '&&map[y+1][x]==' '&&map[y-1][x-1]==' ')) {
                clear();
                if(orientation==0) {
                    orientation=3;
                }
                else {
                    orientation--;
                }
                return;
            }
        }
        if(type=='T') {
            if((orientation==0&&map[y+1][x]==' ')||(orientation==1&&map[y][x-1]==' ')||(orientation==2&&map[y-1][x]==' ')||(orientation==3&&map[y][x+1]==' ')) {
                clear();
                if(orientation==0) {
                    orientation=3;
                }
                else {
                    orientation--;
                }
                return;
            }
        }
        if(type=='s') {
            return;
        }
        if(type=='l') {
            if(((orientation==0||orientation==2)&&map[y+2][x]==' '&&map[y-1][x]==' '&&map[y+1][x]==' ')||((orientation==1||orientation==3)&&map[y][x-1]==' '&&map[y][x-2]==' '&&map[y][x+1]==' ')) {
                clear();
                if(orientation==0) {
                    orientation=3;
                }
                else {
                    orientation--;
                }
                return;
            }
        }
    }
    void moveLeft() {
        if(type=='Z') {
            if(orientation==0||orientation==2) {
                if(map[y+1][x-1]==' '&&map[y][x-2]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1||orientation==3) {
                if(map[y-1][x-1]==' '&&map[y][x-2]==' '&&map[y+1][x-2]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
        if(type=='S') {
            if(orientation==0||orientation==2) {
                if(map[y][x-2]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1||orientation==3) {
                if(map[y][x-2]==' '&&map[y-1][x-2]==' '&&map[y+1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
        if(type=='J') {
            if(orientation==0) {
                if(map[y][x-1]==' '&&map[y+1][x-2]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y-1][x-2]==' '&&map[y][x-2]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x-1]==' '&&map[y-1][x-1]==' '&&map[y+1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x-2]==' '&&map[y+1][x]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
        if(type=='L') {
            if(orientation==0) {
                if(map[y][x-1]==' '&&map[y+1][x-1]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y][x-2]==' '&&map[y+1][x-2]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x-1]==' '&&map[y-1][x-2]==' '&&map[y+1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x-2]==' '&&map[y-1][x]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
        if(type=='T') {
            if(orientation==0) {
                if(map[y][x-2]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y][x-1]==' '&&map[y+1][x-1]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x-2]==' '&&map[y+1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x-2]==' '&&map[y+1][x-1]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
        if(type=='s') {
            if(map[y][x-2]==' '&&map[y-1][x-2]==' ') {
                clear();
                x--;
                put();
                return;
            }
        }
        if(type=='l') {
            if(orientation==0 || orientation==2) {
                if(map[y][x-3]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
            if(orientation==1 || orientation==3) {
                if(map[y][x-1]==' '&&map[y+1][x-1]==' '&&map[y+2][x-1]==' '&&map[y-1][x-1]==' ') {
                    clear();
                    x--;
                    put();
                    return;
                }
            }
        }
    }
    void moveRight() {
        if(type=='Z') {
            if(orientation==0||orientation==2) {
                if(map[y][x+1]==' '&&map[y+1][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1||orientation==3) {
                if(map[y+1][x]==' '&&map[y][x+1]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
        if(type=='S') {
            if(orientation==0||orientation==2) {
                if(map[y][x+1]==' '&&map[y-1][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1||orientation==3) {
                if(map[y-1][x]==' '&&map[y][x+1]==' '&&map[y+1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
        if(type=='J') {
            if(orientation==0) {
                if(map[y][x+1]==' '&&map[y+1][x+1]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y-1][x]==' '&&map[y][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x+1]==' '&&map[y+1][x+1]==' '&&map[y-1][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x+2]==' '&&map[y+1][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
        if(type=='L') {
            if(orientation==0) {
                if(map[y+1][x+2]==' '&&map[y][x+1]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y][x+2]==' '&&map[y+1][x]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x+1]==' '&&map[y-1][x+1]==' '&&map[y+1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x+2]==' '&&map[y-1][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
        if(type=='T') {
            if(orientation==0) {
                if(map[y][x+2]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1) {
                if(map[y][x+2]==' '&&map[y+1][x+1]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==2) {
                if(map[y][x+2]==' '&&map[y+1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==3) {
                if(map[y][x+1]==' '&&map[y-1][x+1]==' '&&map[y+1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
        if(type=='s') {
            if(map[y][x+1]==' '&&map[y-1][x+1]==' ') {
                clear();
                x++;
                put();
                return;
            }
        }
        if(type=='l') {
            if(orientation==0 || orientation==2) {
                if(map[y][x+2]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
            if(orientation==1 || orientation==3) {
                if(map[y][x+1]==' '&&map[y+1][x+1]==' '&&map[y+2][x+1]==' '&&map[y-1][x+1]==' ') {
                    clear();
                    x++;
                    put();
                    return;
                }
            }
        }
    }
    void put() {
        if(cleared) {
            if(type=='Z') {
                if(orientation==0||orientation==2) {
                    map[y+1][x]='0';
                    map[y+1][x+1]='0';
                    map[y][x]='0';
                    map[y][x-1]='0';
                    cleared=false;
                    return;
                }
                if(orientation==1||orientation==3) {
                    map[y][x]='0';
                    map[y-1][x]='0';
                    map[y][x-1]='0';
                    map[y+1][x-1]='0';
                    cleared=false;
                    return;
                }
            }
            if(type=='S') {
                if(orientation==0||orientation==2) {
                    map[y][x]='0';
                    map[y][x-1]='0';
                    if(map[y-1][x]!='-') {
                        map[y-1][x]='0';
                        map[y-1][x+1]='0';
                    }
                    cleared=false;
                    return;
                }
                if(orientation==1||orientation==3) {
                    map[y][x]='0';
                    map[y][x-1]='0';
                    map[y+1][x]='0';
                    map[y-1][x-1]='0';
                    cleared=false;
                    return;
                }
            }
            if(type=='J') {
                if(orientation==0) {
                    map[y][x] = '0';
                    map[y+1][x] = '0';
                    map[y+1][x-1] = '0';
                    if(map[y-1][x]!='-') {
                        map[y-1][x] = '0';
                    }
                    cleared=false;
                    return;
                }
                if(orientation==1) {
                    map[y][x] = '0';
                    map[y][x+1] = '0';
                    map[y][x-1] = '0';
                    map[y-1][x-1] = '0';
                    cleared=false;
                    return;
                }
                if(orientation==2) {
                    map[y][x] = '0';
                    map[y+1][x] = '0';
                    map[y-1][x] = '0';
                    map[y-1][x+1] = '0';
                    cleared=false;
                    return;
                }
                if(orientation==3) {
                    map[y][x] = '0';
                    map[y][x+1] = '0';
                    map[y][x-1] = '0';
                    map[y+1][x+1] = '0';
                    cleared=false;
                    return;
                }
            }
            if(type=='L') {
                if(orientation==0) {
                    map[y][x] = '0';
                    map[y+1][x] = '0';
                    map[y+1][x+1] = '0';
                    if(map[y-1][x]!='-') {
                        map[y-1][x] = '0';
                    }
                    cleared=false;
                    return;
                }
                if(orientation==1) {
                    map[y][x] = '0';
                    map[y][x+1] = '0';
                    map[y][x-1] = '0';
                    map[y+1][x-1] = '0';
                    cleared=false;
                    return;
                }
                if(orientation==2) {
                    map[y][x] = '0';
                    map[y-1][x] = '0';
                    map[y+1][x] = '0';
                    map[y-1][x-1] = '0';
                    cleared=false;
                    return;
                }
                if(orientation==3) {
                    map[y][x] = '0';
                    map[y][x+1] = '0';
                    map[y][x-1] = '0';
                    map[y-1][x+1] = '0';
                    cleared=false;
                    return;
                }
            }
            if(type=='T') {
                if(orientation==0) {
                    map[y][x]='0';
                    map[y][x+1]='0';
                    map[y][x-1]='0';
                    if(map[y-1][x]!='-') {
                        map[y-1][x]='0';
                    }
                    cleared=false;
                    return;
                }
                if(orientation==1) {
                    map[y][x]='0';
                    map[y][x+1]='0';
                    map[y+1][x]='0';
                    map[y-1][x]='0';
                    cleared=false;
                    return;
                }
                if(orientation==2) {
                    map[y][x]='0';
                    map[y][x+1]='0';
                    map[y][x-1]='0';
                    map[y+1][x]='0';
                    cleared=false;
                    return;
                }
                if(orientation==3) {
                    map[y][x]='0';
                    map[y+1][x]='0';
                    map[y-1][x]='0';
                    map[y][x-1]='0';
                    cleared=false;
                    return;
                }
            }
            if(type=='s') {
                map[y][x] = '0';
                map[y][x-1] = '0';
                if(map[y-1][x]!='-') {
                    map[y-1][x] = '0';
                    map[y-1][x-1] = '0';
                }
                cleared=false;
                return;
            }
            if(type=='l') {
                if(orientation==0 || orientation==2) {
                    map[y][x] = '0';
                    map[y][x-1] = '0';
                    map[y][x-2] = '0';
                    map[y][x+1] = '0';
                    cleared=false;
                    return;
                }
                if(orientation==1 || orientation==3) {
                    map[y][x] = '0';
                    map[y+1][x] = '0';
                    map[y+2][x] = '0';
                    map[y-1][x] = '0';
                    cleared=false;
                    return;
                }
            }
        }
    }
    void clear() {
        if(!cleared) {
            if(type=='Z') {
                if(orientation==0||orientation==2) {
                    map[y+1][x]=' ';
                    map[y+1][x+1]=' ';
                    map[y][x]=' ';
                    map[y][x-1]=' ';
                    cleared=true;
                    return;
                }
                if(orientation==1||orientation==3) {
                    map[y][x]=' ';
                    map[y-1][x]=' ';
                    map[y][x-1]=' ';
                    map[y+1][x-1]=' ';
                    cleared=true;
                    return;
                }
            }
            if(type=='S') {
                if(orientation==0||orientation==2) {
                    map[y][x]=' ';
                    map[y][x-1]=' ';
                    if(map[y-1][x]!='-') {
                        map[y-1][x]=' ';
                        map[y-1][x+1]=' ';
                    }
                    cleared=true;
                    return;
                }
                if(orientation==1||orientation==3) {
                    map[y][x]=' ';
                    map[y][x-1]=' ';
                    map[y+1][x]=' ';
                    map[y-1][x-1]=' ';
                    cleared=true;
                    return;
                }
            }
            if(type=='J') {
                if(orientation==0) {
                    map[y][x] = ' ';
                    map[y+1][x] = ' ';
                    map[y+1][x-1] = ' ';
                    if(map[y-1][x]!='-') {
                        map[y-1][x] = ' ';
                    }
                    cleared=true;
                    return;
                }
                if(orientation==1) {
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                    map[y][x-1] = ' ';
                    map[y-1][x-1] = ' ';
                    cleared=true;
                    return;
                }
                if(orientation==2) {
                    map[y][x] = ' ';
                    map[y+1][x] = ' ';
                    map[y-1][x] = ' ';
                    map[y-1][x+1] = ' ';
                    cleared=true;
                    return;
                }
                if(orientation==3) {
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                    map[y][x-1] = ' ';
                    map[y+1][x+1] = ' ';
                    cleared=true;
                    return;
                }
            }
            if(type=='L') {
                if(orientation==0) {
                    map[y][x] = ' ';
                    map[y+1][x] = ' ';
                    map[y+1][x+1] = ' ';
                    if(map[y-1][x]!='-') {
                        map[y-1][x] = ' ';
                    }
                    cleared=true;
                    return;
                }
                if(orientation==1) {
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                    map[y][x-1] = ' ';
                    map[y+1][x-1] = ' ';
                    cleared=true;
                    return;
                }
                if(orientation==2) {
                    map[y][x] = ' ';
                    map[y-1][x] = ' ';
                    map[y+1][x] = ' ';
                    map[y-1][x-1] = ' ';
                    cleared=true;
                    return;
                }
                if(orientation==3) {
                    map[y][x] = ' ';
                    map[y][x+1] = ' ';
                    map[y][x-1] = ' ';
                    map[y-1][x+1] = ' ';
                    cleared=true;
                    return;
                }
            }
            if(type=='T') {
                if(orientation==0) {
                    map[y][x]=' ';
                    map[y][x+1]=' ';
                    map[y][x-1]=' ';
                    if(map[y-1][x]!='-') {
                        map[y-1][x]=' ';
                    }
                    cleared=true;
                    return;
                }
                if(orientation==1) {
                    map[y][x]=' ';
                    map[y][x+1]=' ';
                    map[y+1][x]=' ';
                    map[y-1][x]=' ';
                    cleared=true;
                    return;
                }
                if(orientation==2) {
                    map[y][x]=' ';
                    map[y][x+1]=' ';
                    map[y][x-1]=' ';
                    map[y+1][x]=' ';
                    cleared=true;
                    return;
                }
                if(orientation==3) {
                    map[y][x]=' ';
                    map[y+1][x]=' ';
                    map[y-1][x]=' ';
                    map[y][x-1]=' ';
                    cleared=true;
                    return;
                }
            }
            if(type=='s') {
                map[y][x] = ' ';
                map[y][x-1] = ' ';
                if(map[y-1][x]!='-') {
                    map[y-1][x] = ' ';
                    map[y-1][x-1] = ' ';
                }
                cleared=true;
                return;
            }
            if(type=='l') {
                if(orientation==0 || orientation==2) {
                    map[y][x] = ' ';
                    map[y][x-1] = ' ';
                    map[y][x-2] = ' ';
                    map[y][x+1] = ' ';
                    cleared=true;
                    return;
                }
                if(orientation==1 || orientation==3) {
                    map[y][x] = ' ';
                    map[y+1][x] = ' ';
                    map[y+2][x] = ' ';
                    map[y-1][x] = ' ';
                    cleared=true;
                    return;
                }
            }
        }
    }
};

void refreshMap() {
    string str = "Score: ";
    for(int x=0; x<7; x++) {
        screen[x] = str[x];

    }
    string String = to_string(score);
    for(int y=0; y<String.length(); y++) {
        screen[7+y] = String[y];
    }
    for(int y=0; y<17; y++) {
        for(int x=0; x<13; x++) {
            screen[(120*(y+1))+x] = map[y][x];
        }
    }
}

bool checkForLoss() {
    for(int x=1; x<12; x++) {
        if(map[1][x]!=' ') {
            return true;
        }
    }
    return false;
}

void checkForRow() {
    for(int y=1; y<16; y++) {
        if(map[y][1]=='0'&&map[y][2]=='0'&&map[y][3]=='0'&&map[y][4]=='0'&&map[y][5]=='0'&&map[y][6]=='0'&&map[y][7]=='0'&&map[y][8]=='0'&&map[y][9]=='0'&&map[y][10]=='0'&&map[y][11]=='0') {
            score+=1;
            if(score%2==0) {
                lvl++;
            }
            for(int i=y; i>0; i--) {
                for(int x=1; x<12; x++) {
                    if(i!=1) {
                        map[i][x] = map[i-1][x];
                    }
                }
            }
            continue;
        }
    }
}

int down(tetromino block) {
    if(!block.collision()) {
        block.y++;
        return down(block);
    }
    else {
        return block.y;
    }
}

int main() {
    bool loss = false;
    tetromino b;
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    srand(time(0));
    auto last_time = start;
    milliseconds time=500ms;
    while(!loss&&!GetAsyncKeyState(0x1B)) {
        auto current_time = high_resolution_clock::now();
        auto time_since_last = current_time-last_time;
        if(time_since_last >= time) {
            last_time=current_time;
            b.put();
            refreshMap();
            WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
            if(b.collision()) {
                b.~tetromino();
                loss = checkForLoss();
                checkForRow();
                refreshMap();
                if(time>milliseconds(100)) {
                    time = milliseconds(int(500-(20*lvl)));
                }
                new(&b) tetromino;
            }
            b.clear();
            b.y++;
        }
        if(GetAsyncKeyState(0x53)) {
            b.clear();
            b.y=down(b);
        }
        if(GetAsyncKeyState(0x44)) {
            b.moveRight();
            b.clear();
            b.put();
            refreshMap();
            WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
        }
        if(GetAsyncKeyState(0x41)) {
            b.moveLeft();
            b.clear();
            b.put();
            refreshMap();
            WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
        }
        if(GetAsyncKeyState(0x27)) {
            b.turnRight();
            b.clear();
            b.put();
            refreshMap();
            WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
        }
        if(GetAsyncKeyState(0x25)) {
            b.turnLeft();
            b.clear();
            b.put();
            refreshMap();
            WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
        }
        Sleep(200);
    }
    for(int x=0; x<2160; x++) {
        screen[x] = ' ';
    }
    WriteConsoleOutputCharacterA(hConsole, screen, 120*18, { 0,0 }, &dwBytesWritten);
    string str = "You LostFeels BadScore: " + to_string(score);
    for(int x=0; x<str.length(); x++) {
        if(x>7) {
            if(x>16) {
                screen[240+x-17] = str[x];
            }
            else {
                screen[120+x-8] = str[x];
            }
        }
        else {
            screen[x] = str[x];
        }
    }
    WriteConsoleOutputCharacterA(hConsole, screen, 120*5, { 0,0 }, &dwBytesWritten);
    while(!GetAsyncKeyState(0x0D)) {}
}