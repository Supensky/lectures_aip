/*
СТРУКТУРЫ

main.cpp
int main() {
    int x_re, x_im, y_re, y_im, z_re, z_im;
    x_re = 1;
    x_im = 2;
    y_re = 3;
    y_im = 4;
    z_re = 5;
    z_im = 6;
    printf("%d+%li", x_re, x_im);
    printf("+");
    printf("%d+%li", y_re, y_im);
    printf("+");
    printf("%d+%li", z_re, z_im);
    printf("+");
    printf("%d+%li", x_re, x_im);
    printf("+");
    printf("\n");
}

-----

complex.h

typedef struct complex {
    int re, im;
    void print();
    void set(int, int);

};

void complex_set(complex *, int, int);

void complex complex_add(complex *, complex *, complex *);

void complex_print(complex x);

void add(complex *, complex *);

complex();

complex(complex&);

complex & operator+(complex&, complex&);

----

complex.cpp
void complex_print() {
    printf("%d+%di", re, im);
}

void complex_set(int re, int im) {
    this -> re = re;
    this -> im = im;
}

complex::complex(complex &) {
    re = c.re;
    im = c.im;
}

void complex_add(complex *x, complex *y) {
    set(x->re+y->re, x->im+y->im);
}

complex operator+(complex &x, complex &y) {
    return complex(x.re+y.re, x.im+y.im);
}

После этих структур и функций код будет выглядеть вот так:

main.cpp
int main() {
    struct complex x, y, z;
    x.set(1, 2);
    y.set(3, 4);
    complex_set(&y, 3, 4);
    complex_set(&z, 5, 6);
    x.print(); | complex::print(&x);
    printf("+");
    y.print();
    printf("=");
    z.print();
    printf("\n");
    z.add(&x, &y);

    complex x(1, 2);
    complex y(3, 4);
    complex z = x + y;
}


ВИРТУАЛЬНЫЕ МЕТОДЫ

struct point2d {
    int x, y;
    virtual void print();
};

point_create() {
    print = print2d;
}

void print(point2d *p) {
    p -> print;
}

наследование
struct point3d:public point2d {
    int z;
}

pint2d:print(){
    print("%d:%d", x, y);
}
----


struct ops {
    init
    read
    write
    ioctl
    release
}

struct list
struct ops

как по листу понять что это за объект

offsetof(struct, field)

struct vector {
    point start;
    point end;
}

offsetof(struct vector, end) показывает сколько нам от struct vector до end

container_of(ptr, type, member)

vector = (vector *)((void *)ptr - offsetof(vector, end))


struct animal;
struct name;
struct pet:public animal, name {

}

pet *pet = ... cast <pet>(named);

на си:

struct pet {
    struct animal;
    struct named;
}

pet *pet = container_of(named, pet, named);

extern "c" {
    int do_something(int arg)
}


typedef {
    int re, im;
} *complex;

complex x = new_complex(1, 2);
 на c++     new Complex(1, 2);

delete x;

В C:
complex new_complex(int re, int im) {
    c = malloc(..)
    c -> re = re;
    c -> im = im;
}

В C++:
complex:complex(int re, int im) {
    this -> re = re;
    this -> im = im;
}


ДРУЗЬЯ

public
protected
private

class my_class {
protected
    int x, y;
};

class my_public:public my_class {
    int get_x();
    int get_y();
}
*/