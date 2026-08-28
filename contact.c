#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

int index_arr[MAX_CONTACTS];
int arr_index = 0;


void listContacts(AddressBook *addressBook) 
{
    int choice;
    do{
        printf("\n1. Sort by Name\n");
        printf("2. Sort by Phone no.\n");
        printf("3. Sort by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice){
            case 1: sort_by_name(addressBook);
                    break;
            case 2: sort_by_phone(addressBook);
                    break;
            case 3: sort_by_email(addressBook);
                    break;
            case 4: printf("Exiting...");
                    break;
            default: printf("\nInvalid Choice, Please try again.\n");
        }
    }while(choice!=4);    
}


void sort_by_name(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if(strcasecmp(addressBook->contacts[i].name,addressBook->contacts[j].name) > 0){
                swap(addressBook,i,j);
            }
        }
    }

    print_list(addressBook);
}

void sort_by_phone(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if((strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone)) > 0){
                swap(addressBook,i,j);
            }
        }
    }

    print_list(addressBook);
}

void sort_by_email(AddressBook *addressBook){
    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=i+1;j<addressBook->contactCount;j++){
            if((strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email)) > 0){
                swap(addressBook,i,j);
            }
        }
    }

    print_list(addressBook);
}

void print_list(AddressBook *addressBook){      //Printing the list
    int a=1;
    printf("\nS.no\tName\t\tPhone\t\tEmail\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%d\t%s\t\t%s\t%s\n",a++,addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
    }
}

void swap(AddressBook *addressBook,int i,int j){
    Contact temp = addressBook->contacts[i];
    addressBook->contacts[i] = addressBook->contacts[j];
    addressBook->contacts[j] = temp;
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
        if(addressBook->contactCount < MAX_CONTACTS){
            int i = addressBook->contactCount;
        /*****************************    NAME   *************************************/
        printf("Enter the Name : ");        
        while(1){
            
            scanf(" %49[^\n]",addressBook->contacts[i].name);

            if(valid_name(addressBook->contacts[i].name))
                break;
            else
                printf("Re-Enter the name : ");
        }
        

        /*****************************    Phone   *************************************/
        printf("Enter the Phone no. : ");       
        while(1){
            
            scanf(" %19[^\n]",addressBook->contacts[i].phone);

            if(valid_phone(addressBook->contacts[i].phone,addressBook,-1))
                break;
            else
                printf("Re-Enter the Phone no. : ");
        }


        /*****************************    Email   *************************************/
        printf("Enter the email : ");
        while(1){ 
            
            scanf(" %49[^\n]",addressBook->contacts[i].email);
            

                if(valid_email(addressBook->contacts[i].email,addressBook,-1))
                    break;
                else
                    printf("Re-Enter the email : ");
        }
        addressBook->contactCount++;
    }
    else    
        printf("Contact list is Full.\n");
}

int valid_name(char name[]){

    for(int i=0;name[i]!=0;i++){
        if((!isalnum(name[i])) && (name[i] != ' ')){
            return 0;
        }
    }
    return 1;
}

int valid_phone(char phone[],AddressBook *addressBook, int ignore_index){
    int count = 0;
    count  = strlen(phone);

    if(phone[0]<'6' || phone[0]>'9' || count!=10)
        return 0;

    for(int i=0;phone[i]!=0;i++){
        if(!isdigit(phone[i])){
            return 0;
        }
    }

    //Validating Unique or not
    for(int i=0;i<addressBook->contactCount;i++){
        if(i != ignore_index &&
            (strcmp(phone,addressBook->contacts[i].phone)) == 0)
            return 0;
    }

    return 1;
}

int valid_email(char email[], AddressBook *addressBook, int ignore_index){
        
    for(int i=0;email[i]!=0;i++){  //No uppercase and space
        if((email[i] == ' ') || isupper(email[i])){
                return 0;
            }
    }

    int special_character_pos = 0;
    int special_character_count = 0;        //Must 1 @
    for(int i=0;email[i]!=0;i++){
        if(email[i] == '@'){
            special_character_count++;
            special_character_pos = i;
        }
    }

    if(special_character_count != 1){
        return 0;
    }
    

    // Last 4 characters .com , First not @
    int len = strlen(email);
    char com[] = {".com"};
    if(len<4 || ((strcmp(&email[len-4],com)) != 0) || (email[0] == '@'))
        return 0;

    //Atleast 1 character between @ and .
    if(email[special_character_pos + 1] == '.')
        return 0;

    //Validating Unique or not
    for(int i=0;i<addressBook->contactCount;i++){
        if(i != ignore_index &&
            (strcmp(email,addressBook->contacts[i].email)) == 0)
            return 0;
    }

    //1st character should be isalnum
    if(!isalnum(email[0]))
        return 0;
        
    return 1;
}


void searchContact(AddressBook *addressBook)
{
    int choice;
    do{
        printf("\n1. Search by Name\n");
        printf("2. Search by Phone no.\n");
        printf("3. Search by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice){
            case 1: search_by_name(addressBook);
                    break;
            case 2: search_by_phone(addressBook);
                    break;
            case 3: search_by_email(addressBook);
                    break;
            case 4: printf("Exiting...\n");
                    break;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }while(choice != 4);
}

int search_by_name(AddressBook *addressBook){
    char name[50];
    arr_index = 0;
    int flag = 0;
    int a=1;
    printf("Enter the name : ");
    scanf(" %49[^\n]",name);

            
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcasestr(addressBook->contacts[i].name,name) != NULL){

            if(!flag){
                printf("\nS.no\tName\t\tPhone\t\tEmail\n");
                flag = 1;
            }

            printf("%d\t%s\t\t%s\t%s\n",a++,addressBook->contacts[i].name,
                                    addressBook->contacts[i].phone,
                                    addressBook->contacts[i].email);
        
            index_arr[arr_index++] = i;
        }
    }
    if(!flag){
        printf("\nContact not found\n");
        return 0;
    }
        
    return 1;
}

int search_by_phone(AddressBook *addressBook){
    char phone[20];
    arr_index = 0;
    int flag = 0;
    int a=1;
    printf("Enter the Phone no. :");
    scanf(" %19[^\n]",phone);

    
    
    for(int i=0;i<addressBook->contactCount;i++){
        if(strstr(addressBook->contacts[i].phone,phone) != NULL){

            if(!flag){
                printf("\nS.no\tName\t\tPhone\t\tEmail\n");
                flag = 1;
            }

            printf("%d\t%s\t\t%s\t%s\n",a++,addressBook->contacts[i].name,
                                    addressBook->contacts[i].phone,
                                    addressBook->contacts[i].email);
            
            index_arr[arr_index++] = i;
        }
    }
    if(!flag){
        printf("\nContact not found\n");
        return 0;
    }
    return 1;
}

int search_by_email(AddressBook *addressBook){
    char email[50];
    arr_index = 0;
    int flag = 0;
    int a=1;
    printf("Enter the Email :");
    scanf(" %49[^\n]",email);


    
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcasestr(addressBook->contacts[i].email,email) != NULL){

            if(!flag){
                printf("\nS.no\tName\t\tPhone\t\tEmail\n");
                flag = 1;
            }

            printf("%d\t%s\t\t%s\t%s\n",a++,addressBook->contacts[i].name,
                                    addressBook->contacts[i].phone,
                                    addressBook->contacts[i].email);
            index_arr[arr_index++] = i;
        }
    }
    if(!flag){
        printf("\nContact not found\n");
        return 0;
    }
    return 1;
}


void editContact(AddressBook *addressBook)
{
    //////////////
    int actual_index = 0;
    int search_choice;
    
        printf("\n1. Search by Name\n");
        printf("2. Search by Phone no.\n");
        printf("3. Search by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d",&search_choice);

        switch(search_choice){
            case 1: if(!search_by_name(addressBook))
                        return;
                    break;
            case 2: if(!search_by_phone(addressBook))
                        return;
                    break;
            case 3: if(!search_by_email(addressBook))
                        return;
                    break;
            case 4: printf("Exiting...\n");
                    return;
            default: printf("\nInvalid choice. Please try again.\n");
                    return;
        
    }

    actual_index = S_no(addressBook);
    /********************/


    int choice;
    do{
        printf("\n1. Edit by name\n");
        printf("2. Edit by Phone no.\n");
        printf("3. Edit by email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice){
            case 1: edit_by_name(addressBook,actual_index);
                    break;
            case 2: edit_by_phone(addressBook,actual_index);
                    break;
            case 3: edit_by_email(addressBook,actual_index);
                    break;
            case 4: printf("Exiting...\n");
                    break;
            default: printf("\nInvalid choice, Please try again.\n");

        }
    }while(choice != 4);
}

void edit_by_name(AddressBook *addressBook,int actual_index){

        char name[50];
        printf("Enter the updated name: ");
        
        while(1){
            scanf(" %49[^\n]",name);
            
            if(valid_name(name)){
                strcpy(addressBook->contacts[actual_index].name,name);
                printf("\nContact updated Successfully\n");
                break;
            }
            else
                printf("Re-Enter the updated name : ");
        }
}

void edit_by_phone(AddressBook *addressBook,int actual_index){

        char phone[20];
        printf("Enter the updated phone no. : ");
        
        while(1){
            scanf(" %19[^\n]",phone);
            
            if(valid_phone(phone,addressBook,actual_index)){
                strcpy(addressBook->contacts[actual_index].phone,phone);
                printf("\nContact updated Successfully\n");
                break;
            }
            else
                printf("Re-Enter the updated phone no. : ");
        }
}

void edit_by_email(AddressBook *addressBook,int actual_index){

        char email[50];
        printf("Enter the updated email : ");
        
        while(1){
            scanf(" %49[^\n]",email);
            
            if(valid_email(email,addressBook,actual_index)){
                strcpy(addressBook->contacts[actual_index].email,email);
                printf("\nContact updated Successfully\n");
                break;
            }
            else
                printf("Re-Enter the updated email : ");
        }
}

int S_no(AddressBook *addressBook){
    int edit_index;
    printf("\nEnter the S.no you want to edit: ");
    
    //Check Valid serial number
    while(1){
        scanf(" %d",&edit_index);

        if(edit_index>0 && edit_index<=arr_index)
            break;
        else
            printf("Re-enter the S.no you want to edit: ");
    }

    int actual_index = index_arr[edit_index-1];

    return actual_index;
}

void deleteContact(AddressBook *addressBook)
{
    int choice;
    do{
        printf("\n1. Delete by Name\n");
        printf("2. Delete by Phone no.\n");
        printf("3. Delete by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice){
            case 1: delete_by_name(addressBook);
                    break;
            case 2: delete_by_phone(addressBook);
                    break;
            case 3: delete_by_email(addressBook);
                    break;
            case 4: printf("Exiting...\n");
                    break;
            default: printf("\nInvalid choice, Please try again.\n");
        }
    }while(choice != 4);
}

void delete_by_name(AddressBook *addressBook){
    if(search_by_name(addressBook))
        del_contact(addressBook);
}

void delete_by_phone(AddressBook *addressBook){
    if(search_by_phone(addressBook))
        del_contact(addressBook);
}

void delete_by_email(AddressBook *addressBook){
    if(search_by_email(addressBook))
        del_contact(addressBook);
}

void del_contact(AddressBook *addressBook){
    int del;
    printf("\nEnter the S.no to be deleted: ");

    //Check Valid serial number
    while(1){
        scanf(" %d",&del);

        if(del>0 && del<=arr_index)
            break;
        else
            printf("Re-enter the S.no to be deleted: ");
    }


    int actual_index = index_arr[del-1];

    for(int i=actual_index;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("\nContact Deleted Successfully\n");
}

