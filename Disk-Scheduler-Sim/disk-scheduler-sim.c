#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string.h"

/*
Made by Gus Temple
CMS470
Dr. Summet

A brief overview:
This program simulates 2 different scheduling algorithm, with the option to change the second algorithim slightly.
Using a variety of helper methods when run, main will generate a input number of requests to random tracks 0-99. 
After translating these tracks to an array, main will simulate a r/w arm scanning through each track request for FIFO and SSTF disk scheduling algorithms.
The third scheduling algorithm is SSTF, but with a starting position at an input location. It is referenced as variableSSTF.
For each algorithm, a single histogram prints, on average, when tracks get processed.
The results of how soon each track is processed are stored in a single struct, which has 3 arrays to store these results for each algorithm.
After each algorithm is run, a final method prints a histogram containing the results of all 3 algorithms for easy comparison.
*/

// struct to hold arrays for how efficiently each algo processed a given track
// think of each index the name of the track, and the value at that index as how soon it was processed
// each index in each array gives how many tracks were crossed before proccessing that index as a track
typedef struct{

  int processFIFO[100];
  int processSSTF[100]; 
  int processVariableSSTF[100]; 

} dataArrays;

/*
* Purpose: smaller utility method to print a char a certain number of times
* 
* Input:  numChars - the number of stars to be printed
*
* Outputs: none - prints all of the chars, followed by a newline
*/
void printChars(int numChars, char c) {
  for (int i = 0; i < numChars; i++) {
    printf("%c", c);
  }
  printf("\n");
}

/*
*  Purpose - take two array, a shorter frequency array, and tally how often certain numbers appear
*            in the other processedAt array
*
* Inputs - frequency: an array that holds how often data falls into a certain bin
*                    ex. index 0 holds the number of data points between 0 and 9
*                        index 1 holds the number of points between 10 and 19
*
*  Outputs - none, but the frequency array is filled with meaningful values
*/
void tallyFreq(int frequency[], int processedAt[]) {
  // go through each request and extract the time necessary to process each request.
  for (int i = 0; i < 100; i++) {

    // the time to process each track is that track as an index of the processedAt array
    int time = processedAt[i];

    // if the current track was never a request
    if (time == -1) {
      continue;
    } else {

      // filter the time into its respective bin
      if (time <= 9) {
        frequency[0]++;
      } else if (time <= 19) {
        frequency[1]++;
      } else if (time <= 29) {
        frequency[2]++;
      } else if (time <= 39) {
        frequency[3]++;
      } else if (time <= 49) {
        frequency[4]++;
      } else if (time <= 59) {
        frequency[5]++;
      } else if (time <= 69) {
        frequency[6]++;
      } else if (time <= 79) {
        frequency[7]++;
      } else if (time <= 89) {
        frequency[8]++;
      } else {
        frequency[9]++;
      }
    }
  }
}

/*
* Purpose: count and print the performance of each array in a histogram
*
* Inputs: requests - an array of ints, each represting a request to a specific track
*         processedAt - int array where each track number, as an index, contains the time took to process that track
*         len - the number of inputs in the request arrray
*         char* - string used in histogram printing, usually "FIFO" or "SSTF"
*
* Outputs: prints out the histrogram with bins of length 9, from 0 to 99
*/
void graph(int requests[], int processedAt[], int len, char* algoName) {
  
  int freq[10];      // array to hold the number of tracks that fall into each bin

  // initialize the frequency array to 0
  for (int i = 0; i < 10; i++) {
    freq[i] = 0;
  }

  tallyFreq(freq, processedAt);

  // print out the histogram
  printf("%s scheduling algorithim efficency\n", algoName);
  printf("---------------------------------------------------\n");
  printf("Time to process |      Tracks      |\n");
  printf("----------------|------------------|\n");

  for (int i = 0; i < 10; i++) {
    printf("     %d0-%d9      | ", i, i);      // print the numbers that represent the bin
    printChars(freq[i],'*');           // print the number of stars that were in the bin
  }
}

/*
* Purpose - print out and display the final histogram that contains data from all
*           3 scheduling algorithims compared side by side per each bin
*
* Inputs -  efficency: contains a pointer to a struct that holds arrays which determine when each 
*          track was processed under each algorithim
*
* Outputs - prints the data in a vertical histogram
*/
void masterGraph(dataArrays* efficency) {

  // make 3 arrays for the frequnecy table of every bin
  int FIFOfreq[10];
  int SSTFfreq[10];
  int variableSSTFfreq[10];

  // initalize all the array elements to 0
  for (int i = 0; i < 10; i++) {
      FIFOfreq[i] = 0;
      SSTFfreq[i] = 0;
      variableSSTFfreq[i] = 0;
  }

  // fill each frequency array with values from the arrays from the pointer
  tallyFreq(FIFOfreq, efficency->processFIFO);
  tallyFreq(SSTFfreq, efficency->processSSTF);
  tallyFreq(variableSSTFfreq, efficency->processVariableSSTF);

  // print the histogram
  printf("Total disk scheduling algorithim efficency\n");
  printf("---------------------------------------------------\n");
  printf("Time to process |      Tracks      |\n");
  printf("----------------+-------------------\n");

  // loop through each index of the frequency arrays and print the results
  for (int i = 0; i < 10; i++) {
    printf("           FIFO | ");            // label
      printChars(FIFOfreq[i], 'F');          // data
    printf(" %d0-%d9     SSTF | ",i,i);      // label
      printChars(SSTFfreq[i], 'S');          // data
    printf("          vSSTF | ");            // label
      printChars(variableSSTFfreq[i], 'V');  // data
    printf("----------------|\n");           // seperates each bin visually
  }
}

/*
* Purpose: perform the FIFO scheduling algorithm given the track requests
*
* Inputs: requests - an array of ints, each represting a request to a specific track
*         len - the number of inputs in the request arrray
*
* Outputs: none
*/
void scheduleFIFO(int requests[], int len, dataArrays* efficency) {

  // array to track how long a track takes to process
  // since the range of requests is [0,99], each index of this array acts as the track number
  //  the value at an index is the amount of tracks passed before processing that track
  int timeToProcess[100];
  
  // initialze each cell to key number, like -1
  for (int i = 0; i < 100; i++) {
    timeToProcess[i] = -1;
  }
  
  int traversed = 0;    // total number of traversed tracks
  int prevTrack = 0;    // contains the previously processed track
  int currTrack = 0;    // contains the current track to be processed

  // loop to process each track from the requests array
  for (int i = 0; i < len; i++) {
    currTrack = requests[i];
    // the distance between two tracks is the absolute value of their difference
    traversed += abs(currTrack - prevTrack);

    // update the amount of time that it took to process the current track
    timeToProcess[currTrack] = traversed;

    // reassign the previous track for the next loop
    prevTrack = currTrack;
  }

  // print out how many tracks FIFO crossed overall
  printf("Under FIFO scheduling, the r/w arm crossed %d tracks\n", traversed);

  // graph the results
  graph(requests, timeToProcess, len, "FIFO");

  // copy the result array to struct for graphing all algos together
  for (int i = 0; i < 100; i++) {
    efficency->processFIFO[i] = timeToProcess[i];
  }
  
}

// swap and sort methods from:
// https://www.geeksforgeeks.org/bubble-sort/

/*
*  Purpose - swap the values at 2 pointers
*
*  Inputs - xp: pointer to an arbitrary x value
*           yp: pointer to an arbitrary y value
*
*  Outputs - none
*/
void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
*  Purpose - sort a given array in ascending order
*
*  Inputs - arr: the array to be sorted
*            n: the length of the array
*
*  Outputs - none, the input array is sorted
*/
void bubbleSort(int arr[], int n) {
    int i, j; // loop variables

    // loop over the length of the array - 1
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])  // if any element is greater than the element behind it
                swap(&arr[j], &arr[j + 1]);  // swap them
}

/*
* Purpose: perform the SSTF scheduling algorithm given the track requests
*
* Inputs: requests - an array of ints, each represting a request to a specific track
*         len - the number of inputs in the request arrray
*
* Outputs: none
*/
void scheduleSSTF(int requests[], int len, dataArrays* efficency) {

  // array to track how long a track takes to process
  // since the range of requests is [0,99], each index of this array acts as the track number
  //  the value at an index is the amount of tracks passed before processing that track
  int timeToProcess[100];

  int traversed = 0;  // total number of traversed tracks
  
  // initialze each cell to key number, like -1
  for (int i = 0; i < 100; i++) {
    timeToProcess[i] = -1;
  }
  
  // need to sort the requests in ascending order
  bubbleSort(requests, len);

  // since this algo starts from 0, the total traversed will be the highest track request
  traversed = requests[len-1];

  // the time to process each track is whatever the track number is
  for (int i = 0; i < len; i++) {
    timeToProcess[requests[i]] = requests[i];
  }

  // print out how many tracks SSTF crossed overall
  printf("Under SSTF scheduling, the r/w arm crossed %d tracks\n", traversed);

  // graph the results
  graph(requests, timeToProcess, len, "Static SSTF"); 

  // copy the result array to struct for graphing all algos together
  for (int i = 0; i < 100; i++) {
    efficency->processSSTF[i] = timeToProcess[i];
  }
}

/*
* Purpose: Find the next track closest to the current track for the SSTF algo
*
* Inputs: requests - an array of ints, each represting a request to a specific track
*         currIdx - the index of the location of the r/w head
*         len - the number of requests in the requests array
*
* Outputs: nextIdx - the index of the closest track to the currIdx
*/
int findNext(int requests[], int currIdx, int len){
  int nextIdx = 0;   // int to represent the index of the closest value to the value at currIdx
  int minDiff = 999;  // int to keep track of the smallest difference between the value at currIdx and the value at an arbitrary index

  // loop through all the requests
  for (int i = 0; i < len; i++) {

    // need to make sure that the track hasn't already been processed
    // need to make sure that the track is not the same as the currIdx, otherwise diff = 0
    if (requests[i] == -1 || i == currIdx) {
      continue;
    }

    // calculate the current difference of values at the two indices
    int currDiff = abs(requests[currIdx] - requests[i]);

    // if the current difference is less than the minimum difference, update the minimum difference and the index of that is closest to current index
    if (currDiff < minDiff) {
      nextIdx = i;
      minDiff = currDiff;
    }
  }

  return nextIdx; // return the closest index
}

/*
*    Purpose: Find the first track of the variable SSTF algo
*
*    Inputs: requests - array of the tracks to be processed
*            start - the starting location of the r/w head (not an index!)
*            len -  the number of tracks in requests
*            
*    Outputs: an int, representing the index of the track in requests closest to the             
*             starting position
*/
int findBeginningIdx(int requests[], int start, int len){
  int minDiff = 999;  // minimun differece to keep track of while making comparisons
  int nextIdx = 0;    // closest current idx to start value

  // loop over every track in requests to see which one is closest to the start
  for (int i = 0; i < len; i++) {
    int diff = abs(requests[i] - start);  // determine the difference between a track and the start
    
    // if the calculated difference is smaller than the current minimum difference
    if (diff < minDiff) {
      minDiff = diff;  // reassign the current minimun difference
      nextIdx = i;     // reassign the current next index
    }
  }
  return nextIdx;      // return the closest index to start
}

/*
*  Purpose: Perform a variable SSTF algo where the start is determined by user input
*
* Inputs: requests - an array of ints, each represting a request to a specific track
*         len - the number of inputs in the request arrray
*         startTrack - the location where the r/w head starts
*
*  Outputs: None
*
*/
void scheduleVariableSSTF(int requests[], int len, int startTrack, dataArrays* efficency) {
  // normally, the method input array "requests" can be used for the graphing method
  // since this algorithim modifies the input array, a copy needs to be made and passed to the graph method
  int requestsCopy[len];
  for (int i = 0; i < len; i++) {
    requestsCopy[i] = requests[i];
  }
  
  int currTrackIdx;    // int to keep track of the current index of the current track

  // int to keep track of the previous track index
  // function finds the closest track to wherever the r/w arm starts
  int prevTrackIdx = findBeginningIdx(requests, startTrack, len);

  // array to track how long a track takes to process
  // since the range of requests is [0,99], each index of this array acts as the track         number
  //  the value at an index is the amount of tracks passed before processing that track
  int timeToProcess[100];

  // initialze each cell to key number, like -1
  for (int i = 0; i < 100; i++) {
    timeToProcess[i] = -1;
  }

  // the start value for the traversed variable is however far the r/w head needed to move
  int traversed = abs(startTrack - requests[prevTrackIdx]);

  // the time to process the first track was however far the r/w head move
  timeToProcess[requests[prevTrackIdx]] = traversed;


  //loop through all track-1, since 1 track has already been processed
  for (int i = 0; i < len-1; i++) {

    // find the next closest track to the current track index
    currTrackIdx = findNext(requests, prevTrackIdx, len);

    // add how far the r/w head must move to process the curent track
    traversed += abs(requests[currTrackIdx] - requests[prevTrackIdx]);

    // update the amount of time that it took to process the current track
    timeToProcess[requests[currTrackIdx]] = traversed;

    // mark the previous track as -1, indicating it has already been used
    requests[prevTrackIdx] = -1;

    // update the previous track for next iteration of the loop
    prevTrackIdx = currTrackIdx;
  }

  // print out how many tracks variable SSTF crossed overall
  printf("Under variable SSTF scheduling, the r/w arm crossed %d tracks starting at %d\n", traversed, startTrack);

  // graph the results using the copied array
  graph(requestsCopy, timeToProcess, len, "Variable SSTF");

  // copy the result array to struct for graphing all algos together
  for (int i = 0; i < 100; i++) {
    efficency->processVariableSSTF[i] = timeToProcess[i];
  }
}

/*
* Purpose: generate random requests to each track, ensuring no duplicates are generated
* 
* Input:  numRequests - the number of requests to be generated
*         fp - a pointer to the file where the requests will be written
*
* Outputs: duplicates - the number of duplicates created by the random number generator to
*                       correct the requested number of tracks in main
*/
void inputGenerator(int numRequests, FILE *fp) {
  
  int containsNum[100];  // int (boolean) array to keep track of which numbers have been generated

  // initialze all cells to 0 (false)
  for (int i = 0; i < 100; i++) {
    containsNum[i] = 0;
  }
  
  // correct the number of requests if it is too large, and display a message to the user if so
  if (numRequests > 100) {
    printf("Number of requests too high, lowering to 99");
    numRequests = 99;
  }

  int numCreated = 0;    // keep track of the number of successful track creations

  // loop until we have created enough tracks
  while (numCreated < numRequests) {

    // generate a random number within the range of 0-99
    int x = rand() % 100;

    // if that number has already been generated, go to the next iteration of the loop
    if (containsNum[x]) {
      continue;
    }

    // if that number has not been generated, turn it to a string and write to the file
    
    char* num = malloc(sizeof(int)*2);   // allocate space for a string to hold 2 ints
    sprintf(num, "%d", x);               // convert the integer to a string
    fprintf(fp, "%s\n", num);            // print that number to the file with a newline
    containsNum[x] = 1;                  // update the list of generated numbers
    numCreated++;                        // increment the number of track requests made
    } 
  }

/*
* Purpose - Simulate the effectiveness of the FIFO and SSTF disk scheduling algorithms
*
*  No inputs
*
*  No outputs
*/
int main(void) {
  srand(time(NULL));    // optional seed to control repeatability of track requests
  FILE *fp;             // file pointer where track requests are stored
  int length;           // the number of requests created (INPUT)
  int start;            // the starting position of the variable SSTF algo (INPUT)
  dataArrays* algos = malloc(sizeof(dataArrays)); // struct with arrays store how long each track took to process 

  // initialize all the arrays to 0
  for (int i = 0; i < 100; i++) {
      algos->processFIFO[i] = 0;
      algos->processVariableSSTF[i] = 0;
      algos->processSSTF[i] = 0;
  }

  // open a file to write track requests to
  fp = fopen("trackRequests.txt","w+");

  // get input for the number of requests to generate
  printf("Please enter how many input requests to generate: \n");
  if (scanf("%d", &length) != 1) {
    printf("Error");
    return 0;
  }

  // generate the track requests and store them on a file
  inputGenerator(length, fp);

  rewind(fp);    // reset to top of the file
  
  // pointer to store track requests from the file
  char* track = malloc(sizeof(int)*2);

  // initialze an array to hold all the track requests
  // this variable is passed to each algo
  int tracks[length];
  
  int idx = 0;    // loop variable

  // read through the file, populate the tracks array with requests as generated in the file
  while (fgets(track, sizeof(int)*2, fp) != NULL) {
    tracks[idx] = atoi(track);    // convert each request to int and update the array
    idx++;
  }
  
  scheduleFIFO(tracks, length, algos);    // perform the FIFO algo

  scheduleSSTF(tracks, length, algos);    // perform the SSTF algo starting at 0

  // get input where where SSTF should start
  printf("Please enter a starting position for SSTF: \n");
  if (scanf("%d", &start) != 1) {
    printf("Error");
    return 0;
  }

  // perform SSTF algo with input as starting location
  scheduleVariableSSTF(tracks, length, start, algos);    

  // create the histogram that compares all 3 algorithims
  masterGraph(algos);

  // close the file
  fclose(fp);
  return 0;
}