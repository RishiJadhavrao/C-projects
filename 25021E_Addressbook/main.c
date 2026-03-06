/*
Project Name - Address Book
Name - Rishikesh jadhavrao
Date - 6/1/2026
Batch Id - 25028_033
Language - C language

Description - In this project we have created contact book.
A basic and easy-to-use contact management app in C. You can add, view, search, edit, and delete contacts - all from a simple menu

1.Key Features:

Add Contact – Enter name, phone, and email. Duplicate phones/emails not allowed.
Search – Look up contacts by name, phone, or email.
Edit – Change a contact’s details.
Delete – Remove a contact from your list.
Show All – View all saved contacts in a table.
Save to File – Store your contacts for later use.
Exit – Close the app safely.

2.How to Use:

Run the program.
Choose options from the menu.
Your contacts are saved to a file, so you won’t lose them.

3.Code Structure:

main.c – Main menu and program loop.
contact.c/h – Core contact functions (add, edit, delete,search).
file.c/h – Saving and loading contacts.

*/










#include "contact.h"  // Include the header file where all contact-related functions are declared

int main()
{
	int choice;  // Variable to store user menu choice

	struct AddressBook addressBook;  
	initialize(&addressBook);  // Initialize the address book (e.g., set contactCount to 0, load from file, etc.)

	do
	{
		// Display the main menu options
		printf("\nAddress Book Menu:\n");
		printf("1. Create contact\n");
		printf("2. Search contact\n");
		printf("3. Edit contact\n");
		printf("4. Delete contact\n");
		printf("5. List all contacts\n");
		printf("6. Save & Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);  // Read user input
		printf("\n");

		// Perform action based on user's choice
		switch (choice)
		{
		case 1:
			createContact(&addressBook);  // Add a new contact
			break;
		case 2:
			searchContact(&addressBook);  // Search for an existing contact
			break;
		case 3:
			editContact(&addressBook);  // Modify a contact's details
			break;
		case 4:
			deleteContact(&addressBook);  // Remove a contact
			break;
		case 5:
			listContacts(&addressBook);  // Show all saved contacts
			break;
		case 6:
			printf("Saving and Exiting...\n");
			saveContactsToFile(&addressBook);  // Save all contacts to file before exiting
			break;
		default:
			printf("Invalid choice. Please try again.\n");  // Handle invalid menu input
		}
	} while (choice != 6);  // Repeat until user chooses to exit

	return 0;  // Exit the program
}
