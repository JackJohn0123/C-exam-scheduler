# C-language-exam-scheduler

** OVERVIEW ** 

C language program that purposely use only bit-wise operations to speed up the program execution. The program is able to compute thousands of students exam booking in reasonable time, given that the number of possible scheduling conflicts increases as O(n2).

The standard format for a student booking is placed in a 2d array in a header file and is interpreted as follows:

1. Student number: 0 - 9999
2. Week of exam : 0,1 (Week 1, Week 2)
3. Day of the week : Monday = 1, Tuesday = 2...
4. Start time of exam in 24h format and length of exam.

{20, 0, 3, 9, 3}
{20, 1, 3, 9, 3},
{20, 1, 4, 16, 1},
{20, 1, 5, 15, 2}

The example in the first line provided tells us that student number 20 is booked within Week 1, on a Thursday, from 9-oclock with a duration of an exam of 3 hours.

The data is then converted into a 64 bit unsigned integer that is represented as such 

[0] = 00000000000000000000000011100000
      00000000000000000000000000000000
[1] = 00000000000000000000000011100000
      00000001000000110000000000000000
      
Once all the data is loaded,the
the two cumulative unsigned integet values are converted back to a 2D array of the form

{0 , 0, 0, 13, 2},
{0 , 0, 1, 9, 1},
{0 , 0, 1, 12, 1},
{0, 1, 0, 9, 1},
{0, 1, 0, 16, 1},
{0, 1, 1, 16, 1}....

to show the unbooked times within the week.

The program is able to view a student booked exam, and times where a student is free!

** RUNNING THE PROGRAM ** 

You can simply run the exe file or using MinGW by the command prompt with the comand "gcc assignment1.c" and running the exe file that is generated!

<img src = https://user-images.githubusercontent.com/113872188/225769969-1dfe5e27-f1c5-4bb0-bfba-300eeb08fe37.png>




      
      




