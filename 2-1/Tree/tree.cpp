#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class node
{
public:
    char ch;
    node *left_child;
    node *right_child;

    node()
    {
        left_child=NULL;
        right_child=NULL;
    }


};

void traverse(node *root)
{
    if(root==NULL) return;
    if(root->left_child)
    {
        traverse(root->left_child);
    }
    if(root->right_child)
    {
        traverse(root->right_child);
    }
    cout<<root->ch<<" ";

}
void deleteTree(node *root)
{
    if(root==NULL) return;
    if(root->left_child)
    {
        deleteTree(root->left_child);
    }
    if(root->right_child)
    {
        deleteTree(root->right_child);
    }
    delete root;
}


int main()
{
   node *root=new node;
   char ch1;
   cin>>ch1;
   root->ch=ch1;
   char* str;
   str=new char [10000];
   while(EOF!=scanf("%s", str))
   {
        node *temp = root;
        for(int i=0; i<strlen(str)-1; i++)
       {
           if(str[i]=='L')
           {
                if(temp->left_child==NULL)
                {
                    node *new_node=new node;
                    new_node->ch=str[i+1];
                    temp->left_child=new_node;
                    temp=temp->left_child;
                }
                else
                {
                    temp=temp->left_child;
                }
           }
            if(str[i]=='R')
            {
                if(temp->right_child==NULL)
                {
                    node *new_node=new node;
                    new_node->ch=str[i+1];
                    temp->right_child=new_node;
                    temp=temp->right_child;
                }
                else
                {
                    temp=temp->right_child;
                }
            }
       }

   }
   traverse(root);
   deleteTree(root);

   delete []str;

   return 0;

}


