#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to display all saved contacts in a formatted table
void listContacts(struct AddressBook *addressBook)
{
    printf("\n+-----------------------------------------------------------------------------+\n");
    printf(" %-7s %-20s %-20s %-50s\n", "Sr.no", "Name", "Phone Number", "Email ID");
    printf("+-----------------------------------------------------------------------------+\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Print each contact with serial number, name, phone, and email
        printf("  %-6.2d %-20s %-20s %-50s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("+-----------------------------------------------------------------------------+\n");
}

// Initialize the address book with 0 contacts and load saved contacts from file
void initialize(struct AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook); // Optional: for preloading data
    loadContactsFromFile(addressBook); // Load data from file into address book
}

// Save contacts to file and exit the program
void saveAndExit(struct AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

// Create a new contact (with name, phone, and email)
void createContact(struct AddressBook *addressBook)
{
    int i = addressBook->contactCount; // index for new contact
    int res = 0, check = 0, keep = 0, check1 = 0;

    // Get name from user
    printf("Enter The Name: ");
    scanf(" %[^\n]", addressBook->contacts[i].name);

    // Get and validate phone number
    do
    {
        getchar();
        char demo[20];
        printf("Enter The Mobile Num: ");
        scanf("%s", demo);
        int len = strlen(demo);
        res = check_num(demo, &len); // check if phone number is valid
        check = check_phone_duplicate(addressBook, demo); // check for duplicates
        if (res == 0)
        {
            printf("Invalid Input,Do Try Again\n");
        }
        else
        {
            if (check == 1)
                strcpy(addressBook->contacts[i].phone, demo); // save if valid and not duplicate
            else
                res = 0;
        }
    } while (res != 1);

    // Get and validate email
    do
    {
        getchar();
        char demo1[50];
        printf("Enter The Email: ");
        scanf("%[^\n]", demo1);

        keep = check_email(demo1); // validate email format
        check1 = check_email_duplicates(addressBook, demo1); // check for duplicate email
        if (keep == 1)
        {
            printf("Invalid Input,Do Try Again\n");
        }
        else
        {
            if (check1 == 1)
            {
                strcpy(addressBook->contacts[i].email, demo1); // save if valid and unique
                printf("Contact created successfully!!\n");
                addressBook->contactCount++; // increase total contacts
            }
            else
                keep = 0;
        }

    } while (keep != 0);
}
 
// Search contact by name, phone or email
void searchContact(struct AddressBook *addressBook)
{
    int a;
    char npm[50];

    printf("1.Search By Name\n2.Search By Mobile Number\n3.Search By Mail\n4.Exit\n");
    printf("\nEnter the option: ");
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        printf("Enter The Name: ");
        scanf(" %[^\n]", npm);
        search_name(addressBook, npm); // call function to search by name
        break;
    case 2:
        printf("Enter The Mobile Number: ");
        scanf(" %[^\n]", npm);
        search_phone_number(addressBook, npm); // search by number
        break;
    case 3:
        printf("Enter The Mail: ");
        scanf(" %[^\n]", npm);
        search_mail(addressBook, npm); // search by email
        break;
    default:
        break;
    }
}

// Edit contact details (name, phone, or email)
void editContact(struct AddressBook *addressBook)
{
    searchContact(addressBook); // display matching contact first
    int i = addressBook->contactCount;
    char nnpm[50]; // new value
    char onpm[50]; // old value
    int b, res = 0, ores = 0, oeres = 0, eres = 0, echeck = 0, check = 0, keep = 0, check1 = 0;

    do
    {
        printf("\nWhat Do Want To Edit?");
        printf("\n1.Name\n2.Mobile Phone\n3.Email\n4.Exit\n");
        printf("\nChoose the Option: ");
        scanf("%d", &b);

        switch (b)
        {
        // Edit name
        case 1:
            printf("Enter The old Name: ");
            scanf(" %[^\n]", onpm);

            printf("Enter The New Name: ");
            scanf(" %[^\n]", nnpm);

            edit_name(addressBook, nnpm, onpm);
            break;

        // Edit phone number
        case 2:
            do
            {
                printf("Enter The Present Mobile Number: ");
                scanf(" %[^\n]", onpm);
                int size = strlen(onpm);
                ores = check_num(onpm, &size);
                if (ores == 0)
                    printf("Invalid Input,Do Try Again\n");
            } while (ores != 1);

            do
            {
                printf("Enter The New Mobile Number: ");
                scanf(" %[^\n]", nnpm);

                int len = strlen(nnpm);
                res = check_num(nnpm, &len);
                check = check_phone_duplicate(addressBook, nnpm);
                if (res == 0)
                    printf("Invalid Input,Do Try Again\n");
                else if (check == 0)
                    res = 0;
            } while (res != 1);

            if (res == 1)
                edit_phone_number(addressBook, nnpm, onpm);

            break;

        // Edit email
        case 3:
            do
            {
                printf("Enter The Current Email ID: ");
                scanf(" %[^\n]", onpm);
                oeres = check_email(onpm);
                if (oeres == 1)
                    printf("Invalid Input,Do Try Again\n");
            } while (oeres != 0);

            do
            {
                printf("Enter The New Email ID: ");
                scanf(" %[^\n]", nnpm);
                eres = check_email(nnpm);
                echeck = check_email_duplicates(addressBook, nnpm);
                if (eres == 1)
                    printf("Invalid Input,Do Try Again\n");
                else if (echeck == 0)
                    eres = 1;
            } while (eres != 0);

            if (eres == 0)
                edit_mail(addressBook, nnpm, onpm);
            break;
        }
    } while (b != 4); // loop until user chooses exit
}

// Delete a contact based on serial number (shown after search)
void deleteContact(struct AddressBook *addressBook)
{
    searchContact(addressBook);
    int roll;
    printf("\nEnter Sr.no: ");
    scanf("%d", &roll);
    delete_by_index(addressBook, &roll);
}

// Validate email format (basic check for name@domain.com)
int check_email(char *demo)
{
    int flag = 0, i = 0, at = 0, dot = 0;

    while (demo[i] != '\0')
    {
        if (demo[i] == '@')
            at = i;
        else if (demo[i] == '.')
            dot = i;
        i++;
    }

    for (int j = 0; j < i - 1; j++)
    {
        // Check valid characters before @
        if (j < at)
        {
            if (!((demo[j] >= 'a' && demo[j] <= 'z') || (demo[j] >= '0' && demo[j] <= '9')))
                return 1;
        }
        if (at == 0)
            return 1;
        if (j > at && j < dot)
        {
            if (!((demo[j] >= 'a' && demo[j] <= 'z') || (demo[j] >= '0' && demo[j] <= '9')))
                return 1;
        }
        if ((dot - at) == 1)
            return 1;
        else if (j > dot)
        {
            // Ensure ending is ".com"
            char ch[5] = {'c', 'o', 'm'};
            int f = 0;
            for (int k = j; k < i; k++)
            {
                if (!(demo[k] == ch[f]))
                    return 1;
                f++;
            }
            return flag;
        }
    }
    return flag = 1;
}

// Check if email is already used
int check_email_duplicates(struct AddressBook *addressBook, char *demo1)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, demo1) == 0)
        {
            printf("Duplicate found\n");
            return 0;
        }
    }
    return 1;
}

// Validate phone number: must be 10 digits and all numbers
int check_num(char *demo, int *len)
{
    int j = 0;
    while (demo[j] != '\0')
    {
        if (((demo[j] >= '0' && demo[j] <= '9') && *len == 10))
            return 1;
        j++;
    }
    return 0;
}

// Check if phone number already exists in contact list
int check_phone_duplicate(struct AddressBook *addressBook, char *demo)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, demo) == 0)
        {
            printf("Duplicate found\n");
            return 0;
        }
    }
    return 1;
}
//-----------------------------------------------------Searching Contact--------------------------------------------------------------------
// Search contact by name (partial or full match)
int search_name(struct AddressBook *addressBook, char *npm)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((strcmp(addressBook->contacts[i].name, npm) == 0) || (strstr(addressBook->contacts[i].name, npm)) != NULL)
        {
            printf("%d  ", i + 1);
            printf("%s  ", addressBook->contacts[i].name);
            printf("%s  ", addressBook->contacts[i].phone);
            printf("%s  \n", addressBook->contacts[i].email);
            flag = 1;
        }
    }
    if (flag == 0)
        printf("Contact Not Found!!\n");
}

// Search by phone number
int search_phone_number(struct AddressBook *addressBook, char *npm)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, npm) == 0)
        {
            printf("%d  ", i + 1);
            printf("%s ", addressBook->contacts[i].name);
            printf("%s ", addressBook->contacts[i].phone);
            printf("%s ", addressBook->contacts[i].email);
            printf("\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Contact Not Found!!\n");
}

// Search by email address
int search_mail(struct AddressBook *addressBook, char *npm)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, npm) == 0)
        {
            printf("%d  ", i + 1);
            printf("%s  ", addressBook->contacts[i].name);
            printf("%s  ", addressBook->contacts[i].phone);
            printf("%s  ", addressBook->contacts[i].email);
            printf("\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Contact Not Found!!\n");
}
//------------------------------------------------------ Editing Contact---------------------------------------------------------------------
// Edit name based on old name; if multiple matches, user chooses
int edit_name(struct AddressBook *addressBook, char *nnpm, char *onpm)
{
    int k = 0, flag = 0, p = 0;
    int arr[100];
    printf("\n+-----------------------------------------------------------------------------+\n");
    printf(" %-7s %-20s %-20s %-50s\n", "Sr.no", "Name", "Phone Number", "Email ID");
    printf("+-----------------------------------------------------------------------------+\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((strcmp(addressBook->contacts[i].name, onpm) == 0))
        {
            arr[k] = i;
            k++;
            printf("  %-6.2d %-20s %-20s %-50s\n", k, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    printf("+-----------------------------------------------------------------------------+\n");

    // If multiple matches, ask which one to update
    if (k >= 2 && k < k + 1)
    {
        printf("\nWhich Person's Name You Want To Change:");
        scanf("%d", &p);
        p = p - 1;
        strcpy(addressBook->contacts[arr[p]].name, nnpm);
        printf("Successfully Updated!!\n");
        flag = 1;
    }
    else
    {
        p = 0;
        strcpy(addressBook->contacts[arr[p]].name, nnpm);
        printf("Successfully Updated!!\n");
        flag = 1;
    }

    if (flag != 1)
        printf("Not Updated");
}

// Edit phone number using old number
int edit_phone_number(struct AddressBook *addressBook, char *nnpm, char *onpm)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, onpm) == 0)
        {
            strcpy(addressBook->contacts[i].phone, nnpm);
            printf("Mobile Number Successfully Edited!!");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Contact Not Found!!\n");
}

// Edit email using old email
int edit_mail(struct AddressBook *addressBook, char *nnpm, char *onpm)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, onpm) == 0)
        {
            strcpy(addressBook->contacts[i].email, nnpm);
            printf("Email Successfully Edited!!");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Contact Not Found!!\n");
}
//-------------------------------------------------------------------- Deleting contact -----------------------------------------------------
// Delete a contact by serial number
int delete_by_index(struct AddressBook *addressBook, int* roll)
{
    int flag = 0;
    printf("%d  ", *roll);
    printf("%s  ", addressBook->contacts[*roll - 1].name);
    printf("%s  ", addressBook->contacts[*roll - 1].phone);
    printf("%s  \n", addressBook->contacts[*roll - 1].email);

    
    for (int i = *roll; i < addressBook->contactCount; i++)
    {
        strcpy(addressBook->contacts[i - 1].name, addressBook->contacts[i].name);
        strcpy(addressBook->contacts[i - 1].phone, addressBook->contacts[i].phone);
        strcpy(addressBook->contacts[i - 1].email, addressBook->contacts[i].email);
        flag = 1;
    }
    addressBook->contactCount--; // Decrease count after deletion

    if (flag == 0)
    {
        printf("\nContact Deleted Successfully\n");
        listContacts(addressBook);
    }
    else
    {
        printf("Something Went Wrong, Do Try Again\n");
    }
}
