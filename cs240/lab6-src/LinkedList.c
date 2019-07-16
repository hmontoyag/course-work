
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode *p;
	p = list->head;
	int exs = 0;
	while(p!=NULL){
	  if (p->value == value){
	    exs = 1;
	  }
	  p = p->next;
	}
	return exs;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode *p;
	p = list->head;
	ListNode *aux;
	int did = 0;
	while(p!=NULL){
	  if (p->value == value){
	    aux = p->next;
	    p->value = aux->value;
	    p->next = aux->next;
            did = 1;
	   }
	  p = p->next;
	 }


return did;

}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
       int did = 0;
       int count = 0;
       ListNode *p;
       p = list->head;

       while(p!=NULL){
         if (count == ith){
	    *value = p->value;
	    did = 1;
	  }
	  p = p->next;
	  count++;
        }

       return did;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	int did = 0;
	int count=0;
	ListNode *p;
	p = list->head;
	ListNode *aux;
	while(p!=NULL){
	  if(count == ith){
	    aux = p->next;
	    p->value = aux->value;
	    p->next = aux->next;
	    did = 1;
	   }
	   p = p->next;
	   count++;
	 }   
	return did;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int count = 0;
	ListNode *p;
	p = list->head;
	while(p!=NULL){
	  p = p->next;
	  count++;
	}
	return count;


}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
        FILE * fd = fopen(file_name,"w");
	  if(fd == NULL){
	    return 0;
	  }
	 ListNode *p;
	 p = list->head;
	 while(p!=NULL){
	   fprintf(fd,"%d\n",p->value);
	   p = p->next;
	 }
         fclose(fd);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
        list->head = NULL;
	FILE * fd = fopen(file_name, "r");
	if(fd==NULL) { return 0;}
	int c;
	char word[10];
	int wl;
	wl = 0;
	while((c=fgetc(fd))!=-1){
	  if(c!='\n'&&c!=' '&&c!='\t'&&c!='\r'){
	    word[wl] = c;
	    wl++;
	  } else {
	    word[wl] = '\0';
	    if(wl>0){
	      int f = atoi(word);
	      llist_add(list, f);
	     }
	     wl =0;
	     word[wl] = '\0';
	  }
	 }

	  if(wl>0) {
	    int k = atoi(word);
	    llist_add(list,k);
	  }
	 fclose(fd); 
         return 1;
	
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
        int pa = ascending;
	ListNode * n;
	ListNode * aux;
	int v;
	int count = 0;
	int size = llist_number_elements(list);
	n = list->head;
	int sort = 1;
do{
       sort = 0;
       n = list->head;
       count = 0;
	while(count!=size-1){
	  if (pa == 1){
	    aux = n->next;
	    if (n->value > aux->value){
	      v = aux->value;
	      aux->value = n->value;
	      n->value = v;
	      sort = 1;
	    }
	  }
	  if(pa==0){
	    aux = n->next;
            if(n->value < aux->value){
	      v= aux->value;
	      aux->value = n->value;
	      n->value = v;
	      sort =1;
	    }
	   }
         n = n->next;
	 aux=NULL;
	 count++;
        }
	}while(sort);
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
       ListNode *p;
       p = list->head;
       if(p==NULL){return 0;}
      ListNode *aux = p->next;
      list->head = aux; 
      * value = p->value;
       free(p);
       return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
    ListNode * p;
    p = list->head;
    if(p==NULL){return 0;}
    ListNode * ax;
    int count =0;
   int size = llist_number_elements(list); 
    while(count!=size-1){
     ax = p;
      p = p->next;
      count++;
    }
   
    *value=p->value;
    free(p);
    ax->next = NULL;
    
    return 1;


}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
    ListNode * p;
    ListNode * new;
    new = (ListNode*)malloc(sizeof(ListNode));

    p = list->head;
    new->next = p;
    new->value = value;
    list->head = new;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
   int size = llist_number_elements(list);
   int count = 0;
   ListNode *p;
   p= list->head;
   if(p==0){
     ListNode *new = (ListNode*)malloc(sizeof(ListNode));
     list->head = new;
     new->value = value;
     new->next=NULL;
     }
   while(count!=size-1){
     p = p->next;
     count++;
   } 
   ListNode *new;
   new = (ListNode*)malloc(sizeof(ListNode));
  p->next = new;
  new->value = value;
  new->next=NULL;
}


//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
   int size = llist_number_elements(list);
   int count = 0;
   ListNode * p;   
   int *e;
   while(count!=size){
     llist_remove_first(list,e);
     p = list->head;
     count++;
   }
   p = NULL;




}
