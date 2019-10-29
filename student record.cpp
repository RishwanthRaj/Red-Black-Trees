#include<iostream>
#include<string>
#include<map>
using namespace std;
struct node
{
       int class_rank;
       string name;
       int roll_no;
       int marks;
       node *parent;
       char color;
       node *left;
       node *right;
       node *rno;
};
int c=0;
map<int,node*>rno_node;
class RBtree
{
      node *root;
      node *q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void insert();
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void computeRank();
      void Inorder(node*);
      void displayRank();
      void display1();
      void displayInorder1(node*);
      void display2();
      void displayInorder2(node*);
      void search();
};
void RBtree::insert()
{
     int z,i=0;
     int rno;
     string name1;
     cout<<"\nEnter Name : ";cin>>name1;
     cout<<"\nEnter RNo  :";cin>>rno;
     cout<<"\nEnter marks : "; cin>>z;
     node *p,*q;
     node *t=new node;
     t->name=name1;
     t->roll_no=rno;
     t->marks=z;
     t->class_rank=0;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->marks<t->marks)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->marks<t->marks)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
     c++;
}
void RBtree::insertfix(node *t)
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}

void RBtree::leftrotate(node *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBtree::rightrotate(node *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

void RBtree::computeRank()
{
    Inorder(root);
}
void RBtree::Inorder(node* n)
{
    if(n==NULL)
        return;
    Inorder(n->left);
    n->class_rank=c--;
    rno_node[n->roll_no]=n;
    Inorder(n->right);
}
void RBtree::display1()
{
    displayInorder1(root);
}
void RBtree::displayInorder1(node* n)
{
    if(n==NULL)
        return;
    displayInorder1(n->right);
    cout<<"\nName     : "<<n->name;
    cout<<"\nRoll No. : "<<n->roll_no;
    cout<<"\nMarks    : "<<n->marks;
    cout<<"\nRank     : "<<n->class_rank;
    cout<<endl;
    displayInorder1(n->left);
}
void RBtree::display2()
{
    cout<<"\nName\t\tRollNo.\t\tMarks\t\tRank\t\n";
    displayInorder2(root);
}
void RBtree::displayInorder2(node* n)
{
    if(n==NULL)
        return;
    displayInorder2(n->right);
    cout<<n->name<<"\t\t "<<n->roll_no<<"\t\t"<<n->marks<<"\t\t "<<n->class_rank<<"\n";
    displayInorder2(n->left);
}
void RBtree::displayRank()
{

     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return ;
     }
     int rno;
     cout<<"\nEnter your Roll Number : "; cin>>rno;
     int mark=rno_node[rno]->marks;
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->roll_no==rno)
            {
                found=1;
            }
            if(found==0)
            {
                 if(p->marks<mark)
                    p=p->right;
                 else
                    p=p->left;
            }
     }
     if(found==0)
          cout<<"\nNot Found."<<endl;
     else
     {
        cout<<"The rank of selected student is "<<p->class_rank<<endl;
     }
}
int main()
{
    int ch,y=0;
    RBtree obj;
    do
    {
                cout<<"\nRED BLACK TREE - STUDENT RECORD.\n" ;
                cout<<"\n1. Add new record.";
                cout<<"\n2. Compute Rank.";
                cout<<"\n3. Rank of a record.";
                cout<<"\n4. Display - Record-wise.";
                cout<<"\n5. Display - Table.";
                cout<<"\n6. Exit." ;
                cout<<"\nEnter Your Choice : "; cin>>ch;
                switch(ch)
                {
                          case 1 : obj.insert();
                                   cout<<"\nRecorded.\n";
                                   break;
                          case 2:  obj.computeRank();
                                    cout<<"\nRank Computed.\n";
                                    break;
                          case 3:
                                    obj.displayRank();
                                    break;
                          case 4:   obj.display1();
                                    break;
                          case 5:   obj.display2();
                                    break;
                          case 6 : y=1;
                                   break;
                          default : cout<<"\nEnter a Valid Choice.";
                }
                cout<<endl;

    }while(y!=1);
    return 1;
}
