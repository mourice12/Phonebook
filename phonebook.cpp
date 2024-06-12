#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Author: Jeffery Reed
   Description: Phonebook 3
   Lab Section: CS-130 Online
   Class: CS-130-50-4242
   Date: 3/17/2024

*/
//Person struct for use in the phonebook
struct person {
    char firstName[100];
    char lastName[100];
    char phoneNumber[100];
};
//function initialization
void createRecord(struct person **persons, int *numPersons);
void deleteRecord(struct person **persons, int *numPersons);
void showRecord(struct person **persons, int numPersons);
void sortBook(struct person **persons, int *numPersons);
void findNumber(struct person **persons,int *numPersons);
void randomNumber(struct person **persons,int *numPersons);
void deleteRecords(struct person **persons,int *numPersons);
void writeToFile(struct person **persons, int numPersons);
void readFromFile(struct person **persons, int *numPersons);
int controller();
//main
int main(void){
    int control;
    struct person *persons = NULL;
    int numPersons = 0;
    srand(time(NULL));
   
   
   
    //while loop that iterates until 0 is entered
   do{
   
    control = controller();
        if(control == 1){
            createRecord(&persons, &numPersons);
        }
        else if(control == 2){
            deleteRecord(&persons, &numPersons);
        }
        else if(control == 3){
            showRecord(&persons, numPersons);
        }else if(control == 4){
        	sortBook(&persons,&numPersons);
		}else if(control == 5){
			findNumber(&persons,&numPersons);
		}else if(control ==6){
			randomNumber(&persons,&numPersons);
		}else if(control == 7){
			deleteRecords(&persons,&numPersons);
		}else if (control == 8) {
    		writeToFile(&persons, numPersons);
		} else if (control == 9) {
    		readFromFile(&persons, &numPersons);
}
       
   
    }while(control > 0);    
   
    // Free dynamically allocated memory
    free(persons);
   
    return 0;
}
// Function to print menu and get the controller int for the while loop
int controller(){
    int control;
    printf("Please choose an option:\n");
    printf("Create new record: 1\n");
    printf("Delete a record: 2\n");
    printf("Show Records: 3\n");
    printf("Sort Records: 4\n");
    printf("Find Phone Number: 5\n");
    printf("Random Phone Number: 6\n");
    printf("Delete All Records: 7\n");
    printf("Save to file: 8\n");
    printf("Read to file: 9\n");
    printf("Exit: 0\n");
    scanf("%d", &control);
    return control;
}
//Function to create a phonebook record
void createRecord(struct person **persons, int *numPersons){
    struct person p;
   
    printf("First Name: ");
    scanf("%s", p.firstName);
   
    printf("Last Name: ");
    scanf("%s", p.lastName);
   
    printf("Phone Number: ");
    scanf("%s", p.phoneNumber);
   
    // Increase the size of the array
    (*numPersons)++;
    *persons = (struct person *)realloc(*persons, *numPersons * sizeof(struct person));
    if (*persons == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
   
    // Assign the new struct
    (*persons)[*numPersons - 1] = p;
   
    printf("Record successfully added!\n\n");
    printf("\n\n\n\n");
}

//Function to delete record from phonebook
void deleteRecord(struct person **persons, int *numPersons) {
    if (*numPersons == 0) {
        printf("No records to delete!\n");
        return;
    }

    char firstName[20];
    char lastName[20];
    printf("Enter the first name of the record to delete: ");
    scanf("%s", firstName);
    printf("Enter the last name of the record to delete: ");
    scanf("%s", lastName);

    int foundIndex = -1;

    // Find the index of the record to delete
    for (int i = 0; i < *numPersons; i++) {
        if (strcmp((*persons)[i].firstName, firstName) == 0 && strcmp((*persons)[i].lastName, lastName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Record not found!\n");
        return;
    }

    // Shift elements after the deleted record
    for (int i = foundIndex; i < *numPersons - 1; i++) {
        (*persons)[i] = (*persons)[i + 1];
    }

    // Decrease the number of persons
    (*numPersons)--;

    // Resize the memory block
    *persons = (struct person *)realloc(*persons, (*numPersons) * sizeof(struct person));
    if (*persons == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Record successfully deleted!\n");
    printf("\n\n\n\n");
}


// Function to display records of phonebook
void showRecord(struct person **persons, int numPersons) {
    // Print header
    printf("Records:\n");

    // Iterate through the array
    for (int i = 0; i < numPersons; i++) {
       
        printf("Person %d:\n", i + 1);

        // Print first name, last name, and phone number
        printf("First Name: %s\n", (*persons)[i].firstName);
        printf("Last Name: %s\n", (*persons)[i].lastName);
        printf("Phone Number: %s\n\n", (*persons)[i].phoneNumber);
        printf("\n\n\n\n");
       
    }
}
//function to sort book alphabetically by first or last name
void sortBook(struct person **persons, int *numPersons){
struct person temp;
for(int i = 0; i< *numPersons;i++){
for(int j= i + 1; j<*numPersons;j++){
if  (strcmp((*persons)[i].firstName, (*persons)[j].firstName) > 0 ||  strcmp((*persons)[i].lastName, (*persons)[j].lastName) > 0) {

temp = (*persons)[i];
(*persons)[i]=(*persons)[j];
(*persons)[j] = temp;
}
}
}
for(int p = 0;p < *numPersons;p++){
printf("%s %s \n",(*persons)[p].firstName,(*persons)[p].lastName);
printf("\n\n\n\n");
}
}

//function to find a number based on either first or last name
void findNumber(struct person **persons,int *numPersons){
char name;

printf("Please Enter a Name to find the Phone Number:\n");
scanf("%s",&name);

for(int i = 0;i < *numPersons;i++){
if(strcmp((*persons)[i].firstName,&name) > 0 || strcmp((*persons)[i].lastName,&name)>0){
printf("The phonenumber is: %s\n", (*persons)[i].phoneNumber);
printf("\n\n\n\n");
}
}
}

//function to get a random phone number from the phone book
void randomNumber(struct person **persons,int *numPersons){
int ran = rand() % *numPersons;
printf("\n\n\n\n");
printf("First Name: %s\n",(*persons)[ran].firstName);
printf("Last Name: %s\n",(*persons)[ran].lastName);
printf("Phone Number: %s \n", (*persons)[ran].phoneNumber);
printf("\n\n\n\n");
}

//function to delete all records and resize the memory for the struct
void deleteRecords(struct person **persons,int *numPersons){
(*numPersons) = 0;
*persons = (struct person *)realloc(*persons,(*numPersons) * sizeof(struct person));
}

//function to write phonebook to a file specified by the user
void writeToFile(struct person **persons, int numPersons) {
    char fileName[100];
    printf("Enter the name of the file to save: ");
    scanf("%s", fileName);

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < numPersons; i++) {
        fprintf(file, "%s %s %s\n", (*persons)[i].firstName, (*persons)[i].lastName, (*persons)[i].phoneNumber);
    }

    fclose(file);

    printf("Records saved to %s\n", fileName);
}

//function to read file into struct Person
void readFromFile(struct person **persons, int *numPersons) {
    char fileName[100];
    printf("Enter the name of the file to read: ");
    scanf("%s", fileName);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct person p;
    while (fscanf(file, "%s %s %s", p.firstName, p.lastName, p.phoneNumber) == 3) {
        (*numPersons)++;
        *persons = (struct person *)realloc(*persons, *numPersons * sizeof(struct person));
        if (*persons == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        (*persons)[*numPersons - 1] = p;
    }

    fclose(file);

    printf("Records read from %s\n", fileName);
}
