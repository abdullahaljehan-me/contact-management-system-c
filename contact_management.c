#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.txt"

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // discard characters
    }
}

void removeNewline(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

void readLine(char *str, size_t size)
{
    if (fgets(str, (int)size, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }

    int end = (int)strcspn(str, "\r\n");

    if (str[end] != '\0')
    {
        str[end] = '\0';
    }
    else
    {
        clearInputBuffer();
    }
}

void addContact(void)
{
    struct Contact c;

    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL)
    {
        printf("Error: Could not open/create file.\n");
        return;
    }

    printf("\nEnter Name: ");
    readLine(c.name, sizeof(c.name));

    printf("Enter Phone: ");
    readLine(c.phone, sizeof(c.phone));

    printf("Enter Email: ");
    readLine(c.email, sizeof(c.email));

    if (strlen(c.name) == 0 || strlen(c.phone) == 0 || strlen(c.email) == 0)
    {
        printf("Warning: All fields are required. Contact was not saved.\n");
        fclose(file);
        return;
    }

    fprintf(file, "%s\n%s\n%s\n\n", c.name, c.phone, c.email);
    fclose(file);

    printf("Contact added to contact management system successfully!\n");
}

void displayContacts(void)
{
    struct Contact c;

    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL)
    {
        printf("No contacts found (File does not exist).\n");
        return;
    }

    printf("=======================================================\n");
    printf("||              CONTACT MANAGEMENT SYSTEM            ||\n");
    printf("=======================================================\n");
    printf("\n------ SAVED CONTACTS ------\n");

    int count = 0;

    while (fgets(c.name, sizeof(c.name), file) != NULL)
    {
        removeNewline(c.name);

        if (strlen(c.name) == 0)
        {
            continue;
        }

        if (fgets(c.phone, sizeof(c.phone), file) == NULL)
        {
            break;
        }
        removeNewline(c.phone);

        if (fgets(c.email, sizeof(c.email), file) == NULL)
        {
            break;
        }
        removeNewline(c.email);

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

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n======================================\n");
        printf("||     CONTACT MANAGEMENT SYSTEM    ||\n");
        printf("======================================\n");
        printf("[SYSTEM MENU]\n");
        printf("\t[1] ADD CONTACT\n");
        printf("\t[2] DISPLAY CONTACT\n");
        printf("\t[3] EXIT\n");
        printf("\nENTER YOUR CHOICE (1-3): ");

        int result = scanf("%d", &choice);

        if (result == EOF)
        {
            printf("\nInput closed. Exiting system.\n");
            return 0;
        }

        if (result != 1)
        {
            printf("Invalid input! Please enter a number between 1 and 3.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

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
            return 0;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
