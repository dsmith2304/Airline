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
2.1		November	2020	Multi Flights added
2.2		November	2020	Read Write Completed

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



void main() {
	PLANE myPlane = initPlane("only Plane"); 
	PLANE newPlane = initPlane("new Plane");
	readPlaneData(&myPlane); // setup plain
	readPlaneData(&newPlane);
	FLIGHT flights[MAX_FLIGHTS+1];
	initFlights(myPlane,newPlane,flights);
	bool mainMenu = true;;
	int selectedFlight = 0;


	while (mainMenu == true) { // flights selection menu


		writeFlights();
		int input = -2;
		scanf_s("%d", &input);


		switch (input) { 
		case 1:// flight 102
			selectedFlight = 0;
			mainMenu = false;
			break;
		case 2: // flight 311
			selectedFlight = 1;
			mainMenu = false;
			break;
		case 3: // flight 444
			selectedFlight = 2;
			mainMenu = false;
			break;
		case 4: // flight 519
			selectedFlight = 3;
			mainMenu = false;
			break;
		case 5:
			exit();
			writePlaneData(myPlane);
			writePlaneData(newPlane);
			break;
		}
		int c; while ((c = getchar()) != '\n' && c != EOF) {}// clears the get char buffer

		while (mainMenu == false) { // until f is chosen

			writeOptions(flights[selectedFlight].flightNumber,flights[selectedFlight].plane);

			char input = 'f';
			input = getchar();
			switch (input) {
			case 'A': // case A and a ensures capitilization doesnt matter
			case 'a':
				
				printf_s("Number of empty seats : %d", numberEmptySeats(flights[selectedFlight].plane,flights[selectedFlight].outReturn));
				break;
			case 'B':
			case 'b':
				showListEmptySeats(flights[selectedFlight].plane, flights[selectedFlight].outReturn);
				break;
			case 'C':
			case 'c':
				alphabeticListSeats(flights[selectedFlight].plane, flights[selectedFlight].outReturn);
				break;
			case 'D':
			case 'd':
				assignClientToSeat(flights[selectedFlight].plane, &flights[selectedFlight].plane, flights[selectedFlight].outReturn);
				break;
			case 'E':
			case 'e':
				deleteClientFromSeat(&flights[selectedFlight].plane, flights[selectedFlight].outReturn);
				break;
			case 'F':
			case 'f':
				
				confirm_Seat_Assignment(flights[selectedFlight].plane,&flights[selectedFlight].plane, flights[selectedFlight].outReturn);
				break;
			case 'G':
			case 'g':
				mainMenu = true;
				break;
			}
			printf_s("\n\n");
			int c; while ((c = getchar()) != '\n' && c != EOF) {}// clears the get char buffer

		}// while !mainMenu
	}// while main menu



}