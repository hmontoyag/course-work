#include "DLList.h"

/**
 * @brief      Constructor for the DLList.
 */
DLList::DLList()
{
	/** @todo Write a constructor for a dllist. Check slides! **/

  head = new DLNode();
 
  head->next = head;
  head->prev = head;
}
/**
 * @brief      Destructor for the DLList.
 */
DLList::~DLList()
{
	/** @todo Clean up your mess! **/
	delete head;
}

/**
 * @brief      Print the DLList line by line.
 */
void DLList::print()
{
	/** @todo Print this list line by line **/

 DLNode * tmp = head->next;
 DLNode * flag = head;
 while(tmp!=flag){
   std::cout<<tmp->data<<std::endl;
   tmp=tmp->next;
 }
   
}

/**
 * @brief      Sort and print the list.
 * 
 * This function should sort and print the list.
 * Note: the actual list is NOT to be modified.
 * In other words, it should only *print* in a
 * sorted order, not actually sort the list.
 */
void DLList::printSorted()
{
	/** @todo Print a sorted copy of this list **/
	int stack[1000];
        int count = 0;
	DLNode * tmp = head->next;
	DLNode * flag = head;
	while(tmp!=flag){
	  stack[count] = tmp->data;
	  tmp=tmp->next;
	  count++;
	}
	int ns[count];
	int i;
	for(i=0;i!=count;i++){ ns[i]=stack[i];}
        int j;
	for(i=0;i!=count;i++){
	  for(j=0;j!=count-i-1;j++){
	    if(ns[j]>ns[j+1]){
	      int temp = ns[j];
	      ns[j] = ns[j+1];
	      ns[j+1] = temp;
	    }
	   }
	 }
for(i=0;i!=count;i++){
  std::cout<<ns[i]<<std::endl;}
}

/**
 * @brief      Add to the front of the list.
 *
 * @param[in]  data  Item to add to front.
 */
void DLList::insertFront(int data)
{
	/** @todo Insert to the front of the list **/
	DLNode * e = new DLNode();
	e->data = data;

	e->next = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
}

/**
 * @brief      Removes & stores the last element.
 *
 * The last element is removed and stored in the
 * referenced variable data.
 * 
 * @param      data  Thing in which we are storing the data.
 *
 * @return     True upon successful removal.
 */
bool DLList::removeLast(int & data)
{
	/** @todo Remove the last thing **/
	DLNode * tmp = head;
	data = tmp->prev->data;
	DLNode * aux = head->prev->prev;
	aux->next = head;
	head->prev = head->prev->prev;

	return true;
}

/**
 * @brief      Difference of two lists.
 *
 * @param      list  Subtrahend.
 *
 * @return     Returns a pointer to the difference.
 */
DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	/** @todo Implement this function **/
        DLNode * tmp1 = head->next;
        DLNode * flag1 = head;
	int stack1[100];
	int c1=0;
	while(tmp1!=flag1){
	  stack1[c1]=tmp1->data;
	  tmp1=tmp1->next;
	  c1++;
	}
	int s1[c1];
	int i, j;
	for(i=0;i!=c1;i++){ s1[i]=stack1[i];}
	//2
	DLNode * t2 = list.head->next;
        DLNode * f2 = list.head;
	int stack2[100];
	int c2=0;
	while(t2!=f2){
	  stack2[c2]=t2->data;
	  t2=t2->next;
	  c2++;
	}
	int s2[c2];
	for(i=0;i!=c2;i++){ s2[i]=stack2[i];}
        int ss[100];
	int is = 0;
	int c3=0;
	for(i=0;i!=c1;i++){
	 is = 0;
	  for(j=0;j!=c2;j++){
	    if(s1[i]==s2[j]){
	      is = 1;
	     }
	   }
	  if(is==0){
	    ss[c3] = s1[i];
	    c3++;
           }
	 }
	 int sss[c3];
	 for(i=0;i!=c3;i++){ sss[i]=ss[i];}
	 for(i=c3-1;i!=-1;i--){
	   std::cout<<sss[i]<<std::endl;
	 }

	return diff;
}

/**
 * @brief      Returns a sublist of items in a range.
 *
 * @param[in]  start  First index.
 * @param[in]  end    Second index.
 *
 * @return     Elements between first and second index.
 */
DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
	/** @todo getRange **/
	return range;
}

/**
 * @brief      Intersection of this list and another list.
 *
 * @param      list  The other list.
 *
 * @return     Elements list shares with this one.
 */
DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	/** @todo intersection **/
        DLNode * tmp1 = head->next;
	DLNode * flag1=head;
	int stack1[100];
	int c1=0;
	while(tmp1!=flag1){
	  stack1[c1]=tmp1->data;
	  tmp1=tmp1->next;
	  c1++;
	}
	int s1[c1];
	int i,j;
	for(i=0;i!=c1;i++){ s1[i]=stack1[i];}
	//2
	DLNode * t2 = list.head->next;
	DLNode * f2 = list.head;
	int stack2[100];
	int c2=0;
	while(t2!=f2){
	  stack2[c2]=t2->data;
	  t2=t2->next;
	  c2++;
	}
	int s2[c2];
	for(i=0;i!=c2;i++){ s2[i]=stack2[i];}
	int ss[100];
	int is = 0;
	int c3 = 0;
	for(i=0;i!=c1;i++){
	  is=0;
	  for(j=0;j!=c2;j++){
	   if(s1[i]==s2[j]){
	     is = 1;
	   }
	  }
	  if(is==1){
	    ss[c3] = s1[i];
	    c3++;
	  }
	 }
	 int sss[c3];
	 for(i=0;i!=c3;i++){ sss[i]=ss[i];}
	 for(i=0;i!=c3;i++){

	   std::cout<<sss[i]<<std::endl;
	 }

	return  inter;
}

/**
 * @brief      Removes nodes in the start-end range.
 *
 * @param[in]  start  First node.
 * @param[in]  end    Second node.
 */
void DLList::removeRange(int start, int end)
{
	/** @todo Remove a range of elements **/
}
