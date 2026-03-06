#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[100];
    int contactCount;
};

void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *AddressBook);

void print(struct AddressBook *addressBook);



//Creatcontact:-
//For Mobile Number
int check_num(char* demo,int* len);
int check_phone_duplicate(struct AddressBook* addressbook,char* demo);

//For mail
int check_email(char *demo);
int check_email_duplicates(struct AddressBook *addressBook, char *demo1);

//Search_the_contact:-

int search_name(struct AddressBook *addressBook,char* npm);
int search_mail(struct AddressBook *addressBook,char* npm);
int search_phone_number(struct AddressBook *addressBook,char* npm);

//Edit_Contacts::-
int edit_name(struct AddressBook *addressBook,char* nnpm,char* onpm);
int edit_phone_number(struct AddressBook *addressBook,char* nnpm,char* onpm);
int edit_mail(struct AddressBook *addressBook,char* nnpm,char* onpm);

//Deleting_contact::-
int delete_by_index(struct AddressBook *addressBook,int* roll);

#endif
