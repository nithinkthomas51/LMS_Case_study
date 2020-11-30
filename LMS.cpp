#include<iostream>
#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<cstring>
#include <termios.h>
#include <unistd.h>
#include<sstream>

using namespace std;


//Define Database
GDBM_FILE dbf,dbb,dbp,dbr;
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
   void SearchBook(){			//searching book
       		int a;
       		printf("\n\n\t\t\t\t\t\t1.Particular Book\n\n\t\t\t\t\t\t2.List of Books\n\n\t\t\t\t\t\t3.Back\n\n\t\t\t\t\t\tEnter your choice : ");
       		scanf("%d",&a);
       		dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
       		if(a==2) {
 	printf("How do you want to search book?\n\n\t\t\t\t\t\t1.Name of the book\n\n\t\t\t\t\t\t2.Name of the author\n\n\t\t\t\t\t\t3.Category\n\n\t\t\t\t\t\t4.Back\n\n\t\t\t\t\t\tEnter your choice : ");
 	int csb;
 	char chsb[30];
 	scanf("%d",&csb);
 	switch(csb){
 	
 		case 1:
 			getchar();
 			printf("Book name : ");
 			fgets(chsb,30,stdin);
 			sprintf(keybuf,"%d",ISBN);
 			key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
 			key=gdbm_firstkey(dbb);
    	while(key.dptr){
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c %d",bookName,author,publication,category,&ref);
   			strcat(bookName,"\n");
    		if(strcasecmp(chsb,bookName)==0){
    		printf("\nISBN :%s  ",key.dptr);
    		printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory : %s\n\n\n",bookName,author,publication,category);
    		//break;
    		}
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbb,key);
    		free(key.dptr);
    		key=nextkey;
    		}
			break;
    		
    	
    	case 2:
    		getchar();
    		printf("Author : ");
 			fgets(chsb,30,stdin);
 			sprintf(keybuf,"%d",ISBN);
 			key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
 			key=gdbm_firstkey(dbb);
    	while(key.dptr){
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c %d",bookName,author,publication,category,&ref);
    		strcat(author,"\n");
    		if(strcasecmp(chsb,author)==0){
    		printf("\nISBN :%s  ",key.dptr);
    		printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory : %s\n\n\n",bookName,author,publication,category);
    		//break;
    		}
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbb,key);
    		free(key.dptr);
    		key=nextkey;
    		}
    		break;
    		
    		
    	case 3:
    		getchar();
    		printf("Category : ");
 			fgets(chsb,30,stdin);
 			sprintf(keybuf,"%d",ISBN);
 			key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
 			key=gdbm_firstkey(dbb);
    	while(key.dptr){
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c %d",bookName,author,publication,category,&ref);
    		strcat(category,"\n");
    		if(strcasecmp(chsb,category)==0){
    		printf("\nISBN :%s  ",key.dptr);
    		printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory : %s\n\n\n",bookName,author,publication,category);
    		//break;
    		}
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbb,key);
    		free(key.dptr);
    		key=nextkey;
    		}
    		break;
    		
    	
    	default: 
    		printf("Enter valid option\n");
    			
 		}
 		
 	}
 	else if(a==1){
 		getchar();
 		char bn[30],au[30];
 		printf("Book Name : ");
 		fgets(bn,30,stdin);
 		printf("Author : ");
 		fgets(au,30,stdin);
 		sprintf(keybuf,"%d",ISBN);
 		key.dsize=strlen(keybuf)+1;
        key.dptr=keybuf;
 		key=gdbm_firstkey(dbb);
    	while(key.dptr){
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c %d",bookName,author,publication,category,&ref);
    		strcat(bookName,"\n");
    		strcat(author,"\n");
    		if((strcasecmp(bn,bookName)==0) && (strcasecmp(au,author)==0)){
    		printf("\nISBN :%s  ",key.dptr);
    		printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory : %s\n\n\n",bookName,author,publication,category);
    		//break;
    		}
    		//else
    			//printf("Book not found\n");
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbb,key);
    		free(key.dptr);
    		key=nextkey;
    		}
    		}
    		gdbm_close(dbb);
    		}
    void purchase_req(char* username){
    		dbr=gdbm_open("pur_req.db",0,GDBM_WRCREAT,0666,0);
			if(!dbr)
			{
				printf("\nError occured while receiving the data, please try again");
				printf("\n");
			}
    		getchar();
    		printf("Book Name : ");
    		fgets(bookName,30,stdin);
    		printf("Author : ");
    		fgets(author,30,stdin);
    		srand(time(NULL));
    		int a=rand()%100;
    		sprintf(keybuf,"%d",a);
    		key.dsize=strlen(keybuf)+1;
			key.dptr=keybuf;
			int status=0,approval=0;
    		sprintf(databuf,"%s %s %s %d %d",username,bookName,author,status,approval);
			data.dsize=strlen(databuf)+1;
			data.dptr=databuf;
    		if(gdbm_store(dbr,key,data,GDBM_INSERT))
    		{	
   		 		printf("\nError occured!Request exists.Book  is not added\n");
   		 		exit(0);
        	}
        	else 
				printf("\nPurchase Request placed\n");	

			gdbm_close(dbr);
           
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
        	       	getchar();
        	      	printf("\n Book Name  : ");
        	       	fgets(bookName,30,stdin);
        	       	printf("\n Author  : ");
        	       	fgets(author,30,stdin);
        	      	printf("\n Publication  : ");
        	       	fgets(publication,30,stdin);
        	       	printf("\n Category  : ");
        	        fgets(category,30,stdin);
        	       	printf("\n Is this a Reference Book?  (0 for No/1 for Yes): ");
        	       	scanf("%d",&ref);
        	       	AddBook();
        	       	break;
        	       case 3:  system("clear");
        	      	        printf("\n ISBN :");
        	      	        scanf("%d",&ISBN);
        	      	        DeleteBook();
        	      	        break;
        	       case 4:  int status,approval;
        	       		dbr=gdbm_open("pur_req.db",0,GDBM_WRCREAT,0666,0);
				if(!dbr)
				{
					printf("\nError occured while receiving the data, please try again");
					printf("\n");
				}  
				key=gdbm_firstkey(dbr);
			        while(key.dptr)
			        {
			            char ch;
				    data=gdbm_fetch(dbr,key);
				    strcpy(databuf,data.dptr);
				    sscanf(databuf,"%s %[^\n]%*c %[^\n]%*c  %d %d",username,bookName,author,&status,&approval);
				    if(status==0)
				    {
				      cout<<"The User "<<username<<" has placed a purchase request for the following"<<endl<<"Bookname : "<<bookName<<endl<<"Author   : "<<author<<endl<<"Approve ?(Y/N)";
				      cin>>ch;
				      if(ch=='y'||ch=='Y')
				      {
				        status=1;
				        sprintf(databuf,"%s %s %s %d %d",username,bookName,author,status,approval);
				        data.dsize=strlen(databuf)+1;
     					data.dptr=databuf;
     					gdbm_store(dbr,key,data,GDBM_REPLACE);
				      }
				      else
				      {
				      status=1;
				      approval=1;
				      //gdbm_delete(dbr,key);
				      
				      
				      }
				    }
				      datum nextkey;
    				  nextkey=gdbm_nextkey(dbr,key);
   				      free(key.dptr);
  				      key=nextkey;
				   }
				   gdbm_close(dbr);
				   
				   
				    break;
        	       
        	       case 5: changePassword();
        	       	break;
        	       	
        	       
        	      	        
        	 
        	 }
        
     } 
           
    gdbm_close(dbf);
}


    
    void PurchaseRequest();
    void RemoveUser();

};


class Stud:public Book
{   	int id;
	public:
    	void Student(char* username){
		int ch;
        printf("\n\nWelcome Student \n\n");
        printf("\n\t\t\t\t\t\tSelect an Option \n");
        printf("\n\t\t\t\t\t\t1.Search Book or Journal\n\n\t\t\t\t\t\t2.Book/Journal status\n\n\t\t\t\t\t\t3.Borrow Book \n\n\t\t\t\t\t\t4.Reserve Book\n\n\t\t\t\t\t\t5.Cancel Reservation\n\n\t\t\t\t\t\t6.Purchase Request\n\n\t\t\t\t\t\t7.Notification\n\n\t\t\t\t\t\t8.Close Application\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
        
        switch(ch){
        	case 1:
        		SearchBook();
        		break;
        	case 2:
        		purchase_req(username);
        		break;
        		
        		}
        	
        }
    /*void SearchBook();
    void Borrow();
    void BookStatus();
    void Reserve();
    void ReserveCancellation();
    void PurchaseRequest();
    */
};

class Fac:public Book
{
    int id;
	public:
    void Faculty(){
    	int ch;
        printf("\n\nWelcome Faculty \n\n");
        printf("\n\t\t\t\t\t\tSelect an Option \n");
        printf("\n\t\t\t\t\t\t1.Search Book or Journal\n\n\t\t\t\t\t\t2.Book/Journal status\n\n\t\t\t\t\t\t3.Borrow Book \n\n\t\t\t\t\t\t4.Reserve Book\n\n\t\t\t\t\t\t5.Cancel Reservation\n\n\t\t\t\t\t\t6.Purchase Request\n\n\t\t\t\t\t\t7.Notification\n\n\t\t\t\t\t\t8.Close Application\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
        
        switch(ch){
        	case 1:
        		SearchBook();
        		}
        }
    /*void SearchBook();
    void Borrow();
    void BookStatus();
    void Reserve();
    void ReserveCancellation();
*/
};



//Student


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

/*void  Faculty()
{ 
	int a;
        printf("\n\nWelcome Faculty \n\n Press any key \n");
        scanf("%d",&a);
}
*/

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
	{	Fac f;	
		int ch;
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
              					f.Faculty();
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
             			f.Faculty();
             		}
	   	}
	  		
					
		
	}
	else if(a==3)    //Authentication for Student
	{	Stud s;
		int ch;
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
              					s.Student(username);
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
             			s.Student(username);
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
                goto x;
                break;
         case 5:exit(0);
         
        default:printf("\n\t\tPlease enter correct option :(");
                system("clear");
                goto x;
        }
}
