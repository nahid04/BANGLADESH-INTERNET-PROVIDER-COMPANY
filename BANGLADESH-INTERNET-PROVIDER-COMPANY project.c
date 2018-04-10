#include <windows.h>                //contains declarations for all of the functions in the Windows API,
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>                  //contains string function
#include <ctype.h>
#include <dos.h>                     //contains getdate
#include <time.h>
//list of function prototype
char catagories[][100]={"Premium","Diamond","Platinum ","Gold","Silver","bronze"};
void returnfunc();
void mainmenu();
void add();
void del();
void edit();
void view();
void search();
void packagelist();
void payment();
void closeapplication();
int  getdata();
int  checkid(int);
int  t();

//list of global files
FILE *fp,*ft;

//list of global variable
int s;
char finduser;

struct meroDate
{
    int mm,dd,yy;
};
struct user
{
    int id ;
    char name[50];
    char package[20] ;
    int amount;
    char *cat;

};
struct user a;
int main()

{
    mainmenu();
    getch();
    return 0;

}

void mainmenu()
  {
    system("cls");
    system("color 4a");



    printf("\t\t\t ______________________________________________________________\n");
    printf("\t\t\t*                                                              *\n");
    printf("\t\t\t*                                                              *\n");
    printf("\t\t\t*             WELCOME TO BANGLADESH INTERNET PROVIDER COMPANY  *\n");
    printf("\t\t\t*                                                              *\n");
    printf("\t\t\t*______________________________________________________________*\n\n\n");
    printf("\t  DEVELOPED BY :  \t \t \t Mahmud Brothers \t");

    printf(" \t\n");

        printf("\t\t\t\t\t*********************************** \n\n");
        printf("\t\t\t\t\t**    1.ADD USER:                ** \n\n");
        printf("\t\t\t\t\t**    2.DELETE USER:             ** \n\n");
        printf("\t\t\t\t\t**    3.SEARCH USER:             ** \n\n");
        printf("\t\t\t\t\t**    4.VIEW USER LIST:          ** \n\n");
        printf("\t\t\t\t\t**    5.EDIT USER RECORD:        ** \n\n");
        printf("\t\t\t\t\t**    6.PACKAGE LIST:            ** \n\n");
        printf("\t\t\t\t\t**    7.payment :                ** \n\n");
        printf("\t\t\t\t\t**    8.CLOSE APPLICATION:       ** \n\n");
        printf("\t\t\t\t\t*********************************** \n\n");
        t();
        printf("\t\t\t\t\t\tENTER YOUR CHOICE: ");


	switch(getch())
	{
		case '1':
            add();
            break;
	    case '2':
            del();
            break;
		case '3':
            search();
            break;
	    case '4':
            view();
            break;
	    case '5':
            edit();
            break;
		case '6':
            packagelist();
            break;
            case '7':
            payment();
            break;
	    case '8':
	    {
          system("cls");
          system("color f0");
          printf("   THANKS\n");
          printf("              FOR\n");
          printf("                      USING\n");
          printf("              MY\n");
          printf("   PROGRAM  \n\n\n\n");
          printf("   ******               THANK YOU                 ******\n");

          exit(0);
	    }
	    default:
		{
		printf("\aWrong Entry!!Please re-entered correct option");
		if(getch())
		mainmenu();
		}

    }
}
void add()    //function that adds user
{

	system("cls");
	int i;
	printf("SELECT CATEGORIES\n\n");
	printf(" 1.New USER: \n");
	printf(" 2.Back to main menu\n");
	printf("Enter your choice: ");
	scanf("%d",&s);
	if(s==2)
        mainmenu() ;
	else if (s==1)
	{
		system("cls");
		printf("\n Enter User Id: ");
		scanf("%d",&a.id);
		printf("\n Enter name : ");
		fflush(stdin);
		scanf("%s",&a.name);
		printf("\n Enter amount: ");
		scanf("%d",&a.amount);
		printf("\n Enter PACKAGE : ");
		fflush(stdin);
		scanf("%s",&a.package);


		fp=fopen("internet.txt","a+");


        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        printf("The record is sucessfully saved\n");
        printf("Save any more?(Y / N):");
	if(getch()=='n')
	    mainmenu();
	else
	    system("cls");
	    add();
	}
}

void del()    //function that deletes users from file
{

    system("cls");
    int d,i;
    char checker='y';
    while(checker=='y')  //infinite loop
    {
        system("cls");
        printf("Enter the User id that You want to delete:  ");
        scanf("%d",&d);
        fp=fopen("internet.txt","r+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id == d)
            {
                printf("The user record is available\n");
                printf("User name is: %s\n",a.name);
                printf("User id no. is: %d\n",a.id);
                printf("Package:  %s\n",a.package);
                printf("Price is: %d\n",a.amount);
                finduser='t';
            }
        }
        if(finduser!='t')   //check if t enter in loop
        {

            printf("No record is found modify the search\n");
            if(getch())
            mainmenu();
        }
	if(finduser=='t' )
	{

	    printf("\nDo you want to delete it?(Y/N):");
	    if(getch()=='y')
            {
                ft=fopen("test.txt","w+");  //temporary file for delete
                rewind(fp);
                while(fread(&a,sizeof(a),1,fp)==1)
                    {
                         if(a.id!=d)
                        {
                            fseek(ft,0,SEEK_CUR);
                            fwrite(&a,sizeof(a),1,ft); //write all in temporary file except that
                        }                              //we want to delete
                }
		fclose(ft);
		fclose(fp);
		remove("internet.txt");
		rename("test.txt","internet.txt"); //copy all item from temporary file to fp except that
		fp=fopen("internet.txt","r+");    //we want to delete
		if(finduser=='t')
                {

                printf("\nThe record is sucessfully deleted\n");
                getch();
                mainmenu();

                }
             }
        else
            mainmenu();
            fflush(stdin);
            checker=getch();
	}

    }

    mainmenu();
}
void search() //function that search users
{
    system("cls");
    int d;
    printf("*****************************Search user*********************************\n\n");
    printf("1. Search by id\n");
    printf("2. Search by name\n");
    printf("Enter Your Choice\n");
    fp=fopen("internet.txt","r+"); //open file for reading propose
    rewind(fp);   //move pointer at the beginning of file
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    printf("****Search user By id\n****");
	    printf("Enter the id:\n");
	    scanf("%d",&d);
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(a.id==d)
		{
		    printf("The user is available\n");
		    printf("user id: %d\n",a.id);
		    printf("user name: %s\n",a.name);
		    printf("package: %s\n",a.package);
		    printf("payment: %d\n",a.amount);
      	    finduser='t';
		}
}
	    if(finduser!='t')  //checks whether condition enters inside loop or not
	    {

	    printf("\aNo Record Found");
	    }
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    search();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    printf("****Search user By Name****\n");
	    printf("Enter user name: ");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
            {
                printf("The user is available\n");
                printf(" user id: %d",a.id);
                printf(" user name: %s",a.name);
                printf(" package: %s",a.package);
                printf(" Price: %d",a.amount);
                d++;
            }
        }
	    if(d==0)
            {

                printf("\nNo Record Found");
            }
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    search();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	search();
    }
    fclose(fp);
};
void view()  ////function that shows the list
{
    system("cls");
    system("color e4");

    printf("*********************************user List*****************************\n\n");
    fp=fopen("internet.txt","r");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        printf("User Id :  %d\t",a.id);
        printf("Username : %s\t",a.name);
        printf("Package :  %s\t",a.package);
        printf("amount :   %d",a.amount);
        printf("\n\n");
      }

      fclose(fp);
      returnfunc();
}
void edit()  ////function that edits information
{
	system("cls");
    system("color f0");

	int c=0;
	int d,e;
	printf("****Edit user Record ****\n");
	char another='y';
	while(another=='y')
	{
		system("cls");
		printf("Enter user id to be edited:\n");
		scanf("%d",&d);
		fp=fopen("internet.txt","r+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("The user is availble\n");
				printf("The user id no. :%d\n",a.id);
				printf("Enter new name: \n");
				scanf("%s",a.name);
				printf("Enter new id: \n");
				scanf("%d",&a.id);
				printf("Enter new package: \n");
				scanf("%s",&a.package);
				printf("Enter the new Price : \n");
				scanf("%d",&a.amount);
                printf("The record is modified\n");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("No record found\n");
			}
		}
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void packagelist() //function that shows package info
{
    printf("package list\n\n\n\n\n");
    printf("\tCATEGORY       \t      PACKAGE NAME \t       SPEED    \t   PRICE    \n");
    printf("\t1.Premium      \t             P    \t      30 MbPS   \t   4000 tk  \n");
    printf("\t2.Diamond      \t             D    \t      15 MbPS   \t   2500 tk  \n");
    printf("\t3.Platinum     \t             Pl   \t       8 MbPS   \t   1800 tk  \n");
    printf("\t4.Gold         \t             G    \t       4 MbPS   \t   1200 tk  \n");
    printf("\t5.Silver       \t             S    \t       2 MbPS   \t    850 tk  \n");
    printf("\t6.Bronze       \t             B    \t       1 MbPS   \t    500 tk  \n");
    returnfunc();
}

void  payment() //function that shows payment info

{
    system("cls");
    system("color f0");
	char package[20];
	long int _size=sizeof(a);
	float amt;
	int i;
	fp=fopen("internet.txt","r+");

	system("cls");
	int id;
	printf("Enter user id for payment : ");

	scanf("%d",&id);

	while(fread(&a,sizeof(a),1,fp) ==1)
	{

		if( (a.id) == id)
		{

			printf("\n User id.: %d",a.id);
			printf("\n User name: %s",a.name);
			printf("\n Current amount: %d",a.amount);
			printf("\n");
			for(i=0;i<80;i++)
			printf("-");
			printf("\n\nEnter amount of payment :");
			scanf(" %f",&amt);
			a.amount=a.amount-amt;
			fseek(fp,-_size,SEEK_CUR);
			fwrite(&a,sizeof(a),1,ft);
            printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",a.name);
	        printf ("\nYour Due Payment : %d ",a.amount);
                break;
		}

        else
        {
            printf("No record found\n");
        }
	}

    fclose(fp);
	getch();

    mainmenu();

    return ;
}

void returnfunc() //return function to get to main menu
{
    {
	printf(" Press ENTER to return to main menu\n");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
	int t;
	printf("Enter the Information Below\n");
    printf("Category:");
	printf("%s",catagories[s-1]);
	printf("\n user id:\t");
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		printf("\aThe user id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	printf("user id: \n");
	scanf("%d",&a.id);

	printf("user name: \n");
	scanf("%s",a.name);

	printf("Package: \n");
	scanf("%s",a.package);

	printf("Price: \n");
	scanf("%d",a.amount);
	return 1;
}

int checkid(int t)  //check whether the user is exist  or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if user exits
      return 1; //return 1 if it does not exist
}

int t() //for time
    {
        time_t t;
        time(&t);
        printf("\n\t\t\t\t\tDate and time:%s\n",ctime(&t));

        return 0 ;
    }

