#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


#define MARGIN_OFERROR (0.001)

struct user_config {
    int find_x_method; /* 0: cut, 1: middle */
};

struct user_config config = {
    .find_x_method = 0,
};

float f(float x)
{
    float y = x * x * x - 5 * x * x - 80;
    return y; 
}

float cut(float x1, float x2)
{
    float x = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));
    return x;
}

float get_middle(float x1, float x2)
{
    return ((x1 + x2) / 2);
}

float root(float x1, float x2)
{
    float x;

    do {
        if (config.find_x_method == 0) {
            x = cut(x1, x2);
        } else {
            x = get_middle(x1, x2);
        }
        if (f(x) * f(x1) < 0) {
            x2 = x;
        } else {
            x1 = x;
        }
    } while (f(x) >= 0.001 || f(x) <= -0.001);
    
    return x;
}

void find_initial_x1_x2(float *x1, float *x2)
{
    do {
        printf("input x1, x2:\n");
        scanf("%f%f", x1, x2);
        printf("x1 %f, x2 %f, f(x1) %f, f(x2) %f\n", *x1, *x2, f(*x1), f(*x2));
    } while (f(*x1) * f(*x2) > 0);
    
    return;
}

int32_t parse_cmd(int argc, char *const argv[])
{
    int32_t c = 0;

    while ((c = getopt(argc, argv, "m:h")) != -1) {
        switch (c) {
            case 'm':
                config.find_x_method = atoi(optarg);
                if ((config.find_x_method != 0) && (config.find_x_method != 1)) {
                    printf("find_x_method error %d\n", config.find_x_method);
                    return -1;
                }
                break;
            case 'h':
            default:
                printf("server: ./a.out -m [0: cut, 1: middle]\n");
                return -1;
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    float x1;
    float x2;
    float x;
    
    if (parse_cmd(argc, argv) != 0) {
        printf("parse cmd error\n");
        return -1;
    }    

    find_initial_x1_x2(&x1, &x2);
    printf("found x1 %f, x2 %f\n", x1, x2);
    
    x = root(x1, x2);
    printf("root %f, f(x) %f\n", x, f(x));

    return 0;
}
