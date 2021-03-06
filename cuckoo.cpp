// Assignment 4: Cuckoo Hashing algorithm
// XX YY ( YOU NEED TO COMPLETE YOUR NAME )
// An open addressing method called Cuckoo Hashing
// INPUT: an input file containing strings of characters, one string per line
// OUTPUT: a detailed list of where the strings are inserted.    

#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

// cuckoo tables' size                                                        
const int tablesize = 17;
// combine the two 1-dimensional table into one 2-dimensional table           
char  t[tablesize][2][255];

// compute the hash functions
size_t f(char*, size_t);

// place a string in one of the hash tables
bool place_in_hash_tables (char*);

int main() {

// the strings to be stored in the hash tables
char s[255]="";
char null_st[] ="";
size_t i, len;
bool placed;

// clear the tables
for(i=0; i< tablesize; i++) {
strcpy(t[i][0], null_st);
strcpy(t[i][1], null_st);
}

char filename[255] = "";

// display the header
cout << endl << "CPSC 335-x - Programming Assignment #4: ";
cout << "Cuckoo Hashing algorithm" << endl;

// read the strings from a file
cout << "Input the file name (no spaces)!" << endl;
cin >> filename;

// open the file for reading
FILE *file = fopen ( filename, "r" );
if ( file != NULL )
{
/* read line by line from the file */
while ( fgets ( s, 255, file ) != NULL ) {
// place null character at the end of the line instead of <return>
len = strlen(s);
s[len-2]='\0';
// insert the string in the cuckoo table
placed = place_in_hash_tables(s);
// check whether the placement was successful
if (!placed) {
cout << "Placement has failed" << endl;
return -1;
}
}
fclose ( file );
}
else
{
perror ( filename ); /* why didn't the file open? */
}
return 0;
}


bool place_in_hash_tables (char *s) {

bool placed;
size_t pos;
int index;
char temp_s[255], temp[255];

strcpy(temp_s, s);

// use a counter to detect loops
int counter = 0;

// start with table T1
index = 0;

placed = false;

pos = f(temp_s, index);

while((!placed ) && (counter < 2*tablesize)) {

if (strcmp(t[pos][index], "") == 0 ) {
// the entry at index <pos> in the <index> hash table is available so store the string <temp_s> there
cout << "String <" << temp_s << "> will be placed at";
cout  << " t[" << pos <<"][" << index << "]" << endl;
strcpy(t[pos][index], temp_s);
placed = true;
return placed;
}
else {
// the entry at index <pos> in the <index> hash table is not available so 
// obtain the string stored over there in variable <temp> and store the string <temp_s> there
// now the string <temp> needs to be placed in the other table
cout << "String <" << temp_s << "> will be placed at" << " t[" << pos;
cout <<"][" << index << "]" << " replacing <" << t[pos][index] << ">";
cout << endl;
// YOU NEED TO WRITE THE CODE TO STORE IN temp THE STRING STORED AT
// t[pos][index] AND STORE IN t[pos][index] THE STRING temp_s
    strcpy(temp, t[pos][index]);  //copy t[pos][index] into temp
    strcpy(t[pos][index], temp_s); //copy temp_s string into t[pos][index]
    strcpy(temp_s, temp);
// NOW temp_s CONTAINING THE EVICTED STRING NEEDS TO BE STORED  IN THE OTHER TABLE

// depend on the value of the index, we will decide
// index to T1 (index == 0) and applying f1 hash function
// or index  T2 (index == 1) and apply f2 hash function
    index = index ? 0 : 1;
    
    pos = f(temp_s, index); // calculate and store hash value of temp_s into pos
counter ++;     // go to the next string
}
}
return placed;
};

size_t f(char *s, size_t index) {
// compute the hash functions
// s is the string (the key) to which we apply the hash function
// index indicates which hash function will be used
// index == 0 means the first hash function
// index == 1 means the second hash function
  size_t po, len, i;
int val=0, temp;
po = 1;

len = strlen(s);
    
    
// f1 hashing function
if (index == 0) {

val = s[0];             // get the first element at s[0] storing into val
val = val % tablesize;  // bring the element into the proper range using modulo operator
if (val < 0) val += tablesize;  // if val < 0, then val = val + tablesize

// if the array only has 1 element, simply return it
if (len == 1) return val;
    
 // if array have more than 1 elements
for (i = 1; i < len; i++)  {
temp = s[i];    // get the current element and store into temp
po *= 31;       //multiply po by 31

po = po % tablesize;            //po is equal to remainder of po%tablesize
if (po < 0) po += tablesize;    //if po is less than 0, add tablesize to po

val += temp * po;               // val = val + temp * po
val = val % tablesize;          //val is equal to the remainder of value%tablesize

if (val < 0) val += tablesize;
}    
return val;
}
// f2 hashing function
else {
    
    val = s[len-1]; // get the previous element at s[len-1] storing into val
    val = val % tablesize; // bring the element into the proper range using modulo operator
    if(val <0) val += tablesize;  // if val < 0, then val = val + tablesize
   
    // if the array only has 1 element, simply return it
    if(len == 1) return val;
    // if array have more than 1 elements
    for (i = 1; i < len; i++) {
        temp = s[len-i-1]; // get the previous element then minus 1 and store into temp
        po *= 31;           //multiply po by 31
        
        po = po % tablesize; //po is equal to remainder of po%tablesize
        if (po < 0) po += tablesize; //if po is less than 0, add tablesize to po
        
        val += temp * po; // val = val + temp * po
        val = val % tablesize; //val is equal to the remainder of value%tablesize
        
        if (val < 0) val += tablesize; //if val is less than 0, add tablesize into value
    }
}
    
return val; //return value
}
