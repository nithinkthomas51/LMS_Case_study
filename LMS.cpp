#include<iostream>
#include<cstdio>
#include<gdbm.h>
#include<stdlib.h>
#include<cstring>
#include <termios.h>
#include <unistd.h>
#include <sstream>

using namespace std;

//Define Database
GDBM_FILE dbf,dbb,dbp,dbl,dbs,dbr,dbn,dbpr;
datum key,data,key1,data1,key2,data2;
char keybuf[50],databuf[512];
char nu[]="nill";
int bkid1;

//void Login(char ch)

void authenticate(int);
void changePassword();


class Notif{	
	public:
	void Notification(char *username){
	char username1[50];
	char ttq;
	char notific[256],q;
	dbn=gdbm_open("Notification.db",0,GDBM_WRCREAT,0666,0);
  	 if(!dbn)
  	 {
    		printf("\nError occured while retrieving notifications, please try again");
    		printf("\n");
    		exit(0);
  	 }
	
	do{
	key=gdbm_firstkey(dbn);
	system("clear");
	cout<<"\n\t\t\t************"<<username<<"'s Notifications**************\n\n\n"<<endl;
    	while(key.dptr){
		data=gdbm_fetch(dbn,key);  
		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%s %[^\n]s",username1,notific);
    		int g=strcmp(username,username1);
    		if(!g){cout<<notific<<endl;}
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbn,key);
    		free(key.dptr);
   		key=nextkey;
    		}
  
    	cout<<"\n\nDo you want to exit(Y|N)  ";
    	cin>>ttq;
    	}while(ttq=='n' or ttq=='N');
    	
	gdbm_close(dbn);   
         
	}

	void setNotification(char *username, int type, int bid, char *preq)
	{
		int k;
		int acno1[10];
		char notific[256];
		time_t now=time(0);
		tm *t1=localtime(&now);//+1209600);
		dbn=gdbm_open("Notification.db",0,GDBM_WRCREAT,0666,0);
	   rand:srand(time(NULL));
		k=0;
        	for(int i=0;i<10;i++)
               	acno1[i]=rand()%100; 
    		for (int i=0;i<10;i++)
    			k=10*k+acno1[i];
    		sprintf(keybuf,"%d",k);
		key.dsize=strlen(keybuf)+1;
		key.dptr=keybuf;
   		if(gdbm_exists (dbn,key))
    			{
    			goto rand;
    			}


               if(type==1){	//Borrow
  
               	now+=1209600;
                   	sprintf(notific,"The book having number %d is issued. Due date is on %d-%d-%d.\n",bid,t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
			} 
       	else if(type==2)	//Reserve
               	sprintf(notific,"The book having number %d is reserved on %d-%d-%d.\n",bid,t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
		else if(type==3)	//Another user reserved
               	sprintf(notific,"The book you borrowed having number %d is reserved on %d-%d-%d by another user.\n",bid,t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
               else if(type==4)	//Reservation cancelled
               	sprintf(notific,"The reservation for book having number %d is cancelled on %d-%d-%d.\n",bid,t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
               else if(type==5)	//Purchase Request accepted
               	sprintf(notific,"The purchase request for book %s is accepted by Librarian\n",preq);
     		else if(type==6)	//Purchase Request rejected
               	sprintf(notific,"The purchase request for book %s is rejected by Librarian\n",preq);
               else if(type==7)	//Sending due notification
               	sprintf(notific,"The book number %d is due on %s\n",bid,preq);	
               	
     		
               sprintf(databuf,"%s %s",username,notific);
               data.dsize=strlen(databuf)+1;
               data.dptr=databuf;
               gdbm_store(dbn,key,data,GDBM_INSERT);	
            //   data=gdbm_fetch(dbn,key);
            //   cout<<data.dptr<<endl;
               gdbm_close(dbn);
            
	}
};

class Report:virtual public Notif
{
	
	
	
	public:
	
	char issname[50],resname[50],issdate[15],duedate[15],retdate[15],resdate[15],retdate1[15];
	
	void getReport(int bookid)
	{
	//char issname[50],resname[50],issdate[15],duedate[15],retdate[15],resdate[15];
	dbr=gdbm_open("Report.db",0,GDBM_WRCREAT,0666,0);
		if(!dbr)
  		{
    		printf("\nError occured while retrieving reports, please try again");
    		printf("\n");
    		exit(0);
    		goto norep;
  	 	}
  	sprintf(keybuf,"%d",bookid);
	key1.dsize=strlen(keybuf)+1;
	key1.dptr=keybuf;
	if(gdbm_exists (dbr,key1))
	{
		data1=gdbm_fetch(dbr,key1);
		strcpy(databuf,data1.dptr);
    		sscanf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
    	}
    	else {cout<<"No reports available for book number "<<bookid<<endl;
    		goto norep;
    		}
    	cout<<"\n\t\t\t************"<<bookid<<"'s Status**************"<<endl;
    	cout<<"Issued to\t : "<<issname<<endl<<"Issued on\t : "<<issdate<<endl<<"Due date\t : "<<duedate<<endl;
    	
    	if(strcasecmp(retdate,"nill")){cout<<"Returned on\t : "<<retdate<<endl;}
    	
    	if(strcasecmp(resname,"nill")){cout<<"Reserved by\t : "<<resname<<endl<<"Reserved on\t : "<<resdate<<endl;}
norep:   	
    	gdbm_close(dbr);
    		
	}
	
	void setReport(int bookid, char *issname1, char *resname1, int type)
	{	
	
	int exists=0;
	//char issname[50],resname[50],issdate[15],duedate[15],retdate[15],resdate[15];	
	dbr=gdbm_open("Report.db",0,GDBM_WRCREAT,0666,0);
		if(!dbr)
  		{
    		printf("\nError occured while retrieving reports, please try again");
    		printf("\n");
    		exit(0);
  	 	}
  	sprintf(keybuf,"%d",bookid);
	key1.dsize=strlen(keybuf)+1;
	key1.dptr=keybuf;
	if(gdbm_exists (dbr,key1))
		{
		
		exists++;
		data1=gdbm_fetch(dbr,key1);
		strcpy(databuf,data1.dptr);
    		sscanf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
    		}
    	time_t now=time(0);
	tm *t1=localtime(&now);
    	if(type==1) //book issued
    		{
    		strcpy(issname,issname1);	//replacing old names
    		strcpy(resname,"nill");
    		strcpy(resdate,"nill");
    		strcpy(retdate,"nill");
 
		sprintf(issdate,"%d-%d-%d",t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
		{
		time_t now=time(0);
		now+=1209600;
		tm *t2=localtime(&now);
		sprintf(duedate,"%d-%d-%d",t2->tm_mday,(t2->tm_mon+1),(t2->tm_year+1900));
		}
		sprintf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
		data1.dsize=strlen(databuf)+1;
		data1.dptr=databuf;
		
		if(exists=0)
		gdbm_store(dbr,key1,data1,GDBM_INSERT);
		else
		gdbm_store(dbr,key1,data1,GDBM_REPLACE);
    	
    		}
    	else if(type==2) //book returned
    		{
		sprintf(retdate,"%d-%d-%d",t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
    		sprintf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
    		data1.dsize=strlen(databuf)+1;
		data1.dptr=databuf;
		gdbm_store(dbr,key1,data1,GDBM_REPLACE);
    		}
    	else if(type==3) //book reserved
    		{
    		strcpy(resname,resname1);
		sprintf(resdate,"%d-%d-%d",t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
		sprintf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
		data1.dsize=strlen(databuf)+1;
		data1.dptr=databuf;
		gdbm_store(dbr,key1,data1,GDBM_REPLACE);
		
		Notif::setNotification(issname,3,bkid1,issname);
		
    		}
    	else if(type==4) //reservation cancelled
    		{
    		strcpy(resname,"nill");
    		strcpy(resdate,"nill");
		sprintf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
		data1.dsize=strlen(databuf)+1;
		data1.dptr=databuf;
		gdbm_store(dbr,key1,data1,GDBM_REPLACE);
		
    		}
    		
	gdbm_close(dbr);
	
	}  
	
	void setRemainder(void)
	{
	
	
	int bkid;
	//char issname[50],resname[50],issdate[15],duedate[15],retdate[15],resdate[15],retdate1[15];

	dbr=gdbm_open("Report.db",0,GDBM_WRCREAT,0666,0);
		if(!dbr)
  		{
    		printf("\nError occured while retrieving reports, please try again");
    		printf("\n");
    		exit(0);
  	 	}
  	key1=gdbm_firstkey(dbr);
  
	while(key1.dptr){
		
		data1=gdbm_fetch(dbr,key1);  
		strcpy(databuf,data1.dptr); 
		sscanf(databuf,"%s %s %s %s %s %s",issname,resname,issdate,duedate,retdate,resdate);
		if(strcasecmp(retdate,"nill")==0)
		{
			time_t now=time(0);
			//now+=345600;
			now+=1209600;
			tm *t1=localtime(&now);

			strcpy(keybuf,key1.dptr);
    			sscanf(keybuf,"%d",&bkid);
			
			sprintf(retdate,"%d-%d-%d",t1->tm_mday,(t1->tm_mon+1),(t1->tm_year+1900));
			
			if(strcasecmp(duedate,retdate)==0)
				Notif::setNotification(issname,7,bkid,duedate);

		}
		datum nextkey;
    		nextkey=gdbm_nextkey(dbr,key1);
    		free(key1.dptr);
   		key1=nextkey;
   		
    		}
	gdbm_close(dbr);
	
	}		
		
		
		
		 
};


class Book:virtual public Notif,virtual public Report
{ 
  public:
  char bookName[20];
  char publication[30];
  char category[30];
  int  ref;
  char author[30];
  int  ISBN;
  char  available;
  char  reserved;





void AddBook()
  {	
  	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	available='y';
	reserved='n';
	sprintf(keybuf,"%d",ISBN);
	key.dsize=strlen(keybuf)+1;
	key.dptr=keybuf;
	sprintf(databuf,"%d %c %c %s %s %s %s",ref,available,reserved,bookName,author,publication,category);
	data.dsize=strlen(databuf)+1;
	data.dptr=databuf;
    	if(gdbm_store(dbb,key,data,GDBM_INSERT))
    	{	
   		 printf("\nError occured!ISBN exists.Book  is not added\n");
   		 exit(0);
        }
        else 
	printf("\nBook added\n");
	sleep(1);	

	gdbm_close(dbb);
           
 } 
 
 
 




void DeleteBook()
  {	
  	char ch;
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
        sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
        printf("\nDo You want to delete  %s ?(Y/N)",bookName);
        cin>>ch;
        if(ch=='y'||ch=='Y')
        {
        	int ret;
        	ret=gdbm_delete(dbb,key);
    		if(ret==0)
    			{printf("\n The Book is removed\n");sleep(1);}
    		else
    		printf("\n Error occured,please try again \n");
        }
        else
        exit(0);
        gdbm_close(dbb);
        }
        
        
        
  






void SearchBook()
       {
       	int a;
       	system("clear");
       	printf("\n\n\t\t\t\t\t\t1.List of Books\n\n\t\t\t\t\t\t");
       	printf("2.Particular Book\n\n\t\t\t\t\t\t3.Back\n\n\t\t\t\t\t\tEnter your choice : ");
       	scanf("%d",&a);
       	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
		if(!dbb)
		{
			printf("\nError occured while receiving the data, please try again");
			printf("\n");
		}
       	if(a==1) 
       	{	
       		char choice[50];
 			printf("How do you want to search book?\n\n\t\t\t\t\t\t");
 			printf("1.Name of the book\n\n\t\t\t\t\t\t");
 			printf("2.Name of the author\n\n\t\t\t\t\t\t");
 			printf("3.Category of the book \n\n\t\t\t\t\t\t");
 			printf("4.Back\n\n\t\t\t\t\t\t");
 			printf("Enter your choice : ");
 			int csb;
 			char chsb[30];
 			scanf("%d",&csb);
		        getchar();
 			if(csb==1)printf("\nBook name : ");
 			if(csb==2)printf("\nAuthor : ");
 			if(csb==3)printf("\nCategory : ");
 			
 			fgets(chsb,30,stdin);
 			strcpy(choice,chsb);
 			key=gdbm_firstkey(dbb);
 			
 			
    			while(key.dptr)
    			{	int b;
    				//char temp[50];
    				data=gdbm_fetch(dbb,key);
    				strcpy(databuf,data.dptr);
    				sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
    				if(csb==1){ strcat(bookName,"\n");b=strcasecmp(bookName,choice);}
    				if(csb==2){ strcat(author,"\n");b=strcasecmp(author,choice);}
    				if(csb==3){ strcat(bookName,"\n");b=strcasecmp(category,choice);}
 			        
 			        if(b==0)
    				{
    					printf("\nISBN : %s  ",key.dptr);
    					printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory :   %s\n\n\n",bookName,author,publication,category);
    					sleep(5);
    				}
    				else if(b==1)
    				{
    					cout<<endl<<"Record not found";
    					}
    			datum nextkey;
    			nextkey=gdbm_nextkey(dbb,key);
    			free(key.dptr);
    			key=nextkey;
    		       }
		}
				
    		
    		else if(a==2)
    		{
    		int flag=0;
 		getchar();
 		char bn[30];
 		printf("Book Name : ");
 		fgets(bn,30,stdin);
 		key=gdbm_firstkey(dbb);
    		while(key.dptr)
    		{
    			data=gdbm_fetch(dbb,key);
    			strcpy(databuf,data.dptr);
    			sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
    			strcat(bookName,"\n");
    	  		if(strcasecmp(bn,bookName)==0)
    	  		{	flag=1;
    				printf("\nISBN :%s  ",key.dptr);
    				printf("\nBook Name : %s \nAuthor : %s \nPublication : %s \nCategory : %s\n\n\n",bookName,author,publication,category);
    				sleep(2);
    			
    			}
    		
    		datum nextkey;
    		nextkey=gdbm_nextkey(dbb,key);
    		free(key.dptr);
    		key=nextkey;
    		}
    		if(flag!=1){ printf("Book not found\n"); sleep(2); }
    		
    		}
    		gdbm_close(dbb);
  }
    		








void purchase_req(char* username)
		{
    		
    		dbpr=gdbm_open("pur_req.db",0,GDBM_WRCREAT,0666,0);
		if(!dbpr)
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
    		
    		int a;
    		nit:a=rand()%100;
    		sprintf(keybuf,"%d",a);
    		key.dsize=strlen(keybuf)+1;
		key.dptr=keybuf;
    		if(gdbm_exists(dbpr,key))goto nit;
    		sprintf(databuf,"%s %s %s ",username,bookName,author);
		data.dsize=strlen(databuf)+1;
		data.dptr=databuf;
    		if(gdbm_store(dbpr,key,data,GDBM_INSERT))
    		{	
   		 		printf("\nError occured!Please Try again later\n");
   		 		exit(0);
        	}
        	else 
				{cout<<endl<<a;
				printf("\nPurchase Request placed\n");sleep(2);}

			gdbm_close(dbpr);
           
 } 
 
 
void BorrowBook(char* username,char t)
{
	int flag=0;
	char borrow[50];
	Report r;
      	Notif n;
      	
	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	getchar();
	printf("\n\nEnter name of the book to be borrowed  :");
	//scanf("%s",borrow);
	fgets(borrow,50,stdin);
 	key=gdbm_firstkey(dbb);
 	while(key.dptr)
    	{	//char temp[50];
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
    		//strcpy(temp,bookName);
    		strcat(bookName,"\n");
    		if(strcasecmp(borrow,bookName)==0)
    		{	if(ref==1&&t=='s'){cout<<"Reference books can only be borrowed by the faculty";goto u;}
    			if(available=='y')
    			{	
    				flag=1;
    				reserved='n';
    				available='n';
    				strcat(author,"\n");
    				strcat(publication,"\n");
    				strcat(category,"\n");
    				sprintf(databuf,"%d %c %c %s %s %s %s",ref,available,reserved,bookName,author,publication,category);
    				data.dsize=strlen(databuf)+1;
				data.dptr=databuf;
    				if(gdbm_store(dbb,key,data,GDBM_REPLACE))
      					printf("Error occured, data is not modified\n");
     				else 
     					{printf("Book Successfully Rented\n");
     					 sleep(2);
     					
     					strcpy(keybuf,key.dptr);
    					sscanf(keybuf,"%d",&bkid1);
     					r.setReport(bkid1,username,username,1);
     					//r.getReport(bkid1);
     					Notif::setNotification(username,1,bkid1,username);
     					//n.Notification(username);
   
     					}	
     			}
     	          	else
     	          	{
     	          		cout<<endl<<"Book Already Borrowed"<<endl;
     	          		sleep(2);
     	          	}
     	       }
     	       datum nextkey;
    	       nextkey=gdbm_nextkey(dbb,key);
    	       //free(key.dptr);
    	       key=nextkey;
	}
	if(flag==0)
	cout<<endl<<"Book not found";
	u:gdbm_close(dbb);
}

void ReserveBook(char* username,char t)
{	
	int flag=0;
	char reserve[50];
	Report r;
      	//Notif n;
	
	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	system("clear");
	getchar();
	printf("\n\nEnter name of the book to be reserved  :");
	//scanf("%s",reserve);
	fgets(reserve,50,stdin);
 	key=gdbm_firstkey(dbb);
 	while(key.dptr)
    	{	//char temp[50];
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
    		//strcpy(temp,bookName);
    		strcat(bookName,"\n");
    		if(strcasecmp(reserve,bookName)==0)
    		{	if(ref==1&&t=='s'){cout<<"Reference books can only be reserved by the faculty";goto uv;}
    			if(reserved=='n')
    			{
    				flag=1;
    				reserved='y';
    				strcat(author,"\n");
    				strcat(publication,"\n");
    				strcat(category,"\n");
    				sprintf(databuf,"%d %c %c %s %s %s %s",ref,available,reserved,bookName,author,publication,category);
    				data.dsize=strlen(databuf)+1;
				data.dptr=databuf;
    				if(gdbm_store(dbb,key,data,GDBM_REPLACE))
      					printf("Error occured, data is not modified\n");
     				else 
     					{printf("Book Successfully Reserved\n");
     					
     					strcpy(keybuf,key.dptr);
    					sscanf(keybuf,"%d",&bkid1);
     					r.setReport(bkid1,username,username,3);
     					//r.getReport(bkid1);
     					Notif::setNotification(username,2,bkid1,username);
     					//n.Notification(username);
   
     					
     					}	
     			}
     	          	else
     	          	{	flag=1;
     	          		cout<<endl<<"Book Already Reserved";
     	          	}
     	       }
     	       datum nextkey;
    	       nextkey=gdbm_nextkey(dbb,key);
    	       //free(key.dptr);
    	       key=nextkey;
	}
	if(flag==0)cout<<endl<<"Book not found";
	uv:gdbm_close(dbb);
}


void CancelReservation(char* username)
{
	Report r;
     // Notif n;
	
	int flag=0;
	char reserve[50];
	dbb=gdbm_open("books.db",0,GDBM_WRCREAT,0666,0);
	if(!dbb)
	{
		printf("\nError occured while receiving the data, please try again");
		printf("\n");
	}
	system("clear");
	getchar();
	printf("\n\nEnter name of the book whose reservation is to be cancelled  :");
	//scanf("%s",reserve);
	fgets(reserve,50,stdin);
 	key=gdbm_firstkey(dbb);
 	while(key.dptr)
    	{	
    		
    		data=gdbm_fetch(dbb,key);
    		strcpy(databuf,data.dptr);
    		sscanf(databuf,"%d %c %c %[^\n]%*c %[^\n]%*c %[^\n]%*c %[^\n]%*c ",&ref,&available,&reserved,bookName,author,publication,category);
    		//strcpy(temp,bookName);
    		strcat(bookName,"\n");
    		if(strcasecmp(reserve,bookName)==0)
    		{	
    			if(reserved=='y')
    			{
    				flag=1;
    				reserved='n';
    				strcat(author,"\n");
    				strcat(publication,"\n");
    				strcat(category,"\n");
    				sprintf(databuf,"%d %c %c %s %s %s %s",ref,available,reserved,bookName,author,publication,category);
    				data.dsize=strlen(databuf)+1;
				data.dptr=databuf;
    				if(gdbm_store(dbb,key,data,GDBM_REPLACE))
      					{printf("Error occured, data is not modified\n");sleep(2);}
     				else 
     					{flag=1;
     					printf("Reservation Cancelled\n");
     					sleep(2);
     					
     					strcpy(keybuf,key.dptr);
    					sscanf(keybuf,"%d",&bkid1);
     					r.setReport(bkid1,username,username,4);
     					//r.getReport(bkid1);
     					Notif::setNotification(username,4,bkid1,username);
     					//n.Notification(username);
     					
     					}	
     			}
     	          	else
     	          	{
     	          		flag=1;
     	          		cout<<endl<<"This book has not been reserved"<<endl;
     	          	}
     	       }
     	       datum nextkey;
    	       nextkey=gdbm_nextkey(dbb,key);
    	       //free(key.dptr);
    	       key=nextkey;
	}
	if(flag==0)cout<<endl<<"Book not found";
	gdbm_close(dbb);
}



	


   	       
    				
    				
    			
		
 
 
 
 
 
 
 
 
    	
 
};













class Lib:virtual public Book,virtual public Notif
{
    char name[50];

    public:


Lib(){}
    








void Librarian(char* username)
     {   
     		
     	Report r;
      	//Notif n;
      
          
         dbl=gdbm_open("librarian.db",0,GDBM_WRCREAT,0666,0);
  	 if(!dbl)
  	 {
    		printf("\nError occured while receiving the data, please try again");
    		printf("\n");
  	 }
  	 key=gdbm_firstkey(dbl);
    	 if(key.dptr==NULL)
    	 {  getchar();
    	    printf("\t\t\tWelcome Librarian! \n\n\n\n\nPlease enter your Name    :");
    	    fgets(name,50,stdin);
    	    sprintf(keybuf,"%s",username);
	    key.dsize=strlen(keybuf)+1;
	    key.dptr=keybuf;
	    sprintf(databuf,"%s",name);
	    data.dsize=strlen(databuf)+1;
	    data.dptr=databuf;
	    if(gdbm_store(dbl,key,data,GDBM_INSERT))
            {	
             	printf("\nError occured!Emp id exists.Member  is not added\n");
             	exit(0);
            }
            goto a;
         }
         else 
         {     int ch;
        
         	do
         	{
         	
         	int n;
		sprintf(keybuf,"%s",username);
		key.dsize=strlen(keybuf)+1;
		key.dptr=keybuf;
		data=gdbm_fetch(dbf,key);
		strcpy(databuf,data.dptr);
		sscanf(databuf,"%[^\n]%*c",name);
		a:system("clear");
		printf("\n\t\t\t\t\t\tWelcome %s \n\n\t\t\t\n",name);
         	printf("\n\t\t\t\t\t\tSelect an Option \n");
		printf("\n\t\t\t\t\t\t1.Add New User\n\n\t\t\t\t\t\t");
		printf("2.Add Book or Journal\n\n\t\t\t\t\t\t3.Remove Book or Journal");
		printf(" \n\n\t\t\t\t\t\t4.Purchase Requests\n\n\t\t\t\t\t\t");
		printf("5.Change Password\n\n\t\t\t\t\t\t6.Send Remainders\n\n\t\t\t\t\t\t7.Book Status\n\n\t\t\t\t\t\t8.Back\n\n\t\t\t\t\t\t9.Exit\n\n");
        	printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        	scanf("%d",&ch);
        	switch(ch)
        	{
        		case 1: system("clear");
        			c:printf("\n\n\n\nDo you want add \n\n\n1.Student  Account \n\n\n2.Faculty Account\n\n\nEnter your choice  :");
        			cin>>n;
        			if(n==1)authenticate(3);
        			else if(n==2)authenticate(2);
        			else { system("clear"); cout<<endl<<"\n\nWrong Choice"; goto c;}
        			break;
        			
        		case 2: system("clear");
        	      	        printf("\n ISBN :");
        	       	scanf("%d",&ISBN);
        	       	
        	       	
        	       	printf("\n Is this a Reference Book?  (0 for No / 1 for Yes): ");
        	       	scanf("%d",&ref);
        	       	getchar();
        	       	
        	      	 	printf("\n Book Name  : ");
        	      	 	//scanf("%[^\n]s",bookName);
        	      	 	//strcpy(bookName,spacetouscore(bookName));
        	      	 	fgets(bookName,30,stdin);
        	      	 
        	       	
        	       	
        	       	printf("\n Author  :" );
        	       	//scanf("%[^\n]s",author);
        	      	 	//strcpy(author,spacetouscore(author));
        	      	 	fgets(author,30,stdin);
        	      	 	
        	       	
        	       	     	       	
        	       	
        	      	 	printf("\n Publication  :");
        	      	 	//scanf("%[^\n]s",publication);
        	      	 	//strcpy(publication,spacetouscore(publication));
        	      	 	fgets(publication,30,stdin);
        	      	 	
        	       	
        	       	
        	       	
        	       	printf("\n Category  :");
                               //scanf("%[^\n]s",category);
        	      	 	//strcpy(category,spacetouscore(category));
        	      	 	fgets(category,30,stdin);
        	      	 
        	       	
        	       	
        	       	AddBook();
        	       	break;
        	       
        	       
        	       
        	       case 3:  system("clear");
        	      	        printf("\n ISBN :");
        	      	        scanf("%d",&ISBN);
        	      	        DeleteBook();
        	      	        break;
        	      
        	      
        	      
        	      
        	      
        	      
        	       case 4 :  
        	       	dbpr=gdbm_open("pur_req.db",0,GDBM_WRCREAT,0666,0);
				if(!dbpr)
				{
					printf("\nError occured while receiving the data, please try again\n");
					exit(0);
				}  
				key2=gdbm_firstkey(dbpr);
			        while(key2.dptr)
			        {	
			           char chh;
				   data=gdbm_fetch(dbpr,key2);
				   strcpy(databuf,data.dptr);
				   sscanf(databuf,"%s %[^\n]%*c %[^\n]%*c ",username,bookName,author); 
				   cout<<endl<<endl<<"The User "<<username<<" has placed a purchase request for the following";
				   cout<<endl<<"Bookname : "<<bookName<<endl<<"Author   : "<<author<<endl<<"Approve ?(Y/N)";
				   cin>>chh;
				   if(chh=='y'||chh=='Y')Notif::setNotification(username,5,12345,bookName);
				   else if(chh=='n' || chh=='N')Notif::setNotification(username,6,12345,bookName);
				    datum nextkey2;
    				    nextkey2=gdbm_nextkey(dbpr,key2);
    				    gdbm_delete(dbpr,key2);
   				    free(key2.dptr);
  				    key2=nextkey2;
				}
				   gdbm_close(dbpr);
				   goto a;
        	       
        	       case 5:    changePassword();
        	       	   break;
        	       	   
        	       case 6:	r.setRemainder();
        	       	break;
        	       	
        	       case 7:	char option;
        	       	do{
        	       		system("clear");
        	       		cout<<"Enter the ISBN : ";
        	       		int booknumber;
        	       		cin>>booknumber;
        	       		r.getReport(booknumber);
        	       		cout<<endl<<"\n\t\t\t\tDo you want to check status of another book/journal?(Y|N)";
        				cin>>option; 
       			}while(option=='y'||option=='Y');
        	       
        	       
        	       case 8: break;
        	       
        	       case 9: exit(0);
        	       
        	       default : cout<<endl<<"Invalid Option try again"<<endl;
        	       	  sleep(2);	
        	       
        	      	        
        	 
        	 }}while(ch!=8);
        
     } 
           
    gdbm_close(dbl);
}


    





//void PurchaseRequest();
//void RemoveUser();

};










class Stud:virtual public Book,virtual public Report,virtual public Notif
{   	int id;
	public:
    	
    	void Student(char* username,char userType)
    	{	int ch;
		if(userType=='f')
		{
			cout<<endl<<"Your username is set as your password , Please Change your password before you continue"<<endl;
			changePassword();
		}
		do{
		char t;
		t='s';
		
		Report r;
      		Notif n;
      		system("clear");
        	printf("\n\n\t\t\t\t\t\tWelcome Student \n\n");
        	printf("\n\t\t\t\t\t\tSelect an Option \n");
        	printf("\n\t\t\t\t\t\t1.Search Book or Journal");
        	printf("\n\n\t\t\t\t\t\t2.Book/Journal status");
        	printf("\n\n\t\t\t\t\t\t3.Borrow Book ");
        	printf("\n\n\t\t\t\t\t\t4.Reserve Book\n\n\t\t\t\t\t\t");
        	printf("5.Cancel Reservation\n\n\t\t\t\t\t\t6.Purchase Request\n\n\t\t\t\t\t\t7.Notification");
       	printf("\n\n\t\t\t\t\t\t8.Go Back");
       	printf("\n\n\t\t\t\t\t\t9.Close Application\n");
        	printf("\n\n\n\t\t\t\t\t\tEnter your choice : ");
        	scanf("%d",&ch);
        
		switch(ch)
		{
			case 1 :  SearchBook();
				  break;
        	
        		case 2 :  char option;
        	       	  do{	system("clear");
        	       		cout<<"Enter the ISBN : ";
        	       		int booknumber;
        	       		cin>>booknumber;
        	       		r.getReport(booknumber);
        	       		cout<<endl<<"\n\t\t\t\tDo you want to check status of another book/journal?(Y|N)";
        				cin>>option; 
       			    }while(option=='y'||option=='Y');
        		 	  break;
        	
        		case 3 :  BorrowBook(username,t);
        			  break; 
        	        	
        	        case 4 :  ReserveBook(username,t);
        	        	   break; 
        	        
        	        case 5 :  CancelReservation(username);       		
        	       	   break;
        	        
        	        case 6 :  purchase_req(username);
        	        	   break;
        	        
        	        case 7 :  n.Notification(username);
        	        	   break;
        	        
         	        case 8 :  break;
         	        
         	        case 9 :  exit(0);
         	        	
        		default:   printf("\nWrong option ");
        		}
        	
        }while(ch!=8);}
    
};

class Fac:virtual public Book,virtual public Notif,virtual public Report
{
    	int id;
	
	public:
    	
    	void Faculty(char* username,char userType)
    	{	int ch;
		if(userType=='f')
		{
			cout<<endl<<"Your username is set as your password , Please Change your password before you continue"<<endl;
			changePassword();
		}
		
		do
		{
		char t;
		t='f';
		Report r;
      		Notif n;
      		system("clear");
        	printf("\n\nWelcome Faculty \n\n");
        	printf("\n\t\t\t\t\t\tSelect an Option \n");
        	printf("\n\t\t\t\t\t\t1.Search Book or Journal");
        	printf("\n\n\t\t\t\t\t\t2.Book/Journal status");
        	printf("\n\n\t\t\t\t\t\t3.Borrow Book ");
        	printf("\n\n\t\t\t\t\t\t4.Reserve Book\n\n\t\t\t\t\t\t");
        	printf("5.Cancel Reservation\n\n\t\t\t\t\t\t6.Purchase Request\n\n\t\t\t\t\t\t7.Notification");
       	printf("\n\n\t\t\t\t\t\t8.Back\n");
       	printf("\n\n\t\t\t\t\t\t9.Exit\n");
        	printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        	scanf("%d",&ch);
        
		switch(ch)
		{
			case 1 :  SearchBook();
				  break;
        	
        		case 2 :  char option;
        	       	  do{	
        	       	  	system("clear");
        	       		cout<<"Enter the ISBN : ";
        	       		int booknumber;
        	       		cin>>booknumber;
        	       		r.getReport(booknumber);
        	       		cout<<endl<<"\n\t\t\t\tDo you want to check status of another book/journal?(Y|N)";
        				cin>>option; 
       			    }while(option=='y'||option=='Y');
        		 	  break;
        	
        		case 3 :  BorrowBook(username,t);
        			  break; 
        	        	
        	        case 4 :  ReserveBook(username,t);
        	        	   break; 
        	        
        	        case 5 :  CancelReservation(username);       		
        	       	   break;
        	        
        	        case 6 :  purchase_req(username);
        	        	   break;
        	        
        	        case 7 :   n.Notification(username);  
        	        	   break;
        	        
         	        case 8 :  break;
         	        
         	        case 9 :  exit(0);
         	        	
        		default:   printf("\nWrong option ");
        		}
        	
        }while(ch!=8);}
};





void Help()
{ 
	int c;
	char ch;
	using namespace std;
	
	do{
	system("clear");
	cout<<"\t\t\t**********Welcome to Library**********"<<endl;
	cout<<"1. Registration and Login\n2. Search\n3. Borrowing book/journal\n";
	cout<<"4. Reservation\n5. Request for new book\n6. Notification\n";
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





void Report()
{





}





void login(int n)
{			
			Lib L;
			Stud S;
			Fac F;
			dbf=gdbm_open("users.db",0,GDBM_WRCREAT,0666,0);
		  	if(!dbf)
		  	{
		    		printf("\nError occured while receiving the data, please try again");
		    		printf("\n");
		    		exit(0);
		    		//goto exit;
		  	} 
		  	char t;
			int attempts=1,flag=0;
			int maxTry = 3;
			while(attempts<=maxTry&&flag==0)
    			{	
    				char username[50];
  	                	char password[50];
	    			printf("\nEnter the Username  :");
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
             				if(n==1)t='L';
             				else if(n==2)t='F';
             				else if(n==3)t='S';
             				if(realType==t)
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
             				{       //gdbm_close(dbf); 
             					flag=1;
              					system("clear");
              					if(realType=='L'){gdbm_close(dbf);L.Librarian(username);}
              					if(realType=='F'){gdbm_close(dbf);F.Faculty(username,'o');}
              					if(realType=='S'){gdbm_close(dbf);S.Student(username,'o');}
              				}
    					else
     					{			
       					printf("\nPassword incorrect!\nYou have %d attempts remaining \n",(3-attempts));
       					attempts++;
       					
   					}
   					}
   					else
   					{
   						printf("\nYou dont have Permission to access this\n");
   						gdbm_close(dbf);
   				
   					}
   					
				}

				else
 				{
 					
        				printf("\nWrong user name!\nYou have %d attempts remaining\n ",(3-attempts));
        				attempts++;
       			}
       			
			}
			
}


void signup(int n)
{			
			char username[50];
			char password[50];
			char type;
			dbs=gdbm_open("users.db",0,GDBM_WRCREAT,0666,0);
		  	if(!dbs)
		  	{
		    		printf("\nError occured while receiving the data, please try again");
		    		printf("\n");
		    		exit(0);
		    		//goto exit;
		  	} 
                       Lib L;
                       Stud S;
                       Fac F;
	               if(n==1)type='L';
	               if(n==2)type='F';
	               if(n==3)type='S';
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
	         	if(gdbm_store(dbs,key,data,GDBM_INSERT))
            	        {	
             			printf("\nError occured!userid exists.Member  is not added\n");
            		} 
             		else    
             		{       
             			 printf("\nAccount Created\n");
             			 gdbm_close(dbs);
             			 if(type=='L')L.Librarian(username);
             			 if(type=='F')F.Faculty(username,'f');
             			 if(type=='S')S.Student(username,'f');
             			 
             		}
             		
             		
           }
             		
  
  
   



//Authenticate

void authenticate(int a)
{	Lib l;
  	char username[50];
  	char password[50];
  	char type;
  	if(a==1)  //Authentication for Librarian
  	{	 
    		dbf=gdbm_open("users.db",0,GDBM_WRCREAT,0666,0);
  		if(!dbf)
  		{
    			printf("\nError occured while receiving the data, Please try again");
    			printf("\n");
    			exit(0);
  		}
  		
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
           			g:printf("\n\n\nEnter a Unique user name without white spaces:");
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
            			 	
             				printf("\nError occured!User ID exists.Member not added\n");
             				goto g;
            			 } 
             			else    
             			{       system("clear");
             				printf("\n\n\nLibrarian account Created\n");
             				printf("\n\nLogin to continue \n\n\n");
             				gdbm_close(dbf);
					login(1);
					
					
             			}
             				             			
	   		}
	  		else   
	  		{
	  			printf("\nWrong PIN! Access Denied !");
	  			gdbm_close(dbf);
	  			//exit(0);
	  		}
	  	}
		else
		{
			gdbm_close(dbf);
			login(1);
			
		}
	}
	
	else if(a==2)   //Authentication for Faculty
	{	
		int ch;
               getchar();
               abc:system("clear");
		printf("\n\t\t\t\t\tWelcome to Central Library");
		printf("\n\n\n\nDo you want to\n\n1.Login\n\n2.Signup");
		printf("\n\n\n\nEnter your choice  :");
        	scanf("%d",&ch);
		if(ch==1)
		{
			
			login(2);
			
		}
		else if(ch==2)
		{	
		   	signup(2);
	   	}
	   	else
	   	{
	   	cout<<endl<<"Wrong Option! Try again"<<endl;
	   	sleep(1);
	   	goto abc;
	   	}
	  		
					
		
	}
	else if(a==3)    //Authentication for Student
	{	int ch;
                getchar();
                pqr:system("clear");
		printf("\n\t\t\t\t\tWelcome to Central Library");
		printf("\n\n\n\nDo you want to\n\n1.Login\n\n2.Signup");
		printf("\n\n\n\nEnter your choice  :");
        	scanf("%d",&ch);
		if(ch==1)
		{	
			login(3);
		}
		else if(ch==2)
		{	
		   	signup(3);
	   	}
	   	else
	   	{
	   	cout<<endl<<"Wrong Option! Try again"<<endl;
	   	sleep(1);
	   	goto pqr;
	   	}
	  		
					
		
	}		
	
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
  	system("clear");
	uname:printf("\nEnter Your username  :");
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
          pass:printf("\n\nEnter Current Password  : ");

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
                    q:cout<<endl<<"\nEnter New Password   :";
                    
                    //Disable echo
      		       termios oldt;
		      tcgetattr(STDIN_FILENO, &oldt);
		      termios newt = oldt;
		      newt.c_lflag &= ~ECHO;
	              tcsetattr(STDIN_FILENO, TCSANOW, &newt);
																					   
		  //Input the password
																					       		      scanf("%s",newPassword1);
																					 
		   //Re-enable
																					       		      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
											
                    cout<<endl<<"\nEnter New Password Again   :";
                     //Disable echo
      		       //termios oldt;
		      tcgetattr(STDIN_FILENO, &oldt);
		       newt = oldt;
		      newt.c_lflag &= ~ECHO;
	              tcsetattr(STDIN_FILENO, TCSANOW, &newt);
																					   
		  //Input the password
																					       		      scanf("%s",newPassword2);
																					 
		   //Re-enable
																					       		      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    if(strcmp(newPassword1,newPassword2)==0)
                    {
                    	sprintf(databuf,"%s %c",newPassword1,realType);
                    	data.dsize=strlen(databuf)+1;
     		     	data.dptr=databuf;
		     	if(gdbm_store(dbp,key,data,GDBM_REPLACE))
		     	{
		     		printf("\nError occured, Password not Changed\n");
		      		exit(0);
		     	}
		     	else {
		     	printf("\nPassword Changed\n");
		     	sleep(2);
		     	}
                }
                else
                {
                cout<<endl<<"Password dont match \nTry Again";
                goto q;
                }
                }
                else
                {
                cout<<endl<<"Password is wrong. Please try again"<<endl;
                goto pass;
                }
                
                
           }
           else
 		{
 			system("clear");
        		printf("\nWrong user name!");
        		goto uname;
        		
       			}
       gdbm_close(dbp);
        
}













int main(int argc,char* argv[])
{
      int ch;
      char c;
      
      // Welcome Screem
        
      do
      {
        system("clear");
        printf("\n\t\t\t\t    *********** LIBRARY MANAGEMENT SYSTEM ***********\n\n\t\t\t\n");
        printf("\n\t\t\t\t\t\tSelect Profile \n");
        printf("\n\t\t\t\t\t\t1.Librarian\n\n\t\t\t\t\t\t2.Faculty\n\n\t\t\t\t\t\t3.Student\n\n\t\t\t\t\t\t4.Help\n\n\t\t\t\t\t\t5.Close Application\n");
        printf("\n\n\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
       
        {
         
         case 1:system("clear");                                     //Librarian Signup or Login
                authenticate(1);
                break;
         
         case 2:system("clear");                                    //Faculty Signup or Login
                authenticate(2);
                break;
         
         case 3:system("clear");                                    //Student Signup or Login
                authenticate(3);
                break;
         
         case 4:system("clear");                                   //Help Menu
                Help();
                break;
         
         case 5:exit(0);                                           //Exit From the Program
         
         
         default:  printf("\n\t\t\t\t\t\tOption You have entered is wrong \n \n");
         	   
     
        }
        cout<<endl<<"\n\t\t\t\t\t\tDo you want to Logout?(Y|N)";
        cin>>c; 
        }while(c=='y'||c=='Y');
        
        return 0;
}
