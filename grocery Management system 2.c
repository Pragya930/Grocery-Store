#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct grocery{
    int id;
    char groceryName[50];
    char categoryName[50];
    char date[12];
}b;

struct customer{
    int id;
    char sName[50];
    char saddress[50];
    int sID;
    char groceryName[50];
    char date[12];
}s;

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
        printf("<== Grocery Management System ==>\n");
        printf("1.Add Grocery\n");
        printf("2.Grocery List\n");
        printf("3.Remove Grocery\n");
        printf("4.Issue Grocery\n");
        printf("5.Issued Grocery List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            addgrocery();
            break;

        case 2:
            groceryList();
            break;

        case 3:
            del();
            break;

        case 4:
            issuegrocery();
            break;

        case 5:
            issueList();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}


void addgrocery(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("grocery.txt", "ab");

    printf("Enter Grocery id: ");
    scanf("%d", &b.id);

    printf("Enter Grocery name: ");
    fflush(stdin);
    gets(b.groceryName);

    printf("Enter Category name: ");
    fflush(stdin);
    gets(b.categoryName);

    printf("Grocery Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}


void groceryList(){

    system("cls");
    printf("<== Available Grocery ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Grocery id", "Grocery Name", "Category", "Date");

    fp = fopen("grocery.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.groceryName, b.categoryName, b.date);
    }

    fclose(fp);
}

void del(){
    int id, f=0;
    system("cls");
    printf("<== Remove Grocery ==>\n\n");
    printf("Enter Grocery id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("Grocery.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f=1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nDeleted Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("Grocery.txt");
    rename("temp.txt", "Grocery.txt");

}


void issuegrocery(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("<== Issue Grocery ==>\n\n");

    printf("Enter Grocery id to issue: ");
    scanf("%d", &s.id);

    //Check if we have grocery of given id
    fp = fopen("Grocery.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.groceryName, b.groceryName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("No Grocery found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Customer Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Customer Address: ");
    fflush(stdin);
    gets(s.saddress);

    printf("Enter Customer ID: ");
    scanf("%d", &s.sID);

    printf("Grocery Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList(){
    system("cls");
    printf("<== Grocery Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Address", "ID", "Grocery Name", "Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.saddress, s.sID, s.groceryName, s.date);
    }

    fclose(fp);
}




