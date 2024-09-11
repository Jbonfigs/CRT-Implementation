#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//Number of integers
#define k 5

void generate_m(int *m);
void generate_x(int *x);
_Bool is_prime(int n);
void euclid_extended(int *u_v_d, int a, int b);


int main()
{
/*
    Given pairwise co prime integers m and integers x, this algorithm finds 
    an integer x such that x is equivalent to xi mod mi for all i, (1 <= i <= k).
*/
    int i, m[k], x[k];
    long M, X;
    int u_v_d[3]; //array for euclid extended algorithm
    
    //Generate first k prime numbers
    generate_m(m);

    //Generate k integers between 0 and 1000
    generate_x(x);

    for(int i = 0; i < k; i++){
        printf("%d,", m[i]);
    }
    printf("\n");
    for(int i = 0; i < k; i++){
        printf("%d,", x[i]);
    }
    printf("\n");

    i = 0;
    M = m[0];
    X = x[0];

    while(i != (k-1)){
        i++;
        euclid_extended(u_v_d, M, m[i]);
        X = (u_v_d[0]*M*x[i]) + (u_v_d[1]*m[i]*X);
        M *= m[i];
        X = X % M;
    }
    
    printf("x is %ld \n", X);
    return 0;

}


//Generates the first k prime numbers 
void generate_m(int *m)
{
    int num = 2;
    int index = 0;
    while (index < k) {
        if (is_prime(num)) {
            m[index++] = num;
        }
        num++;
    }
  
}

//Generates random numbers between 0 and 99 to fill x
void generate_x(int *x)
{
    for(int i = 0; i < k; i++){
        x[i] = rand() % 101; //Lets keep number small 
    }

}

//Checks if a number is prime 
_Bool is_prime(int n)
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void euclid_extended(int *u_v_d, int a, int b)
{
    int v1, v3, t1, t3, q;

    u_v_d[0] = 1;
    u_v_d[2] = a;

    if(b == 0){
        u_v_d[1] = 0;
        return;
    } else {
        v1 = 0;
        v3 = b;
    }

    while(v3 != 0){
        q = floor(u_v_d[2]/v3);
        t3 = u_v_d[2] % v3;
        t1 = u_v_d[0] - q*v1;
        u_v_d[0] = v1;
        u_v_d[2] = v3;
        v1 = t1;
        v3 = t3;
    }

    u_v_d[1] = (u_v_d[2] - a*u_v_d[0]) / b;
    return;

}

