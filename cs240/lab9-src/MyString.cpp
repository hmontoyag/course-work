
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
  // Add implementation here
  int i=0;
  int cnt = 0;
  for(i=0;s[i]!='\0';i++){
    cnt++;
  }
  return cnt;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
  // Add implementation
   int a = slength(s);
  // Allocate memory for _s.
 _s = new char[a];

  // Copy s into _s
  int i =0;
  for(i=0;i!=a;i++){
    _s[i]=s[i];
  }
  _s[i]='\0';
 
  
 
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
  initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  *_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete [] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  // Add implementation here
  int a = slength(_s);
  // Make sure that i is not beyond the end of string
  if(a<i){
    return "";
  }
  // Allocate memory for substring
  

  // Copy characters of substring
  MyString sub;
  int j;
  for(j=0;j!=n;j++){
    sub._s[j]=_s[i+j];
  }
  // Return substring
  return sub._s;
}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
  // Add implementation here
   int a = slength(_s);
  // If i is beyond the end of string return
   if (i>a){return;}
  // If i+n is beyond the end trunc string

  // Remove characters
  int j;
  int k;
  for (j=0;j!=n;j++){
   for(k=i;k!=a;k++){
     _s[k] = _s[k+1];
   }
 }
 _s[a-n]='\0';
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
  // Add implementation here
  int ol = slength(_s);
  int sl = slength(s._s);
  if(sl!=ol){return false;}
  int i;
  int equal = 1;
  for(i=0;i!=ol;i++){
    if(_s[i]!=s._s[i]){
      equal = 0;
    }
  }
  if(equal==1){
    return true;
  }
  return false;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
  int ol = slength(_s);
  int sl = slength(s._s);
  if(sl!=ol){return true;}
  int i;
  int equal = 1;
  for(i=0;i!=ol;i++){
    if(_s[i]!=s._s[i]){
      equal = 0;
     }
  }
  if(equal==0){return true;}
  return false;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
  // Add implementation here
  int ol = slength(_s);
  int sl = slength(s._s);
  int i;
  int equal = 0;
  if(ol>sl){return false;}
  if(sl>ol){return true;}
  for(i=0;i!=ol;i++){
    if(_s[i]>s._s[i]){ return false;}
    if(_s[i]<s._s[i]){ return true;}
  }
  return true;
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
  // Add implementation here
  if((_s<=s._s)==true){
    return false;
  }
  return true;
}

// Return character at position i.  Return '\0' if out of bounds.
char
MyString::operator [] (int i)
{
  // Add implementation here
  int a = slength(_s);
  if(i>a){return '\0';}
  char f;
  f = _s[i];
  return f;
}

// Return C representation of string
const char *
MyString::cStr()
{
  // Add implementation here
  
  return _s;
}

// Get string length of this string.
int
MyString::length() const
{
  // Add implementation here
  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  // Add implementation here
  delete [] _s;
}

// Concatanate twotrings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
  // Add implementation here
  int i;
  int len1 = 0, len2 = 0;
  for(i=0;s1._s[i]!='\0'; i++){ len1++;}
  for(i=0;s2._s[i]!='\0';i++) { len2++;}

  

  // Allocate memory for the concatenated string
 char * ss= new char[len1+len2];
 for(i=0;i!=len1;i++){
   ss[i]=s1._s[i];
  
 }
 int j;
 for(j=0;j!=len2;j++){
   ss[i+j]=s2._s[j];
 }
 MyString initialize(ss);
  // Add s1
    
  // Add s2

//  MyString s;
  return ss;
}

