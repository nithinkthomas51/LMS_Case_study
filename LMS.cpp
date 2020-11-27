#include<iostream>
#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<cstring>
#include <termios.h>
#include <unistd.h>

using namespace std;


//Define Database
GDBM_FILE dbf;
datum key,data;
char keybuf[50],databuf[256];

//void Login(char ch)


/*
class Book
{ char bookName[100];
  char publication[100];
  char category[100];
  bool ref;
  char author[100];
  int ISBN;
  public:
  string getBookName(void)const
  {
          return bookName;
  }
  string  getPublication(void)const
  {
          return publication;
  }
  string getCategory(voi(d)const
  {
          return category;
  }
  string getAuthor(void)const
  {
          return author;
  }
  bool isRef(void)const
  {
          return ref;
  }
  int getISBN(void)const
  {
          return ISBN;
  }
};


*/
class Lib
//:public Books
{
    char name[50];

    public:
    Lib(){
    }
    
    void Librarian(char* username)
     {        
         dbf=gdbm_open("librarian.db",0,GDBM_WRCREAT,0666,0);
  	 if(!dbf)
  	 {
    		printf("\nError occured while receiving the data, please try again");
    		printf("\n");
  	 }
  	 key=gdbm_firstkey(dbf);
    	 if(key.dptr==NULL)
    	 {
    	    printf("Welcome Librarian please enter your name");
    	    scanf("%s",name);
    	    sprintf(keybuf,"%s",username);
	    key.dsize=strlen(keybuf)+1;
	    key.dptr=keybuf;
	    sprintf(databuf,"%s",name);
	    data.dsize=strlen(databuf)+1;
	    data.dptr=databuf;
	    if(gdbm_store(dbf,key,data,GDBM_INSERT))
            {	
             	printf("\nError occured!Emp id exists.Member  is not added\n");
            }
            else 
            
            printf("\n\n\t\t\t************Welcome Librarian************** \n\nPress any key \n");
            
    gdbm_close(dbf);
}
}

    void AddBook();
    void RemoveBook();
    void PurchaseRequest();
    void RemoveUser();

};

/*
class Stud:public Book
{   int 
	public:
    void Student();
    void SearchBook();
    void Borrow();
    void BookStatus();
    void Reserve();
    void ReserveCancellation();
    void PurchaseRequest();
    
};

class Fac:public Book
{
    int 
	public:
    void Student();
    void SearchBook();
    void Borrow();
    void BookStatus();
    void Reserve();
    void ReserveCancellation();

};

*/

//Student
void Student()
{
	int a;
        printf("\n\nWelcome Student \n\n Press any key \n ");
        scanf("%d",&a);

}



//Librarian

   /* exit:
	gdbm_close(dbf);
    	    
	 int b;
  	 printf("\n\n\t\t\t************Welcome Librarian************** \n\nPress any key \n");
  	 printf("\n\t\t\t\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n\n\t\t\t\n");
         printf("\n\t\t\t\t\t\tSelect Profile \n");
         printf("\n\t\t\t\t\t\t1.Librarian\n\n\t\t\t\t\t\t2.Faculty\n\n\t\t\t\t\t\t3.Student\n\n\t\t\t\t\t\t4.Help\n\n\t\t\t\t\t\t5.Close Application\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
  	scanf("%d",&b);
}



//Faculty
*/

void  Faculty()
{ 
	int a;
        printf("\n\nWelcome Faculty \n\n Press any key \n");
        scanf("%d",&a);
}


//Library Reports
void Report()
{

}



//Help
void Help()
{ 
	int c;
	char ch;
	using namespace std;
	
	do{
	system("clear");
	cout<<"\t\t\t**********Welcome to Library**********"<<endl;
	cout<<"1. Registration and Login\n2. Search\n3. Borrowing book/journal\n4. Reservation\n5. Request for new book\n6. Notification\n";
	cout<<"Enter your choice : ";
	cin>>c;
	switch(c)
	{
		case 1:
		{
			system("clear");
			cout<<"****Registration and Login****\n\n";
			cout<<"\n***Librarian***\n\n* To register, enter the Unique 6 digit PIN and create username and password \n* To login, enter your username and password\n\n";
			cout<<"***Faculty/Student***\n\n* To register, enter your unique username and password. Remember, by default your username is the password\n* once you login to the system, you have to change the password\n\n";
			break;
		}
		case 2:
		{
			system("clear");
			cout<<"****search****\n\n";
			cout<<"* You can search any book/journal by using book name, author's name, category\n* You can search for the list of books/journal under author's name, category\n* You can see who has borrowed a book/journal and the due date for the same\n";
			break;
		}
		case 3:
		{
			system("clear");
			cout<<"****Borrowing Book/journal****\n\n";
			cout<<"* Faculty can access any book/journal\n* Students can access any book/journal except reference books\n";
			break;
		}
		case 4:
		{
		system("clear");
		cout<<"****Reservation****\n\n";
		cout<<"* You can reserve a book/journal borrowed by others currently\n* You can see the status of the book/journal which is reserved or borrowed and respective due date\n* You can also cancel the reservation made earlier\n";
		break;
		}
		case 5:
		{
		system("clear");
		cout<<"****Request for new book****\n\n";
		cout<<"* User can place request for purchase of new book by providing details about the name of the book,author's name and publisher\n"; 
		break;
		}
		case 6:
		{
		system("clear");
		cout<<"****Notification****\n\n";
		cout<<"* You will recieve a notification when you made the reservation\n* You will recieve a notification when a user made a reservation for the book which you have currently\n* You will recieve a notification about the expiry of due date of the book 4 days in advance\n";
		break;
		}
	}
	cout<<"\n\nBack to help(Y/N)";
	cin>>ch;
	}while(ch=='Y' or ch=='y');
}




//Authenticate

void authenticate(int a)
{Lib l;
  	dbf=gdbm_open("users.db",0,GDBM_WRCREAT,0666,0);
  	if(!dbf)
  	{
    		printf("\nError occured while receiving the data, please try again");
    		printf("\n");
  	}
  	char username[50];
  	char password[50];
  	char type;
  	if(a==1)  //Authentication for Librarian
  	{	 
    		key=gdbm_firstkey(dbf);
    		if(key.dptr==NULL)
    		{ 	
      			type='L';
     			int PIN;
     			system("clear");
     			printf("\n\n\t\t\t         Welcome to the Library Manangement System Portal\n\n\n");
     			printf("Please provide your unique 6 digit pin to gain Admin Privilages\n\n\n");
    		        printf("PIN :");
       
       		//Disable echo
       		termios oldt;
       		tcgetattr(STDIN_FILENO, &oldt);
       		termios newt = oldt;
       		newt.c_lflag &= ~ECHO;
       		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
       
                       //input the password
       		scanf("%d",&PIN);
       
       		//Re-enable echo
        		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
         
        		if(PIN==123456)
       	        {  
       	        	system("clear");
           			printf("\nEnter a Unique user name  :");
           			scanf("%s",username);
	      			sprintf(keybuf,"%s",username);
	      			key.dsize=strlen(keybuf)+1;
	       	   	key.dptr=keybuf;
	       		printf("\n\nEnter your Password   : ");
	      
          			 //Disable echo
          			 termios oldt;
          			 tcgetattr(STDIN_FILENO, &oldt);
				 termios newt = oldt;
				 newt.c_lflag &= ~ECHO;
				 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	                        
	                        //input the password
            			 scanf("%s",password);
       
       
            			//Re-enable
           			 tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	   
	   
	        		 sprintf(databuf,"%s %c",password,type);
	        		 data.dsize=strlen(databuf)+1;
	         	         data.dptr=databuf;
	         	         if(gdbm_store(dbf,key,data,GDBM_INSERT))
            			 {	
             				printf("\nError occured!Emp id exists.Member  is not added\n");
            			 } 
             			else    
             			{
             				printf("\n\n\nLibrarian account Created\n");
             				printf("\n\nLogin to continue \n\n\n\n\n\n\n\n\n");
             				goto x;
             			}
             				             			
	   		}
	  		else   printf("Access Denied !");
	  	}
		else
		{
			x:int attempts=1,flag=0;
			int maxTry = 3;
			while(attempts<=maxTry&&flag==0)
    			{	
	    			printf("\nEnter a User name  :");
        			scanf("%s",username);
        			sprintf(keybuf,"%s",username);
       			key.dsize=strlen(keybuf)+1;
        			key.dptr=keybuf;
        			if(gdbm_exists (dbf,key))
       			 {      char realType;
       			 	char realPassword[50];
       			 	data=gdbm_fetch(dbf,key);
             				strcpy(databuf,data.dptr);
             				sscanf(databuf,"%s %c",realPassword,&realType);
             				if(realType=='L')
             				{
           				
           				printf("\n\nPassword  : ");

         				//Disable echo
       				termios oldt;
				       tcgetattr(STDIN_FILENO, &oldt);
				       termios newt = oldt;
				       newt.c_lflag &= ~ECHO;
				       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				   
				       // Input the password
				       scanf("%s",password);
				 
				      //Re-enable
				       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
             
             			        
             				if(strcmp(password,realPassword)==0)
             				{       gdbm_close(dbf);
             					flag=1;
              					system("clear");
                                       l.Librarian(username);
              				}
    					else
     					{	
     						system("clear");		
       					printf("\nPassword incorrect!\nYou have %d attempts remaining \n",(3-attempts));
       					attempts++;
       					
   					}
   					}
   					else
   					{
   						printf("\nYou dont have Permission to access this\n");
   						exit(0);
   					}
   					
				}

				else
 				{
 					system("clear");
        				printf("\nWrong user name!\nYou have %d attempts remaining\n ",(3-attempts));
        				attempts++;
       			}
			}
		}
	}
	else if(a==2)   //Authentication for Faculty
	{	int ch;
               getchar();
		printf("\n\t\t\tWelcome to Central Library");
		printf("\n\nDo you want to\n1.Login\n2.Signup");
		printf("\n\nEnter your choice  :");
        	scanf("%d",&ch);
		if(ch==1)
		{
			int attempts=1,flag=0;
			int maxTry = 3;
			while(attempts<=maxTry&&flag==0)
    			{
	    			printf("\nEnter a User name  :");
        			scanf("%s",username);
        			sprintf(keybuf,"%s",username);
       			key.dsize=strlen(keybuf)+1;
        			key.dptr=keybuf;
        			if(gdbm_exists (dbf,key))
       			 {      char realType;
       			 	char realPassword[50];
       			 	data=gdbm_fetch(dbf,key);
             				strcpy(databuf,data.dptr);
             				sscanf(databuf,"%s %c",realPassword,&realType);
             				if(realType=='F')
             				{
           				
           				printf("\n\nPassword  : ");

         				//Disable echo
       				termios oldt;
				       tcgetattr(STDIN_FILENO, &oldt);
				       termios newt = oldt;
				       newt.c_lflag &= ~ECHO;
				       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				   
				       // Input the password
				       scanf("%s",password);
				 
				      //Re-enable
				       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
             
             			        
             				if(strcmp(password,realPassword)==0)
             				{
             					flag=1;
              					system("clear");
              					Faculty();
              				}
    					else
     					{	system("clear");		
       					printf("\nPassword incorrect!\nYou have %d attempts remaining \n",(3-attempts));
       					attempts++;
       					
   					}
   					}
   					else
   					{	system("clear");
   						printf("\nYou dont have Permission to access this\n");
   						exit(0);
   					}
   					
				}

				else
 				{
 					system("clear");
        				printf("\nWrong user name!\nYou have %d attempts remaining\n ",(3-attempts));
        				attempts++;
       			}
			}
		}
		if(ch==2)
		{	
		   	type='F';
		   	system("clear");
           		printf("\nEnter a Unique user name  :");
           		scanf("%s",username);
	      		sprintf(keybuf,"%s",username);
	      		key.dsize=strlen(keybuf)+1;
	       	key.dptr=keybuf;
	       	strcpy(password,username);
	       	sprintf(databuf,"%s %c",password,type);
	        	data.dsize=strlen(databuf)+1;
	         	data.dptr=databuf;
	         	if(gdbm_store(dbf,key,data,GDBM_INSERT))
            	        {	
             			printf("\nError occured!Emp id exists.Member  is not added\n");
            		} 
             		else    
             		{
             			printf("\nFaculty account Created\n");
             			Faculty();
             		}
	   	}
	  		
					
		
	}
	else if(a==3)    //Authentication for Student
	{	int ch;
               getchar();
		printf("\n\t\t\tWelcome to Central Library");
		printf("\n\nDo you want to\n1.Login\n2.Signup");
		printf("\n\nEnter your choice  :");
        	scanf("%d",&ch);
		if(ch==1)
		{
			int attempts=1,flag=0;
			int maxTry = 3;
			while(attempts<=maxTry&&flag==0)
    			{
	    			printf("\nEnter a User name  :");
        			scanf("%s",username);
        			sprintf(keybuf,"%s",username);
       			key.dsize=strlen(keybuf)+1;
        			key.dptr=keybuf;
        			if(gdbm_exists (dbf,key))
       			 {      char realType;
       			 	char realPassword[50];
       			 	data=gdbm_fetch(dbf,key);
             				strcpy(databuf,data.dptr);
             				sscanf(databuf,"%s %c",realPassword,&realType);
             				if(realType=='S')
             				{
           				
           				printf("\n\nPassword  : ");

         				//Disable echo
       				termios oldt;
				       tcgetattr(STDIN_FILENO, &oldt);
				       termios newt = oldt;
				       newt.c_lflag &= ~ECHO;
				       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				   
				       // Input the password
				       scanf("%s",password);
				 
				      //Re-enable
				       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
             
             			        
             				if(strcmp(password,realPassword)==0)
             				{
             					flag=1;
              					system("clear");
              					Student();
              				}
    					else
     					{	system("clear");		
       					printf("\nPassword incorrect!\nYou have %d attempts remaining \n",(3-attempts));
       					attempts++;
       					
   					}
   					}
   					else
   					{
   						printf("\nYou dont have Permission to access this\n");
   						exit(0);
   					}
   					
				}

				else
 				{
 					system("clear");
        				printf("\nWrong user name!\nYou have %d attempts remaining\n ",(3-attempts));
        				attempts++;
       			}
			}
		}
		if(ch==2)
		{	
		   	type='S';
		   	system("clear");
           		printf("\nEnter a Unique user name  :");
           		scanf("%s",username);
	      		sprintf(keybuf,"%s",username);
	      		key.dsize=strlen(keybuf)+1;
	       	key.dptr=keybuf;
	       	strcpy(password,username);
	       	sprintf(databuf,"%s %c",password,type);
	        	data.dsize=strlen(databuf)+1;
	         	data.dptr=databuf;
	         	if(gdbm_store(dbf,key,data,GDBM_INSERT))
            	        {	
             			printf("\nError occured!Emp id exists.Member  is not added\n");
            		} 
             		else    
             		{
             			printf("\nStudent account Created\n");
             			Student();
             		}
	   	}
	  		
					
		
	}		
	gdbm_close(dbf);
    	return ;
}













int main(int argc,char* argv[])
{
        int ch;

x:system("clear");
        printf("\n\t\t\t\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n\n\t\t\t\n");
        printf("\n\t\t\t\t\t\tSelect Profile \n");
        printf("\n\t\t\t\t\t\t1.Librarian\n\n\t\t\t\t\t\t2.Faculty\n\n\t\t\t\t\t\t3.Student\n\n\t\t\t\t\t\t4.Help\n\n\t\t\t\t\t\t5.Close Application\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
         case 1:system("clear");
                authenticate(1);
                break;
         case 2:system("clear");
                authenticate(2);
                break;
         case 3:system("clear");
                authenticate(3);
                break;
         case 4:system("clear");
                Help();
                goto x;
                break;
         case 5:exit(0);
         
        default:printf("\n\t\tPlease enter correct option :(");
                system("clear");
                goto x;
        }
}
