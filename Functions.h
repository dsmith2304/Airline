#pragma once

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

#define MAXSEATS 12 // max seats any plane can have
#define PLANENAMESIZE 25 // how long the plane name can be
#define CLIENTNAMESIZE 25 // max size of a clients first or last name individually
#define MAX_FILE_NAME 50 // max length a file name can be for writting or reading
#define MAX_FLIGHTS 4 // number of daily flights
#define TOTAL_PLANES 2 // number of planes
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct seat { // This structure is for a seat of a plane to be nested in a plane struct
	int seatID;
	char letter;
	int number;
	char assigned;
	char confirmed;
	char window;
	char firstName[CLIENTNAMESIZE];
	char lastName[CLIENTNAMESIZE];
}SEAT;
typedef struct seat SEAT;


typedef struct seatSelector {
	SEAT seats[MAXSEATS];
}SEATSELECTOR;
typedef struct plane { // this structure is the plane being usedd
	int capacity;
	char name[CLIENTNAMESIZE];
	SEATSELECTOR currentFlight[(MAX_FLIGHTS / TOTAL_PLANES) +1]; // should = 3 right now 11.22.20
}PLANE;
typedef struct plane PLANE;

typedef struct flight {
	int flightNumber;
	int outReturn;
	PLANE plane;
}FLIGHT;

// function descriptions are tied to the function in Functions.c check that file for descriptions
PLANE initPlane(const char*);
void assignClientToSeat(PLANE, PLANE*,int);
void writeOptions(int flightNumber, PLANE);
int numberEmptySeats(PLANE,int);
void showListEmptySeats(PLANE,int);
void alphabeticListSeats(PLANE,int);
void deleteClientFromSeat(PLANE*,int);
int writePlaneData(PLANE);
int readPlaneData(PLANE*);
void writeFlights();
void confirm_Seat_Assignment(PLANE reference, PLANE* plane, int flight);
FLIGHT* initFlights(PLANE, PLANE,FLIGHT[]);