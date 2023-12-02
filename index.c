#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function declarations
void login_user();
void set_budget();
void save_income();
void save_expenses();
void set_goal();
void read_goal();
void searchIncome();
void searchExpenses();
void delete_entry();
void delete_from_income();
void delete_from_expenses();
void exit_function();
// income and expenses
typedef struct
{
    char date[20];
    char category[20];
    float amount;
    struct income *next;
} income;
typedef struct
{
    char date[20];
    char category[20];
    float amount;
    struct expenses *next;
} expenses;

int main()
{
    login_user();
    int choice;
    while (1)
    {
        system("cls");
        readIncomeFromFile("income_data.txt");
        readExpensesFromFile("expenses_data.txt");
//        system("color 9");
        printf("\n\n\n\t\t\t******* WELCOME TO THE MAIN MENU *******\n");
        read_goal();
        // Initialize the transactions array
        printf("\n\t\t1. Save Income\n");
        printf("\t\t2. Save Expense\n");
        printf("\t\t3. Set Budget\n");
        printf("\t\t4. Check Budget\n");
        printf("\t\t5. Check Transaction History\n");
        printf("\t\t6. Set Goal\n");
        printf("\t\t7. Search Transaction\n");
        printf("\t\t8. Delete Entry\n");
        printf("\t\t9. Exit\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            save_income();
            break;
        case 2:
            system("cls");
            save_expenses();
            break;
        case 3:
            system("cls");
            set_budget();
            break;
        case 4:
            system("cls");
            check_budget();
            break;
        case 5:
            system("cls");
            transaction();
            break;
        case 6:
            system("cls");
            set_goal();
            break;
        case 7:
            system("cls");
            printf("\n\t\t1. Search From Income List\n");
            printf("\n\t\t2. Search From Expenses List\n");
            printf("\n\t\tChoose Your Option: ");
            int x;
            scanf("%d",&x);
            if(x==1)
            {
                searchIncome();
            }
            else searchExpenses();
            break;
        case 8:
            system("cls");
            delete_entry();
            break;
        case 9:
            system("cls");
            freeIncomeList();
            freeExpensesList();
            exit_function();
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
//log in
void login_user()
{
    char username[10];
    char password[10];
    system("cls");
//    system("color 9");
    printf("\n\n\n");
    printf("\n\t\t\t\t            ---------***---------");
    printf("\n\t\t\t            ~~~~~~~~~~~~~~~~~ * ~~~~~~~~~~~~~~~~~ ");
    printf("\n\t\t\t        |                                           |");
    printf("\n\t\t\t        |                  WELCOME                  |");
    printf("\n\t\t\t        |                    TO                     |");
    printf("\n\t\t\t        |               MONEY MANAGER               |");
    printf("\n\t\t\t        |                                           |");
    printf("\n\t\t\t            ~~~~~~~~~~~~~~~~~ * ~~~~~~~~~~~~~~~~~ ");
    printf("\n\t\t\t\t            ---------***---------");
    printf("\n\n\t\t\t\t\t  Username: ");
    scanf("%s", username);
    printf("\n\t\t\t\t\t  Password: ");
    scanf("%s", password);
    printf("***********************************\n");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tLogin successful. Welcome, %s!", username);
        getchar();
        getchar();
    }
    else
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tLogin failed. Please try again.");
        getchar();
        getchar();
        login_user();
    }
}


income *income_head;
expenses *expenses_head;
// Function to create a new income node
income *createIncomeNode(char date[20], char cat[20], float amount)
{
    income *newIncome = (income *)malloc(sizeof(income));
    if (newIncome == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(newIncome->date, date);
    strcpy(newIncome->category, cat);
    newIncome->amount = amount;
    newIncome->next = NULL;
    return newIncome;
}

// Function to add a new income to the linked list
void addIncome(char date[30], char cat[30], float amount)
{
    income *newIncome = createIncomeNode(date, cat, amount);
    newIncome->next = income_head;
    income_head = newIncome;
}
void listincome(char date[30], char cat[30], float amount)
{
    income *newIncome = createIncomeNode(date, cat, amount);
    if(income_head==NULL) income_head=newIncome;
    else
    {
        income *c=income_head;
        while(c->next!=NULL)
        {
            c=c->next;
        }
        c->next=newIncome;
    }
}
// Function to read income data from a file
void readIncomeFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nFile opening failed\n");
        exit(1);
    }

    income_head = NULL;
    char date[20];
    char category[20];
    float amount;
    while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
    {
        listincome(date, category, amount);
    }

    fclose(file);
}
// Function to write income data to a file
void writeIncomeToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("File opening failed");
        exit(1);
    }

    income *current = income_head;
    while (current != NULL)
    {
        fprintf(file, "%s %s %.2f\n", current->date, current->category, current->amount);
        current = current->next;
    }

    fclose(file);
}

// Function to free the memory used by the linked list
void freeIncomeList()
{
    while (income_head != NULL)
    {
        income *temp = income_head;
        income_head = income_head->next;
        free(temp);
    }
}

void save_income()
{
    char d[20];
    float amount;
    int x;
    // Read existing data from the file
    printf("\t\tEnter The Date: ");
    scanf("%s",d);
    printf("\n\t\t1. Salary\n");
    printf("\t\t2. Bonus\n");
    printf("\t\t3. Pocket_Money\n");
    printf("\t\t4. Other\n");
    printf("\n\t\tEnter The Category No.: ");
    scanf("%d",&x);
    printf("\t\tEnter The Amount: ");
    scanf("%f",&amount);
    printf("\n\n\n");
    if(x==1) addIncome(d, "Salary", amount);
    else if(x==2) addIncome(d, "Bonus", amount);
    else if(x==3) addIncome(d, "PMoney", amount);
    else if(x==4) addIncome(d, "Other", amount);
    else
    {
        printf("\t\t\n\nSelect Again...");
        getchar();
        save_income();
    }
    // Write the entire updated linked list back to the file
    writeIncomeToFile("income_data.txt");
    // Free memory
    freeIncomeList();
    printf("\n\t\tIncome Save To File Successfully...\n\n\t\tEnter 1 For Save Another Income or Enter 2 To Return Main Menu:  ");
    int y;
    scanf("%d",&y);
    if(y==1) save_income();
    else return;
}

// Function to create a new expenses node
expenses *createExpensesNode(char date[20], char cat[20], float amount)
{
    expenses *newExpenses = (expenses *)malloc(sizeof(expenses));
    if (newExpenses == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(newExpenses->date, date);
    strcpy(newExpenses->category, cat);
    newExpenses->amount = amount;
    newExpenses->next = NULL;
    return newExpenses;
}

// Function to add a new expenses to the linked list
void addExpenses(char date[30], char cat[30], float amount)
{
    expenses *newExpenses = createExpensesNode(date, cat, amount);
    newExpenses->next = expenses_head;
    expenses_head = newExpenses;
}
//function for taking file data and creating list
void listexpenses(char date[30], char cat[30], float amount)
{
    expenses *newExpenses = createExpensesNode(date, cat, amount);
    if(expenses_head==NULL) expenses_head=newExpenses;
    else
    {
        expenses *c=expenses_head;
        while(c->next!=NULL)
        {
            c=c->next;
        }
        c->next=newExpenses;
    }
}
// Function to read expenses data from a file
void readExpensesFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nFile opening failed\n");
        exit(1);
    }

    expenses_head = NULL;
    char date[20];
    char category[20];
    float amount;
    while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
    {
        listexpenses(date, category, amount);
    }

    fclose(file);
}
// Function to write expenses data to a file
void writeExpensesToFile(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("File opening failed");
        exit(1);
    }

    expenses *current = expenses_head;
    while (current != NULL)
    {
        fprintf(file, "%s %s %.2f\n", current->date, current->category, current->amount);
        current = current->next;
    }

    fclose(file);
}

// Function to free the memory used by the linked list
void freeExpensesList()
{
    while (expenses_head != NULL)
    {
        expenses *temp = expenses_head;
        expenses_head = expenses_head->next;
        free(temp);
    }
}

void save_expenses()
{
    char d[20];
    float amount;
    int x;
    // Read existing data from the file
    readExpensesFromFile("expenses_data.txt");
    printf("\t\tEnter The Date: ");
    scanf("%s",d);
    printf("\n\t\t1. Food\n");
    printf("\t\t2. Transportation\n");
    printf("\t\t3. Health\n");
    printf("\t\t4. Other\n");
    printf("\n\t\tEnter The Category No.: ");
    scanf("%d",&x);
    printf("\t\tEnter The Amount: ");
    scanf("%f",&amount);
    printf("\n\n\n");
    if(x==1) addExpenses(d, "Food", amount);
    else if(x==2) addExpenses(d, "TPort", amount);
    else if(x==3) addExpenses(d, "Health", amount);
    else if(x==4) addExpenses(d, "Other", amount);
    else
    {
        printf("\t\t\n\nSelect Again...");
        getchar();
        save_expenses();
    }
    // Write the entire updated linked list back to the file
    writeExpensesToFile("expenses_data.txt");
    // Free memory
    freeExpensesList();
    int y;
    do
    {
        printf("\n\t\tExpenses Save To File Successfully...\n\n\t\tEnter 1 For Save Another Income or Enter 2 To Return Main Menu:  ");
        scanf("%d",&y);
        if(y==1) save_expenses();
        else if(y==2) return;
    }
    while (y != 1 && y != 2);
}
//income history
void income_history()
{
    FILE *file = fopen("income_data.txt", "r");
    if (file == NULL)
    {
        printf("\nFile opening failed\n");
        exit(1);
    }
    char date[20];
    char category[20];
    float amount,total=0.00;
    int d1,d2,m1,m2,y1,y2;
    printf("\n\t\tEnter Todays Date(dd/mm/yyyy): ");
    char d[20];
    scanf("%s",d);
    sscanf(d, "%d/%d/%d", &d1, &m1, &y1);
    printf("\n\n\t\t1. Check Daily Income\n");
    printf("\n\t\t2. Check Monthly Income\n");
    printf("\n\t\t3. Check Yearly Income\n");
    printf("\n\t\tChoose Your Option: ");
    int x;
    scanf("%d",&x);
    printf("\n\t\tDate\t\t\tCategory\t\tAmount\n\n");
    if(x==1)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            //converting string to int by sscanf
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m1==m2 && y1==y2)
            {
                printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
            }
        }
    }
    if(x==2)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m2==m1-1 && y1==y2) break;
            total+=amount;
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tYour Monthly Income From %d/%d/%d To %d/%d/%d: %.2f",++d1,--m1,y1,d1,m1,y1,total);
    }
    if(x==3)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m2==m1 && y2==y1-1) break;
            total+=amount;
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tYour Yearly Income From %d/%d/%d To %d/%d/%d: %.2f",++d1,m1,--y1,d1,m1,y1,total);
    }
    printf("\n\n\t\tPress Any Key To Return Main Menu...");
    getchar();
    getchar();
    fclose(file);
}

void expenses_history()
{
    FILE *file = fopen("expenses_data.txt", "r");
    if (file == NULL)
    {
        printf("\nFile opening failed\n");
        exit(1);
    }
    char date[20];
    char category[20];
    float amount,total;
    int d1,d2,m1,m2,y1,y2;
    printf("\n\t\tEnter Todays Date(dd/mm/yyyy): ");
    char d[20];
    scanf("%s",d);
    sscanf(d, "%d/%d/%d", &d1, &m1, &y1);
    printf("\n\n\t\t1. Check Daily Expenses\n");
    printf("\n\t\t2. Check Monthly Expenses\n");
    printf("\n\t\t3. Check Yearly Expenses\n");
    printf("\n\t\tChoose Your Option: ");
    int x;
    scanf("%d",&x);
    printf("\n\t\tDate\t\t\tCategory\t\tAmount\n\n");
    if(x==1)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m1==m2 && y1==y2)
                printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
    }
    if(x==2)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m2==m1-1 && y1==y2) break;
            total+=amount;
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tYour Monthly Expenses From %d/%d/%d To %d/%d/%d: %.2f",++d1,--m1,y1,d1,m1,y1,total);
    }
    if(x==3)
    {
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            sscanf(date, "%d/%d/%d", &d2, &m2, &y2);
            if(d1==d2 && m2==m1 && y2==y1-1) break;
            total+=amount;
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tYour Yearly Income From %d/%d/%d To %d/%d/%d: %.2f",++d1,m1,--y1,d1,m1,y1,total);
    }
    printf("\n\n\t\tPress Any Key To Return Main Menu...");
    getchar();
    getchar();
    fclose(file);
}
void transaction()
{
    char date[20];
    char category[20];
    float amount;
    printf("\n\t\t1. All Income History\n");
    printf("\n\t\t2. Income History(Daily/Monthly/Yearly)\n");
    printf("\n\t\t3. All Expenses History\n");
    printf("\n\t\t4. Expenses History(Daily/Monthly/Yearly)\n");
    printf("\n\t\tChoose The Option:  ");
    int x;
    scanf("%d",&x);
    if(x==1)
    {
        system("cls");
        FILE *file = fopen("income_data.txt", "r");
        printf("\t\tDate\t\t\tCategory\t\tAmount\n\n");
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tPress Any Key To Return Main Menu...");
        getchar();
        getchar();
        fclose(file);
    }
    else if(x==2)
    {
        system("cls");
        income_history();
    }
    else if(x==3)
    {
        system("cls");
        FILE *file = fopen("expenses_data.txt", "r");
        printf("\t\tDate\t\t\tCategory\t\tAmount\n\n");
        while (fscanf(file, "%s %s %f", date, category, &amount) != EOF)
        {
            printf("\t\t%s\t\t%s\t\t\t%.2f\n",date, category, amount);
        }
        printf("\n\n\t\tPress Any Key To Return Main Menu...");
        getchar();
        getchar();
        fclose(file);
    }
    else if(x==4)
    {
        system("cls");
        expenses_history();
    }
    else
    {
        printf("\n\n\t\tChoose Valid Option...");
        getchar();
        transaction();
    }

}

void set_budget()
{
    float budget;
    char sd[20],ed[20];
    printf("\n\t\tEnter the Starting Date: ");
    scanf("%s",sd);
    printf("\n\t\tEnter the Ending Date: ");
    scanf("%s",ed);
    printf("\n\t\tEnter the budget amount: ");
    scanf("%f", &budget);
    FILE *file = fopen("budget.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%s %s %.2f",sd,ed, budget);
    fclose(file);
    printf("\n\t\tBudget set successfully.\n\n\t\tPress Any Key To Return Main Menu...");
    getchar();
    getchar();
}
void check_budget()
{
    readExpensesFromFile("expenses_data.txt");
    float budget;
    char sd[20];
    char ed[20];

    FILE *file = fopen("budget.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fscanf(file, "%s %s %f", sd, ed, &budget);
    fclose(file);
    float totalExpenses = 0.0;
    expenses *current = expenses_head;
    while (current!= NULL)
    {
        if (strcmp(ed, current->date) == 0)
        {
            break;
        }
        current = current->next;
    }
    if(current==NULL) current = expenses_head;
    expenses *cnext = current->next;

    while (current != NULL)
    {
        if (strcmp(sd, current->date) == 0 || current->next==NULL)
        {
            //for calculating end date all data
            if((current->next==NULL || strcmp(sd, cnext->date) != 0))
            {
                totalExpenses += current->amount;
                break;
            }
        }
        totalExpenses += current->amount;
        current = current->next;
        cnext=cnext->next;
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\t\tTotal Expenses Between %s And %s: %.2f\n", sd, ed, totalExpenses);
    printf("\n\t\tRemaining Budget: %.2f\n\n\t\tPress Any Key To Return Main Menu...", budget - totalExpenses);
    getchar();
    getchar();
}


void set_goal()
{
    char goal[20];
    float amount;
    printf("\n\n\n\t\tEnter The Goal: ");
    scanf("%s",goal);
    printf("\n\n\t\tEnter The Amount: ");
    scanf("%f",&amount);
    FILE *file = fopen("goal.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s %.2f\n", goal, amount);
    fclose(file);
}

void read_goal()
{
    char goal[20];
    float amount;
    FILE *file = fopen("goal.txt", "r");
    if (file == NULL)
    {
        printf("Error reading goal data.\n");
        return;
    }
    if (fscanf(file, "%s %f", goal, &amount) != 2)
    {
        printf("\n\n\t\tNo Goal Data Found.\n");
        fclose(file);
        return;
    }
    fclose(file);
    printf("\n\t\tYour Goal is: %s\n\t\tAnd Required Amount is: %.2f", goal, amount);
    printf("\n");
}


void searchIncome()
{
    printf("\n\n\t\t1. Search By Date\n");
    printf("\n\t\t2. Search By Category\n");
    printf("\n\t\tChoose Your Option: ");
    int x;
    scanf("%d",&x);
    if(x==1)
    {
        printf("\n\n\t\tEnter Your Searching Date: ");
        char d[20];
        scanf("%s",d);
        system("cls");
        income *current = income_head;
        while (current!= NULL)
        {
            if (strcmp(d, current->date) == 0)
            {
                printf("\n\n\t\tYour Searching Date Details: ");
                printf("\n\n\t\tDate: %s",current->date);
                printf("\n\t\tCategory: %s",current->category);
                printf("\n\t\tIncome Amount: %.2f",current->amount);
                break;
            }
            current = current->next;
        }
    }
    else
    {
        printf("\n\n\t\tEnter Your Category: ");
        char c[20];
        scanf("%s",c);
        system("cls");
        income *current = income_head;
        printf("\n\n\t\tYour Searching Category Details: ");
        while (current!= NULL)
        {
            if (strcmp(c, current->category) == 0)
            {
                printf("\n\n\t\tDate: %s",current->date);
                printf("\n\t\tCategory: %s",current->category);
                printf("\n\t\tIncome Amount: %.2f",current->amount);
            }
            current = current->next;
        }
    }
    printf("\n\n\t\tFor Searching Again From Income List Enter 1 or Enter 2 To Return Main Menu:  ");
    int y;
    scanf("%d",&y);
    if(y==1) searchIncome();
    else return;
}

void searchExpenses()
{
    printf("\n\n\t\t1. Search By Date\n");
    printf("\n\t\t2. Search By Category\n");
    printf("\n\t\tChoose Your Option: ");
    int x;
    scanf("%d",&x);
    if(x==1)
    {
        printf("\n\n\t\tEnter Your Searching Date: ");
        char d[20];
        scanf("%s",d);
        system("cls");
        expenses *current = expenses_head;
        while (current!= NULL)
        {
            if (strcmp(d, current->date) == 0)
            {
                printf("\n\n\t\tYour Searching Date Details: ");
                printf("\n\n\t\tDate: %s",current->date);
                printf("\n\t\tCategory: %s",current->category);
                printf("\n\t\tExpenses Amount: %.2f",current->amount);
                break;
            }
            current = current->next;
        }
    }
    else
    {
        printf("\n\n\t\tEnter Your Category: ");
        char c[20];
        scanf("%s",c);
        system("cls");
        expenses *current = expenses_head;
        printf("\n\n\t\tYour Searching Category Details: ");
        while (current!= NULL)
        {
            if (strcmp(c, current->category) == 0)
            {
                printf("\n\n\t\tDate: %s",current->date);
                printf("\n\t\tCategory: %s",current->category);
                printf("\n\t\tExpenses Amount: %.2f",current->amount);
            }
            current = current->next;
        }
    }
    printf("\n\n\t\tFor Searching Again From Expenses List Enter 1 or Enter 2 To Return Main Menu:  ");
    int y;
    scanf("%d",&y);
    if(y==1) searchExpenses();
    else return;
}
void delete_entry()
{
    int c;
    printf("\n\t\t1. Delete From Income\n");
    printf("\t\t2. Delete From Expenses\n");
    printf("\t\tEnter Your Choice: ");
    scanf("%d",&c);
    if(c==1) delete_from_income();
    else delete_from_expenses();
}
void delete_from_income()
{
    char d[20];
    char c[20];
    printf("\n\t\tEnter the Date of the income to be deleted: ");
    scanf("%s", d);
    printf("\t\tEnter the Category of the income to be deleted: ");
    scanf("%s", c);
    FILE *file = fopen("income_data.txt", "w");
    if (file == NULL)
    {
        perror("File opening failed");
        exit(1);
    }

    income *current = income_head;
    while (current != NULL)
    {
        if (!(strcmp(d, current->date) == 0 && strcmp(c, current->category) == 0))
            fprintf(file, "%s %s %.2f\n", current->date, current->category, current->amount);
        current = current->next;
    }

    fclose(file);
    printf("\n\t\tIncome entry deleted successfully.\n\n\t\tPress any key to return to main menu...");
    getchar();
    getchar();
}
void delete_from_expenses()
{
    char d[20];
    char c[20];
    printf("\n\t\tEnter the Date of the expense to be deleted: ");
    scanf("%s", d);
    printf("\t\tEnter the Category of the expense to be deleted: ");
    scanf("%s", c);
    FILE *file = fopen("expenses_data.txt", "w");
    if (file == NULL)
    {
        perror("File opening failed");
        exit(1);
    }

    expenses *current = expenses_head;
    while (current != NULL)
    {
        if (!(strcmp(d, current->date) == 0 && strcmp(c, current->category) == 0))
            fprintf(file, "%s %s %.2f\n", current->date, current->category, current->amount);
        current = current->next;
    }

    fclose(file);
    printf("\n\t\tExpense entry deleted successfully.\n\n\t\tPress any key to return to main menu...");
    getchar();
    getchar();
}
void forsleep()
{
    for (int i = 0; i <300000000; i++)
    {

    }
}
void exit_function()
{
    printf("\n\n\n\n\n\n\t\t\tMoneyManager Made By @Team ByteBuilders\n\n\t\t\tExiting");
    for(int i=0; i<5; i++)
    {
        printf(".");
        forsleep();
    }
    printf("\n\n\n\n");
}


