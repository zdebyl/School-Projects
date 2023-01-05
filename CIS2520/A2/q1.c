/*
Name: Zoe Debyl
ID: 1186610
Date: October 22nd 2022
Assignment: Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//car node
struct Car {
	char licensePlate[20];
	int mileage;
	int returnDate;
	struct Car *next;
};

//add new node to end
void addNode(struct Car* head, char licensePlate[20], int mileage, int returnDate) {
	struct Car *ptr, *temp;
	ptr = head;
	temp = (struct Car*)malloc(sizeof(struct Car));

	//create temporary node
	strcpy(temp->licensePlate, licensePlate);
	temp->mileage = mileage;
	temp->returnDate = returnDate;

	temp->next=NULL;

	//traverse list
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}

	ptr->next = temp;
}

//add node so it is ordered by mileage
struct Car* addNodeByMileage(struct Car* head, char licensePlate[20], int mileage, int returnDate) {
	struct Car *ptr, *temp, *ptrprev;
	ptr = head;
	ptrprev = head;
	temp = (struct Car*)malloc(sizeof(struct Car));

	//create temporary node
	strcpy(temp->licensePlate, licensePlate);
	temp->mileage = mileage;
	temp->returnDate = returnDate;

	temp->next=NULL;

	//check if its head
	if (mileage<ptr->mileage) {
		temp->next = head;
		head = temp;
	} else {
		ptr=ptr->next;

		//traverse list
		while (ptr->next != NULL && mileage>ptr->mileage) {
			ptr = ptr->next;
			ptrprev = ptrprev->next;
		}

		//check if its the end of the list
		if (ptr->next == NULL) {
			ptr->next = temp;
		} else {
			temp->next = ptr;
			ptrprev->next = temp;
		}
	}

	return head;
}

//add node so it is ordered by return date
struct Car* addNodeByReturnDate(struct Car* head, char licensePlate[20], int mileage, int returnDate) {
	struct Car *ptr, *temp, *ptrprev;
	ptr = head;
	ptrprev = head;
	temp = (struct Car*)malloc(sizeof(struct Car));

	//create temporary node
	strcpy(temp->licensePlate, licensePlate);
	temp->mileage = mileage;
	temp->returnDate = returnDate;

	temp->next=NULL;

	//check if its head
	if (returnDate<ptr->returnDate) {
		temp->next = head;
		head = temp;
	} else {
		ptr=ptr->next;

		//traverse list
		while (ptr->next != NULL && returnDate>ptr->returnDate) {
			ptr = ptr->next;
			ptrprev = ptrprev->next;
		}

		//check if its the end of the list
		if (ptr->next == NULL) {
			ptr->next = temp;
		} else {
			temp->next = ptr;
			ptrprev->next = temp;
		}
	}

	return head;
}

//find node in list
void findNode(struct Car* head, char licensePlate[20], int *mileage, int *returnDate) {
	struct Car *ptr;
	ptr = head;

	//find car and return get its data
	while (ptr != NULL) {
		if (strcmp(ptr->licensePlate, licensePlate)==0) {
			*mileage = ptr->mileage;
			*returnDate = ptr->returnDate;
		}
		ptr = ptr->next;
	}
}

//remove node from list
struct Car* deleteNode(struct Car* head, char licensePlate[20]) {
	struct Car *ptr;
	struct Car *ptrprev;
	ptrprev = head;
	ptr = head;
	int exit = 0;

	//check if its the first node
	if (strcmp(ptr->licensePlate, licensePlate)==0) {
		head = ptr->next;
	} else {
		ptr = ptr->next;

		//check all other nodes
		while (ptr != NULL && exit==0) {
			if (strcmp(ptr->licensePlate, licensePlate)==0) {
				ptrprev->next = ptr->next;
				
				exit = 1;
			}

			ptr = ptr->next;
			ptrprev = ptrprev->next;
		}
	}

	return head;
}

//print list
void printList(struct Car *head) {
	struct Car *ptr;
	ptr = head;

	//traverse list and print
	while (ptr != NULL) {
		printf("%s\n", ptr->licensePlate);
		printf("%d\n", ptr->mileage);
		printf("%d\n", ptr->returnDate);
		printf("\n");
		ptr = ptr->next;
	}
}

//compare license plate to license plates in list
int checkLicense(struct Car *head, char userLicense[20]) {
	struct Car *ptr;
	ptr = head;
	int checkUnique=1;

	//check if license is unique
	while (ptr != NULL) {
		if (strcmp(ptr->licensePlate, userLicense)==0) {
			checkUnique=0;
		}
		ptr = ptr->next;
	}

	//return 0 if its not unique, else return 1
	return checkUnique;
}

//calculate charge
double calculateCharge (int newMileage, int oldMileage) {
	//flat fee
	double charge = 80;

	//charge more if more than 200 miles are passed
	if ((newMileage-oldMileage)>200) {
		charge = charge + 0.15*(newMileage - oldMileage - 200);
	}

	return charge;
}

int main(void) {
	int first=0;
	int check=0;
	int exit = 0;
	int userChoice;
	char userLicense[20];
	int userMileage;
	int userReturnDate;
	int checkLicenseUnique=0;
	char foundUserLicense[20];
	int foundMileage;
	int foundReturnDate;
	double charge;
	double totalCharge=0.0;
	struct Car *temp2;
	struct Car *temp3;
	struct Car *temp4;

	//create head nodes
	struct Car *available;
	struct Car *rented;
	struct Car *atWkshop;

	//create temporary node
	struct Car *temp;

	//allocate space for head nodes
	available = (struct Car*)malloc(sizeof(struct Car));
	available->next = NULL;
	rented = (struct Car*)malloc(sizeof(struct Car));
	rented->next = NULL;
	atWkshop = (struct Car*)malloc(sizeof(struct Car));
	atWkshop->next = NULL;

	//allocate space for temporary node
	temp = (struct Car*)malloc(sizeof(struct Car));

	//create file pointers
	FILE* ptr1;
	FILE* ptr2;
	FILE* ptr3;
	
	//open files for reading
	ptr1 = fopen("availableForRent.txt", "r");
	ptr2 = fopen("rented.txt", "r");
	ptr3 = fopen("inRepair.txt", "r");

	//load file for available for rent
	do {
		if (first==0) {
			fscanf(ptr1,"%s",available->licensePlate);
			fscanf(ptr1,"%d",&available->mileage);
			fscanf(ptr1,"%d",&available->returnDate);

			available->next = NULL;

			first = 1;
		} else {
			fscanf(ptr1,"%s",temp->licensePlate);
			fscanf(ptr1,"%d",&temp->mileage);
			fscanf(ptr1,"%d",&temp->returnDate);

			temp->next = NULL;

			addNode(available, temp->licensePlate, temp->mileage, temp->returnDate);
		}
	}
	while (!feof(ptr1));

	//load file for Rented
	first = 0;

	do {
		if (first==0) {
			fscanf(ptr2,"%s",rented->licensePlate);
			fscanf(ptr2,"%d",&rented->mileage);
			fscanf(ptr2,"%d",&rented->returnDate);

			rented->next = NULL;

			first = 1;
		} else {
			fscanf(ptr2,"%s",temp->licensePlate);
			fscanf(ptr2,"%d",&temp->mileage);
			fscanf(ptr2,"%d",&temp->returnDate);

			temp->next = NULL;

			addNode(rented, temp->licensePlate, temp->mileage, temp->returnDate);
		}
	}
	while (!feof(ptr2));

	//load file for InRepair
	first = 0;
	do {
		if (first==0) {
			fscanf(ptr3,"%s",atWkshop->licensePlate);
			fscanf(ptr3,"%d",&atWkshop->mileage);
			fscanf(ptr3,"%d",&atWkshop->returnDate);

			atWkshop->next = NULL;

			first = 1;
		} else {
			fscanf(ptr3,"%s",temp->licensePlate);
			fscanf(ptr3,"%d",&temp->mileage);
			fscanf(ptr3,"%d",&temp->returnDate);

			temp->next = NULL;

			addNode(atWkshop, temp->licensePlate, temp->mileage, temp->returnDate);
		}
	}
	while (!feof(ptr3));

	//close file
	fclose(ptr1);
	fclose(ptr2);
	fclose(ptr3);

	//display menu and get user input
	while (exit==0) {
		check = 0;
		
		while (check==0) {
			printf("What you would like to do?\n");
			printf("1. Add a new car to available for rent\n");
			printf("2. Add a returned car to available for rent\n");
			printf("3. Add a returned car to repair\n");
			printf("4. Transfer a car from repair to available for rent\n");
			printf("5. Rent the first available car\n");
			printf("6. Print all lists\n");
			printf("7. Exit\n");
			scanf("%d", &userChoice);

			//check if lists are empty
			if (userChoice>7 || userChoice<1) {
				printf("Invalid choice. Please try again.\n\n");
			} else if (rented==NULL && (userChoice==2 || userChoice==3)) {
				printf("There are no cars rented right now. Please select a different option.\n\n");
			} else if (atWkshop==NULL && userChoice==4) {
				printf("There are no cars repair right now. Please select a different option.\n\n");
			} else if (available==NULL && userChoice==5) {
				printf("There are no cars available for rent right now. Please select a different option.\n\n");
			}
			else {
				check = 1;
			}
		}

		//perform what user wanted
		switch(userChoice) {
			//Get user input for new car and add to available list
			case 1:
				//get user input check car doesn't exist
				checkLicenseUnique = 0;

				while(checkLicenseUnique==0) {
					printf("Enter license plate number for new car: ");
					scanf("%s", userLicense);

					checkLicenseUnique = checkLicense(available, userLicense);

					if (checkLicenseUnique==0) {
						printf("This car already exists. Please try again.\n");
					}
				}
				
				printf("Enter mileage: ");
				scanf("%d", &userMileage);

				//add car to available list
				available = addNodeByMileage(available,userLicense,userMileage,0);

				//output message to user
				printf("New car added to available for rent list.\n\n");

				break;

			//get user input for returned car and take this car off rented list and add to available list
			case 2:
				//get user input and check car exists
				checkLicenseUnique = 1;

				while(checkLicenseUnique==1) {
					printf("Enter license plate number for returning car: ");
					scanf("%s", userLicense);

					checkLicenseUnique = checkLicense(rented, userLicense);

					if (checkLicenseUnique==1) {
						printf("This car does not exist. Please try again.\n");
					}
				}
				
				printf("Enter mileage: ");
				scanf("%d", &userMileage);

				//find previous mileage
				findNode(rented, userLicense, &foundMileage, &foundReturnDate);

				//delete car from rented list
				rented = deleteNode(rented, userLicense);

				//add car to available list
				available = addNodeByMileage(available,userLicense,userMileage,0);

				//calculate charge
				charge = calculateCharge(userMileage,foundMileage);
				totalCharge = totalCharge + charge;

				//output message to user
				printf("Car returned to available for rent list. The charge is $%.2lf.\n\n", charge);

				break;

			//get user input for returned car and take this car off rented list and add to repair list
			case 3:
				//get user input and check car exists
				checkLicenseUnique = 1;

				while(checkLicenseUnique==1) {
					printf("Enter license plate number for returning car: ");
					scanf("%s", userLicense);

					checkLicenseUnique = checkLicense(rented, userLicense);

					if (checkLicenseUnique==1) {
						printf("This car does not exist. Please try again.\n");
					}
				}
				
				printf("Enter mileage: ");
				scanf("%d", &userMileage);

				//find previous mileage
				findNode(rented, userLicense, &foundMileage, &foundReturnDate);

				//delete car from rented list
				rented = deleteNode(rented, userLicense);

				//add car to repair list
				addNode(atWkshop,userLicense,userMileage,0);

				//calculate charge
				charge = calculateCharge(userMileage,foundMileage);
				totalCharge = totalCharge + charge;

				//output message to user
				printf("Car returned to repair list. The charge is $%.2lf.\n\n", charge);
				break;

			//get user input for transferring car (from repair list) and take this car off repair list and add to available list
			case 4:
				//get user input and check car exists
				checkLicenseUnique = 1;

				while(checkLicenseUnique==1) {
					printf("Enter license plate number for car to transfer from repair list: ");
					scanf("%s", userLicense);

					checkLicenseUnique = checkLicense(atWkshop, userLicense);

					if (checkLicenseUnique==1) {
						printf("This car does not exist. Please try again.\n");
					}
				}

				//get milage and return date of car
				findNode(atWkshop, userLicense, &foundMileage, &foundReturnDate);

				//delete car from repair list
				atWkshop = deleteNode(atWkshop, userLicense);

				//add car to available list (**change mileage and return date)
				available = addNodeByMileage(available,userLicense,foundMileage,foundReturnDate);

				//output message to user
				printf("Car transferred from repair list to available list.\n\n");

				break;

			//take first car (head node) off available list and add to rented list
			case 5:
				//get user input
				printf("Enter expected return date: ");
				scanf("%d", &userReturnDate);

				//get data of first car
				strcpy(foundUserLicense, available->licensePlate);
				foundMileage = available->mileage;

				//delete first car from available list
				available = available->next;

				//add car to rented list
				rented = addNodeByReturnDate(rented, foundUserLicense, foundMileage, userReturnDate);

				//output message to user
				printf("First available car rented.\n\n");

				break;

			//print all lists
			case 6:
				printf("Avaiable for rent:\n");
				printList(available);
				printf("Rented:\n");
				printList(rented);
				printf("In repair:\n");
				printList(atWkshop);

				break;

			//exit
			case 7:
				//open files for writing
				ptr1 = fopen("availableForRent.txt", "w");
				ptr2 = fopen("rented.txt", "w");
				ptr3 = fopen("inRepair.txt", "w");

				//write available list onto file
				temp2 = available;

				while (temp2 != NULL) {
					fprintf(ptr1, "%s\n", temp2->licensePlate);
					fprintf(ptr1, "%d\n", temp2->mileage);
					fprintf(ptr1, "%d\n", temp2->returnDate);
					fprintf(ptr1, "\n");
					temp2 = temp2->next;
				}

				//write rented list onto file
				temp3 = rented;

				while (temp3 != NULL) {
					fprintf(ptr2, "%s\n", temp3->licensePlate);
					fprintf(ptr2, "%d\n", temp3->mileage);
					fprintf(ptr2, "%d\n", temp3->returnDate);
					fprintf(ptr2, "\n");
					temp3 = temp3->next;
				}

				//write in repair list onto file
				temp4 = atWkshop;

				while (temp4 != NULL) {
					fprintf(ptr3, "%s\n", temp4->licensePlate);
					fprintf(ptr3, "%d\n", temp4->mileage);
					fprintf(ptr3, "%d\n", temp4->returnDate);
					fprintf(ptr3, "\n");
					temp4 = temp4->next;
				}

				//close file
				fclose(ptr1);
				fclose(ptr2);
				fclose(ptr3);

				//print total charge
				printf("The total income calculated is %.2lf.\n", totalCharge);

				//exit
				exit = 1;

				break;

			default:
				break;
		}
	}

	return 0;
}