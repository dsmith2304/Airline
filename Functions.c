#define _CRT_SECURE_NO_WARNINGS
/*
Week 9 Program 2 Assignment 4
Danny A. Smith
PROG71985- Fall 2020
November 2020

Revision History
1.0		October		2020	Initial
1.1		October		2020	Struct and bones created
1.2		October		2020	Functions created
1.3		November	2020	Edits made
Program definition :
The Colossus Airlines fleet consists of one plane with a seating capacity of 12. It makes one flight daily. Write a seating reservation program with the following features:
1.The program uses an array of 12 structures. 
	Each structure should hold a seat identification number, 
	a marker that indicates whether the seat is assigned, 
	the last name of the seat holder, 
	and the first name of the seat holder.
2.The program displays the following menu:
	To choose a function, enter its letter label:
		a) Show number of empty seats
		b) Show list of empty seats
		c) Show alphabetical list of seats
		d) Assign a customer to a seat assignment
		e) Delete a seat assignment
		f) Quit3.
The program successfully executes the promises of its menu. Choices
d) and e) require additional input, and each should enable the user to abort an entry.
4.After executing a particular function, the program shows the menu again, except for choice f) 
5.Data is saved in a file between runs. When the program is restarted, it first loads in the data, if any, from the file.


*/

#include "Functions.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void writeOptions(int flightNumber,PLANE plane) { // display users options to the screen
	printf_s("\n**********************************************\nTo choose a function, enter its letter label:                   Plane : %s                  Flight : %d \n",plane.name,flightNumber);
	printf_s("a) Show number of empty seats\n");
	printf_s("b) Show list of empty seats\n");
	printf_s("c) Show alphabetical list of seats\n");
	printf_s("d) Assign a customer to a seat assignment\n");
	printf_s("e) Delete a seat assignment\n");
	printf_s("f) Confirm Seat Assignment\n");
	printf_s("g) Return to Flights Menu\n***********************************************\n");
	printf_s("Enter : ");
} //writeOptions



int numberEmptySeats(PLANE plane,int Flight) { // return the number of empty seats on the plane
	int count = 0;
	for (int i = 0; i < MAXSEATS; i++) {
		if (plane.currentFlight[Flight].seats[i].assigned == 'N') { // if any seats arent assigned increase count by 1
			count++;
		}
	}
	printf_s("\n");
	return count;
}//numberEmptySeats



void showListEmptySeats(PLANE plane,int Flight) { // show all availible seats on the plane
	printf_s("\n");
	for (int counter = 0; counter < MAXSEATS; counter++) {
		if (plane.currentFlight[Flight].seats[counter].assigned != 'Y') { // for all seats if the seat is assignedd display its information
			printf_s("Row : %c \tNumber : %d \tWindow : %c \tID : %d\n", plane.currentFlight[Flight].seats[counter].letter, plane.currentFlight[Flight].seats[counter].number, plane.currentFlight[Flight].seats[counter].window, plane.currentFlight[Flight].seats[counter].seatID);
		} //if
	}//for
}//showListEmptySeats

void assignClientToSeat(PLANE reference, PLANE* plane, int Flight) { // assign a client to a seat on the plane
	if ((numberEmptySeats(reference,Flight)) != 0) { // if there are empty seats || UNTESTED if theres full seats
		char firstname[CLIENTNAMESIZE];
		char lastname[CLIENTNAMESIZE];
		int ID = 0;
		
		printf_s("Enter the clients first name or 'end' to cancel : ");
		scanf_s("%s", firstname, CLIENTNAMESIZE); // get client first name
		if (strcmp(firstname, "end") == 0) {
			return;
		}


		printf_s("\nEnter the clients last name or 'end' to cancel: ");
		scanf_s("%s", lastname, CLIENTNAMESIZE); // get client last name
		if (strcmp(lastname, "end") == 0) {
			return;
		}



		printf_s("\n\n");
		showListEmptySeats(reference,Flight);
		printf_s("\n\nEnter a seat ID or enter '-1' to cancel : ");
		scanf_s("%d", &ID); // get seat ID to assign them to
		if (&ID == -1) {
			return;
		}


		// assign data to selected seat
		plane->currentFlight[Flight].seats[ID].assigned = 'Y';
		strncpy(plane->currentFlight[Flight].seats[ID].firstName, firstname, CLIENTNAMESIZE-1);
		plane->currentFlight[Flight].seats[ID].firstName[CLIENTNAMESIZE-1] = '\0';
		strncpy(plane->currentFlight[Flight].seats[ID].lastName, lastname, CLIENTNAMESIZE-1);
		plane->currentFlight[Flight].seats[ID].lastName[CLIENTNAMESIZE-1] = '\0';
		printf_s("The client %s %s has been assigned to seat %d this status is unconfirmed",firstname,lastname,ID);

	} // if a seat exists
}//assignClientToSeat

void deleteClientFromSeat(PLANE* plane, int Flight) { // delete a client from an assigned seat on the plane
	int ID = 0;
	char confirm = 'N';
	int check_Empty_Seats = 0;
	char null[CLIENTNAMESIZE];


	for (int i = 0; i < CLIENTNAMESIZE; i++) {
		null[i] = '\0';
		if (plane->currentFlight[Flight].seats[i].assigned ==  'Y') { // if there are empty seats and write null to the entire null array
			check_Empty_Seats++;
			
		} //if
	} //for
	if (check_Empty_Seats == 0) {
		printf("\nNO OCCUPIED SEATS\n");
		return;
	}//if


	for (int counter = 0; counter < MAXSEATS; counter++) { // display seat info of all assigned seats
		if (plane->currentFlight[Flight].seats[counter].assigned == 'Y') {
			printf_s("Row : %c \tNumber : %d \tWindow : %c \tID : %d\t\t First name : %s\t\t Last name : %s\n", plane->currentFlight[Flight].seats[counter].letter, plane->currentFlight[Flight].seats[counter].number, plane->currentFlight[Flight].seats[counter].window, plane->currentFlight[Flight].seats[counter].seatID, plane->currentFlight[Flight].seats[counter].firstName, plane->currentFlight[Flight].seats[counter].lastName);
		} //if
	}//for


	printf_s("\nEnter a seat ID to delete or enter '-1' to cancel: ");
	scanf_s("%d", &ID); // get seat ID to delete
	if (ID == -1) {
		return;
	} // if
	printf_s("Are you sure you want to delete client from %d[y/n] : ", ID);
	
	
	int c; while ((c = getchar()) != '\n' && c != EOF) {}// clear buffer			https://www.reddit.com/r/learnprogramming/comments/jd1mnt/flush_getchar_buffer/
	
	
	confirm = getchar();


	if (confirm == 'Y' || confirm == 'y') { // if the user identifies they are sure, delete the client info from the seat
		plane->currentFlight[Flight].seats[ID].assigned = 'N';
		strncpy(plane->currentFlight[Flight].seats[ID].firstName, null, CLIENTNAMESIZE);
		plane->currentFlight[Flight].seats[ID].firstName[CLIENTNAMESIZE-1] = '\0';
		strncpy(plane->currentFlight[Flight].seats[ID].lastName, null, CLIENTNAMESIZE);
		plane->currentFlight[Flight].seats[ID].lastName[CLIENTNAMESIZE-1] = '\0';

	} // if
} //deleteClientFromSeat

void alphabeticListSeats(PLANE plane,int Flight) { // list occupied seats in alphabetical order last name then first
	int seat_ID[MAXSEATS];
	char* min;
	min = "ZZZZZZZZZZZZZZZZZZ";
	int dontCheck[MAXSEATS];
	for (int b = 0; b < MAXSEATS; b++) {
		for (int i = 0; i < MAXSEATS; i++) {
			if (plane.currentFlight[Flight].seats[i].lastName < min && dontCheck[i] != 1) {				// This function failed and needs to be repaired in refactor
				min = plane.currentFlight[Flight].seats[i].lastName;
				seat_ID[i] = i;
				dontCheck[i] = 1;
			}
		}
	}
	for (int counter = 0; counter < MAXSEATS; counter++) {
		if (seat_ID[counter] >= 0 && seat_ID[counter] < MAXSEATS) {
			if (plane.currentFlight[Flight].seats[seat_ID[counter]].assigned != 'Y') { // for all seats if the seat is assignedd display its information
				printf_s("Row : %c \tNumber : %d \tWindow : %c \tID : %d\n", plane.currentFlight[Flight].seats[seat_ID[counter]].letter, plane.currentFlight[Flight].seats[seat_ID[counter]].number, plane.currentFlight[Flight].seats[seat_ID[counter]].window, plane.currentFlight[Flight].seats[seat_ID[counter]].seatID);
			}
		}
	}//for
} // alphabeticListSeats

void confirm_Seat_Assignment(PLANE reference,PLANE* plane, int flight) {
	if ((numberEmptySeats(reference, flight)) != 0) { // if there are empty seats || UNTESTED if theres full seats
		char firstname[CLIENTNAMESIZE];
		char lastname[CLIENTNAMESIZE];
		char confirm [CLIENTNAMESIZE];
		int ID = 0;
		int found = 0;
		printf_s("Enter the clients first name or 'end' to cancel : ");
		scanf_s("%s", firstname, CLIENTNAMESIZE); // get client first name
		if (strcmp(firstname, "end") == 0) {
			return;
		}


		printf_s("\nEnter the clients last name or 'end' to cancel: ");
		scanf_s("%s", lastname, CLIENTNAMESIZE); // get client last name
		if (strcmp(lastname, "end") == 0) {
			return;
		}

		printf_s("\n\n");
	
		for (int counter = 0; counter < MAXSEATS; counter++) {
			if (plane->currentFlight[flight].seats[counter].assigned == 'Y') { // for all seats if the seat is assigned check if the name matches the one given
			
				if (strcmp(firstname,reference.currentFlight[flight].seats[counter].firstName) == 0){
				if (strcmp(lastname, reference.currentFlight[flight].seats[counter].lastName) == 0) {
					found = 1;
					printf_s("%s %s is assigned to seat %d enter 'Confirm' to confirm : ", reference.currentFlight[flight].seats[counter].firstName, reference.currentFlight[flight].seats[counter].lastName,counter);
					scanf_s("%s", confirm, CLIENTNAMESIZE); // get client first name
					if (strcmp(confirm, "Confirm") == 0) {
						plane->currentFlight[flight].seats[counter].confirmed = 'Y';
					}
					else {
						return;
					}
				}
				}
			}
		}
		if (found == 0) {
			printf("Client not found please add them to a seat then return to confirm...");
		}
		return;
		

	} // if a seat exists
}

int writePlaneData(PLANE plane) { // write plane data to a file

	FILE* output_File;
	FILE* output_File_Two;
	int Flight = 0;
	const char* location = "./AIRLINES/onlyPlane/Flight1.plane";
	const char* locationtwo = "./AIRLINES/onlyPlane/Flight2.plane";
	if (plane.name == "only Plane") {
		location = "./AIRLINES/onlyPlane/Flight1.plane";
	locationtwo = "./AIRLINES/onlyPlane/Flight2.plane";
	}
	else {
		location = "./AIRLINES/newPlane/Flight1.plane";
		locationtwo = "./AIRLINES/newPlane/Flight2.plane";
	}


	if ((output_File = fopen(location, "w")) == NULL) {
		printf_s("***********************************************\nFile 1 corrupted... Data not saved...\n*******************************************************\n"); // if access to the file is not granted go back to menu to allow chance to fix it
		return 0;
	} // if
	if ((output_File_Two = fopen(locationtwo, "w")) == NULL) {
		printf_s("***********************************************\nFile 2 corrupted... Data not saved...\n*******************************************************\n"); // if access to the file is not granted go back to menu to allow chance to fix it
		return 0;
	} // if


	else { // file access is granted

		
		for (int i = 0; i < plane.capacity; i++) { // issue with plane.cap
	
			if (plane.currentFlight[Flight].seats[i].assigned == 'y' || plane.currentFlight[Flight].seats[i].assigned == 'Y') { // write ID, /n first name /n lastname
				
				fprintf(output_File, "%d\n%s\n%s,\n%c\n", plane.currentFlight[Flight].seats[i].seatID, plane.currentFlight[Flight].seats[i].firstName, plane.currentFlight[Flight].seats[i].lastName,plane.currentFlight[Flight].seats[i].confirmed);				// flight 1
			}
		} //for

		fclose(output_File);
		output_File = fopen(location, "a");
		fprintf(output_File, "-1\nNULL\nEND OF FILE"); // allows last run of loop with no input to struct
		fclose(output_File);





		int Flight = 1;
		for (int i = 0; i < plane.capacity; i++) { // issue with plane.cap

			if (plane.currentFlight[Flight].seats[i].assigned == 'y' || plane.currentFlight[Flight].seats[i].assigned == 'Y') { // write ID, /n first name /n lastname

				fprintf(output_File_Two, "%d\n%s\n%s\n%c\n", plane.currentFlight[Flight].seats[i].seatID, plane.currentFlight[Flight].seats[i].firstName, plane.currentFlight[Flight].seats[i].lastName, plane.currentFlight[Flight].seats[i].confirmed); // flight 2
			}
		} //for

		fclose(output_File_Two);
		output_File_Two = fopen(location, "a");
		fprintf(output_File_Two, "-1\nNULL\nEND OF FILE"); // allows last run of loop with no input to struct
		fclose(output_File_Two);



		return 1;
	} // else

} // writePlaneData

int readPlaneData(PLANE* plane) { // read plane data from a file
	FILE* input_File;
	int Flight = 0;
	FILE* input_File_two;
	const char* location = "./AIRLINES/onlyPlane/Flight1.plane";
const char* locationtwo= "./AIRLINES/onlyPlane/Flight2.plane";
	if (strcmp(plane->name,"only Plane")==0) {
		location = "./AIRLINES/onlyPlane/Flight1.plane";
		locationtwo = "./AIRLINES/onlyPlane/Flight2.plane";
	}
	else {
		location = "./AIRLINES/newPlane/Flight1.plane";
		locationtwo = "./AIRLINES/newPlane/Flight2.plane";
	}
	
	if ((input_File = fopen(location, "r")) == NULL) {
		printf_s("***********************************************\nFile 1 corrupted... Data not retrieved...\n*******************************************************\n"); // did not get access to file
		return 0;
	} // if
	if ((input_File_two = fopen(locationtwo, "r")) == NULL) {
		printf_s("***********************************************\nFile 2 corrupted... Data not retrieved...\n*******************************************************\n"); // did not get access to file
		return 0;
	} // if

	else {
		char input[PLANENAMESIZE];
		int input2 = 0;
		
		fseek(input_File, 0, SEEK_END);
		if (ftell(input_File) == 0) {
			
		} // if

		else { // file is not null
			int continueOn = 1;
			
				fclose(input_File);
				input_File = fopen(location, "r");
				while (continueOn == 1) {
				fscanf(input_File, "%d", &input2);
				plane->currentFlight[Flight].seats[input2].assigned = 'Y'; // set seat ID to assigned



				fgets(input, PLANENAMESIZE, input_File);
				fgets(input, PLANENAMESIZE, input_File); // get firstname
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; // null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].firstName, input, CLIENTNAMESIZE); // write firstname						// flight 1



				fgets(input, PLANENAMESIZE, input_File); // last name
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; //null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].lastName, input, CLIENTNAMESIZE); // write lastname

				/*
				fgets(input, PLANENAMESIZE, input_File); // last name
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; //null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].confirmed, input, CLIENTNAMESIZE); // write lastname
				*/

	
				if (strcmp(input, "END OF FILE") == 0) { // iterate until next line is "END OF FILE"
					continueOn = 0;
				} // if
			} // while
		}//else 
		fclose(input_File); // close file
		



	 input2 = 0;
		Flight = 1;
		fseek(input_File_two, 0, SEEK_END);
		if (ftell(input_File_two) == 0) {

		} // if

		else { // file is not null
			int continueOn = 1;

			fclose(input_File_two);
			input_File_two = fopen(locationtwo, "r");
			while (continueOn == 1) {
				fscanf(input_File_two, "%d", &input2);
				plane->currentFlight[Flight].seats[input2].assigned = 'Y'; // set seat ID to assigned
			


				fgets(input, PLANENAMESIZE, input_File_two);
				fgets(input, PLANENAMESIZE, input_File_two); // get firstname
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; // null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].firstName, input, CLIENTNAMESIZE); // write firstname							// Flight 2



				fgets(input, PLANENAMESIZE, input_File_two); // last name
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; //null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].lastName, input, CLIENTNAMESIZE); // write lastname

				/*
				fgets(input, PLANENAMESIZE, input_File_two); // last name
				for (int i = 0; i < sizeof(input); i++) {
					if (input[i] == '\n') {
						input[i] = '\0'; //null terminate
					} // if
				} // for
				strncpy(plane->currentFlight[Flight].seats[input2].confirmed, input, CLIENTNAMESIZE); // write lastname
				*/

				if (strcmp(input, "END OF FILE") == 0) { // iterate until next line is "END OF FILE"
					continueOn = 0;
				} // if
			} // while
		}//else 
		fclose(input_File_two); // close file






		
		plane->capacity = MAXSEATS;
		return 1;
	} // else
} //readPlaneData

PLANE initPlane(const char* name) { // intialize a plane with data and the name "onlyPlain" | can be overwritten after initialized
	PLANE myPlain = { .name = "only Plane",.capacity = MAXSEATS };
	if (strcmp(name, "only Plane") == 0) {
		strncpy(myPlain.name, "only Plane", CLIENTNAMESIZE - 1);
		myPlain.name[CLIENTNAMESIZE - 1] = '\0';
	}
	else {
		strncpy(myPlain.name, "new Plane", CLIENTNAMESIZE - 1);
		myPlain.name[CLIENTNAMESIZE - 1] = '\0';
	}
	

	int numswitch = 0;
	char letters[29] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	int number = 1;
	int count = 0;
	int seats_Per_Row = 2;
	int add_sub = 0;
	int letterSpot = -1;
	int min = 1;
	for (int counter = 0; counter < myPlain.capacity; counter++) {

		if (count % seats_Per_Row == 0) {
			letterSpot++;
		} // if
		SEAT seat = { .letter = letters[letterSpot],.number = number,.seatID = counter,.assigned = 'N',.confirmed = 'N'};
		if (number == min || number == seats_Per_Row) {
			seat.window = 'Y';
		} // if
		else {
			seat.window = 'N';
		} // else
		count++;
		myPlain.currentFlight[0].seats[counter] = seat;
		myPlain.currentFlight[1].seats[counter] = seat;
		if (add_sub == 0) {
			number++;
		} // if

		if (number == seats_Per_Row + 1) {
			number = 1;
		}// if

	} // plane seat init
	return myPlain;
} // initPlane

FLIGHT* initFlights(PLANE myPlain, PLANE newPlain,FLIGHT flights[]) { // init array of flights
	FLIGHT newflight = { .flightNumber = 102,.plane = myPlain,.outReturn=0 };
	flights[0] = newflight;
	strncpy(flights[0].plane.name, "onlyPlane", CLIENTNAMESIZE - 1);
	flights[0].plane.name[CLIENTNAMESIZE - 1] = '\0';
	newflight.flightNumber = 311;
	newflight.outReturn = 1;
	flights[1] = newflight;
	strncpy(flights[1].plane.name, "onlyPlane", CLIENTNAMESIZE - 1);
	flights[1].plane.name[CLIENTNAMESIZE - 1] = '\0';
	FLIGHT newflightSecond = { .flightNumber = 444,.plane = newPlain,.outReturn = 0 };
	flights[2] = newflightSecond;
	strncpy(flights[2].plane.name, "newPlane", CLIENTNAMESIZE - 1);
	flights[2].plane.name[CLIENTNAMESIZE - 1] = '\0';
	newflightSecond.flightNumber = 519;
	newflightSecond.outReturn = 1;
	flights[3] = newflightSecond;
	strncpy(flights[3].plane.name, "newPlane", CLIENTNAMESIZE - 1);
	flights[3].plane.name[CLIENTNAMESIZE - 1] = '\0';
	return flights;

}

void writeFlights() { // writes all flights | Needs to read flights from file for future optimization but not currently required
	printf("***********    FLIGHTS    ****************");
	printf("\n\n1. 102");
	printf("\n2. 311");
	printf("\n3. 444");
	printf("\n4. 519");
	printf("\n5. exit");
	printf("\n\nEnter an option[1-5] : ");
}