#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


struct public{
int comp_id;
char name[50];
int age;
char date[10];
char comp[1000];
int dept;
char status[10];
}c;

FILE *fp;
FILE *fptr;
FILE *kptr;

void menu_pub();
void admin();
void add_comp();
void admin_page();
void view_comp();
void comp_status(int);
void pause();
void dept(int);
void display();
void delete_record();
void comp_number();
void public_login();

void main()
{
    int x;
    printf("\n-------------------------------------WELCOME TO STATE COMPLAINT MANAGEMENT SYSTEM--------------------------------------\n");
    do
    {
        printf("\nARE YOU A :\n1.PUBLIC\n2.ADMINISTRATOR\n3.EXIT\n");
        printf("Enter the choice:");
        scanf("%d",&x);
        system("cls");
        switch(x)
        {
        case 1:
        menu_pub();
        break;
        case 2:
        admin();
        break;
        case 3:
        break;
        default:
        printf("\nwrong choice.......");
         fflush(stdin);
        pause();
    }

    } while (x!=3);
    exit(1);
}
//public menu
void menu_pub()
{
    int p;
    do
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1.ADD A COMPLAINT\n2.VIEW A COMPLAINT STATUS\n3.GO BACK\n");
        printf("Enter the choice:");
        scanf("%d",&p);
        system("cls");
        switch(p)
        {
            case 1:
            add_comp();
            break;
        case 2:
            comp_status(1);
        break;
        case 3:
        break;
        default:
            printf("\nwrong choice.......");
            fflush(stdin);
            pause();
        }

    } while (p!=3);
}


//Add a complaint
void add_comp()
{
    int r;
    strcpy(c.status,"Not Seen");
    srand(time(0));
    r=rand()%500;
    fp=fopen("complaint.bin","ab");
    c.comp_id=r;
    printf("\nYour USER ID is %d\n",c.comp_id);
    printf("\nAdd your complaint details:\n");
    printf("-----------------------------------\n");
    fflush(stdin);
    printf("Enter your name:");
    fgets(c.name,sizeof(c.name),stdin);
    printf("Enter your age :");
    scanf("%d",&c.age);
    printf("Enter date (dd/mm/yyyy):");
    scanf("%s",c.date);
    printf("\n1.Civil Aviation\n2.Education\n3.Railways and Highways\n4.Telecommunication\n5.Tourism\n6.CGHS");
    do
    {
        printf("\nChoose the department of your complaint:");
        scanf("%d",&c.dept);
    }while(c.dept>6);
    printf("enter your complaint :\n");
    fflush(stdin);
    fgets(c.comp,sizeof(c.comp),stdin);
    fwrite(&c,sizeof(c),1,fp);
    printf("\n----------------------------------------------------\n\n");
    printf("Your complaint is successfully added\n");
    fclose(fp);
    fflush(stdin);
    pause();

}
//Complaint status
void comp_status(int x)
{
    if(x==1)
    {
         int id,a,flag=0;
    char s_name[20];
    printf("\n----------------------------------------------------\n");
    printf("1.Search by Complaint ID\n");
    printf("2.Search by Name\n");
    printf("Enter the choice:");
    scanf("%d",&a);
    printf("\n----------------------------------------------------\n");
    switch(a)
    {
        case 1:
        printf("\nEnter the complaint id:\n");
        scanf("%d",&id);
        if((fp=fopen("complaint.bin","rb"))==NULL)
	        {
		        printf("\n cannot open the record file\n");
		        exit(1);
	        }
	        while(fread(&c,sizeof(c),1,fp))
	        {
	        if(c.comp_id==id)
		    {
                printf("\nComplaint ID: %d",c.comp_id);

                printf("\nName: %s",c.name);

                printf("\nAge: %d",c.age);

                printf("\nDate of Complaint: %s",c.date);

                printf("\nDepartment: ");
                dept(c.dept);

                printf("\nComplaint:%s",c.comp);

                printf("\nComplaint status: %s",c.status);

                printf("\n");

                printf("\n----------------------------------------------------\n\n");

                flag=1;
            }
        }
        if(flag!=1)
	    {
		    printf("\nThere is no record available\n");
	    }
        fflush(stdin);
        pause();
        break;

        case 2:
            printf("\nEnter Name:\n");
            fflush(stdin);
            fgets(s_name,sizeof(s_name),stdin);
            if((fp=fopen("complaint.bin","rb"))==NULL)
	        {
		        printf("\n cannot open the record file");
		        fflush(stdin);
		        pause();
	        }
	        else{
	        while(fread(&c,sizeof(c),1,fp))
	        {
	        if(strcmp(c.name,s_name)==0)
		    {
                printf("\nComplaint ID: %d",c.comp_id);

                printf("\nName: %s",c.name);

                printf("\nAge: %d",c.age);

                printf("\nDate of Complaint: %s",c.date);

                printf("\nDepartment: ");
                dept(c.dept);

                printf("\nComplaint:%s",c.comp);

                printf("\nComplaint status: %s",c.status);

                printf("\n\n----------------------------------------------------\n\n");

                flag=1;
            }
        }
        if(flag!=1)
	    {
		    printf("\nThere is no record available\n");
	    }
        fflush(stdin);
        pause();
    }
    }}
    if(x==2)
    {
        printf("\n----------------------------------------------------\n\n");
        int z,st,id,i,l;
        fp=fopen("complaint.bin","rb+");
        do
        {
            i=1;id=-1;
            printf("COMPLAINT IDs:\n");
            rewind(fp);
            while (fread(&c,sizeof(c),1,fp))
            {
                if(strcmp(c.status,"Not Seen")==0)
                {
                    printf("%d= %d\n",i,c.comp_id);
                    i++;
                }
            }
            if(i==1)
            {
                printf("\nNo new complaint is available");
                break;
            }
            l=0;
            printf("Enter ID:");
            scanf("%d",&id);
            rewind(fp);
            while(fread(&c,sizeof(c),1,fp))
            {
                l++;
                if(id==c.comp_id)
                {
                    printf("\nCOMPLAINT: %s",c.comp);
                    printf("\nDEPARTMENT: ");
                    dept(c.dept);
                    printf("Press 0 to update status to SEEN.....");
                    scanf("%d",&st);
                    if(st==0)
                    {
                        strcpy(c.status,"Seen");
                        fseek(fp,(l-1)*sizeof(c),SEEK_SET);
                        fwrite(&c,sizeof(c),1,fp);
                    }
                    printf("\n1.Update next complaint ");
                    printf("\n2.Go back");
                    printf("\nEnter the choice:");
                    scanf("%d",&z);
                    break;
                }

        }
        } while(z==1);

        printf("\n----------------------------------------------------\n\n");
        fclose(fp);
        fflush(stdin);
        pause();

    }
}

//Admin login module
void admin()
{
    char u[10],pwd[10];
    int z=0;
    char c;
    printf("\n----------------------------------------------------\n\n");
    printf("Enter username:");
    scanf("%s",u);
    printf("Enter the password:");
    while((c=getch())!=13)
        {
          pwd[z++]=c;
          printf("%c",'*');
        }
        pwd[z]='\0';
    if(strcmp(u,"user")==0&&strcmp(pwd,"pwd")==0){
    system("cls");
    admin_page();
    }
    else
    {
        printf("\nYou have entered wrong username or password\n");
        printf("\n----------------------------------------------------\n\n");
        fflush(stdin);
        pause();

    }
       system("cls");
}
//Admin menu
void admin_page()
{
    int y;
    do
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1.VIEW A COMPLAINT \n2.UPDATE COMPLAINT STATUS\n3.PRINT THE COMPAINTS ACCORDING TO THE DEPARTMENT\n4.DELETE A COMPLAINT\n5.PRINT THE NUMBER OF COMPLAINTS FROM ALL DEPARTMENTS\n6.LOGOUT");
        printf("\nEnter the choice:");
        scanf("%d",&y);
        system("cls");
        switch(y)
        {
            case 1:
            view_comp();
            break;
            case 2:
            comp_status(2);
            break;
            case 3:
            display();
            break;
            case 4:
            delete_record();
            break;
            case 5:
            comp_number();
            break;
            case 6:
            printf("\n----------------------------------------------------\n\n");
            break;
            default:
            printf("\nwrong choice.......");
            fflush(stdin);
            pause();
        }

    } while (y!=6);
}
//View a compliant
void view_comp()
{
    printf("\n----------------------------------------------------\n\n");
        int z=0,id,i;
        fp=fopen("complaint.bin","rb+");
        do
        {
            i=1;
            printf("COMPLAINT IDs:\n");
            rewind(fp);
            while (fread(&c,sizeof(c),1,fp))
            {
                printf("%d)%d\n",i,c.comp_id);
                i++;
            }
            if(i==1)
            {
                printf("No Complaints\n");
                fflush(stdin);
                pause();
            }
            else
            {
                printf("Enter ID:");
                scanf("%d",&id);
                rewind(fp);
                while(fread(&c,sizeof(c),1,fp))
                {
                    if(id==c.comp_id)
                    {
                        printf("\nName:%s",c.name);
                        printf("\nAge:%d",c.age);
                        printf("\nDate:%s",c.date);
                        printf("\n.................................");
                        printf("\nCOMPLAINT: %s",c.comp);
                        printf("\nDEPARTMENT: ");
                        dept(c.dept);
                        printf("\nEnter 1 to review the ID's list and any key to main page...");
                        scanf("%d",&z);
                    }

                }
            }


        } while(z==1);
}

//Delete a complaint
void delete_record()
{
    printf("\n----------------------------------------------------\n\n");
    int id;
    int flag=0;
     if((fptr=fopen("complaint.bin","rb"))==NULL)
	        {
		        printf("\n Cannot open the record file\n\n");
	        }
            else
            {
                printf("\n\nEnter the complaint id you want to delete:");
                scanf("%d",&id);
                kptr=fopen("temp.bin","wb");
                while(fread(&c,sizeof(c),1,fptr))
                {
                    if(c.comp_id==id)
                    {
                        printf("\nRecord found and deleted\n");
                        flag=1;
                    }
                    else
                    {
                        fwrite(&c,sizeof(c),1,kptr);
                    }
                }
                    if(flag!=1)
                        {
                            printf("\nThere is no record available\n");
                        }
                    fclose(fptr);
                    fclose(kptr);
                    fptr=fopen("complaint.bin","wb");
                    kptr=fopen("temp.bin","rb");
                    while(fread(&c,sizeof(c),1,kptr))
                    fwrite(&c,sizeof(c),1,fptr);
                    fclose(fptr);
                    fclose(kptr);
            }
        fflush(stdin);
        pause();

}
//Display the complaint according to the department
void display()
{
    struct public temp,buf;
    fp=fopen("complaint.bin","rb");
    int x,count;
    Label:
    printf("Choose the department whose complaints are to be shown :\n");
    printf("\n1.Civil Aviation\n2.Education\n3.Railways and Highways\n4.Telecommunication\n5.Tourism\n6.CGHS\n");
    scanf("%d",&x);
    printf("Chosen option : %d\n",x);
    rewind(fp);
    count=0;
    while( fread(&temp,sizeof(temp),1,fp))
    {

            if(x==temp.dept)
            {
            count++;
            printf("Complaint Id :%d\nName :%s\nAge :%d\nDate :%s\nComplaint :\n%s \nStatus :%s\n",temp.comp_id,temp.name,temp.age,temp.date,temp.comp,temp.status);
            printf("-------------------------------------------------------------------------------------\n");
            }
    }
    if(count==0)
        printf("There are no complaints in this department.\n\n");

    printf("Do You want to check another department.If so press 1 else any key to get back to main page");
    scanf("%d",&x);
    system("cls");
    if(x==1){
        goto Label;
    }
fclose(fp);
}



void pause()
{
    printf("Press enter to continue......");
    fflush(stdout);
    getchar();
    system("cls");
}
//No.of complaints department wise
void dept(int x)
{
     switch(x)
                {
                    case 1:
                    printf( "Civil Aviation\n");
                    break;
                    case 2:
                     printf( "Education\n");
                    break;
                    case 3:
                     printf( "Railways and Highways\n");
                    break;
                    case 4:
                     printf( "Telecommunication\n");
                    break;
                    case 5:
                     printf( "Tourism\n");
                    break;
                    case 6:
                     printf( "CGHS\n");
                    break;
                }

}

 void comp_number()

		 {
	int c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;
    fp=fopen("complaint.bin","rb");
	while(fread(&c,sizeof(c),1,fp)){
		int s;
		s=c.dept;
		switch(s){
			case 1:
			  c1++;
			  break;
			case 2:
			   c2++;
			   break;
			case 3:
			   c3++;
			   break;
			 case 4:
			   c4++;
			   break;
			 case 5:
			   c5++;
			   break;
			 case 6:
			   c6++;
			   break;
			 default:
			   break;
		}
	}
printf("\nThe number of complaints in all department\n\nCivil Aviation:\n%d\nEducation:\n%d\nRailways and highways :\n%d\nTelecommunication:\n%d\nTourism:\n%d\nCGHS:\n%d\n",c1,c2,c3,c4,c5,c6);
printf("\n----------------------------------------------------\n\n");
fclose(fp);
fflush(stdin);
pause();
		 }



