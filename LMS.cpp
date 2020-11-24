#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<string>
class Student
{
};
void Librarian()
{int a;
        printf("\n\nWelcome Librarian \n\n");
        scanf("%d",&a);
}
void Student()
{int a;
        printf("\n\nWelcome Student \n\n");
        
        scanf("%d",&a);
}
void Faculty()
{ int a;
        printf("\n\nWelcome Faculty \n\n");
        
        scanf("%d",&a);
}







int main(int argc,char* argv[])
{
        int ch;
x:printf("\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n\n\t\t\t\n");
        printf("\n\t\tSelect Profile \n");
        printf("\n\t\t1.Librarian\n\n\t\t2.Faculty\n\n\t\t3.Student\n\n\t\t4.Close Application\n");
        printf("\n\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
         case 1:system("clear");
                Librarian();
                break;
         case 2:system("clear");
                Faculty();
                break;
         case 3:system("clear");
                Student();
                break;
         case 4:exit(0);
         
        default:printf("\n\t\tPlease enter correct option :(");
                system("clear");
                goto x;
        }
}
