/*LIBRARY SYSTEM

input: number of commands,, shelf capacity,, time books can be in recommendation shelf before needing to be put away
1xx for RETURN, 101 return, 102 process
2xx for RESERVE, 201 reserve, 202 give
3xx for DEQUEUE, 301 add back, 302 remove front


--STACK: RETURN DROP BOX
To ensure books are handled carefully, books are returned and placed in a narrow box where the librarian can only access one at a time so as to make sure they are still in great condition
[push] the book into the drop box,, [pop] when processed,, if empty then print drop box empty

--QUEUE: RESERVE WAITLIST
As its peak season, many books are in high demand, to borrow one students need to reserve the book and be put in a waitlist
[reserve] student put in book list,, [give] assign book to next student

--DEQUEUE: WEEKLY RECOMMENDATIONS
The library has a weekly recommendations section where popular/underrated books are placed.
Theres a set amount of time where books can be placed there, and it can be removed once their 'old'.
VIP reccs are also put in front.


*/ //still has some mismatch logic with final



#include <stdio.h>
#include <string.h>

#define MAX 10001

//FOR RETURNS
char stack[MAX][30]; //row for books, char for title
int top = -1; //stack curr empty

//FOR RESERVE
char qname[MAX][30]; //person in queue
char qbook[MAX][30]; //persons book
int qfront = 0; //first in line
int qback = 0; //next person who joins,, last

//FOR WEEKLY RECS
char dqbook[MAX][30];
int dqtime[MAX]; //when book was added so can see if inbound
int dql = 5000; //dq left
int dqr = 5000; //dq right, middle of MAX so can move either left or right freely
int shelfcount = 0; //num of book in shelf

//add to stack
void returnbook(char *title) {
	if(top < MAX - 1) { //checking if curr top is smaller than last possible index
		top++; //possible, then add on top first for more space, then add new book
		strcpy(stack[top], title); //copy book title to top idx,, most recent
	}
}
//get top book from stack
char* pop() {
	if(top == -1) { //if still -1 still empty
		return NULL;
	} //otherwise
	
	return stack[top--]; //return top book then go down since LIFO
}
//add student to queue
void reserve(char *name, char *book) {
	if(qback < MAX) { //check for available space
		strcpy(qname[qback], name); //store name at end of line, since queue then will keep pushing forward
		strcpy(qbook[qback], book); //store title
		qback++; //move pointer to the added spot
	}
}
//DEQUEUE
void pushback(char *title, int time) { //for normal books going to recc shelf, no priority, so when theres vip book dont need to move all other books
	strcpy(dqbook[dqr], title); //copy title to back idx,, putting book from the back
	dqtime[dqr] = time; //setting what time it went in
	dqr++;
	shelfcount++;
}
//add book to shelf
void pushfront(char *title, int time) { //for vip book so dont need to push other books, jsut go to the left which is more front
	dql--;
	strcpy(dqbook[dql], title);
	dqtime[dql] = time; //saves time it was put in
	shelfcount++;
}
//remove oldest book
void popfront() {
	if(dql < dqr) { //since dql going left and dqr going right,, if dql still smaller then theres still books in middle
		printf("%s has been removed from recommendation shelf\n", dqbook[dql]); //taken from dql since front,, oldest book in queue
		dql++; //once removed go forward
		shelfcount--;
	}
}

int timer = 0;

int main() {
	
	int N, K, T; //num of cmds, shelf cap, time books can be on recc shelf
	int cmd;
	
	scanf("%d %d %d", &N, &K, &T);
	
	for (int i = 0; i < N; i++){ //start going thru all cmds
		timer++; //for every cmd it goes thru,, adds one time
		
		scanf("%d", &cmd);
		
		//RETURNS : STACK PUSH
		if(cmd == 101) {
			char title[30];
			scanf("%s", title);
			returnbook(title); //put in box,, this still waiting to be put in shelf properly
		}
		//PROCESS RETURN : POP N QUEUE CHECK
		else if(cmd == 102) { //starts getting put in shelf
			char *retbook = pop(); //get from top, does pop func and gives back address pop gives, puts in retbook container
			if(retbook == NULL) { //retbook holds address where book is getting put
				printf("Drop box empty\n");
			} else {
				
				//check if person in queue wants book
				if(qfront < qback && strcmp(retbook, qbook[qfront]) == 0) { //same logic as dql dqr
					printf("Waitlist Match! %s assigned to %s\n", retbook, qname[qfront]); //given to person at fornt of line
					qfront++; //remove person from queue, next
				} else {
					if (qfront < qback) { //same logic as dql dqr, then shows what person actually needs
						printf("Waitlist Check: %s needs %s. \n", qname[qfront], qbook[qfront]);
					}
					printf("%s returned to shelf\n", retbook);
				}
			}
		}
		//RESERVE : QUEUE
		else if(cmd == 201) {
			
			char name[30], book[30];
			scanf("%s %s", name, book); //person and book req
			reserve(name, book);
		}
		//ADD TO SHELF : PUSH BACK FOR NORM RECS
		else if(cmd == 301) {
			char title[30];
			scanf("%s", title);
			pushback(title, timer);
		}
		//ADD TO SHELF : PUSH FRONT FOR VIP RECS
		else if(cmd == 302) {
			char title[30];
			scanf("%s", title);
			pushfront(title, timer);
		}
		//REMOVE BOOKS OLDER THAN SET TIME ALLOWED ON SHELF
		while (dql < dqr && (timer - dqtime[dql]) >= T) { //curr time - time it was put in
			popfront(); //keep popping until oldest is still within range, from front since queue holds oldest in front
		}
		//REMOVE BOOKS IF OVER CAP
		while(shelfcount > K) {
			popfront(); //until matches K
		}
	} //end of N loop
	
	//OUTPUT TIMEE
	printf("Final Shelf: ");
	if(dql == dqr) {
		printf("Empty"); //if front and back idx same, empty shelf no other books in betweene
		
	} else {
		for(int i = dql; i < dqr; i++) {
			printf("%s \n", dqbook[i]); //print all remaining books
		}
	}
	printf("\n");
	
	return 0;
}










