#include <stdio.h>

int strlen(char str[]);
char stac[50];
int top=0;
void push(char ch);
char pop();
int isEmpty();

int main()
{
    int len, i;
    char ch;
    char str[100];
    gets(str);

    len =strlen(str);

    for(i=0; i<len; i++){
        if (str[i]=='('||str[i]=='{'||str[i]=='['){
              push(str[i]);
        }
        else if(str[i]==')'||str[i]=='}'||str[i]==']'){
            if(isEmpty()){
                printf("Error at position %d", i+1);
                return 0;
            }
            else if(str[i]==')' && stac[top-1]!='('){
                printf("Error at position %d", i+1);
                return 0;
            }
            else if(str[i]=='}' && stac[top-1]!='{'){
                printf("Error at position %d", i+1);
                return 0;
            }
            else if(str[i]==']' && stac[top-1]!='['){
                printf("Error at position %d", i+1);
                return 0;
            }
            else{
                pop();
            }

        }

    }
    if(isEmpty()){
            printf("Matched");
            return 0;
        }
    else{
            printf("Error at position %d", i+1);
    }
    return 0;

}
void push(char ch)
{
    stac[top]=ch;
    top++;
}
char pop()
{
    top--;
    return stac[top];
}
int isEmpty()
{
    if(top==0) return 1;
    else return 0;
}
int strlen(char str[])
{
    int i;
    for(i=0; str[i]!='\0'; i++);
    return i;
}
