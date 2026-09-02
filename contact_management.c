#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "contacts.txt"
#define MAX_CONTACTS 1000

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Clears leftover characters (e.g. '\n') left in stdin after scanf.
void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

// Strips a trailing \r or \n from a string in place.
void removeNewline(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

// Reads a line of input into str, supports spaces, and never overflows size.
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
        // Input was longer than the buffer; drop the rest of the line.
        clearInputBuffer();
    }
}

// Copies src into a fixed-size field, truncating instead of overflowing.
void copyBounded(char *dest, const char *src, size_t destSize)
{
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}

// Loads contacts from FILE_NAME into memory. Returns the count loaded,
// or 0 if the file doesn't exist yet.
int loadContacts(Contact contacts[])
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    char line[100];

    while (count < MAX_CONTACTS && fgets(line, sizeof(line), file) != NULL)
    {
        removeNewline(line);
        if (strlen(line) == 0)
        {
            continue;
        }

        copyBounded(contacts[count].name, line, sizeof(contacts[count].name));

        if (fgets(contacts[count].phone, sizeof(contacts[count].phone), file) == NULL)
            break;
        removeNewline(contacts[count].phone);

        if (fgets(contacts[count].email, sizeof(contacts[count].email), file) == NULL)
            break;
        removeNewline(contacts[count].email);

        count++;
    }
    fclose(file);
    return count;
}

// Writes all in-memory contacts back to FILE_NAME, overwriting it.
void saveContacts(Contact contacts[], int count)
{
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Error: could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n%s\n%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(file);
}

void addContact(Contact contacts[], int *count)
{
    if (*count >= MAX_CONTACTS)
    {
        printf("Contact limit reached.\n");
        return;
    }

    Contact newContact;
    printf("\nEnter Name: ");
    readLine(newContact.name, sizeof(newContact.name));
    printf("Enter Phone: ");
    readLine(newContact.phone, sizeof(newContact.phone));
    printf("Enter Email: ");
    readLine(newContact.email, sizeof(newContact.email));

    if (strlen(newContact.name) == 0 || strlen(newContact.phone) == 0 || strlen(newContact.email) == 0)
    {
        printf("Warning: all fields are required. Contact was not saved.\n");
        return;
    }

    contacts[*count] = newContact;
    (*count)++;

    saveContacts(contacts, *count);
    printf("Contact added successfully.\n");
}

void deleteContact(Contact contacts[], int *count)
{
    if (*count == 0)
    {
        printf("No contacts to delete.\n");
        return;
    }

    printf("\nEnter exact name to delete: ");
    char deleteName[50];
    readLine(deleteName, sizeof(deleteName));

    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(contacts[i].name, deleteName) == 0)
        {
            for (int j = i; j < *count - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            (*count)--;
            saveContacts(contacts, *count);
            printf("Contact deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }
}

void listContacts(const Contact contacts[], int count)
{
    printf("\n=======================================================\n");
    printf("||          CONTACT MANAGEMENT SYSTEM                ||\n");
    printf("=======================================================\n");

    if (count == 0)
    {
        printf("\nNo contacts saved yet.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nContact %d:\n", i + 1);
        printf("Name  : %s\n", contacts[i].name);
        printf("Phone : %s\n", contacts[i].phone);
        printf("Email : %s\n", contacts[i].email);
    }
    printf("\nTotal contacts: %d\n", count);
}

void searchContact(const Contact contacts[], int count)
{
    if (count == 0)
    {
        printf("No contacts to search.\n");
        return;
    }

    printf("\nEnter keyword to search (name, phone, or email): ");
    char keyword[50];
    readLine(keyword, sizeof(keyword));

    if (strlen(keyword) == 0)
    {
        printf("Search keyword cannot be empty.\n");
        return;
    }

    int found = 0;
    printf("\n--- Search Results ---\n");
    for (int i = 0; i < count; i++)
    {
        if (strstr(contacts[i].name, keyword) != NULL ||
            strstr(contacts[i].phone, keyword) != NULL ||
            strstr(contacts[i].email, keyword) != NULL)
        {
            printf("\nContact %d:\n", i + 1);
            printf("Name  : %s\n", contacts[i].name);
            printf("Phone : %s\n", contacts[i].phone);
            printf("Email : %s\n", contacts[i].email);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No contacts found matching '%s'.\n", keyword);
    }
    else
    {
        printf("\nTotal matches: %d\n", found);
    }
}

// Comparison function for qsort to sort contacts alphabetically by name (case-insensitive)
int compareByName(const void *a, const void *b)
{
    const Contact *contactA = (const Contact *)a;
    const Contact *contactB = (const Contact *)b;
    const char *strA = contactA->name;
    const char *strB = contactB->name;

    while (*strA && *strB)
    {
        int charA = tolower((unsigned char)*strA);
        int charB = tolower((unsigned char)*strB);
        if (charA != charB)
        {
            return charA - charB;
        }
        strA++;
        strB++;
    }
    return tolower((unsigned char)*strA) - tolower((unsigned char)*strB);
}

// Sorts contacts alphabetically by name and saves the new order to disk
void sortContacts(Contact contacts[], int count)
{
    if (count <= 1)
    {
        printf("\nNot enough contacts to sort.\n");
        return;
    }

    qsort(contacts, count, sizeof(Contact), compareByName);
    saveContacts(contacts, count);
    printf("\nContacts sorted alphabetically by name successfully.\n");
}

int main(void)
{
    Contact contacts[MAX_CONTACTS];
    int count = loadContacts(contacts);
    int choice;

    while (1)
    {
        printf("\n======================================\n");
        printf("||     CONTACT MANAGEMENT SYSTEM    ||\n");
        printf("======================================\n\n");
        printf("[1] Add Contact\n");
        printf("[2] Delete Contact\n");
        printf("[3] List Contacts\n");
        printf("[4] Search Contact\n");
        printf("[5] Sort Contacts (by Name)\n");
        printf("[6] Exit\n");
        printf("\nEnter your choice (1-6): ");

        int result = scanf("%d", &choice);
        if (result == EOF)
        {
            printf("\nInput closed. Exiting.\n");
            return 0;
        }
        if (result != 1)
        {
            printf("Invalid input. Enter a number between 1 and 6.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            addContact(contacts, &count);
            break;
        case 2:
            deleteContact(contacts, &count);
            break;
        case 3:
            listContacts(contacts, count);
            break;
        case 4:
            searchContact(contacts, count);
            break;
        case 5:
            sortContacts(contacts, count);
            break;
        case 6:
            saveContacts(contacts, count);
            printf("Exiting. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}
