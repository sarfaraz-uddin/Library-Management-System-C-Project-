#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

//FUNCTION DECLARATION
void home();
void adminMenu();
void customerMenu();
void passWord();
void addBook();
void viewBooksList();
void editBookRecord(int key,char keyBookName[20],char KeyAuthor[20],int keyId); //when checking in key==1 and checking out key ==2 and editing record key == 0);
void searchBook();
void searchById();
void searchByBookName();
void searchByBookAuthor();
void removeBook();
void checkInOut(int key);
void changePassword();

//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//GLOBAL VARIABLES

char credential[2][20];
char userName[20],password[20];

FILE *fp,*fp2, *pw, *pw1;

struct Books{
	int id;
	char bookName[20];
	char author[20];
	int stock;
	int availableQty;
	int checked;
}book,book2;

int x1,x2,x3,x4,x5;

int main()
{
	home();
	return 0;
	
}

//Function definition

void adminMenu()
{
	int choice;
	label3:
	system("cls");
	gotoxy(20,7);
	printf("1.Add Book");
	gotoxy(20,9);
	printf("2.Remove Book");
	gotoxy(20,11);
	printf("3.View Books List");
	gotoxy(20,13);
	printf("4.Edit Book Record");
	gotoxy(20,15);
	printf("5.Change Password");
	gotoxy(20,17);
	printf("6.Back to Main menu");
	gotoxy(20,19);
	printf("7.Exit Program");
	gotoxy(20,21);
	printf("Enter your choice:");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
				
				addBook();
				
			
				break;
				
		case 2:
				removeBook();
				
				break;
				
		case 3:
				viewBooksList();
				
				break;
				
		case 4:
				editBookRecord(0,"0","0",0);
				
			
				break;
			
		case 5:
				changePassword();	
				break;
				
		case 6:
				return;
				break;
		
		case 7:
				system("cls");
				gotoxy(20,7);
				printf("Please Visit Again!");
				exit(0);
		default:
				break;	
	}
	
	goto label3;
}

void customerMenu()
{
	
	int choice;
	label7:
	system("cls");
	gotoxy(20,7);
	printf("1.CheckOut Book");
	gotoxy(20,9);
	printf("2.CheckIn Book");
	gotoxy(20,11);
	printf("3.Search Book");
	gotoxy(20,13);
	printf("4.Back to Main menu");
	gotoxy(20,15);
	printf("5.Exit Program");
	gotoxy(20,17);
	printf("Enter your choice:");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			checkInOut(2);
			break;
		
		case 2:
			checkInOut(1);
			break;
			
		case 3:
			searchBook();
			
			break;
		
		case 4:
			return;
			break;
		
		case 5:
			system("cls");
			gotoxy(20,7);
			printf("Please Visit Again!");
			exit(0);
			break;
					
		default:
			break;
	}	
	goto label7;
	
}

void passWord()
{
	char ch;
	int count1 = 0;
	int count2 = 0;
	
	pw = fopen("password.dat","r");
	int count = 1;
	char temp[20];
	while(fscanf(pw,"%s",temp)!=EOF)
	{
		if(count==1){
			strcpy(credential[0],temp);
		
		}else{
			strcpy(credential[1],temp);
		}
		count++;
	}
	fclose(pw);
	label2:
	system("cls");
	if(count1>0)
	{
		gotoxy(20,5);
		printf("Incorrect Username!!!");
	}
	gotoxy(20,7);
	printf("Enter Username:");
	fflush(stdin);
	gets(userName);
	label1:
	
	if(count2>0)
	{
		system("cls");
		gotoxy(20,5);
		printf("Incorrect Password!!!");
	}
	gotoxy(20,9);
	printf("Enter PassWord:");
	int p=0;
    while(1)
    {
    	ch=getch();
    
    	if(ch!=13&& ch!=8)
    	{
    		printf("*");
    		password[p]=ch;
    		p++;
		}
		else{
			password[p]='\0';
			break;
		}
	}
	
	
	
	if(strcmp(credential[0],userName)==0)
	{
		if(strcmp(credential[1],password)==0)
    	{
    		adminMenu();
    	
		}
		else{
		count2++;
		goto label1;	
		}
	}else{
		count1++;
		goto label2;
	}
    	
	
}

void addBook()
{
	char key;
	int alreadyEntried;
	fp = fopen("bookdata.dat","a+");
	fp2 = fopen("bookdata.dat","r+");
	system("cls");
	if (fp == NULL || fp2 == NULL)
	{
		printf("Error Opening File!!");
		return;	
	}
	do{
		
		alreadyEntried = 0;
		fseek(fp2,0,SEEK_SET);
		printf("Enter book id: ");
		scanf("%d",&book.id);
			while(book.id<=0)
		{
			printf("\nID cant be less than or equal to zero!");
			printf("\nEnter again:");
			scanf("%d",&book.id);
		}
		fflush(stdin);
		printf("Enter book name: ");
		gets(book.bookName);
		printf("Enter author name: ");
		gets(book.author);
		printf("Enter the stock quantity:");
		scanf("%d",&book.stock);
		book.availableQty=0;
		fflush(stdin);
		while(book.stock<=0)
		{
			printf("\nQuantity cant be less than or equal to zero!");
			printf("\nEnter again:");
			scanf("%d",&book.stock);
		}
		book.checked = 1;
		while(fread(&book2,sizeof(book2),1,fp2))
		{
			if(strcmp(book2.author,book.author)==0 && strcmp(book2.bookName,book.bookName)==0  && book.id == book2.id)
			{
				fseek(fp2,-sizeof(book2),SEEK_CUR);
				book.availableQty = book.stock + book2.availableQty;
				book.stock += book2.stock;
				
				fwrite(&book,sizeof(struct Books),1,fp2);
				alreadyEntried = 1;
				break;
			}
		}
		if(alreadyEntried == 0)
		{
			book.availableQty = book.stock;
			fwrite(&book,sizeof(struct Books),1,fp);
		}
		printf("Do you want to make more entries? (y/n)");
		key = getchar();
	}while(key == 'y' || key == 'Y');
	fclose(fp);
	fclose(fp2);
	
}

void viewBooksList()
{
	fp = fopen("bookdata.dat","r");
	system("cls");
	x1=10;
	x2=30;
	x3=50;
	x4=70;
	x5=90;
	int y=0,i=0;
	gotoxy(x1,y);
	printf("ID");
	gotoxy(x2,y);
	printf("Book Name");
	gotoxy(x3,y);
	printf("Author");
	gotoxy(x4,y);
	printf("Quantity");
	gotoxy(x5,y);
	printf("Available");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
	while(fread(&book,sizeof(book),1,fp))
	{
		i+=3;
		gotoxy(x1,y+i);
		printf("%d",book.id);
		gotoxy(x2,y+i);
		printf("%s",book.bookName);
		gotoxy(x3,y+i);
		printf("%s",book.author);
		gotoxy(x4,y+i);
		printf("%d/%d",book.availableQty,book.stock);
		gotoxy(x5,y+i);
		printf("%s",(book.checked==0?"No":"Yes"));
		

	}
	fclose(fp);
	printf("\n\n\nPress Enter to Continue:");
	getch();
		
}



void searchBook()
{

	int choice;
	label66:
	system("cls");
	fp=fopen("bookdata.dat","r");
	printf("\nHow do you want to search book:");
	printf("\n\t1.By ID");
	printf("\n\t2.By BOOK NAME");
	printf("\n\t3.By AUTHOR");
	printf("\n\t4. Go Back");
	printf("\n\t5. Exit Program");
	printf("\n\n\tEnter any other key to go back\n");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
		{
			case 1:
			
				searchById();
				break;
		
			case 2:
				searchByBookName();
				break;
			
			case 3:
				searchByBookAuthor();
				break;
		
			case 4:
				return;
				break;
			case 5:
				system("cls");
				gotoxy(20,7);
				printf("Please Visit Again!");	
				exit(0);
				break;
			default:	
				break;
		}
		
	
	goto label66;
}

void searchById()
{
	int id;
	system("cls");
	printf("Enter ID:");
	fflush(stdin);
	scanf("%d",&id);
	x1=10;
	x2=30;
	x3=50;
	x4=70;
	x5=90;
	int y=0,i=0;
	gotoxy(x1,y);
	printf("ID");
	gotoxy(x2,y);
	printf("Book Name");
	gotoxy(x3,y);
	printf("Author");
	gotoxy(x4,y);
	printf("Available");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
	while(fread(&book,sizeof(book),1,fp))
	{
		if(book.id==id)
		{
			i+=3;
			gotoxy(x1,y+i);
			printf("%d",book.id);
			gotoxy(x2,y+i);
			printf("%s",book.bookName);
			gotoxy(x3,y+i);
			printf("%s",book.author);
			gotoxy(x4,y+i);
			printf("%s",(book.checked==0?"No":"Yes"));
		
		}
	
	}
	fclose(fp);
	printf("\n\nEnter any key to exit");
	getch();
}

void searchByBookName(){
	char bookName[20];
	printf("Enter Book Name:");
	fflush(stdin);
	gets(bookName);
	x1=10;
	x2=30;
	x3=50;
	x4=70;
	x5=90;
	int y=0,i=0;
	gotoxy(x1,y);
	printf("ID");
	gotoxy(x2,y);
	printf("Book Name");
	gotoxy(x3,y);
	printf("Author");
	gotoxy(x4,y);
	printf("Quantity");
	gotoxy(x5,y);
	printf("Available");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
	
	while(fread(&book,sizeof(book),1,fp))
	{
		if(strcmp(book.bookName,bookName)==0)
		{
			i+=3;
		gotoxy(x1,y+i);
		printf("%d",book.id);
		gotoxy(x2,y+i);
		printf("%s",book.bookName);
		gotoxy(x3,y+i);
		printf("%s",book.author);
		gotoxy(x4,y+i);
		printf("%s",(book.checked==0?"No":"Yes"));
		
		}
	}
	fclose(fp);
	printf("\n\nEnter any key to exit");
	getch();
}

void searchByBookAuthor(){
	char author[20];
	printf("Enter Author Name:");
	fflush(stdin);
	gets(author);
	x1=10;
	x2=30;
	x3=50;
	x4=70;
	x5=90;
	int y=0,i=0;
	gotoxy(x1,y);
	printf("ID");
	gotoxy(x2,y);
	printf("Book Name");
	gotoxy(x3,y);
	printf("Author");
	gotoxy(x4,y);
	printf("Quantity");
	gotoxy(x5,y);
	printf("Available");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
	
	while(fread(&book,sizeof(book),1,fp))
	{
		if(strcmp(book.author,author)==0)
		{
			i+=3;
		gotoxy(x1,y+i);
		printf("%d",book.id);
		gotoxy(x2,y+i);
		printf("%s",book.bookName);
		gotoxy(x3,y+i);
		printf("%s",book.author);
		gotoxy(x4,y+i);
		printf("%s",(book.checked==0?"No":"Yes"));
		}
	}
	fclose(fp);
	printf("\n\nEnter any key to exit");
	getch();
}

void editBookRecord(int key,char keyBookName[20],char keyAuthor[20],int keyId) //when checking in key==1 and checking out key ==2 and editing record key == 0 
{
	system("cls");
	fp=fopen("bookdata.dat","r");
	fp2=fopen("newbook.dat","w");
	int id;
	if(key==0)
	{
		printf("Enter id of the book:");
		fflush(stdin);
		scanf("%d",&id);
	}else{
		if(keyId>0){
		id = keyId;
		}		
	}

	
	x1=10;
	x2=30;
	x3=50;
	x4=70;
	x5=90;
	int y=0,i=0;
	gotoxy(x1,y);
	printf("ID");
	gotoxy(x2,y);
	printf("Book Name");
	gotoxy(x3,y);
	printf("Author");
	gotoxy(x4,y);
	printf("Available");
	gotoxy(x5,y);
	printf("Quantity");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
	
	while(fread(&book,sizeof(book),1,fp))
	{
		if(id== book.id || strcmp(keyBookName,book.bookName)==0 || strcmp(keyAuthor,book.author)==0)
		{
			i+=3;
			gotoxy(x1,y+i);
			printf("%d",book.id);
			gotoxy(x2,y+i);
			printf("%s",book.bookName);
			gotoxy(x3,y+i);
			printf("%s",book.author);
			if(key==0)
			{
				gotoxy(x5,y+i);
				printf("%d/%d",book.availableQty,book.stock);
				
			}
			gotoxy(x4,y+i);
			printf("%s",(book.checked==0?"No":"Yes"));
		
			if(key==0)
			{
				printf("\n\nWhat changes would you like to make:\n");
				printf("\nEnter New Book id:");
				scanf("%d",&book.id);
				printf("\nEnter New Book Name:");
				fflush(stdin);
				gets(book.bookName);
				printf("\nEnter New Author Name:");
				gets(book.author);
				do{
					printf("Enter the stock quantity:");
					scanf("%d",&book.stock);
					printf("Enter the available quantity:");
					scanf("%d",&book.availableQty);
				}while(book.availableQty>book.stock);
				fflush(stdin);
				printf("\n BOOK EDITED SUCCESSFULLY!!");
			}
			else if(key==2 && book.checked==1)
			{
				char flag;
				fflush(stdin);
					printf("\n\nDo you want to check out?(Y/N)");
					fflush(stdin);
					flag= getchar();
					if(flag=='Y' || flag=='y')
					{
						--book.availableQty;
						printf("\nChecked out successfully!");
					}
					
					printf("\n Press any key to continue:");
					getch();
			}else if(key==1 && book.checked==0)
			{
				char flag;
				fflush(stdin);
				printf("\n\nDo you want to check in?(Y/N)");
				flag= getchar();
				if(flag=='Y' || flag=='y')
				{
					if(book.availableQty<book.stock)
					{
						book.availableQty = book.availableQty+1;
						book.checked=1;
						printf("\nSuccesfully Checked In!");
					}else{
						printf("\nError!!The stock is already full");
					}
				}
				
				printf("\n Press any key to continue:");
				getch();
			}
			if(book.availableQty==0 )
			{
				book.checked = 0;
			}
		}		
		fwrite(&book,sizeof(book),1,fp2);
	}
	fclose(fp),
	fclose(fp2);
	remove("bookdata.dat");
	rename("newbook.dat","bookdata.dat");
	if(key==0){
		printf("\nEdited Successfully!! Press any key to exit:");
		getch();
	}

	
}

void removeBook()
{
	int id;
	char key;
	system("cls");
	fp = fopen("bookdata.dat","r");
	fp2 = fopen("newbookdata.dat","w");
	printf("Enter id of the book:");
	fflush(stdin);
	scanf("%d",&id);
	printf("\nAre you sure you want to delete the book?");
	fflush(stdin);
	key=getchar();
	if(key == 'y' || key == 'Y')
	{
		while(fread(&book,sizeof(book),1,fp))
		{
			if(id == book.id)
			{
				continue;
			}
			fwrite(&book,sizeof(book),1,fp2);
		}
		printf("\nDeleted Successfully!\n");
		fclose(fp);
		fclose(fp2);
		remove("bookdata.dat");
		rename("newbookdata.dat","bookdata.dat");
		printf("Enter any button to exit:");
		getch();
	}
	return;
}

void checkInOut(int key)
{
	
	int choice;
	label34:
	system("cls");
	printf("\nHow do you want to search the book?");
	printf("\n\t1.Id");
	printf("\n\t2.Book Name");
	printf("\n\t3.Book Author");
	printf("\n\t4. Go back");
	printf("\n\t5. Exit Program");
	printf("\n Enter your choice:");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			{	
				int id;
				system("cls");
				printf("\nEnter ID:");
				scanf("%d",&id);
				if(key==1)
				{
					editBookRecord(1,"0","0",id);
				}else{
					editBookRecord(2,"0","0",id);
				}
				break;
			}
		case 2:
			{
				char bookName[20];
				system("cls");
				fflush(stdin);
				printf("\nEnter Book Name:");
				
				gets(bookName);
				if(key==1)
				{
					editBookRecord(1,bookName,"0",0);
				}else{
					editBookRecord(2,bookName,"0",0);
				}
				break;
			}
		case 3:
			{
				char bookAuthor[20];
				system("cls");
				printf("Enter Book Author:");
				fflush(stdin);
				gets(bookAuthor);
					if(key==1)
				{
					editBookRecord(1,"0",bookAuthor,0);
				}else{
					editBookRecord(2,"0",bookAuthor,0);
				}
				break;		
			}
		case 4:
				return;
				break;
		case 5:
				system("cls");
				gotoxy(20,7);
				printf("Please Visit Again!");
				exit(0);
				break;
		default:
				break;
	} goto label34;
}
void home(){
	int choice;
	label3:
	system("cls");
	gotoxy(20,5);
	printf("****************WELCOME TO DYNAMIC LIBRARY*****************\n");
	gotoxy(20,7);
	printf("1.Admin Panel");
	gotoxy(20,9);
	printf("2.Customer Panel");
	gotoxy(20,11);
	printf("3.Press Any Other Key to exit:");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			
			passWord();

			break;
		
		case 2:
			
			customerMenu();
			
			break;
		
		default:
			system("cls");
			gotoxy(20,7);
			printf("Please Visit Again!");
			return;
		
	}
	goto label3;
}
void changePassword()
{
	system("cls");
	char ch;
	char passWord[2][20];
	printf("\nEnter old password:");
	fflush(stdin);
	int p=0;
    while(1)
    {
    	ch=getch();
    
    	if(ch!=13&& ch!=8)
    	{
    		printf("*");
    		password[p]=ch;
    		p++;
		}
		else{
			password[p]='\0';
			break;
		}
	}
	if(strcmp(credential[1],password)==0)
	{
		printf("\nEnter new password:");
		 p=0;
    	while(1)
    	{
   		 	ch=getch();
    
    		if(ch!=13&& ch!=8)
    		{
    			printf("*");
    			passWord[0][p]=ch;
    			p++;
			}
			else{
				passWord[0][p]='\0';
				break;
			}
		}	
		
		printf("\nConfirm password:");
 		p=0;    		
		while(1)
   		{
   	 		ch=getch();
    
    		if(ch!=13&& ch!=8)
    		{
    			printf("*");
    			passWord[1][p]=ch;
    			p++;
			}
			else{
				passWord[1][p]='\0';
				break;
			}	
		}
		if(strcmp(passWord[0],passWord[1])==0)
		{	
			pw1 = fopen("newpassword.dat","w");
			fprintf(pw1,"%s\n","admin");
			fprintf(pw1,"%s",passWord[0]);
			fclose(pw1);
			remove("password.dat");
			rename("newpassword.dat","password.dat");
			printf("\nPassword updated successfully!");
			printf("\nPress any key to exit:");
			getch();
		}else{
		printf("\nThe new password doesn't match!");
		}
	}else{
		printf("\nThe current password doesn't match!");
		printf("\n Press any key to exit:");
		getch();
	}
} 
	
