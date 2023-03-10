// Jack Johnston 
// 07/07/2022
// Exam booking software focusing primarily on the use of bitwise operation and binary.

#include <stdio.h>
#include <stdlib.h> 
#include "student.h"

typedef struct uLLInt {
   unsigned long long int binaryReservations[2][2];
   unsigned long long int weekReservations;
   unsigned long long int bitmask;
   unsigned long long int examBooking;
   unsigned long long int bookedExams;
   unsigned long long int week1Binary;
   unsigned long long int week2Binary;
} uLLInt;

typedef struct weekInfo {
  int week;
   int day;
   int timeStart;
   int lengthOfExam;
} weekInfo;

#define Day(dayOfTheWeek) printf("\nWeek %d: %s %d:00 - %d:00",StudentExamSchedule.week+1,#dayOfTheWeek,StudentExamSchedule.timeStart,StudentExamSchedule.lengthOfExam+StudentExamSchedule.timeStart);

int displayStudentExamSchedule(int studentNo,int examBookings[][5],int sizeOfArray);      //forward declarations
int convertuLLIntIntToArray();
int setExamBookingTime();
int displayUnbookedTimes();
void menuOption();
uLLInt binaryReservations[][2] = {0,0};

int main(void) {
int inputChoice;
int studentNumber;

while(inputChoice != 4)
{
menuOption();
scanf("%d",&inputChoice);
switch(inputChoice)
{
case 1:
printf("Enter student number\n");
scanf("%d",&studentNumber);
int sizeOfArray = sizeof(examBookings) / sizeof(int); //counts the total elements in the array
sizeOfArray = sizeOfArray / 5;  // finds the amount of the rows
printf("Exam booked for student %d:",studentNumber);
displayStudentExamSchedule(studentNumber,examBookings,sizeOfArray);
break;

case 2:
setExamBookingTime();
break;

case 3:
displayUnbookedTimes();
convertuLLIntIntToArray(studentNumber);
break;

case 4:
printf("Exiting Exam Booking Software\n");
break;
}
}
}        

void menuOption(){ //prints out the menu options
printf("\n1. display a student's exam schedule\n");
printf("2. load a new exam booking\n");
printf("3. find unbooked times\n");
printf("4. exit\n");
}

int displayStudentExamSchedule(int studentNumber,int examBookingss[][5],int sizeOfArray){ // goes into examBooking array and convert into printable output

weekInfo StudentExamSchedule;

for(int e = 0; e < sizeOfArray; e++) {

if (studentNumber == examBookingss[e][0]){
StudentExamSchedule.week = examBookingss[e][1];
StudentExamSchedule.day = examBookingss[e][2];
StudentExamSchedule.timeStart = examBookingss[e][3];
StudentExamSchedule.lengthOfExam = examBookingss[e][4];

switch(StudentExamSchedule.day)
{
case 0:
Day(Monday);
break;

case 1:
Day(Tuesday);
break;

case 2:
Day(Wednesday);
break;

case 3:
Day(Thursday);
break;

case 4:
Day(Friday);
break;

case 5:
Day(Saturday);
break;

case 6:
Day(Sunday);
break;
}
}
}
return 0;
}

int setExamBookingTime(){ //sets an exam booking time in the array and checks if there are duplicate bookings
int week,studentNumber,day,startingTime,examLength;
uLLInt BookedExamBinary;
weekInfo weekInformation;
BookedExamBinary.bitmask = 0xFFFFFFFFFFFFFFFF;
BookedExamBinary.examBooking = 0;
BookedExamBinary.bookedExams = 0;

int sizeOfBookingArray = sizeof(examBookings) / sizeof(int); //counts the total elements
sizeOfBookingArray = sizeOfBookingArray / 5; //counts the total rows

printf("Enter the Details of the exam!\n");

printf("Enter student number\n");
scanf("%d",&studentNumber);

printf("Enter exam (1 or 2)\n");
scanf("%d",&week);

printf("Enter exam day (M = 0; T = 1...):\n");
scanf("%d",&day);

printf("Enter exam start time (9 to 17):\n");
scanf("%d",&startingTime);

printf("Enter number of hours:\n");
scanf("%d",&examLength);

BookedExamBinary.bitmask = BookedExamBinary.bitmask >>= examLength; //bitmask is a hexadecimal which equals to 1111111..(and so on), it shifts to the right to represent the length of the exam,(we take 2 hours for this example) it becomes 0011111..
BookedExamBinary.bitmask = ~BookedExamBinary.bitmask; // we invert the bitmask so that it is equal to 1100000
BookedExamBinary.bitmask = BookedExamBinary.bitmask >> startingTime - 9; //we shift the bitmask to the right to match the starting time. It is subtracted by nine, as that is the starting time.
BookedExamBinary.examBooking = BookedExamBinary.examBooking | BookedExamBinary.bitmask; //we set setExamBooking equal to bitmask, as the variable bitmask will be used again

for(int z = 0; z < sizeOfBookingArray; z++)
{
if(examBookings[z][0] == studentNumber && examBookings[z][1]== week-1 && examBookings[z][2]== day){ //iterate over the array and find matching arrays withthe information provided by the user, if found, the information is converted into binary format
   BookedExamBinary.bitmask = 0xFFFFFFFFFFFFFFFF;
   weekInformation.week=examBookings[z][1]; 
   weekInformation.day=examBookings[z][2];
   weekInformation.timeStart = examBookings[z][3];
   weekInformation.lengthOfExam= examBookings[z][4]; //we compare the binary of an existing week and day and compare with the values entered by the user to determine of there are any conflicting schedules
   
   BookedExamBinary.bitmask = BookedExamBinary.bitmask >>=  weekInformation.lengthOfExam; //same process as above, bitmask has the value 111111....it shifts to the right to represent the length of a booked exam it becomes 11111100..
   BookedExamBinary.bitmask = ~BookedExamBinary.bitmask; //inverts the binary into 110000....
   BookedExamBinary.bitmask = BookedExamBinary.bitmask >>  weekInformation.timeStart - 9; //shifts the bitmask into the correct time
   BookedExamBinary.bookedExams = BookedExamBinary.bookedExams | BookedExamBinary.bitmask; //we set variable bookedExams equal to bitmask, as the variable bitmask will be used again

}
}
BookedExamBinary.bookedExams = ~BookedExamBinary.bookedExams | ~BookedExamBinary.examBooking; //this compares the two inverted variable we have earlier, essentially, if there were no conflicts in the schedule booked exam will show 11111100.... and set Exam booking will show the user generated binary which is 11001111... which equals to 11111111... that determines that there is no conflicting schedule
                                              //a bad case scenario would be that there is a conflicting schedule with bookedExam showing 11111100.... and Exam booking will show the user generated binary which is 11111001. if we were to OR these two variables they would not result in 11111111... instead as 11111101 which flags as an error
for(int x = 0; x < sizeOfBookingArray; x++)
if(BookedExamBinary.bookedExams == 0xFFFFFFFFFFFFFFFF && examBookings[x][0] == -1){ //iterates over the exam booking array and finds those with a student number of "-1" that we added as placeholder if the user want to add new exam bookings
  examBookings[x][0] = studentNumber;
  examBookings[x][1] = week-1;
  examBookings[x][2] = day;
  examBookings[x][3] = startingTime;
  examBookings[x][4] = examLength;
  x = sizeOfBookingArray; //ends the loop if an array with student number -1 is found
}
if(BookedExamBinary.bookedExams != 0xFFFFFFFFFFFFFFFF){ // we used the or trick (line 158) to validate that if bookedExamTime is not equal to hex 0xFFFFFFFFFFFFFFFF it outputs to the user that the timeslot is not available
   printf("That time is not available");
}
} 


int displayUnbookedTimes(){ //  Prints all the examBooking array which has been unbooked
weekInfo c1 = {0,0,0,0};
uLLInt BookedExamBinary;
BookedExamBinary.week2Binary = 0;
BookedExamBinary.week1Binary = 0;

size_t n = sizeof(examBookings) / sizeof(int); //counts the total elements
n = n / 5; //counts how much rows are in the array
for(int e = 0; e < n; e++) 
{
c1.week = examBookings[e][1];
c1.day = examBookings[e][2];
c1.timeStart = examBookings[e][3];
c1.lengthOfExam = examBookings[e][4];

BookedExamBinary.bitmask = BookedExamBinary.bitmask  >> c1.timeStart + c1.lengthOfExam - c1.timeStart;  
BookedExamBinary.bookedExams = ~BookedExamBinary.bitmask ;
BookedExamBinary.bookedExams = BookedExamBinary.bookedExams >>= c1.timeStart - 9;
BookedExamBinary.bookedExams = BookedExamBinary.bookedExams >>= c1.day * 8;

if(examBookings[e][1] == 1){ //if the week in the array is listed as one, shift the binary into the correct format
BookedExamBinary.week1Binary  = BookedExamBinary.bookedExams | BookedExamBinary.week1Binary;
BookedExamBinary.bitmask  = 0xFFFFFFFFFFFFFFFF; //resets the bitmask for the next operation
BookedExamBinary.bookedExams = 0;  //resets the bookedExam binary for the next operation
binaryReservations[0][0].weekReservations= ~BookedExamBinary.week1Binary; // adds the binary into an array
}

if(examBookings[e][1] == 0){ //if the week in the array is listed as zero, shift the binary into the correct format
BookedExamBinary.week2Binary = BookedExamBinary.bookedExams | BookedExamBinary.week2Binary;
BookedExamBinary.bitmask  = 0xFFFFFFFFFFFFFFFF;  //resets the bitmask for the next operation
BookedExamBinary.bookedExams = 0;  //resets the bookedExam binary for the next operation
binaryReservations[1][1].weekReservations= ~BookedExamBinary.week2Binary;  // adds the binary into an array
}
}
return 0;
}

int convertuLLIntIntToArray(){ //iterates the unbooked time 1 hour at a time
   uLLInt Binary;
   int studentNumber;
   int BookedExam[][5]= {0};
   int n = sizeof(BookedExam) / sizeof(int); //counts the total elements
   n = n / 5; //counts how much rows are in the array
   int incrementRow = 0;
   printf("\nAvailable Exam Bookings\n");
   printf("\nWeek 1\n");
   for (int c = 63; c >= 0; c--)
  {
    Binary.week1Binary = ~binaryReservations[1][1].weekReservations >> c;
   if (Binary.week1Binary & 1){
    }
    else{
         BookedExam[0][0] = studentNumber;
         BookedExam[0][1] = 0;
         BookedExam[0][2] = incrementRow/8;
         BookedExam[0][3] = incrementRow%8 + 9;
         BookedExam[0][4] = 1;
         displayStudentExamSchedule(studentNumber,BookedExam,n);

    }
         incrementRow++;
  }

  printf("\n");
  printf("\nWeek 2\n");

  incrementRow = 0;
 for (int c = 63; c >= 0; c--)
  {
    Binary.week2Binary = ~binaryReservations[0][0].weekReservations >> c;
   if (Binary.week2Binary & 1){
    }
    else{
         BookedExam[0][0] = studentNumber;
         BookedExam[0][1] = 1;
         BookedExam[0][2] = incrementRow/8;
         BookedExam[0][3] = incrementRow%8 + 9;
         BookedExam[0][4] = 1;
         displayStudentExamSchedule(studentNumber,BookedExam,n);
    }
   incrementRow++;
  }
return 0;
}
