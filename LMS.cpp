#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<cstring>
#include <termios.h>
#include <unistd.h>

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

class Lib:public Books
{
 	int userid;
 	char name
	public:
	void librarian;
};


class Stud:public Book
{
	public:
        void Student();
};

class Fac:public Book
{

};
*/



//Student
void /*Stud::*/Student()
{
	int a;
        printf("\n\nWelcome Student \n\n Press any key \n ");
        scanf("%d",&a);

}



//Librarian
void /*Lib::*/Librarian()
{   
	int b;
  	printf("\n\n\t\t\t************Welcome Librarian************** \n\nPress any key \n");
  	scanf("%d",&b);
}



//Faculty
void /*Fac::*/ Faculty()
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
{
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
             			else    printf("\nLibrarian account Created\n");
	   		}
	  		else   printf("Access Denied !");
	  	}
		else
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
             				{
             					flag=1;
              					system("clear");
              					Librarian();
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
                break;
         case 5:exit(0);
         
        default:printf("\n\t\tPlease enter correct option :(");
                system("clear");
                goto x;
        }
}
