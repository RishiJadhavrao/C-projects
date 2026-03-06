#include <stdio.h> // Includes standard input/output functions
#include "file.h"  // Includes your custom header (make sure it doesn't conflict with std headers)

// Function to save all contacts to a file
void saveContactsToFile(struct AddressBook *addressBook)
{
    FILE *fp;
    fp = fopen("Savedcontact.csv", "w+"); // Open the file for reading and writing, overwrite if it exists

    int size = addressBook->contactCount; // Get the total number of contacts
    fprintf(fp, "%d\n", size);            // Write the number of contacts at the top of the file

    // Loop through each contact and write it to the file
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); // Save name, phone, and email separated by commas
    }

    fclose(fp); // Close the file after writing
}

// Function to load contacts from a file
void loadContactsFromFile(struct AddressBook *addressBook)
{
    FILE *fp = fopen("Savedcontact.csv", "r+"); // Open the file for reading and writing

    fscanf(fp, "%d", &addressBook->contactCount); // Read the number of contacts from the top of the file

    int size = addressBook->contactCount;

    // Loop to read each contact's details
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, " %[^,],%[^,],%[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); // Read name, phone, email separated by commas
    }

    fclose(fp); // Close the file after reading
}
