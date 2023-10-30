#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct todolist {
    char title[400];
    char description[500];
    char type[30];
    struct date_of_deadline {
        int date, year;
        char month[3];
    } dd;
    struct todolist *next;
};
typedef struct todolist task;
task *start = NULL;
task *del = NULL;

void replacechar(char *s, char c1, char c2) {
    int i;
    for (i = 0; s[i]; i++) {
        if (s[i] == c1) {
            s[i] = c2;
        }
    }
}

task *getnode() {
    task *new1;
    new1 = malloc(sizeof(task));
    printf("\nEnter title of the task (use underscores for spaces): \n");
    scanf("%s", new1->title);
    printf("Enter description of the task (use underscores for spaces):\n");
    scanf("%s", new1->description);
    replacechar(new1->title, '_', ' ');
    replacechar(new1->description, '_', ' ');
    printf("Enter the type of the task (Personal-PER\\Work-WOR\\Educational-EDU)\n");
    scanf("%s", new1->type);
    printf("Enter deadline month (eg:Jan):\n");
    scanf("%s", new1->dd.month);
    printf("Enter deadline date:\n");
    scanf("%d", &new1->dd.date);
    printf("Enter deadline year:\n");
    scanf("%d", &new1->dd.year);
    new1->next = NULL;
    return (new1);
}

void add_task(task *new1,int pos)
{
    if (pos < 0) {
        return;
    }
    if (pos == 0) {          //add task in the beginning
        new1->next = start;
        start = new1;
        return;
    }
    task *prev = NULL;        //add task at the required position
    task *curr = start;
    int i = 0;
    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (i == pos) {
        prev->next = new1;
        new1->next = curr;
    }
    task *temp = start;            //add task at the end
    if (start == NULL) {
        start = new1;
        return;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new1;
    }
}

void delete_task() {
    int pos, i;
    task *temp = start, *prev = NULL;
    if (start == NULL) {
        printf("\nNo Tasks Ongoing.\n");
        return;
    }
    printf("\nEnter the index of the task to be deleted: ");
    scanf("%d", &pos);
    task *new1 = malloc(sizeof(task));
    new1->next = NULL;
    if (pos == 1) {
        printf("Deleted title is %s\n", start->title);
        start = start->next;
        if (del == NULL) {
            del = new1;
        } else {
            task *t = del;
            while (t->next != NULL)
                t = t->next;
            t->next = new1;
        }
        strcpy(new1->title, temp->title);
        free(temp);
        return;
    }
    for (i = 1; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid index!\n");
        return;
    }
    printf("\nDeleted title is %s\n", temp->title);
    prev->next = temp->next;
    if (del == NULL) {
        del = new1;
    } else {
        task *t = del;
        while (t->next != NULL)
            t = t->next;
        t->next = new1;
    }
    strcpy(new1->title, temp->title);
    free(temp);
}

void edit_task() {
    int pos, i, choice;
    task *temp = start;
    if (start == NULL) {
        printf("\nNo Tasks Ongoing.\n");
        return;
    }
    printf("\nEnter the position of the task to be edited: ");
    scanf("%d", &pos);
    for (i = 1; temp != NULL && i < pos; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("\nInvalid position\n");
        return;
    }
    printf("\nChoose what to edit:\n");
    printf("1. Title\n");
    printf("2. Description\n");
    printf("3. Deadline\n");
    printf("4. Type of task\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("\nEnter new title: ");
            scanf("%s", temp->title);
            break;
        case 2:
            printf("\nEnter new description: ");
            scanf("%s", temp->description);
            break;
        case 3:
            printf("\nEnter new deadline month (eg:Jan):\n");
            scanf("%s", temp->dd.month);
            printf("Enter new deadline date:\n");
            scanf("%d", &temp->dd.date);
            printf("Enter new deadline year:\n");
            scanf("%d", &temp->dd.year);
            break;
        case 4:
            printf("Enter the correct type of the task (Personal-PER\\Work-WOR\\Educational-EDU)\n");
            scanf("%s", temp->type);
        default:
            printf("\nInvalid choice.\n");
    }
}

void sort_tasks() {
    if (start == NULL) {
        printf("\nNo Tasks Ongoing.\n");
        return;
    }
    int swapped;
    task *ptr1;
    task *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            // Compare the deadline of the current task and the next task
            int cmp = strcmp(ptr1->dd.month, ptr1->next->dd.month);
            if (ptr1->dd.year > ptr1->next->dd.year || (ptr1->dd.year == ptr1->next->dd.year && cmp > 0) || (ptr1->dd.year == ptr1->next->dd.year && cmp == 0 && ptr1->dd.date > ptr1->next->dd.date)) {
                // Swap the tasks if the next task's deadline is earlier
                task *temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;
                if (ptr1 == start) {
                    start = temp;
                } else {
                    task *prev = start;
                    while (prev->next != ptr1) {
                        prev = prev->next;
                    }
                    prev->next = temp;
                }
                ptr1 = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("\nTasks sorted by deadline.\n");
}


void display() {
    int choice;
    task *temp = start;
    if (start == NULL) {
        int i = 1;
        if (del == NULL) {
            printf("\nNo Tasks Ongoing.\n");
        } else {
            printf("\nCompleted Tasks: (Once view only)\n");
            task *t;
            while (del != NULL) {
                t = del;
                printf("%d. ", i);
                printf("Title: %s\n", del->title);
                free(t);
                del = del->next;
                i++;
            }
        }
        return;
    }
    int x;
    printf("Enter the type of task you want to view: \n1. Personal\n2. Work\n3. Educational\n\nEnter your choice: ");
    scanf("%d", &x);
    char *c;
    printf("\nTask List:\n");
    int i = 1;
    int q = 0;
    if (x == 1) {
        printf("----- PERSONAL TASKS -----\n");
        c = "PER";
    } else if (x == 2) {
        printf("----- WORK TASKS -----\n");
        c = "WOR";
    } else if (x == 3) {
        printf("----- EDUCATIONAL TASKS -----\n");
        c = "EDU";
    }
    while (temp != NULL) {
        if (strcmpi(temp->type, c) == 0) {
            printf("\n%d. ", i);
            printf("Title: %s\n", temp->title);
            printf("Deadline: %s %d %d\n\n", temp->dd.month, temp->dd.date, temp->dd.year);
            q++;
        }
        temp = temp->next;
        i++;
    }
    if (q == 0) {
        printf("NO such categorized tasks ongoing\n");
        return;
    }
    printf("\nEnter the corresponding index of the task to display its description: (enter 0 to skip): \n");
    scanf("%d", &choice);
    if (choice > 0) {
        temp = start;
        i = 1;
        while (temp != NULL) {
            if (i == choice) {
                printf("Description of task %d: %s\n", i, temp->description);
                break;
            }
            temp = temp->next;
            i++;
        }
        if (temp == NULL) {
            printf("Invalid choice.\n");
        }
    }
    printf("\nEnter 1 to view completed tasks or 0 to skip this: (These tasks are viewed once only and are deleted)"
           "\n*Note: These files are not stored to the drive!\n\n");
    int ch;
    scanf("%d", &ch);
    i = 1;
    if (ch == 1) {
        if (del == NULL) {
            printf("\nNo completed Tasks!\n");
        } else {
            printf("\nCompleted Tasks: \n");

            task *prev = NULL;
            while (del != NULL) {
                prev = del;
                printf("\n%d. ", i);
                printf("Title: %s\n", del->title);
                del = del->next;
                free(prev);
                i++;
            }
        }
    }
}

void storeList() { //Used to Store the Ongoing Task List at the End Of the Program
    FILE *fp = fopen("todo_list_tasks.bin", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    task *temp = start;
    while (temp != NULL) {
        fwrite(temp, sizeof(task), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

void loadList() {
    task *new1 = malloc(sizeof(task));
    FILE *fp = fopen("todo_list_tasks.bin", "rb");
    if (fp == NULL) {
        printf("\nNote: Empty Data file, the program is being run for the 1st time!!\n");
    } else {
        while (fread(new1, sizeof(task), 1, fp)) {
            new1->next = NULL; //Solve Linking issue
            if (start == NULL) {
                start = new1;
            } else {
                task *temp = start;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new1;
            } //insert function copy
            new1 = malloc(sizeof(task)); //to create another new node
        }
    }
}


int main() {
    //For loading the list from file at the start of the program
    loadList();
    int ch,pos;
    for (;;) {
        printf("\n====================================== TODO LIST PROGRAM ======================================\n");
        printf("\n1.Add a new Task\n2.Delete Current tasks\n3.Edit Current Tasks\n4.Display all the tasks (Completed\\Ongoing)\n5.Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("\n==============================\n");
                task *new1 = getnode();
                add_task(new1,pos);
                break;
            case 2:
                printf("\n==============================\n");
                delete_task();
                break;
            case 3:
                printf("\n==============================\n");
                edit_task();
                break;
            case 4:
                printf("\n===============================\n");
                sort_tasks();
                break;

            case 5:
                printf("\n==============================\n");
                display();
                break;
            case 6:
                printf("\n==============================\n");
                printf("\nProgram exited! Thank you! We are saving your data to the drive! Have a great Day!!\n");
                storeList();
                exit(0);
            default:
                printf("\n==============================\n");
                printf("Invalid choice...Try again");
        }
    }
}
