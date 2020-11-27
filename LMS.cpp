#include<iostream>
#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<cstring>
#include <termios.h>
#include <unistd.h>
using namespace std;

//Define Database
GDBM_FILE dbf,dbb,dbp;
datum key,data;
char keybuf[50],databuf[512];

//void Login(char ch)

void authenticate(int);
void changePassword();

class Book
{ public:
  char bookName[30];
  char publication[30];
  char category[30];
  int ref;
  char author[30];
  int ISBN;
  /*string getBookName(void)const
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
  }*/
  void AddBook()
  {	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	
	sprintf(keybuf,"%d",ISBN);
	key.dsize=strlen(keybuf)+1;
	key.dptr=keybuf;
	sprintf(databuf,"%s %s %s %s %d",bookName,author,publication,category,ref);
	data.dsize=strlen(databuf)+1;
	data.dptr=databuf;
    	if(gdbm_store(dbb,key,data,GDBM_INSERT))
    	{	
   		 printf("\nError occured!ISBN exists.Book  is not added\n");
   		 exit(0);
        }
        else 
	printf("\nBook added\n");	

	gdbm_close(dbb);
           
 } 
  void DeleteBook()
  {	char ch;
  	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	
	sprintf(keybuf,"%d",ISBN);
	key.dsize=strlen(keybuf)+1;
	key.dptr=keybuf;
	data=gdbm_fetch(dbb,key);
        strcpy(databuf,data.dptr);
        sscanf(databuf,"%s %s %s %s %d",bookName,author,publication,category,&ref);
        printf("\nDo You want to delete  %s ?(Y/N)",bookName);
        cin>>ch;
        if(ch=='y'||ch=='Y')
        {int ret;
        	ret=gdbm_delete(dbb,key);
    		if(ret==0)
    			printf("\n The Book is removed\n");
    		else
    		printf("\n Error occured,please try again \n");
        }
        else
        exit(0);
        gdbm_close(dbb);
        }
    	
 
};



class Lib:public Book
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
             	exit(0);
            }
            goto a;
         }
         else 
         {     int ch,n;
         	sprintf(keybuf,"%s",username);
	    	key.dsize=strlen(keybuf)+1;
	    	key.dptr=keybuf;
	    	data=gdbm_fetch(dbf,key);
	    	strcpy(databuf,data.dptr);
               sscanf(databuf,"%s ",name);
	        a:printf("\n\t\t\t\t*********** Welcome %s ***********\n\n\t\t\t\n",name);
        	printf("\n\t\t\t\t\t\tSelect an Option \n");
               printf("\n\t\t\t\t\t\t1.Add New User\n\n\t\t\t\t\t\t2.Add Book or Journal\n\n\t\t\t\t\t\t3.Remove Book or Journal \n\n\t\t\t\t\t\t4.Purchase Requests\n\n\t\t\t\t\t\t5.Change Password\n\n\t\t\t\t\t\t6.Notifications\n\n\t\t\t\t\t\t7.Close Application\n");
        	printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        	scanf("%d",&ch);
        	switch(ch)
        	{
        		case 1: system("clear");
        			c:printf("\n\n\nDo you want add \n1.Student  Account \n2.Faculty Account\nEnter your choice  :");
        			cin>>n;
        			if(n==1)authenticate(3);
        			else if(n==2)authenticate(2);
        			else { system("clear"); cout<<endl<<"\n\nWrong Choice"; goto c;}
        			break;
        			
        		case 2: system("clear");
        	      	        printf("\n ISBN :");
        	       	scanf("%d",&ISBN);
        	      	 	printf("\n Book Name  : ");
        	       	scanf("%s",bookName);
        	       	printf("\n Author  : ");
        	       	scanf("%s",author);
        	      	 	printf("\n Publication  : ");
        	       	scanf("%s",publication);
        	       	printf("\n Category  : ");
        	       	scanf("%s",category);
        	       	printf("\n Is this a Reference Book?  (0 for No/1 for Yes): ");
        	       	scanf("%d",&ref);
        	       	AddBook();
        	       	break;
        	       case 3:  system("clear");
        	      	        printf("\n ISBN :");
        	      	        scanf("%d",&ISBN);
        	      	        DeleteBook();
        	      	        break;
        	       case 4:  break;
        	       
        	       case 5: changePassword();
        	       	break;
        	       	
        	       
        	      	        
        	 
        	 }
        
     } 
           
    gdbm_close(dbf);
}


    
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
	int a;
        printf("\n\nHELP\n\n");
        scanf("%d",&a);
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
              					Student();
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
             			Student();
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
	//gdbm_close(dbf);
    	return ;
}

//Change Password

void changePassword()
{	dbp=gdbm_open("users.db",0,GDBM_WRCREAT,0666,0);
  	if(!dbp)
  	{
    		printf("\nError occured while receiving the data, please try again");
    		printf("\n");
  	}
  	char username[50];
	printf("\nEnter Your name  :");
        scanf("%s",username);
        sprintf(keybuf,"%s",username);
        key.dsize=strlen(keybuf)+1;
        key.dptr=keybuf;
        if(gdbm_exists (dbp,key))
        { char password[50];
          char realType;   
          char realPassword[50];
          char newPassword1[50];
          char newPassword2[50];
          data=gdbm_fetch(dbp,key);
          strcpy(databuf,data.dptr);
          sscanf(databuf,"%s %c",realPassword,&realType);
          printf("\n\nEnter Current Password  : ");

		//Disable echo
      		 termios oldt;
		 tcgetattr(STDIN_FILENO, &oldt);
		 termios newt = oldt;
		 newt.c_lflag &= ~ECHO;
	       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
																					   
		//Input the password
																					       		scanf("%s",password);
																					 
		//Re-enable
																					       		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
             
             			        
                if(strcmp(password,realPassword)==0)
                {
                    q:cout<<endl<<"\n Enter New Password";
                    scanf("%s",newPassword1);
                    cout<<endl<<"\n Enter New Password Again";
                    scanf("%s",newPassword2);
                    if(strcmp(newPassword1,newPassword2)==0)
                    {
                    	sprintf(databuf,"%s %c",newPassword1,realType);
                    	data.dsize=strlen(databuf)+1;
     		     	data.dptr=databuf;
		     	if(gdbm_store(dbp,key,data,GDBM_REPLACE))
		     	{
		     		printf("\n Error occured, Password not Changed\n");
		      		exit(0);
		     	}
		     	else printf("\n Password Changed\n");
                }
                else
                {
                cout<<"Password Dont Matcn \n Try Again";
                goto q;
                }
                }
           }
           else
 		{
 			system("clear");
        		printf("\nWrong user name!");
        		exit(0);
        		
       			}
       gdbm_close(dbp);
        
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
                break;
         case 5:exit(0);
         
        default:printf("\n\t\tPlease enter correct option :(");
                system("clear");
                goto x;
        }
}
