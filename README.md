# Employee-Database
MEMBERS - 
Sagar(Leader) sagar.r16@iiits.in
Rahul Kumar rahul.k16@iiits.in
Shubham Gupta shubham.g16@iiits.in
Adamya Gupta adamya.g16@iiits.in

# Description: 

This project will help to perform some specific   tasks   related   for   maintaining   an  
Employee   Database . This database will have the details of the employees working in  a  
certain   company i.e employee ID,name,department,hiring date,manager ID .  Employee's  
ID are used as a primary key.

The project functions perform the following tasks:-

# 1.Creates a new record.
# 2.Search  records.
# 3.Modify records.
# 4.Delete records.
# 5.Print records

The program consists of following structures:

# 1.Employee
	The department node consists of the following parameters:
		>>>Department id
		>>>Department name
		>>>Total no. of managers
		>>>Total no. of employees
# 2.Manager
	The manager node consists of following parameters
		>>>Employee id--decided automatically
		>>>Manager id---manager id of a manager is always zero
		>>>Department id
		>>>Total no. of employees
		>>>Name of manager
		>>>Date of joining
		>>>Age 
		>>>Years of experience
		>>>Pay
		>>>Marital status
# 3.Department
	The employee node consists of following parameters
		>>>Employee id
		>>>Department tid
		>>>Manager id
		>>>Name
		>>>Date of joining
		>>>Years of experience
		>>>Marital status
		>>>Pay

The data structure used is 1).A linked list of all departments 
each department consists   2).A linked list of all managers in the department
each manager consists of   3).A linked list of all employees under the manager.

Id  of an Employee is as as follows:-
	Department Id:Manager Id:Employee Id
If the Employee is a Manager then the employees Manager ID is zero(0)

Use of data structure:-
	The given strcture is a form of a tree which basically forms heirarchy structure.
	Heirarchy:
		Departments->Managers->Employees 

# task 1:---Create a new record
	# Subtask 1:---Create a new department
		Creates a new department node and attaches it at the end of list of departent
		Input:
			*Department name
		Output:
			*Department id
			*Department name
			*No. of employees
			*No. of managers
	# Subtask 2:---Create a new manager
		Creates a new manager node and attaches it to a particular department's managers list.
		Input:
			*Name
			*Date of joining
			*Age
			*Years of experience
			*Marital status
			*Department id
		Output:
			*Employee id assigned to the manager

	# Subtask 3:---Create a new employee
		Creates a new employee node and attaches it to a particular department.the department id and manager id are taken as Input.
		Input:
			*Name
			*Date of joining
			*Age 
			*Years of experience
			*Marital status
			*Pay
			*Department id 
			*Manager id
		Output:
			*Employee id assigned to employee
# task 2:---Search record
    # Subtask 1:---Search Department By Id
    	prompts the user
    	Input:
    	    *Department Id
    	Output:
    	    *Existence of Department
    	    *Department Id
    	    *No. of Employee
    	    *No. of Manager
	# Subtask 2:---Search Employee by Id
        Input:
            *Employee Id
        Output:
            *Existence of Employee
            *Name
            *Age
            *Year of Experiene
            *Marital Status
            *Pay
            *Manager Id
            *Department Id
    # Subtask 3:---Search Employee by date of joining
        Input:
            *Date of Joining(dd/mm/yyyy)
        Output:
            *Employee Name
            *Employee Id
    # Subtask 4:---Search all those with family insurance
        Input:
            *No Input(Only to Print All Data)
        Output:
            *Employee Name
            *Employee Id
    # Subtask 5:---Search top paid managers
        Input:
            *No Input
        Output:
            *Manager Name
            *Manager Pay
    # Subtask 6:---Search employee by name
        Input:
            *Employee Name
        Output:
            *Existence of employee
            *Name
            *Age
            *Year Of Exprience
            *Marital Experience
            *Pay
            *Manager Id
            *Department Id
# task 3:---modify record
    # Subtask 1:---Change Employee's Department
        Input:
            *Employee Id
            *Desired Department
            *Desired Manage
        Output:
            *Changed Id
    # Subtask 2:---Change Employee's Manager
        Input:
            *Employee Id
            *Desired Manager
        Output:
            *Changed Id
    # Subtask 3:---Promote Employee
        Input:
            *Manager's Employee Id
            (A List of Shot-lised Employee is printed)
            *Employee Id To Promote
        Output:
            *Existence of Employee
            *Eployee promoted to Manager Position Printed
            *Position
            *Name
            *Department Id
            *Employee Id
            *No. of Employee Under Manager
            *Date of Joining
            *Age
            *Years of Experience
            *Pay
            *Marital Status
    # Subtask 4:---Demote Employee
        Input:
            *Employee Id
            *Employee Id from Short-Listed List
        Output:
            *Employee Get Demoted
    # Subtask 5:---Personal Data Modification(managers)
        Input:
            *Manager Id
            *Do Login(Redirected to company's login page)
            (A manager can only modify his personal details and the salary of his all employes)
            assumption-a manager can't modify his salary, date of journey and name of his employees.
        Output:
            *Data Get Modified
    # Subtask 6:---Personal Data Modification(employee)
        Input:
            *Employee Id
            *Do Login(Redirected to company's login page)
        Output:
            *Data Get Modified
             (Personal details of employee can be modified)
             assumption-an employee can't modify his salary and his date of journey.
# task 4:---delete record
	# Subtask 1:---Delete Employee
		Input:
			*Employee id to delete
		Output:
			*Deletes the employee
	# Subtask 2:---Delete Manager
		Input:
			*Manager id to be deleted
			*Employee under manager to be deleted 
		Output:
			*Employee deleted
	# Subtask 3:---Delete Department
		Input:
			*Department id to delete
			*Confirmation to delete
		Output:
			*Department deleted
	# Subtask 4:---Delete Multitple Employees(Employees+Managers)
		Input:
			*No. of employees/managers to be deleted
			*List of employee id of these employees
		Output:
			*All employees deleted (if manager it will ask for the employee to be upgraded to manager)
# task 5:---Print database
	# Subtask 1:---Print all departments
		prints the list of:-
			*Departments id and names
			*Total no. of managers in department
			*Total no. of employees in the department
	# Subtask 2:---Print department wise managers
		prints the list of:-
			*Departments id and names
			*Total no. of managers 
			*List of all managers and their name 
			*Total no. of employees under manager
	# Subtask 3:---Print mega database of department wise managers and employees
		prints the list of:-
			*Departments id and names 
			*List of all managers and manager id
			*List of all employees and employee id under manager
			*Employees under manager with their names and employee id
	# Subtask 4:---Print details of a manager
		Input:
			*Manager's employee id
		ouput:
			*Manager id
			*Manager name
			*Department name
			*No. of employees under manager
			*Date of joining
			*Age
			*Years off experiencce
			*Pay
			*Marital ststus
			*List of employee under manager with their name and id

