#include <stdio.h>
#define MAX_DEGREE 101
#define MAX(x, y) (x) > (y) ? (x) : (y)

typedef struct {
    int degree;
    int coef[MAX_DEGREE];
} polynomial;

void print_poly(polynomial p) {
    for (int i = p.degree; i>0; i--) {
        printf("%dx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%d\n", p.coef[p.degree]);
}

polynomial poly_add1(polynomial x, polynomial y) {
    polynomial z;
    int xpos = 0, ypos = 0, zpos = 0;
    int degree_x = x.degree; 
    int degree_y = y.degree;
    z.degree = MAX(x.degree, y.degree);
    while (xpos <= x.degree && ypos <= y.degree) {
        if (degree_x > degree_y) {
            z.coef[zpos++] = x.coef[xpos++];
            degree_x--;
        } else if (degree_x == degree_y) {
            z.coef[zpos++] = x.coef[xpos++] + y.coef[ypos++];
            degree_x--;
            degree_y--;
        } else {
            z.coef[zpos++] = y.coef[ypos++];
            degree_y--;
        }
    }
    return z;
}

int main() {
    polynomial frontStudentNum = {3, {2, 0, 2, 1}};
    polynomial backStudentNum = {4, {0, 1, 3, 7, 5}};
    polynomial c = poly_add1(frontStudentNum, backStudentNum);
    print_poly(frontStudentNum);
    printf("+\n");
    print_poly(backStudentNum);
    printf("==\n");
    print_poly(c);
}