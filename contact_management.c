#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};
void addContact()
{
    struct Contact c;
    FILE *file = fopen("contacts.txt", "a");

    if (file == NULL)
    {
        printf("Error: Could not open/create file.\n");
        return;
    }

    printf("\nEnter Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    fprintf(file, "%s\n%s\n%s\n", c.name, c.phone, c.email);
    fprintf(file, "\n");
    fclose(file);

    printf("Contact added to contact management system successfully!\n");
}

void displayContacts()
{
    struct Contact c;
    FILE *file = fopen("contacts.txt", "r");

    if (file == NULL)
    {
        printf("No contacts found (File does not exist).\n");
        return;
    }

    printf("\n=======================================================\n");
    printf("||     CONTACT MANAGEMENT SYSTEM @abdullahaljehan    ||\n");
    printf("=======================================================\n\n");
    printf("\n           ------ SAVED CONTACTS ------               \n");

    int count = 0;

    while (fscanf(file, " %[^\n]\n %[^\n]\n %[^\n]\n", c.name, c.phone, c.email) != EOF)
    {
        count++;
        printf("\nContact %d:\n", count);
        printf("Name  : %s\n", c.name);
        printf("Phone : %s\n", c.phone);
        printf("Email : %s\n", c.email);
    }

    if (count == 0)
    {
        printf("No contact records present.\n");
    }

    fclose(file);
}
int main()
{
    int choice;

    while (1)
    {
        printf("\n======================================\n");
        printf("||     CONTACT MANAGEMENT SYSTEM    ||\n");
        printf("======================================\n\n");

        printf("[SYSTEM MENU]\n\n");
        printf("\t[1] ADD CONTACT\n");
        printf("\t[2] DISPLAY CONTACT\n");
        printf("\t[3] EXIT\n");

        printf("\nENTER YOUR CHOICE (1-3) : ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            displayContacts();
            break;
        case 3:
            printf("Exiting system. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    addContact();
    displayContacts();

    return 0;
}
