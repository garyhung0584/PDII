#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ShapeText(TYPE)          \
    char name[10];               \
    double (*perimeter)(struct TYPE *); \
    double (*area)(struct TYPE *)

/* Base ¡§class¡¨ for all shapes */
typedef struct shape_s {
    ShapeText(shape_s);
} shape_t;

/* Circle: has radius */
typedef struct circle_s {
    ShapeText(circle_s);
    double radius;
} circle_t;

/* Rectangle: has length and width */
typedef struct rectangle_s {
    ShapeText(rectangle_s);
    double length;
    double width;
} rectangle_t;

/* Square: has one edge */
typedef struct square_s {
    ShapeText(square_s);
    double edge;
} square_t;

/* Triangle: has three edges */
typedef struct triangle_s {
    ShapeText(triangle_s);
    double a;
    double b;
    double c;
} triangle_t;

/* Function prototypes for each shape¡¦s perimeter and area */
double circle_perimeter(circle_t *c);
double circle_area(circle_t *c);

double rectangle_perimeter(rectangle_t *r);
double rectangle_area(rectangle_t *r);

double square_perimeter(square_t *s);
double square_area(square_t *s);

double triangle_perimeter(triangle_t *t);
double triangle_area(triangle_t *t);

/* Implementations */
double circle_perimeter(circle_t *c) {
    /* Perimeter = 2 * £k * r, with £k = 3.14 */
    return 2.0 * 3.14 * (c->radius);
}

double circle_area(circle_t *c) {
    /* Area = £k * r^2, with £k = 3.14 */
    return 3.14 * (c->radius) * (c->radius);
}

double rectangle_perimeter(rectangle_t *r) {
    /* Perimeter = 2*(length + width) */
    return 2.0 * (r->length + r->width);
}

double rectangle_area(rectangle_t *r) {
    /* Area = length * width */
    return (r->length) * (r->width);
}

double square_perimeter(square_t *s) {
    /* Perimeter = 4 * edge */
    return 4.0 * (s->edge);
}

double square_area(square_t *s) {
    /* Area = edge^2 */
    return (s->edge) * (s->edge);
}

double triangle_perimeter(triangle_t *t) {
    /* Perimeter = a + b + c */
    return (t->a + t->b + t->c);
}

double triangle_area(triangle_t *t) {
    /* Heron¡¦s formula:
       s = (a + b + c) / 2
       area = sqrt(s * (s - a) * (s - b) * (s - c)) */
    double a = t->a, b = t->b, c = t->c;
    double s = (a + b + c) / 2.0;
    double under_sqrt = s * (s - a) * (s - b) * (s - c);
    if (under_sqrt <= 0.0) {
        /* Degenerate or invalid triangle: area = 0 */
        return 0.0;
    }
    return sqrt(under_sqrt);
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }
    /* An array of shape_t pointers to hold each allocated shape */
    shape_t *shapes[5] = { NULL };

    for (int i = 0; i < N; i++) {
        char type;
        scanf(" %c", &type);
        if (type == 'C') {
            /* Circle: read radius */
            int r_int;
            scanf("%d", &r_int);
            circle_t *c = (circle_t *)malloc(sizeof(circle_t));
            /* (Optional) store a name string for debugging; not used in output */
            strcpy(c->name, "Circle");
            c->perimeter = (double (*)(struct circle_s *))circle_perimeter;
            c->area      = (double (*)(struct circle_s *))circle_area;
            c->radius    = (double)r_int;
            /* Store as a shape_t pointer */
            shapes[i] = (shape_t *)c;
        }
        else if (type == 'R') {
            /* Rectangle: read length and width */
            int l_int, w_int;
            scanf("%d %d", &l_int, &w_int);
            rectangle_t *r = (rectangle_t *)malloc(sizeof(rectangle_t));
            strcpy(r->name, "Rectangle");
            r->perimeter = (double (*)(struct rectangle_s *))rectangle_perimeter;
            r->area      = (double (*)(struct rectangle_s *))rectangle_area;
            r->length    = (double)l_int;
            r->width     = (double)w_int;
            shapes[i] = (shape_t *)r;
        }
        else if (type == 'S') {
            /* Square: read edge */
            int e_int;
            scanf("%d", &e_int);
            square_t *s = (square_t *)malloc(sizeof(square_t));
            strcpy(s->name, "Square");
            s->perimeter = (double (*)(struct square_s *))square_perimeter;
            s->area      = (double (*)(struct square_s *))square_area;
            s->edge      = (double)e_int;
            shapes[i] = (shape_t *)s;
        }
        else if (type == 'T') {
            /* Triangle: read three edges */
            int a_int, b_int, c_int;
            scanf("%d %d %d", &a_int, &b_int, &c_int);
            triangle_t *t = (triangle_t *)malloc(sizeof(triangle_t));
            strcpy(t->name, "Triangle");
            t->perimeter = (double (*)(struct triangle_s *))triangle_perimeter;
            t->area      = (double (*)(struct triangle_s *))triangle_area;
            t->a = (double)a_int;
            t->b = (double)b_int;
            t->c = (double)c_int;
            shapes[i] = (shape_t *)t;
        }
        else {
            /* Unknown type: skip */
            shapes[i] = NULL;
        }
    }

    double total_perimeter = 0.0;
    double total_area = 0.0;

    /* For each shape, call its perimeter and area and print */
    for (int i = 0; i < N; i++) {
        shape_t *s = shapes[i];
        if (!s) {
            /* Should not happen with valid input */
            printf("0.00 0.00\n");
            continue;
        }
        double p = s->perimeter(s);
        double a = s->area(s);
        total_perimeter += p;
        total_area += a;
        /* Print ¡§per-shape¡¨ results rounded to 2 decimal places */
        printf("%.2f %.2f\n", p, a);
    }

    /* Finally, print the summed totals (then rounded) */
    printf("%.2f %.2f\n", total_perimeter, total_area);

    /* Free allocated memory */
    for (int i = 0; i < N; i++) {
        free(shapes[i]);
    }

    return 0;
}
