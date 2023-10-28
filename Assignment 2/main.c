//  main.c
//  prority_queue implementation using an unsorted, circular, doubly linked lists with a sentinel
#pragma GCC diagnostic ignored "-Wformat" // switches off format
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC optimise("", off)

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#define INIT - 128 // // The queue should utilize -128 to signify empty queue elements.
#define UNDERFLOW(0x80 + 0x01) // When a dequeue operation encounters an underflow, it should return -127 to indicate this condition
#define OVERFLOW 0x80 + 0x02
#define BADPTR(0x80 + 0x03)
#define PQLIMIT(unsigned long) 1.20E1

struct QElement // also called Node
{
  char key;
  unsigned long prio;
};

struct LElement {
  /*
   each element of a doubly linked list L is an object with an attribute element (having key and prio)
   and two other pointer attributes next and prev
   Given an element x in the list, x.next points to its successor in the linked list,
   and x.prev points to its predecessor.
   If x.pre == NIL, the element x has no predecessor and is therefore the first element, or head, of the list.
   If x.next == NIL, the element x has no successor and is therefore the last element, or tail, of the list.
   
   Note: Update the definitions to use a sentinel for checking the error conditions
   */
  struct QElement element;
  struct LElement * next, * prev;
};

struct DLLS {
  /*
   unsorted, circular, doubly linked list with a sentinel.
   If sentinel.next = sentinel , the list is empty.
   
   A list may have one of several forms. It may be either singly linked or doubly linked,
   it may be sorted or not, and it may be circular or not.
   
   If the list was sorted, the linear order of the list would correspond to the linear order of keys stored in elements of the list;
   the minimum element then would be the head of the list, and the maximum element would be the tail.
   
   In a circular list, the pre pointer of the sentinel of the list points to the tail, and the next pointer of
   the tail of the list points to the sentinel.
   */
  /*
   A sentinel is a dummy object that allows us to simplify boundary conditions.
   Wherever we have a reference to NIL in list code, we replace it by a reference to the sentinel,
   changing a regular doubly linked list into a circular, doubly linked list with a sentinel,
   in which the sentinel lies between the head and tail.
   */
  struct LElement * sentinel;

};

// PQ stands for priority queue
struct PQ {
  struct DLLS * L; // DLLS stands for doubly linked list with a sentinel
  unsigned long max_size, element_num; // element_num counts the number of elements in the queue
};
/*
 The procedure LIST-SEARCH(L, k) finds the first element with key k in list L by a simple linear search,
 returning a pointer to this element. If no object with key k appears in the list, then the procedure returns NULL.
 Takes linear time in the worst case to find an element.
 */
struct LElement * LISTSEARCH(struct DLLS * L, int k);

/*
 Given an element x whose key attribute has already been set, the LISTINSERT procedure “splices” x onto the
 front (aka head) of the linked list. Runs in constant time.
 */
void LISTINSERT(struct DLLS * L, struct QElement x);

/*
 The procedure LISTDELETE removes an element x from the linked list L. It must be given a pointer to x,
 and it then “splices” x out of the list by updating pointers. Runs in constant time.
 If we wish to delete an element with a given key, we must first call LISTSEARCH to retrieve a pointer to the element.
 [The caller may free the deleted element x]
 */
struct LElement * LISTDELETE(struct DLLS * L, struct LElement * x);

/*
 The procedure LISTDELETE_LAST removes the last element (the tail) from the linked list L.
 [The caller may free the deleted element x]
 */
struct LElement * LISTDELETE_LAST(struct DLLS * L);
/*
 iterate() walks through the sequence L and prints its elements in order.
 */
void iterate(struct DLLS * L);

void enqueue(struct PQ * pq, struct QElement e);
char dequeue(struct PQ * pq);
char dequeue_max(struct PQ * pq);
char find_max(struct PQ * pq);
struct PQ * build(unsigned long maxlen);
struct PQ * myQ;

struct LElement * LISTSEARCH(struct DLLS * L, int k) { // PENDING REVIEW~~~~~~~~~~
    struct LElement * x = NULL; // creates a empty list element
    
    if (!L) { // check to see if the list is NULL
        printf("empty list\n");
        return x;
        
    } else {
        if (!L -> sentinel) {
            x = NULL;
        }
        else {
            x = L->sentinel; // point x at head of list
            while (x->next != L->sentinel && x->element.key != k) // loop until back at head or you find key
            {
                x = x->next; // move to next element
            }
            if(x == L->sentinel){ // if you search the whole list and end up back at the sentinel then there is no key in the list
                printf("Key not in list\n");
                return x = NULL; // return null to signify missing key
            }
        }
    }
        return x; // return the element with matching key
    }

    // change the parameter profile. X should be of type struct LElement. X should be initialized
    // by the caller (within the enqueue() subprogram)
    void LISTINSERT(struct DLLS * L, struct QElement x) { // PENDING REVIEW
      struct LElement * new = NULL; //  CREATE A NEW LIST ELEMENT
      if (!L) // CHECK IF LIST IS NULL
        return;
      if (!(L -> sentinel)) // CHICK IF LIST HAS SENTINEL
        return;

      new->next = L->sentinel->next; // NEW ELEMENT POINTS TO PREVIOUS HEAD OF LIST
      L->sentinel->next->prev = new; // SET THE OLD HEAD PREV POINTER TO NEW ELEMENT
      L->sentinel->next = new; // SET SENTINEL NEXT POINTER TO NEW ELEMENT
      new->prev = L->sentinel; // SET NEW ELEMENT PREV POINTER AS SENTINEL
      new->element = x; // GIVE NEW ELEMENT THE VALUE OF X
    }
    
    // The parameter L is kept for compatibility. We are not using it. x must be freed by the caller.
    struct LElement * LISTDELETE(struct DLLS * L, struct LElement * x) {
      //If the order of the evaluation is from left to right, no problem. Otherwise, access to the null pointer is possible
      // Please fix this so NO pointer is accessed, if it is NULL
      if (x && x -> prev && x -> next) {
        x->next->prev = x->prev;
        x->prev->next = x->next;
      }
      return x;
    }

    struct LElement * LISTDELETE_LAST(struct DLLS * L) { // IN PROGRESS
      struct LElement * x = NULL;
      // Assuming that the expression is evaluated from left to right
      if (!L || !(L -> sentinel))
        exit(-1);
      x = // complete
        x -> prev -> next = //complete
        x -> next -> prev = // complete
        return x;
    }

    void iterate(struct DLLS * L) {
      struct LElement * x;
      if (!L || !(L -> sentinel))
        exit(-1);
      x = // Complete
        while ((x != NULL) && (x != L -> sentinel)) {
          printf("\n key %d and priority %d", x -> element.key, x -> element.prio);
          x = x -> next;
        }
    }

    // ---- Build ---- //
    struct PQ * build(unsigned long maxlen) { // COMPLETE
      struct PQ * pq = NULL;
      if ((maxlen > 0) && (maxlen <= PQLIMIT)) {
        pq = (struct PQ * ) malloc(sizeof(struct PQ));
        if (pq) {
          pq -> max_size = maxlen; // Complete;
          pq -> element_num = 0; // Complete;

          if (pq -> L = malloc(sizeof(struct DLLS))) {
            pq -> L -> sentinel = malloc(sizeof(struct LElement)); // Complete;
            if (pq -> L -> sentinel) {
              pq -> L -> sentinel -> next = pq -> L -> sentinel; // Points to itself when empty
              pq -> L -> sentinel -> prev = pq -> L -> sentinel; // Points to itself when empty
              pq -> L -> sentinel -> element.key = 0; // insignificant
              pq -> L -> sentinel -> element.prio = 0; // insifnificant
            } else {
              printf("\build()>> Could not allocate memory for the lists' sentinel - Bad pointer %x \n", BADPTR);
              return NULL;
            }
            // using a sentinel, eliminates the needs for the head (front) and tail (rear) pointers in a list structure
            //pq->L->head = NULL;
            //pq->L->tail = NULL;
          } else {
            printf("\build()>> Could not allocate memory for the queue's list - Bad pointer %x \n", BADPTR);
            return NULL;
          }
        } else {
          printf("\build()>> Could not allocate memory for the pririty queue - Bad pointer %x \n", BADPTR);
          return NULL;
        }

      } // we could add an else-clause to print an error message regarding invalid maxlen
      return pq;
    }
// ---- Enqueue ---- //
    void enqueue(struct PQ * pq, struct QElement e) { // COMPLETE
        if (pq == NULL) {
            printf("\nenqueue()>> Attempt to overflow the queue at %p was prevented.\n", pq);
        }
        // insert e into the list
        // create a new element
        struct LElement * newElement = (struct LElement * ) malloc(sizeof(struct LElement));

        if (newElement == NULL) {
          printf("\nenqueue()>> Memory allocation failed. Exiting.\n");
          exit(EXIT_FAILURE);
        }

        newElement -> element = e; // set NewElement to element provided

        // insert the element into the list
        struct LElement * selected = pq -> L -> sentinel -> next; // create a pointer to the elements after sentinel
        struct LElement * prev = pq -> L -> sentinel; // set prev pointer to sentinel

        while (selected != pq -> L -> sentinel && selected -> element.prio >= e.prio) { // select is goint to loop through until it finds a spot where the prio of e is 
          prev = selected;
          selected = selected -> next;
        }

        // Update pointers
        newElement -> next = selected;
        newElement -> prev = prev;
        prev -> next = newElement;
        selected -> prev = newElement;

        // Update element count
        pq -> element_num = pq -> element_num + 1;
    }
    // change to return a QElement
    char dequeue(struct PQ * pq) {
      char val = -1;
      // COMPLETE THE CODE HERE TO DO ALL THE FOLLOWING TESTINGS:
      // Checking pq must precede checking pq->L.
      // Also, pq->L->sentinel must be checked before accessing it
      // Always, check a pointer before dereferencing it.

      // COMPLETE THE CODE BELOW TO PREVENT UNDERFLOW OF THE QUEUE
      if ( // COMPLETE)
        {
          printf("\ndequeue()>> Attempt to underflow the queue was prevented.\n");
          return (char) UNDERFLOW;
        }
        struct LElement * ptr = LISTDELETE_LAST(pq -> L);
        if (ptr) {
          // COMPLETE
        }
      }
      return (char) val;
    }

    char dequeue_max(struct PQ * pq) {
      // COMPLETE THE DECLARATION OF DEQUEUE_MAX.
      // It should dequeue the element with the maximal priority. If several
      // elements with the same max priority exist, the element with the longest waiting time should be dequeued.
      // After dequeuing, the element should be deleted from the list and corresponding memory deallocated.
      if !(PQ->L->sentinel) {
        printf("empty list\n");
        return 0;
      }
      struct LElement * temp = pq->L->sentinel->next;
      struct LElement * max = pq->L->sentinel->next;
      char data = temp->element->key;

      while (temp->next != PQ->L->sentinel) {
          if (temp->next->element->prio >= temp->element->prio) {
            data = temp->next->element->key;
            max = temp->next;
          }
          temp = temp->next;
      }

      free(temp);
      max->next->prev = max->prev;
      max->prev->next = max->next;
      free(max);

      return data;
    }

    // main
    int main(int argc,
      const char * argv[]) {

      int test = PQLIMIT; // test contains the number of elements with which I want to test the creation of the PQ

      myQ = build(test);
      if (myQ == NULL) {
        printf("\nBadpointer. \n");
        exit(-1);
      }

      struct QElement e; // create a element

      for (int i = 0; i < test; i++) {
        e.key = rand() % 127;
        e.prio = rand() % 4;
        enqueue(myQ, e); // Contents of e are passed to enqueue() by-value and stored in myQ->L
        printf("After Enqueue(%d, %lu) counter takes %lu\n", e.key, e.prio, myQ -> element_num);
      }
      iterate(myQ -> L);
      enqueue(myQ, e);

      struct LElement * l = LISTSEARCH(myQ -> L, 25);
      if (l == NULL) {
        printf("\nBadpointer. \n");
      } else {
        if (l == myQ -> L -> sentinel)
          printf("\n We could not find k = %d in the Queue\n", e.key);
        else {
          printf("\n We found the list element containing %d at %p\n", l -> element.key, l);
        }
      }
      // Complete this section to dequeue the element that has the maximum priority. If several elements have the same max priority, then the element enqueued first should be dequeued.

      for (int i = 0; i < test; i++) {
        dequeue(myQ);
        printf("After Dequeue() -> the counter takes %lu\n", myQ -> element_num);
      }

      dequeue(myQ);

      printf("\n\nYou can store a maximum of %lu elements in your PQ (PQ->max_size), whereas max_size of a PQ is capped at PQLIMIT,"
        "which is currently set to %lu in your program.\n\n\n", myQ -> max_size, PQLIMIT);

      // free anything that was created with malloc!
      // Dont forget to free all elements of the list in myQ->L before freeing L->sentinel
      // Walk through the list and free all elements
      // Complete

      return 0;
    }
