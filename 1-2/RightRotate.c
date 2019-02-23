#include <stdio.h>
#include <conio.h>

int printbit(unsigned int a);

int main()
{
    unsigned int x;
    int  n, temp,b, len, i;
    scanf("%u", &x);
    scanf("%d", &n);

    temp=x;

    len=sizeof(x)*8;

    for(i=1; i<=n; i++){
        b=(x&1);
        x=x>>1;
        b=b<<len-1;
        x=(x|b);
    }
    printf("Bit pattern of the input:\n");
    printbit(temp);
    printf("\n");
    printf("Resulting bit pattern:\n");
    printbit(x);

    getch();

    return 0;
}

int printbit(unsigned int a)
{
    int size, bit,i;

    int ara[40];

    size=sizeof(a)*8;

    for(i=0; i<size; i++){
        ara[i]=(a&1);
        a=a>>1;
    }

    for(i=size-1; i>=0; i--){
        printf("%d", ara[i]);
    }


    return 0;
}



