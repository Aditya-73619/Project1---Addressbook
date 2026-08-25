#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int valid_name(char name[]);
int valid_phone(char phone[]);
int valid_email(char email[]);

void searchContact(AddressBook *addressBook);
void search_by_name(AddressBook *addressBook);
void search_by_phone(AddressBook *addressBook);
void search_by_email(AddressBook *addressBook);

void editContact(AddressBook *addressBook);

void deleteContact(AddressBook *addressBook);
void delete_by_name(AddressBook *addressBook);
void delete_by_phone(AddressBook *addressBook);
void delete_by_email(AddressBook *addressBook);
void del_contact(AddressBook *addressBook);

void listContacts(AddressBook *addressBook);
void sort_by_name(AddressBook *addressBook);
void sort_by_phone(AddressBook *addressBook);
void sort_by_email(AddressBook *addressBook);
void print_list(AddressBook *addressbook);
void swap(AddressBook *addressBook,int i,int j);

void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
