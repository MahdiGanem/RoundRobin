#include<stdio.h>  
#include<curses.h>  
#include <stdlib.h>
#include <stdbool.h>

void main(int argc, char* argv[])
{
	// initlialize the variable name 


	int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, *at, *bt, *temp, *nol, *temp_nol, *wtop, *temp_wtop, *is_started, *waitingTimeForLoop;
	char *loopArray;
	bool flag;
	float avg_wt, avg_tat;
	FILE *fp;
	char line[10];
	if(argc > 1){
		fp = fopen(argv[1], "r");
		if(fp == NULL){
			printf("Could not oen file\n");
		}
		NOP = atoi(fgets(line,10,fp));
	}
	else{
		printf(" Total number of process in the system: ");
		scanf("%d", &NOP);
	}
	
	at = (int*)malloc(sizeof(int)*NOP);
	bt = (int*)malloc(sizeof(int)*NOP);
	temp = (int*)malloc(sizeof(int)*NOP);
	nol = (int*)malloc(sizeof(int)*NOP);
	temp_nol = (int*)malloc(sizeof(int)*NOP);
	wtop = (int*)malloc(sizeof(int)*NOP);
	temp_wtop = (int*)malloc(sizeof(int)*NOP);
	is_started = (int*)malloc(sizeof(int)*NOP);
	waitingTimeForLoop = (int*)malloc(sizeof(int)*NOP);
	loopArray = (char*)malloc(sizeof(char)*NOP);
	y = NOP; // Assign the number of process to variable y  

	if(argc > 1){
		for (i = 0; i < NOP; i++)
		{
			//initialize parameters
			flag = true;
			wtop[i] = 0;
			temp_wtop[i] = 0;
			nol[i] = 0;
			temp_nol[i] = 0;
			waitingTimeForLoop[i] = 0;
			is_started[i] = 0;
			printf("\n Enter the Arrival and Burst time of gcc  Process[%d]\n", i + 1);
			printf(" Arrival time is: \t");  // Accept arrival time
			at[i] = atoi(fgets(line,10,fp));
			printf("%d\n",at[i]);
			while (flag) {
				printf("\nDoes Process[%d] include loop? (y/n) \t", i + 1);  // Accept arrival time  
				loopArray[i] = fgets(line,10,fp)[0];
				printf("%c\n",loopArray[i]);
				if (loopArray[i] == 'y') {
					flag = false;
					printf("\nDoes Process[%d] include loop? (y/n) \t", i + 1);  // Accept arrival time 
					wtop[i] = atoi(fgets(line,10,fp));
					printf("%d\n",wtop[i]);
					printf("\n Enter the number of loops: \t");  // Accept arrival time
					nol[i] = atoi(fgets(line,10,fp));
					printf("%d\n",nol[i]);
					temp_nol[i] = nol[i];
				}
				else if (loopArray[i] == 'n') {
					flag = false;
				}
				else {
					printf("\nthe input not valid try again");
				}
			}
			
			printf(" \nBurst time is: \t"); // Accept the Burst time 
			bt[i] = atoi(fgets(line,10,fp));
			printf("%d\n",bt[i]);
			temp[i] = bt[i]; // store the burst time in temp array 
		}
		// Accept the Time qunat  
		printf("Enter the Time Quantum for the process: \t");
		quant = atoi(fgets(line,10,fp));
		printf("%d\n",quant);
	}
	
	else{
		// Use for loop to enter the details of the process like Arrival time and the Burst Time  
		for (i = 0; i < NOP; i++)
		{
			//initialize parameters
			flag = true;
			wtop[i] = 0;
			temp_wtop[i] = 0;
			nol[i] = 0;
			temp_nol[i] = 0;
			waitingTimeForLoop[i] = 0;
			is_started[i] = 0;
			printf("\n Enter the Arrival and Burst time of gcc  Process[%d]\n", i + 1);
			printf(" Arrival time is: \t");  // Accept arrival time  
			scanf("%d", &at[i]);
			while (flag) {
				printf("\nDoes Process[%d] include loop? (y/n) \t", i + 1);  // Accept arrival time  
				scanf("%c", &loopArray[i]);
				scanf("%c", &loopArray[i]);
				if (loopArray[i] == 'y') {
					flag = false;
					printf("\n Enter the waiting time: \t");  // Accept arrival time  
					scanf("%d", &wtop[i]);
					printf("\n Enter the number of loops: \t");  // Accept arrival time  
					scanf("%d", &nol[i]);
					temp_nol[i] = nol[i];
				}
				else if (loopArray[i] == 'n') {
					flag = false;
				}
				else {
					printf("\nthe input not valid try again");
				}
			}


			printf(" \nBurst time is: \t"); // Accept the Burst time  
			scanf("%d", &bt[i]);
			temp[i] = bt[i]; // store the burst time in temp array  
		}
		// Accept the Time qunat  
		printf("Enter the Time Quantum for the process: \t");
		scanf("%d", &quant);
	}
	
	// Display the process No, burst time, Turn Around Time and the waiting time  
	printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
	
	
	int remainingTime;
	
	for (sum = 0, i = 0; y != 0; )
	{
		flag = false;
		remainingTime = 0;
		int lastIndex = i - 1;

		if (i == 0) {
			temp_wtop[y - 1] = wtop[y - 1];
		}
		else {
			temp_wtop[lastIndex] = wtop[lastIndex];
		}
		is_started[i] = 1;
		if (temp[i] + temp_wtop[i] <= quant && temp[i] > 0) // define the conditions   
		{
			sum = sum + temp[i] + temp_wtop[i];
			temp_wtop[i] = 0;
			remainingTime = temp[i];
			temp[i] = 0;
			count = 1;
		}
		else if (temp[i] > 0)
		{
			temp_wtop[i] = temp_wtop[i] - quant;
			if (temp_wtop[i] < 0) {
				temp[i] = temp[i] + temp_wtop[i];
				temp_wtop[i] = 0;
			}
			sum = sum + quant;
			count = 0;
		}
		else {//nothing change, sum the waiting time
			flag = true;
			int sumWaitingTime = temp_wtop[0];
			for (int z = 1; z < NOP; z++)
			{
				if (sumWaitingTime < temp_wtop[z]) {
					sumWaitingTime = temp_wtop[z];
				}
			}
			if (sumWaitingTime > quant) {
				sumWaitingTime = quant;
			}
			for (int z = 0; z < NOP; z++)
			{
				temp_wtop[z] = temp_wtop[z] - sumWaitingTime;
				if (temp_wtop[z] < 0) {
					temp_wtop[z] = 0;
				}
			}
			sum = sum + sumWaitingTime;
			waitingTimeForLoop[i] = waitingTimeForLoop[i] + sumWaitingTime;
		}
		for (int z = 0; is_started[i] != 0, z < NOP; z++)
		{
			if (z != i)
			{
				if (count == 1) {
					temp_wtop[z] = temp_wtop[z] - remainingTime;
				}
				else {
					temp_wtop[z] = temp_wtop[z] - quant;
				}

				if (temp_wtop[z] < 0) {
					temp_wtop[z] = 0;
				}
			}

		}
		if (temp[i] == 0 && count == 1)
		{
			if (loopArray[i] == 'y' && temp_nol[i] > 0) {
				temp_nol[i]--;
				temp_wtop[i] = wtop[i];
				temp[i] = bt[i];
			}
			else if (!flag) {
				y--; //decrement the process no.
				wt = wt + sum - at[i] - bt[i] * (nol[i] + 1) + waitingTimeForLoop[i];
				if (temp_nol[i] == 0) {
					wt = wt - bt[i] * (nol[i]) + nol[i] * wtop[i];
					printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i] * (nol[i] + 1) + waitingTimeForLoop[i]);
				}
				tat = tat + sum - at[i];
			}

		}
		if (i == NOP - 1)
		{
			i = 0;
		}
		else if (at[i + 1] <= sum)
		{
			i++;
		}
		else
		{
			i = 0;
		}
	}
	// represents the average waiting time and Turn Around time  
	avg_wt = wt * 1.0 / NOP;
	avg_tat = tat * 1.0 / NOP;
	printf("\n Average Turn Around Time: \t%f", avg_tat);
	printf("\n Average Waiting Time: \t%f\n", avg_wt);

}
