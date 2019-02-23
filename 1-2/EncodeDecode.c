#include <stdio.h>
#include <conio.h>

unsigned int get_encode(unsigned int a);
int parity(unsigned int a);

int main()
{
    int f, test;
    unsigned int a, roll, sub, score;

    printf("For encoding mode Press 0 / For decoding mode press 1 :\n");

    scanf("%d", &f);

    if(f==0){
        printf("Enter the Roll, sub code, score respectively:\n");
        scanf("%u %u %u", &roll, &sub, &score);

        a=roll<<11;
        sub=sub<<8;
        a=(a|sub);
        score=score<<1;
        a=(a|score);

        get_encode(a);//output
    }

    else if(f==1){
        printf("Enter an unsigned integer:\n");
        scanf("%u", &a);
        test=parity(a);
        if(test%2!=0){
            printf("Error");
        }
        else{
            a=a>>1;
            score=(a&(~((~0)<<7)));
            a=a>>7;
            sub=a&(~((~0)<<3));
            a=a>>3;
            roll=a&(~((~0)<<21));
            printf("Roll  : %u\n", roll);
            printf("Subject code : %u\n", sub);
            printf("Score  : %u\n",score);
        }
    }

    getch();
    return 0;
}

unsigned int get_encode(unsigned int a)
{
    int bit,i,count, b;
    unsigned int v;

    v=a;

    count =0;


    for(i=0; i<32; i++){
        b=(a&1);
        if(b==1){
            count++;
        }
        a=a>>1;
    }
    if(count%2==0){
       printf("%u", v);
    }
    else{
        v=(v|1);
        printf("%u", v);
    }

    return 0;
}
int parity(unsigned int a)
{
    int count ,i,b;
    for(i=0; i<32; i++){
        b=(a&1);
        if(b==1){
            count++;
        }
        a=a>>1;
    }
    return count;
}
