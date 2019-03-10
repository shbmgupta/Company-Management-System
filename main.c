#define to  "\x1B[32m"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int eid=1;
char dname[10][30]={"Production","Purchasing","Marketing","Sales","Training","Engineering","Facilities","Security","Insurance","Travel"};
//Function for employee structure
typedef struct employee{
	int empid;//employee id
	int depid;//employee's department id
	int manid;//employee's manger id
	char name[20],doj[15];
	int age,yoe/*years of experience*/,mar/*marital status*/,pay,ismanager;
	struct employee *next;
}emp;


//Function for manager structure
typedef struct manager{
	int empid;//manager's employee id
	int manid;//manager's manager id (always 0)
	int depid;//manger's department id
	int employeetotal;//total no. of employees under manager
	char name[20],doj[15];
	int age,yoe/*years of experience*/,mar/*marital status*/,pay,ismanager;
	emp* employees;
	struct manager *next;
}man;

//Function for Department structure
typedef struct dep{
	int depid;//Department No
	char depname[30];
	int managertotal;//total no. of maangers under manager
	int employeetotal;//total no. of employees under manager
	man *managers;
	struct dep *next;
}dep;

void printmanagerdetails(dep* comp,int id);
void printalldepartmentandmanagers(dep* comp);
void searchDepartmentById(dep *company,int id);
void printalldepartments(dep *company);
void printalldepartmentmanagersandemeployees(dep*);
void allemployeeundermanager(dep* comp,int id);

//Function to add a new department
dep* adddepartment(dep* comp,int c)
{
	int q;
	dep* x,*y;
	/*to create a new department*/
	x=(dep*)malloc(sizeof(dep));//Dynammically space provided in memeory
	x->managertotal=0;
	x->employeetotal=0;
	if(c==1)
	{
		printf("Enter the name of department(without spaces): ");
		scanf("%s",x->depname);
	}
	x->managers=NULL;
	x->next=NULL;
	y=comp;
	if(comp==NULL)//If there is no department in the company.
	{
		x->depid=1;
		comp=x;
	}
	else//If Departments are present in the Company.
	{
		/*add department at end and also number it*/
		while(y->next!=NULL)
			y=y->next;
		x->depid=y->depid+1;
		y->next=x;
	}
	if(c==0)
		strcpy(x->depname,dname[x->depid-1]);
	if(c==1)
	{
		printf("New Department added\n");
		printf("Department Id: %d\n",x->depid);
		printf("Department Name:%s\n",x->depname);
		searchDepartmentById(comp,x->depid);
	}
	return comp;
}


//Function to add Manager in the Department
dep* addmanager(dep *comp,int d,man *x,int choice)
{
	dep* a;
	a=comp;
	int flag=0;
	int i=1;
	while(a!=NULL)//If there is no Department
	{
		if(a->depid==d)
		{
			flag=1;
			break;
		}
		a=a->next;
	}
	if(flag==0)
	{
		printf("Invalid Department Id\n");
		return comp;
	}
	man *y;
	x->empid=eid++;//Assigning Employee Id to the Manager
	x->manid=0;//Assigning Manager Id to the Manager
	x->employeetotal=0;//Giving Initial no. of Employee in Manager
	x->depid=a->depid;//Telling that Manager will belong to which Department
	x->next=NULL;
	x->employees=NULL;//Initially providing no employee to Manager
	y=a->managers;
	a->managertotal++;//Increasing No. of manager
	if(a->managers==NULL)
	{
		
		a->managers=x;//Giving Newly made Manager to Company
	}
	else
	{
		while(y->next!=NULL)
		{
			y=y->next;
		}
		//x->manid=y->manid+1;
		y->next=x;
	}
	if(choice==1)
		printf("id: %d:%d:%d\n",a->depid,x->manid,eid-1);
	
	return comp;
}

//Function to Add New Employee
dep* addemployee(dep* comp,int d,int m,emp *x,int choice,int oldnew)
{
	dep* a;
	man *b;
	a=comp;
	int flag=0;
	//Going till end of department to find the particular manager
	while(a!=NULL)
	{
		if(a->depid==d)//if department is found then break to add new employee;
			{
				flag=1;
				break;
			}
		a=a->next;
	}
	if(flag==0)
	{
		printf("Invalid Department Id\n");
		return comp;
	}
	b=a->managers;//Manager is marked to add the employee
	flag=0;
	while(b!=NULL)
	{
		if(b->empid==m)
			{
				flag=1;
				break;
			}
		b=b->next;
	}
	if(flag==0)
	{
		printf("No Manager with such employee id in the given Department\n");
		return comp;
	}
	a->employeetotal++;
	emp *y;
	if(oldnew==1)
		x->empid=eid++;
	x->manid=b->empid;
	x->depid=a->depid;
	x->next=NULL;
	y=b->employees;
	b->employeetotal++;
	if(b->employees==NULL)
		b->employees=x;
	else
	{
		while(y->next!=NULL)
			y=y->next;
		y->next=x;
	}
	if(choice==1)
		printf("id: %d:%d:%d\n",x->depid,x->manid,x->empid);
	return comp;
}

//Function To Add Manager To Dept of least Manager
dep* addmanagertoleast(dep* comp,man* x)
{
	int min=comp->managertotal,id=comp->depid;
	dep* a=comp;
	//Checking Min no of Manager in Dept
	while(a!=NULL)
	{
		if(min > a->managertotal)
		{
			min=a->managertotal;
			id=a->depid;
		}
		a=a->next;
	}
	comp=addmanager(comp/*0*/,id/*depid*/,x/*manager node*/,0/*print details*/);
	return comp;
}

//Function To Add Empl to Manager having least no empl
dep* addemployeetoleast(dep* comp,int d,emp *x)
{
	dep *a=comp;
	//Checking for specific Dept
	while(a!=NULL)
	{
		if(a->depid==d)
			break;
		a=a->next;
	}
	int min=(a->managers)->employeetotal;
	int id=(a->managers)->empid;
	man* b;
	b=a->managers;
	//searching for manager having min no of empl
	while(b!=NULL)
	{
		if(min > b->employeetotal)
		{
			min=b->employeetotal;
			id=b->empid;
		}
		b=b->next;
	}
	comp=addemployee(comp,d,id,x,0,1/*empid new or old*/);
	return comp;
}

//Function to Generate Database
dep* generatedatabase()
{
	char c,name[20],doj[15];
	int age,yoe,mar,pay,ismanager,manid,depid;//used to read data from file
	FILE *fp;
	fp=fopen("employdatabase.txt","r");//opening database file
	int i;
	dep *comp,*d;
	comp=NULL;
	/*creates 10 departments*/
	for(i=0;i<10;i++) 
		comp=adddepartment(comp,0);//creates department and attaches it at end of series
	if(fp==NULL)//if the file does not exists or couldn't be opened
		printf("no such file found\n");
	else
	{
		while(fscanf(fp,"%c",&c)>0)
		{	
			fseek(fp,-1,SEEK_CUR);
			//to move char back to overcome 1st char skipped while checking 
			fscanf(fp,"%s",name);
			//used to skip the space b/w name and date of joining
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%s",doj);
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%d",&age);
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%d",&yoe);
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%d",&mar);
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%d",&pay);
			fseek(fp,+1,SEEK_CUR);
			fscanf(fp,"%d",&ismanager);
			fseek(fp,+1,SEEK_CUR);
			/*if according to file the employee is a manager*/
			if(ismanager==0) 
			{
				man *x;
				x=(man*)malloc(sizeof(man));
				strcpy(x->name,name);
				strcpy(x->doj,doj);
				x->age=age;
				x->yoe=yoe;
				x->mar=mar;
				x->pay=pay;
				x->ismanager=ismanager;
				/*function that adds manger to the department
				 with leat no. of manager*/
				comp=addmanagertoleast(comp,x);
			}
			/*else an employee*/
			else
			{
				emp *y;
				y=(emp*)malloc(sizeof(emp));
				strcpy(y->name,name);
				strcpy(y->doj,doj);
				y->age=age;
				y->yoe=yoe;
				y->mar=mar;
				y->pay=pay;
				y->ismanager=ismanager;
				/*adds employee to the manager with least no. of employees under
				 him in a particular department*/
				comp=addemployeetoleast(comp,rand()%10+1,y);
			}
		}
		fclose(fp);//closes the file
	}
	return comp;
}
//-------------------------------------------------------------------
//Function to Create New Record For Empl
dep* newrecord(dep* comp){
	emp* x;
	man* y;
	x=(emp*)malloc(sizeof(emp));//Dynammically size is allocated for Empl
	y=(man*)malloc(sizeof(man));//Dynammically size is allocated for Manager
	int choice,d,m,c;
	while(1)
	{
		printf("1.add new employee\n");
		printf("2.add new manager\n");
		printf("3.create new department\n");
		printf("0.return\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return comp;
			case 1:
				printf("please enter the employee details\n");
				printf("name: ");
				getchar();
				scanf("%[^\n]s",x->name);
				printf("date of joining(dd/mm/yyyy): ");
				scanf("%s",x->doj);
				printf("age(should be greater than 20): ");
				scanf("%d",&x->age);
				printf("years of experience: ");
				scanf("%d",&x->yoe);
				while(x->yoe > x->age-20){
					printf("	Invalid entry(either age or experience)	\n");
					printf("years of experience: ");
					scanf("%d",&x->yoe);
					}
				printf("marital status(0/1): ");
				scanf("%d",&x->mar);
				printf("pay: ");
				scanf("%d",&x->pay);
				x->ismanager=0;
				printalldepartmentandmanagers(comp);
				printf("enter department no. to add employee: ");
				scanf("%d",&d);
				printf("enter manager id to add employee: ");
				scanf("%d",&m);
				comp=addemployee(comp,d,m,x,1,1);
				//printemployeedetails
				break;
			case 2:
				printf("please enter the manager details\n");
				printf("name: ");
				getchar();
				scanf("%[^\n]s",y->name);
				printf("date of joining(dd/mm/yyyy): ");
				scanf("%s",y->doj);
				printf("age(should be greater than 20): ");
				scanf("%d",&y->age);
				printf("years of experience: ");
				scanf("%d",&y->yoe);
				while(y->yoe > y->age-20){
					printf("\tInvalid entry(either age or experience)	\n");
					printf("years of experience: ");
					scanf("%d",&y->yoe);
					}
				printf("marital status(0/1): ");
				scanf("%d",&y->mar);
				printf("pay: ");
				scanf("%d",&y->pay);
				x->ismanager=1;
				printalldepartments(comp);
				printf("enter department no. to add manager: ");
				scanf("%d",&d);
				comp=addmanager(comp,d,y,1);
				break;
			case 3:
				printf("Creating new department\n");
				c=1;
				if(c==0)
					continue;
				else if (c==1)
					comp=adddepartment(comp,1);
				else
					printf("Invalid Input\n");
				break;
			default:
				printf("\nInvalid entry\n");	
				break;			
		}
	}
}
//-------------------------------------------------------
//Function to Search specififc Dept using Dept_Id
void searchDepartmentById(dep *company,int id)
{
	if(company == NULL)
	{
		printf("Department does not exist!!!\n");
		return;
	}
	else
	{
		if(company -> depid == id)//Condition to Search the Dept
		{
			printf("Department with deapartment id %d is present.\n",id);
			printf("Department Id is %d.\n",company ->depid);
			if(company->depname[0]!='\0')
				printf("Department Name is %s\n",company->depname);
			printf("No of Employes %d\n",company->employeetotal);
            printf("No of Managers %d\n",company->managertotal);
			return;
		}
		else
		{
			searchDepartmentById(company -> next,id);
		}
	}
	
}


//Searching an Empl by their Date of Joining
void searchByDateofJoining(dep *mydep,char str[])
{
	dep *a;
	man *b;
	emp *c;
	a=mydep;
	while(a!=NULL)
	{
		b=a->managers;//First going to Managers
		while(b!=NULL)
		{
			if(strcmp(b->doj,str)==0)//This is for empl's manager
			{
				printf("%d:%d:%d----%s\n",b->depid,b->manid,b->empid,b->name);
			} 				
			c=b->employees;
			while(c!=NULL)
			{
				if(strcmp(c->doj,str)==0)//Now,Empl is going to be searched
				{
					printf("%d:%d:%d----%s\n",c->depid,c->manid,c->empid,c->name);
				}
				c=c->next;
			}
		b=b->next;
		}
	a=a->next;
	}
}		

//Searching an Empl by their family_insurance
void searchForFamilyInsurance(dep *company)
{	
	dep *a;
	man *b;
	emp *c;
	a = company;
	//if a person is married then he/she is eligble for the family insurance
	while(a != NULL)
	{
		b=a->managers;
		while(b!=NULL)
		{
			if(b->mar==1)//condition to check Marital Status of Manager
			{
				printf("%d:%d:%d - %s\n",b->depid,b->manid,b->empid,b->name);
			}
			c=b->employees;
			while(c!=NULL)
			{
				//condition to check Marital Status of Empl
				if(c->mar==1)
				{
					printf("%d:%d:%d - %s\n",c->depid,c->manid,c->empid,c->name);
				}
				c=c->next;
			}
		b=b->next;
		}
	a=a->next;
	}
}	

//Searching Empl by their Name
void SearchEmpByName(dep *company,char Name[])
{
	dep *a;
	man *b;
	emp *c;
	a=company;
	while(a != NULL)
	{
		b=a->managers;
		while(b != NULL)
		{
			c=b->employees;
			while(c != NULL)
			{
				//If input name matches Empl name,Search compl
				if(strcmp(c -> name,Name) == 0)
				{
					printf("Employee with name %s is present in the company\n",Name);
					printf("Name : %s \nAge : %d \nYOE : %d \nMAR : %d \nPay : %d \nManager ID : %d \nDepartment ID : %d \n",c -> name,c -> age,c -> yoe,c-> mar,c -> pay,c ->manid,c -> depid);
					return ;
				}
				c = c -> next;	
			}
			b = b -> next;
		}
		a = a -> next;
	}
}

//Search Empl by Empl_id
void SearchEmpById(dep *company,int id)
{
	dep *a;
	man *b;
	emp *c;
	a=company;
	while(a != NULL/*Going into Dept*/)
	{
		b=a->managers;
		while(b != NULL/*Going into Managers*/)
		{
			c=b->employees;
			while(c != NULL/*Going into Empl*/)
			{

				if(c->empid==id)//If Input Id matches Emp_Id,Empl is Searched
				{
					printf("Employee with id %d is present in the company\n",id);
					printf("Name : %s \nAge : %d \nYOE : %d \nMAR : %d \nPay : %d \nManager ID : %d \nDepartment ID : %d \n",c -> name,c -> age,c -> yoe,c-> mar,c -> pay,c ->manid,c -> depid);
					return ;
				}
				c = c -> next;	
			}
			b = b -> next;
		}
		a = a -> next;
	}
}



void insertionsort(int *array,char str1[][100],int n)
{
	int c,d,t;
	char str2[200];
	for (c = 1 ; c <= n - 1; c++) 
	{
    	d = c;
 
    	while ( d > 0 && array[d] > array[d-1]) 
    	{
	      t = array[d];
	      array[d]   = array[d-1];
	      array[d-1] = t;
	      strcpy(str2,str1[d]);
	      strcpy(str1[d],str1[d-1]);
	      strcpy(str1[d-1],str2);
	      d--;
    
    	}
  	}
}

//Function to sort Manager based on their pay
void SearchTopPaidManagers(dep *company)
{
	dep *a;
	man *b;
	int i=0,j=0;
	int list1[200];
	char list2[200][100];
	a=company;
	while(a!=NULL)
	{
		b=a->managers;
		while(b!=NULL)
		{
			list1[i]=b->pay;
			strcpy(list2[i],b->name);
			b=b->next;
			i++;
		}
	a=a->next;
	
	}
	insertionsort(list1,list2,i);
	printf("~~~~Top paid managers of the company~~~~\n\n");
	for(j=0;j<10;j++)
	{
		printf("%s---->	Rs.%d\n",list2[j],list1[j]);
	}
	printf("\n");	
}		
	
//Function to Search on the basis of Various Parameters
dep* searchrecord(dep* company)
{
	char date[15],name[20];
	int choice,id;
	while(1)
	{
		printf("0.Return to Back\n");
		printf("1.Search Department By Id\n");
		printf("2.Search Employee by Id\n");
		printf("3.Search Employee by date of joining\n");
		printf("4.Search all those with family insurance\n");
		printf("5.Search top paid managers\n");
		printf("6.Search employee by name\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return company;
			case 1:
				printf("Enter the Department Id: ");
				scanf("%d",&id);
				searchDepartmentById(company,id);//Search Dept by Id
				break;
			case 2:
				printf("Enter Employee Id: ");//Search Empl by Id
				scanf("%d",&id);
				SearchEmpById(company,id);
				break;
			case 3:
				printf("Enter the Date of Joining (dd/mm/yyyy): ");
				scanf("%s",date);
				searchByDateofJoining(company,date);//Search Empl by Date of Joining
				break;
			case 4:
				searchForFamilyInsurance(company);//Search for married Epml
				break;
			case 5:
				SearchTopPaidManagers(company);//Search Top-Paid Managers
				break;
			case 6:
				printf("Enter Employee Name: ");
				scanf("%s",name);
				SearchEmpByName(company,name);
				break;
		}
	}
}
//-------------------------------------------------------------

//function that take employee node and return manager node
man* emptoman(emp* b){
	man* a;
	a=(man*)malloc(sizeof(man));
	a->empid=b->empid;
	a->depid=b->depid;
	a->manid=0;
	strcpy(a->name,b->name);
	strcpy(a->doj,b->doj);
	a->age=b->age;
	a->yoe=b->yoe;
	a->mar=b->mar;
	a->pay=b->pay;
	a->ismanager=1;
	a->employeetotal=0;
	a->employees=NULL;
	a->next=NULL;
	return a;
	}

//promoting an emloyee
dep* promoteemployee(dep* comp,int id){
	int flag=0;
	dep* a;
	man *b,*w;
	emp *c,*q;
	a=comp;
	w=(man*)malloc(sizeof(man));
	while(a!=NULL){//Dept loop{
		b=a->managers;
		while(b!=NULL){//Manager Loop{
			if(b->empid==id){//Checking the id does it belong to Manager or not
				printf("\nThe person is already a Manager\n");
				return comp;
				}
			c=b->employees;
			if(c->empid==id){//Comparing the id to check the 1st empl under the manager
				q=c;
				b->employees=c->next;
				b->employeetotal--;
				printf("Employee found\n");
				flag=1;
				}
			else{
				//Travelling to (n-1)th empl
				while(c->next!=NULL){
					if(c->next->empid==id){
						q=c->next;
						flag=1;
						c->next=c->next->next;
						b->employeetotal--;
						printf("Employee found\n");
						break;
						}
					c=c->next;
					}
				}
			if(flag==1)
				break;
			b=b->next;
			}
		if(flag==1){
			//Traversing through all managers to reach last manager node
			b=a->managers;
			while(b->next!=NULL)
				b=b->next;
			w=emptoman(q);//converting employee node to manager node
			printf("Employee promoted to Manager Position\n\n");
			printf("Manager details:\n\n");
			b->next=w;//adding the promoted manager at the end of list
			free(q);//deleting the space for the employee node
			a->managertotal++;
			printmanagerdetails(comp,w->empid);
			break;
			}
		a=a->next;
		}
	return comp;
	}

dep* changeempdep(dep* comp,int id)
{
	int flag=0,d,m;
	dep *a;
	man *b;
	emp *c,*q;
	a=comp;
	while(a!=NULL)
	{
		b=a->managers;
		while(b!=NULL)
		{
			if(b->empid==id)
			{
				printf("Employee is a manager");
				return comp;
			}
			else{
				c=b->employees;
				if(c->empid==id)
				{
					flag=1;
					q=b->employees;
					b->employees=b->employees->next;
				}
				else
				{
					while(c->next!=NULL)
					{
						if(c->next->empid==id)
						{
							flag=1;
							q=c->next;
							c->next=q->next;
							break;
						}
						c=c->next;
					}
				}
			}
			if(flag==1)
				break;
			b=b->next;
		}
		if(flag==1)
			break;
		a=a->next;
	}
	if(flag==1)
	{
		b->employeetotal--;
		a->employeetotal--;
	}
	printalldepartmentandmanagers(comp);
	printf("Enter the Department: ");
	scanf("%d",&d);
	printf("Enter the Manager: ");
	scanf("%d",&m);
	comp=addemployee(comp,d,m,q,1,0);
	return comp;

}

//
//Function to print employees under Manager
void Print(man *manager){
	emp* x;
	x=manager->employees;//Getting the employees under a manager
	while(x != NULL){
		printf("id : %d , Name : %s\n",x -> empid,x -> name);
		x = x -> next;
		}
	}

//Check Existence of employee 
int isemployee(dep *comp,int id){
	dep* a;
	man* b;
	emp* c;
	a=comp;
	while(a!=NULL)/*Dept loop*/{
		b=a->managers;
		while(b!=NULL)/*Manager loop*/{
			c=b->employees;
			while(c!=NULL)/*Empl loop to check existence*/{
				if(c->empid==id)
					return 1;
				c=c->next;
				}
			b=b->next;
			}
		a=a->next;
		}	
	return 0;
	}

//Function to Swap informations
void swapdata(emp *b,man *c){
	int x;
	char y[20];
	x=b->empid;
	b->empid=c->empid;
	c->empid=x;
    	x=b->depid;
	b->depid=c->depid;
	c->depid=x;
    	b->manid=c->empid;
    	strcpy(y,b->name);
    	strcpy(b->name,c->name);
    	strcpy(c->name,y);
    	strcpy(y,b->doj);
    	strcpy(b->doj,c->doj);
    	strcpy(c->doj,y);
    	x=b->age;
	b->age=c->age;
	c->age=x;
    	x=b->yoe;
	b->yoe=c->yoe;
	c->yoe=x;
	x=b->mar;
	b->mar=c->mar;
	c->mar=x;

	}

//Function to Demote Manager
dep* demotemanager(dep* comp,int id){
	int flag=0;
	if(isemployee(comp,id)==1){
		printf("Already an Employee\n");
		return comp;
		}
	dep* a;
	man *b;
	a=comp;
	while(a!=NULL){
		b=a->managers;
		while(b!=NULL){
			if(b->empid==id){
				printf("Enter the employee to upgrade to Manager:\n");
				flag=1;
				break;
				}
			b=b->next;
			}
		if(flag==1)
			break;
		a=a->next;
		}
	Print(b);
	printf("Enter Employee Id to Upgrade to Manager: ");
	scanf("%d",&id);
	emp *c;
	c=b->employees;
	flag=0;
	while(c!=NULL){
		if(id==c->empid){
			flag=1;
			break;
			}
		else
			c=c->next;
		}
	if(flag==1){
		swapdata(c,b);
		c=b->employees;
		while(c!=NULL){
			c->manid=id;
			c=c->next;
			}
		}
	else
		printf("Employee ID not under the given Manager.");
	return comp;
	}
	
void modifybymanagers(dep *mydep,char str1[]){	
	dep *a; 	//	temp variable for storing the linked list (of department).
	man *b;		//	temp variable for storing the linked list (of manager).
	emp *c;		//	temp variable for storing the linked list (of employee).
	a=mydep;
	int ko=0;
	int u=0;
	int n1,n2,id,n3,sal,co=0;
	char str[20];
	while(a!=NULL){
		b=a->managers;
		while(b!=NULL){
			if(strcmp((b->name),str1)==0){//comparing the enterd name with name of managers in a perticular linked list.
				printf("\t\t\t\t\t\t++++++++++++++++++++++++\n");
        printf("\t\t\t\t\t\t +       Welcome       +\n");
        printf("\t\t\t\t\t        ++++++++++++++++++++++++\n");
        			u=1;
				printf("1.MODIFY YOUR DETAILS\n");
				printf("2.MODIFY YOUR EMPLOYEES DETAILS\n");
				ko=1;	
				scanf("%d",&n1);	//taking input for selecting options.
				while(n1!=1 && n1!=2){
					printf("invalid input Try again\n"); //if the input value is not in options.
					scanf("%d",&n1);
					}
				if(n1==1){
					printf("PRESS 1 FOR MODIFY YOUR NAME\n");
					printf("PRESS 2 FOR MODIFY YOUR MARITAL STATUS\n");
					scanf("%d",&n2);
					while(n2!=1 && n2!=2){
						printf("invalid input Try again\n");
						scanf("%d",&n2);
					}
					if(n2==1){
						char chname[20];
						printf("TYPE YOUR NEW NAME\n");
						getchar();
						scanf("%[^\n]s",chname);
						strcpy(b->name,chname);
						printf("YOUR NAME HAS BEEN MODIFIED\n");
						}
					if(n2==2){
						if(b->mar==1){
							b->mar=0;
							printf("YOUR MARITIAL STATUS IS BEING CHANGED\n");
							printf("NOW YOU WON'T GET YOUR FAMILY INSURANCE\n");
							}							
						else{
							b->mar=1;
							printf("YOUR MARITIAL STATUS IS BEING CHANGED\n");
							printf("NOW YOU WILL HAVE THE BENIFIT OF FAMILY INSURANCE\n");	
							}
						}
						break;
					}
				if(n1==2){
					printf("ENTER THE NAME OF YOUR EMPLOYEE \n");
					scanf("%s",str);
					c=b->employees;
					while((c)!=NULL){
						if(strcmp((c->name),str)==0){
							printf("PRESS 1 FOR MODIFY THE SALARY OF %s\n",c->name);
							printf("Press 2 FOR EXIT\n");
							scanf("%d",&n3);
							while(n3!=1 && n3!=2){
								printf("invalid input\n");
								scanf("%d",&n3);
							}
							if(n3==1){
								printf("ENTER THE NEW SALARY OF %s\n",c->name);
								scanf("%d",&sal);
								if(sal>(c->pay))
								printf("SALARY INCREMENTED\n");
								else
								printf("SALARY DECREMENTED\n");
								c->pay=sal;
								co=1;
								break;
								}
							if(n3==2){
								co=1;
								break;
								}
							}		
						else
							(c)=(c)->next;
							
						}
				
					}
				}	
								
		if(co==1|| ko==1)
			break;
		(b)=(b)->next;
		
		}
	a=a->next;
	}
	if(u==0)
		printf("Something is wrong-----No one is in company with that name\n");
}

//Function to modify employee details
void modifyEmlpoyeeDetails(dep *mydep,char str2[]){	
	dep *a;
	man *b;
	emp *c;
	int count=0;
	int n;
	int u=0;
	a=mydep;
	while(a!=NULL/*Dept loop to go to manager*/){
		b=a->managers;
		while(b!=NULL/*manager loop to go to empl*/){
				c=b->employees;
			while((c)!=NULL/*Empl loop*/){
				if(strcmp((c->name),str2)==0)//condtion to modify Personal Details of empl
				{	u=1;
					printf("PRESS 1 FOR MODIFY YOUR NAME\n");
					printf("PRESS 2 FOR MODIFY YOUR MARITAL STATUS\n");
					scanf("%d",&n);
					while(n!=1 && n!=2){
						printf("invalid input Try again\n");
						scanf("%d",&n);
					}
					if(n==1){/*Empl Name is modifying*/
						char chname[20];
						printf("TYPE YOUR NEW NAME\n");
						getchar();
						scanf("%[^\n]s",chname);
						strcpy(c->name,chname);
						printf("YOUR NAME HAS BEEN MODIFIED\n");
						}
					if(n==2){/*Empl Marital Status is modifying*/
						if(c->mar==1){
							c->mar=0;
							printf("YOUR MARITIAL STATUS IS BEING CHANGED\n");
							printf("NOW YOU WON'T GET YOUR FAMILY INSURANCE\n");
							}							
						else{
							c->mar=1;
							printf("YOUR MARITIAL STATUS IS BEING CHANGED\n");
							printf("NOW YOU WILL HAVE THE BENIFIT OF FAMILY INSURANCE\n");	
							}
						}
					break;	
				
				}
				else
					(c)=(c)->next;
					count++;
					
				}
		(b)=(b)->next;
		}
	a=a->next;
	}
	if(u==0)
		printf("Something is wrong-----No one is in company with that name\n");
}




//Function to Modify Personal Details
void modifypersonaldetails(dep *mydep){	
	int n;
	char str1[20],str2[20];
	printf("1.MANAGER LOGIN\n");
	printf("2.EMPLOYEE LOGIN\n");
	scanf("%d",&n);
	while(n!=1 && n!=2){
		printf("invalid input\n");
		scanf("%d",&n);
		}
	if(n==1){
		printf("ENTER YOUR NAME\n");
		scanf("%s",str1);
		modifybymanagers(mydep,str1);	
		}
	if(n==2){
		printf("ENTER YOUR NAME\n");
		scanf("%s",str2);
		modifyEmlpoyeeDetails(mydep,str2);
		}
	}		

//Function to check that for particular id manager is existing or not
int ismanager(dep* comp,int id){
	dep* a;
	man* b;
	emp* c;
	a=comp;
	while(a!=NULL){//Dept loop
		b=a->managers;
		while(b!=NULL){//Manager loop to Access particular manager
			if(b->empid==id)
				return 1;
			b=b->next;
			}
		a=a->next;
		}
	return 0;
	}

void printallemployeesundermanager(dep* comp,int mid){
	dep* a;
	man* b;
	emp *c;
	a=comp;
	while(a!=NULL){
		b=a->managers;
		while(b!=NULL){
			if(b->empid==mid){
				c=b->employees;
				while(c!=NULL){
					printf("%d:%d:%d\t%s\n",c->depid,c->manid,c->empid,c->name);
					c=c->next;
					}
				}
			b=b->next;
			}
		a=a->next;
		}
	}
int employeeundermanager(dep* comp,int mid,int id){
	dep* a;
	man* b;
	emp *c;
	a=comp;
	while(a!=NULL){
		b=a->managers;
		while(b!=NULL){
			if(b->empid==mid){
				c=b->employees;
				while(c!=NULL){
					if(c->empid==id)
						return 1;
					c=c->next;
					}
				return 0;
				}
			b=b->next;
			}
		a=a->next;
		}
	}
//Function to modify Record
dep* modifyrecord(dep* comp){
	int choice,id,x,mid;
	while(1)
	{
		printf("0.Return\n");
		printf("1.Personal Data Modification(managers)\n");
		printf("2.Personal Data Modification(employee)\n");
		printf("3.Change Employee's Department\n");
		printf("4.Promote Employee\n");
		printf("5.Demote Employee(manager)\n");
		
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return comp;
			case 1:
				printf("Enter your Manager Id: ");
				scanf("%d",&id);
				int a;
				a=ismanager(comp,id);
				if(a==1)
					modifypersonaldetails(comp);
				else
					printf("Entered ID is not of any Manager in the company\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			case 2:
				printf("Enter your Employee Id: ");
				scanf("%d",&id);
				int b;
				b=isemployee(comp,id);
				if(b==1)
					modifypersonaldetails(comp);
				else
					printf("Entered ID is not of any Employee in the company\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	
				break;
			case 3:
				printf("Enter Employee Id: ");
				scanf("%d",&id);
				comp=changeempdep(comp,id);
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;	

			case 4:
				printf("Enter your Employee Id(Manager): ");
				scanf("%d",&mid);
				x=ismanager(comp,mid);
				if(x==1)
				{
					printallemployeesundermanager(comp,mid);
					printf("Enter Employee Id to Promote: ");
					scanf("%d",&id);
					x=employeeundermanager(comp,mid,id);
					if(x==1)
						comp=promoteemployee(comp,id);
					else
						printf("No such employee found\n");
				}
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;			
				
			case 5:
				printf("Enter Employee Id(Manager): ");
				scanf("%d",&id);
				comp=demotemanager(comp,id);				
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
				
			default:
				printf("\nInvalid Entry\n");	
				break;
		}
	}
	return comp;
}

//-----------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Function To Delete Dept
dep *DeleteDept(dep *Department,int id){
	dep *x,*y;
	x=Department;
	//checking existence of dept
	if(Department==NULL){
		printf("No Department\n");
		return Department;
	}	

	//From Here Input Id is used to match with dept_id to delete the dept
	if(Department->depid==id){
		x=Department;
		Department=Department->next;
		return Department;
	}	
	else{
		x=Department;
		while(x->next!=NULL){
			if(x->next->depid==id){
				y=x->next;
				x->next=y->next;
				free(y);
				printf("DEPARTMENT DELETED\n\n");
				break;
			}
			x=x->next;
		}
		return Department;
	}
}

//Function To Delete Empl
dep *DeleteEmp(dep *company,int id,int flag)
{
	int i,j,k;
	emp *temp;
	emp *c;
	man *b;
	dep *a;
	temp = (emp*)malloc(sizeof(emp));

	a = company;
	while(a != NULL) // Company loop
	{
		b = a -> managers;
		while(b != NULL) // Manager loop
		{	
			c = b -> employees;
			if(c!=NULL)
			{
				if(c -> empid == id){					
					temp = c;
					b->employees = b->employees -> next;
					free(temp);
					if(flag == 0)
					{
						printf("EMPLOYEE DELETED\n\n");	
					}
					
					a->employeetotal--;
					b->employeetotal--;
					return company;
				}
				//Empl loop for searching to delete
				while(c -> next != NULL){
					if(c -> next -> empid == id){
						temp = c -> next;
						c -> next = c -> next -> next;
						free(temp);
						if(flag == 0)
						{
							printf("EMPLOYEE DELETED\n\n");	
						}
					
						a->employeetotal--;
						b->employeetotal--;
						return company;
					}
					else{
						c = c -> next;
					}
				}
			}
			b = b -> next;
		}
		a = a -> next;
	}
	return company;
}

//Function to Delete Manager
dep* DeleteMan(dep* Department,int id){

    int i=ismanager(Department,id)/*checking Id is of Manager or Not*/;
    if(i==1){
        Department=demotemanager(Department,id);

        Department=DeleteEmp(Department,id,1);
        printf("\n\nMANAGER DELETED\n\n");
        return Department;
    }
    else{
        printf("No such Manager found\n");
        return Department;
    }
}
dep* deltemultiple(dep* Department,int aa[],int n){
	int i;
	dep *a ;
	man* b;
	emp *c;
	for(i=0;i<n;i++){
		printf("deleted %d\n",aa[i]);
		if(ismanager(Department,aa[i])==1){
			Department=DeleteMan(Department,aa[i]);
			printf("\n\nDELETED\n");
			//printalldepartmentmanagersandemeployees(Department);
		}
		else if(isemployee(Department,aa[i])==1){
			Department=DeleteEmp(Department,aa[i],1);
			printf("\nDELETED\n");
				//printalldepartmentmanagersandemeployees(Department);
		
		}
		else
			printf("no employee with id %d is there in database\n",aa[i]);
	}
	return Department;
}
//Function To Delete Record
dep* deleterecord(dep* Department){
	int choice,id,i,n,a[100];
	while(1){
		
		printf("1.Delete Employee\n");
		printf("2.Delete Manager\n");
		printf("3.Delete Department\n");
		printf("4.Delete Multitple Employees(Employees+Managers)\n");
		printf("0.Return\n");
		printf("ENTER YOUR CHOICE  ");
		scanf("%d",&choice);
		switch(choice){
			
			case 1:
				printf("Enter Employee Id: ");
				scanf("%d",&id);
				Department=DeleteEmp(Department,id,0);
				break;
			case 2:
				printf("Enter Employee Id: ");
				scanf("%d",&id);
				Department=DeleteMan(Department,id);
				break;
			case 3:
				printf("Enter Department Id: ");
				scanf("%d",&id);
				Department=DeleteDept(Department,id);
				break;
			case 4:
				printf("Enter no. of Employees to Delete: ");
				scanf("%d",&n);
				for(i=0;i<n;i++)
					scanf("%d",&a[i]);
				Department=deltemultiple(Department,a,n);
				break;
			case 0:
				return Department;
			default:
				printf("\nInvalid Entry\n");	
				break;	
		}
	}
}

//-----------------------------------------------

//Function To print Dept List
void printalldepartments(dep *company)
{
	dep* comp;
	comp=company;
	while(comp!=NULL)
	{
		//Dept Details to Print
		printf("Dep %d(%s):\n\tManager Count:%d(%d)\n",comp->depid,comp->depname,comp->managertotal,comp->employeetotal);
		comp=comp->next;
	}
}

//Function To Print Dept and Managers
void printalldepartmentandmanagers(dep* comp)
{
	man* x;

	while(comp!=NULL)
	{
		//Printing Details for Dept
		if(comp->depname[0]!='\0')
			printf("Dep %d(%s)\tManager Count:%d\n",comp->depid,comp->depname,comp->managertotal);
		x=comp->managers;
		while(x!=NULL)
		{
			//Printing Details for Manager
			printf("\t%d:%d:%d  %s(%d)\n",x->depid,x->manid,x->empid,x->name,x->employeetotal);
			x=x->next;
		}
		comp=comp->next;
	}
}

//Function To Print Dept,Manager And Empl
void printalldepartmentmanagersandemeployees(dep *comp)
{
	dep *a;
	man *b;
	emp *c;
	a=comp;
	while(a!=NULL)
	{
		//Details For Dept
		//printf("Dep %d(%d)(%d):\n",a->depid,a->managertotal,a->employeetotal);
		if(a->depname[0]!='\0')
			printf("Dep:%d(%s)\tManager Count: %d\tEmplyee Count: %d\n",a->depid,a->depname,a->managertotal,a->employeetotal);		
		else
			printf("Dep:%d\tManager Count: %d\tEmplyee Count: %d\n",a->depid,a->managertotal,a->employeetotal);		
		
		b=a->managers;
		while(b!=NULL)
		{
			//Details For Manager
			printf("\t%d:%d:%d(%d):",b->depid,b->manid,b->empid,b->employeetotal);
			printf("%s",b->name);
			c=b->employees;
			while(c!=NULL)
			{
				//Details For Empl
				printf("\n\t\t%d:%d:%d ",c->depid,c->manid,c->empid);
				printf("%s",c->name);
				c=c->next;
			}
			printf("\n\n");
			b=b->next;
		}
		a=a->next;
	}
}

void allemployeeundermanager(dep* comp,int id)
{
	dep* a;
	man *b;
	emp *c;
	a=comp;
	while(a!=NULL)
	{
		b=a->managers;
		while(b!=NULL)
		{
			if(b->empid==id)
			{
				c=b->employees;
				while(c!=NULL)
				{
					printf("%d:%d:%d\t%s\n",c->depid,c->manid,c->empid,c->name);
					c=c->next;
				}
				return;
			}
			b=b->next;
		}
		a=a->next;
	}
}
//Function To Print Manager Details
void printmanagerdetails(dep* comp,int id)
{
	dep* a;
	man *b;
	a=comp;
	while(a!=NULL)
	{
		b=a->managers;
		while(b!=NULL)
		{
			//condition to check Particular Manager
			if(b->empid==id)
			{
				printf("Position: Manager\n");
				printf("Name: %s\nDepartment Id: %d\nDepartment Name: %s\nEmployee Id: %d\n",b->name,b->depid,a->depname,b->empid);
				printf("No. of Employees under Manager:%d\n",b->employeetotal);
				printf("Date of Joining: %s\n",b->doj);
				printf("Age: %d\nYears of Experience: %d\n",b->age,b->yoe);
				printf("Pay: %d\nMarital Status: ",b->pay);
				if(b->mar==0)
					printf("Not Married\n");
				else
					printf("Married\n");
				printf("Employees under manager: \n");
				allemployeeundermanager(comp,id);
				return;
			}
			b=b->next;
		}
		a=a->next;
	}
	printf("no manager found with the given id\n");
}

//Function to Print all Details of Database
void printdatabase(dep* comp){
	int choice,id;
	while(1)
	{
		printf("\t\t\t\t\t\t++++++++++++++++++++++++\n");
        printf("\t\t\t\t\t\t +   Print Database   +\n");
        printf("\t\t\t\t\t  	++++++++++++++++++++++++\n");
		printf("0.Return\n");
		printf("1.Print all departments\n");
		printf("2.Print department wise managers\n");
		printf("3.Print mega database of department"); 
		printf("wise managers and employees\n");
		printf("4.Print details of a manager\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return;
			case 1:
				printf("\n--------------------------------------------------\n");
				printalldepartments(comp);
				break;
			case 2:
				printf("\n--------------------------------------------------\n");
				printalldepartmentandmanagers(comp);
				break;
			case 3:
				printf("\n--------------------------------------------------\n");
				printalldepartmentmanagersandemeployees(comp);
				break;
			case 4:
				printf("\n--------------------------------------------------\n");
				printf("Enter Manager's Employee Id: ");
				scanf("%d",&id);
				printmanagerdetails(comp,id);
				break;
		}
	}
}
//------------------------------------------------
void feedback(){
    char s[1000];int t=0;
    getchar();
    s[0]='\0';
    printf("\nWrite Your Feedback: ");
    scanf("%[^\n]s",s);
if(s!='\0'){
	 printf("\nYour Valuable Feedback is received: *%s*\n\n",s);
    printf("\t\t\t\t\t\t+++++++++++++++++++++++++++\n");
    printf("\t\t\t\t\t\t+   Thank You,            +\n");
    printf("\t\t\t\t\t\t+        See You Soon.    +\n");
    printf("\t\t\t\t\t\t+++++++++++++++++++++++++++\n\a");
    printf("\n\n");}
    else
        {printf("\t\t\t\t\t\t\t\t\t\t++++++++++++++++++++++++\n");
        printf("\t\t\t\t\t\t\t\t\t\t+     Try Later        +\n");
        printf("\t\t\t\t\t\t\t\t\t\t++++++++++++++++++++++++\n");}
}
//------------------------------------------------


//Main Function
int main()
{
	dep* comp=NULL;
	int choice,x;
	//To generate Random Number
	time_t t;
	//srand((unsigned) time(&t));
	printf("Do you want to Auto Generate Database(0/1): ");
	scanf("%d",&x);
	if(x!=0)
		comp=generatedatabase();
	while(1)
	{
		printf("\t\t\t\t%s\t++++++++++++++++++++++++++++++++++++++++\n",to);
        printf("\t\t\t\t\t+                                      +\n");
        printf("\t\t\t\t\t +    Welcome to Employee Database    +\n");
        printf("\t\t\t\t\t+                                      +\n");
        printf("\t\t\t\t\t++++++++++++++++++++++++++++++++++++++++\n\n\n");
		printf("1.New_Record\n");
		printf("2.Search_Record\n");
		printf("3.Modify_Record\n");
		printf("4.Delete_Record\n");
		printf("5.Print_Database\n");
		printf("6.Feedback\n");
		printf("0.Exit\n");
		printf("Enter Your Choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				printf("--------------------------------------------------\n");
				comp=newrecord(comp);
				break;
			case 2:
				printf("--------------------------------------------------\n");
				comp=searchrecord(comp);
				break;
			case 3:
				printf("--------------------------------------------------\n");
				comp=modifyrecord(comp);
				break;
			case 4:
				printf("--------------------------------------------------\n");
				comp=deleterecord(comp);
				break;
			case 5:
				printf("--------------------------------------------------\n");
				printdatabase(comp);
				break;
			case 6:
				printf("--------------------------------------------------\n");
                feedback();
                break;
            default:
            	printf("Invalid Entry\n"); 
		}
	}
	return 0;
}
