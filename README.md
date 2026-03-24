# PROJECT-STRUKDAT-LIBRARY-SYSTEM

Context: The library is at peak season where lots of students are coming in borrowing and returning books. With the high traffic, this system is used to help lessen the burden on the librarian. 
Here we use: 
STACK for the return drop box, as the librarian can only get to one at a time to also ensure its being properly taken care of.
QUEUE for popular books that many students are reserving, first come first serve to be fair.
We also have a weekly recommendation shelf with a limited capacity and time. We have normal recommendations as well VIP recommendations.
DEQUEUE is used if the shelf gets too full or a book stays too long. VIP recommendations are put to the front for extra visibility.

IMPLEMENTATION
STACK (DROP BOX) - Uses a top index. When a book is returned, top moves up as books are piling up. When the librarian has processed it, top moves down.
Queue (WAITLIST) - Uses qfront and qback. Students join at the back and leave from the front.
Deque (RECOMMENDATION SHELF) - Starts in the middle of array so it can grow both ways. Standard books go to the right (dqr++). VIP books go to the left (dql--). Here, every time a command runs, the system checks timer - dqtime[dql]. If it's more than T, the oldest book is popped from the front.

INPUT
Input 3 numbers: 
N (total commands), 
K (shelf max size), 
T (max time allowed on shelf).

Then the commands:
1xx STACK / RETURNS
101 [BookName] : Drop a book in the box.
102 : Librarian processes the top book (checks waitlist).

2xx QUEUE / WAITLIST
201 [StudentName] [BookName] : Add a student to the waitlist.

3xx DEQUEUE / RECOMMENDATION SHELF
301 [BookName] : Add a regular recommendation.
302 [BookName] : Add a VIP recommendation to the front.

OUTPUT
When you process a return (102), the system checks the waitlist. If the names match, it prints a "Waitlist Match!" message. If not, it says the book is "Returned to shelf."
If the recommendation shelf gets too old or too crowded, it prints a message showing which book was kicked off.
At the very end, it prints the "Final Shelf" showing every book currently on display from left to right.




