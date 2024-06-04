﻿#include <iostream>
#include "glut.h"
#include <string>
#include <fstream>
#include <vector>


struct Point {
    float x, y;
    Point() = default;
    Point(float a, float b) {
        x = a;
        y = b;
    }
};
class Button {
public:
    float x;
    float y;
    float width;
    float height;
    const char* text;
    int sz = 0;
    Button() = default;
    Button(float x0, float y0, float width0, float height0, const char* text0) {
        x = x0;
        y = y0;
        width = width0;
        height = height0;
        text = text0;
        sz = strlen(text0);
    }
    Button(float x0, float y0, float width0, float height0, int int0) {
        x = x0;
        y = y0;
        width = width0;
        height = height0;
        int s = 1;
        while (int0 / (10 * s) > 0) {
            ++s;
        }
        sz = s;
        char* char0 = new char[s];
        for (int i = 0; i < s; ++i) {
            if (int0 > 9) {
                char0[i] = char(int0 / (pow(10, (s - i - 1))) + 48);
                int g = (pow(10, (s - i - 1)));
                int0 = int0 % g;

            }
            else {
                char0[i] = char(int0 % 10 + 48);

            }
        }

        text = char0;


    }
    ~Button() {
        delete[] text;
    }
    void drawButton() {
        glBegin(GL_POLYGON);
        glColor3f(0.666, 0.5, 0.9);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(1, 0.9, 0);

        float textX = x + 0.1;
        float textY = y + 1;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < sz; ++i) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }

        glFlush();
    }
    void drawButton(int d) {
        glBegin(GL_POLYGON);
        glColor3f(0.666, 0.5, 0.9);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(1, 0.9, 0);

        float textX = x + 0.1;
        float textY = y + 1;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < sz; ++i) {

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }

        glFlush();
    }
    bool isButtonHovered(Point press) {
        return press.x >= x && press.x <= x + width &&
            press.y >= y && press.y <= y + height;
    }
};
struct cell
{
    float x;
    float y;
    float width;
    float height;
    char ans;
    char current = ' ';
    char num[2] = { '*','*' };
    int sz = 0;
    cell() = default;
    cell(float x0, float y0, float width0, float height0, char num0[2], char ans0) {
        x = x0;
        y = y0;
        width = width0;
        height = height0;
        ans = ans0;
        num[0] = num0[0];
        num[1] = num0[1];
    }

    ~cell() {
        //delete[] num;
    }
    void drawButton() {
        glBegin(GL_POLYGON);
        glColor3f(0, 0.45, 0.9);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(1, 0.6, 0);

        float textX = x + 0.3;
        float textY = y + 0.7;

        glRasterPos2f(textX, textY);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, current);
        if (num[0] != '*') {
            float textX = x + 0.3;
            float textY = y + 3;
            glRasterPos2f(textX, textY);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, num[0]);

            textX = x + 1.2;

            glRasterPos2f(textX, textY);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, num[1]);
        }

        glFlush();
    }
    void drawButton(int d) {
        glBegin(GL_POLYGON);
        glColor3f(0.666, 0.5, 0.9);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(1, 0.9, 0);

        float textX = x + 0.1;
        float textY = y + 1;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < sz; ++i) {

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ans);
        }

        glFlush();
    }
    bool isButtonHovered(Point press) {
        return press.x >= x && press.x <= x + width &&
            press.y >= y && press.y <= y + height;
    }
};


enum MenuState
{
    MAIN,
    PLAY,
    WIN,
};
MenuState currentMenuState = MAIN;


struct H {
    static std::vector<cell*> ce;
    static Button cr1;
    static Button cr2;
    static Button cr3;
    static Button to_manu;
    static Button ok;
}; std::vector<cell*> H::ce;
Button H::cr1(20, 50, 11, 5, "crossword 1"), H::cr2(70, 50, 11, 5, "crossword 2"), H::cr3(120, 50, 11, 5, "crossword 3"), H::to_manu(130, 5, 10, 5, "to manu");

std::vector<cell*> cells(const std::vector<std::vector<char>>& fld, const int& s, const int& c) {
    std::vector<cell*> cells;
    char num[2] = { '*','*' };
    for (int i = 1; i < s; i += 2) {
        for (int j = 1; j < c; j += 2) {
            if (fld[i][j] != '.') {
                if (fld[i - 1][j - 1] != '.') {
                    num[0] = fld[i - 1][j - 1];
                    num[1] = fld[i - 1][j];
                    cell* n = new cell(0 + 2.8 * (j - 1), 100 - 2.8 * (i - 1) - 5, 5, 5, num, fld[i][j]);
                    cells.push_back(n);
                }
                else {
                    cell* n = new cell(0 + 2.8 * (j - 1), 100 - 2.8 * (i - 1) - 5, 5, 5, num, fld[i][j]);
                    cells.push_back(n);
                }
            }
            num[0] = { '*' };
            num[1] = { '*' };
        }
    }
    return cells;
}

void renderBitmapString(float x, float y, void* font, std::string string) {
    glRasterPos2f(x, y);
    for (char c : string) {
        glutBitmapCharacter(font, c);
    }
}

void DrawField() {


    switch (currentMenuState)
    {
    case MAIN:
        renderBitmapString(55, 80, GLUT_BITMAP_TIMES_ROMAN_24, "Choose a crossword puzzle");
        H::cr1.drawButton();
        H::cr2.drawButton();
        H::cr3.drawButton();
        break;
    case PLAY:
        H::to_manu.drawButton();
        for (int i = 0; i < H::ce.size(); ++i) {
            (*H::ce[i]).drawButton();
        }
        break;
    }




}



void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    DrawField();
    glutSwapBuffers();

}

void MousePressed(int button, int state, int x, int y) {
    float x0 = x / 9.7;
    float y0 = (1000 - y) / 10;
    Point xy(x0, y0);


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        switch (currentMenuState) {
        case MAIN:
            if (H::cr1.isButtonHovered(xy)) {
                std::ifstream fin("crossword_field1.txt");
                std::vector<std::vector<char>> field;
                std::string s;
                int cl = 0;
                int st = 0;
                while (fin >> s) {
                    cl = s.size();
                    std::vector<char> str;
                    for (int i = 0; i < s.size(); ++i) {
                        str.push_back(s[i]);
                    }
                    field.push_back(str);
                    ++st;
                }
                H::ce = cells(field, st, cl);
                fin.close();
                currentMenuState = PLAY;
            }
            else if (H::cr2.isButtonHovered(xy)) {
                std::ifstream fin("crossword_field2.txt");
                std::vector<std::vector<char>> field;
                std::string s;
                int cl = 0;
                int st = 0;
                while (fin >> s) {
                    cl = s.size();
                    std::vector<char> str;
                    for (int i = 0; i < s.size(); ++i) {
                        str.push_back(s[i]);
                    }
                    field.push_back(str);
                    ++st;
                }
                H::ce = cells(field, st, cl);
                fin.close();
                currentMenuState = PLAY;
            }
            else if (H::cr3.isButtonHovered(xy)) {
                std::ifstream fin("crossword_field3.txt");
                std::vector<std::vector<char>> field;
                std::string s;
                int cl = 0;
                int st = 0;
                while (fin >> s) {
                    cl = s.size();
                    std::vector<char> str;
                    for (int i = 0; i < s.size(); ++i) {
                        str.push_back(s[i]);
                    }
                    field.push_back(str);
                    ++st;
                }
                H::ce = cells(field, st, cl);
                fin.close();
                currentMenuState = PLAY;
            }
            display();
            break;
        case PLAY:
            if (H::to_manu.isButtonHovered(xy)) {
                currentMenuState = MAIN;
            }
            display();
            break;
        }


    }
}

void init() {
    // Цвет фона
    glClearColor(0.1, 0.2111, 0.4511, 0.8);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Ортогональная проекция
    gluOrtho2D(0, 150, 0, 100);
    glMatrixMode(GL_MODELVIEW);
}





int main(int argc, char** argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);

    glutCreateWindow("crossword");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(MousePressed);
    glutMainLoop();

    return 0;



}

