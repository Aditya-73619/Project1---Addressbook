#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
// #include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    printf("Name\t\tPhone\t\tEmail\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%s\t\t%s\t%s\n",addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    for(int i=addressBook->contactCount;i<3;i++){

        /*****************************    NAME   *************************************/
        printf("Enter the Name : ");        
        while(1){
            int valid = 1;
            scanf(" %49[^\n]",addressBook->contacts[i].name);

            for(int j=0;addressBook->contacts[i].name[j]!=0;j++){
                if((!isalnum(addressBook->contacts[i].name[j])) && 
                    (addressBook->contacts[i].name[j] != ' ')){
                    valid = 0;
                    break;
                }
            }
            if(valid)
                break;
            else
                printf("Re-Enter the name : ");
        }
        

        /*****************************    Phone   *************************************/
        printf("Enter the Phone no. : ");       
        while(1){
            int count = 0;
            int valid = 1;
            scanf(" %19[^\n]",addressBook->contacts[i].phone);

            count  = strlen(addressBook->contacts[i].phone);

            if(addressBook->contacts[i].phone[0]<'6' || 
                addressBook->contacts[i].phone[0]>'9' || 
                count!=10)
                valid = 0;

            for(int j=0;addressBook->contacts[i].phone[j]!=0;j++){
                if(!isdigit(addressBook->contacts[i].phone[j])){
                    valid = 0;
                    break;
                }
            }

            if(valid)
                break;
            else
                printf("Re-Enter the Phone no. : ");
        }


        /*****************************    Email   *************************************/
        printf("Enter the email : ");
        while(1){ 
            int valid = 1;
            scanf(" %49[^\n]",addressBook->contacts[i].email);

            for(int j=0;addressBook->contacts[i].email[j]!=0;j++){  //No uppercase and space
                if((addressBook->contacts[i].email[j] == ' ') ||
                    isupper(addressBook->contacts[i].email[j])){
                        valid = 0;
                        break;
                    }
            }

            int special_character_pos = 0;
            if(valid){
                int special_character_count = 0;        //Must 1 @
                for(int j=0;addressBook->contacts[i].email[j]!=0;j++){
                    if(addressBook->contacts[i].email[j] == '@'){
                        special_character_count++;
                        special_character_pos = j;
                    }
                }

                if(special_character_count != 1){
                    valid = 0;
                }
            }

                if(valid == 1){     
                    char extension[5];      // Last 4 characters .com
                    sscanf(addressBook->contacts[i].email,"%*[^@]@%*[^.]%s",extension);

                    char com[] = {".com"};
                                                        //First not @
                    if((strcmp(extension,com) != 0) || (addressBook->contacts[i].email[0] == '@'))
                        valid = 0;
                }

                if(valid == 1){             //Atleast 1 character between @ and .
                    if(addressBook->contacts[i].email[special_character_pos + 1] == '.')
                        valid = 0;
                }

                if(valid)
                    break;
                else
                    printf("Re-Enter the email : ");
        }
        addressBook->contactCount++;
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
