#include <iostream>
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

struct cell
{
    float x;
    float y;
    float width;
    float height;
    char ans;
    char current = '*';
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
        glColor3f(0.666, 0.5, 0.9);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(1, 0.9, 0);

        float textX = x + 0.1;
        float textY = y + 0.7;

        glRasterPos2f(textX, textY);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ans);
        if (num[0] != '*') {
            float textX = x + 0.1;
            float textY = y + 3;
            glRasterPos2f(textX, textY);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, num[0]);

            textX = x + 1;

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

struct H {
    static std::vector<cell*> ce;
}; std::vector<cell*> H::ce;

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



void DrawField() {
    for (int i = 0; i < H::ce.size(); ++i) {
        (*H::ce[i]).drawButton();
    }


}



void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    DrawField();
    glutSwapBuffers();

}


void init() {
    // Цвет фона
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Ортогональная проекция
    gluOrtho2D(0, 150, 0, 100);
    glMatrixMode(GL_MODELVIEW);
}





int main(int argc, char** argv)
{
    std::ifstream fin("srossword_field.txt");
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);

    glutCreateWindow("crossword");
    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;



}

