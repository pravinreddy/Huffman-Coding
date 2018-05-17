#include <iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
using namespace std;


// Tree data structure
typedef struct Node{
    string str;                              //to store the character in the string 
    int freq;                               //to store the frequency in the root node
    struct Node *left;                      //to store the left sub tree
    struct Node *right;                     //to store the right sub tree
}Node;



// Data structure for the characters in the queue
typedef struct elements{
    string a;
    int f;
    struct Node *n; 
}elements;

elements e[20];

int n;                                     //number of elements in the queue
static int totalvariablebits;			  //total number bits counter for variable length



/**
* Sorting the values into ascending order in the queue
*/

void sort(void){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(e[i].f > e[j].f){
                struct elements temp = e[j];
                e[j] = e[i];
                e[i] = temp;
            }
        }
    }
}

/**
* Insering the new computed value into queue
*/

void insert(string s, int tf, struct Node *nd){
    e[n].a = s;
    e[n].f = tf;
    e[n].n = nd;
    n=n+1;
    sort();
    
}

/**
* deleting the least two minimum values in the queue
*/
void mindelete(){
    for(int i=0;i<n;i++){
        e[i] = e[i+2];
    }
    n=n-2;
}



/**
 * this function helps gives number of bits requried for the elements to represent the all elements in list
*/
int numberofbits(int n){
    int x =0;
    int y =1;
    if (n==1){
        return 1;
    }
    while(y<=n){
        y = y*2;
        x++;
    }
    return x;
}

/**
 * This function helps to print the the fixed length huffman code for each element
 * we give 2 input parameters decimal value and number of bits
*/
void binaryconverter(int n, int k){
    int x=0;
    int z=k;
    int y=1;
    int a[k];
    while(k!=0){
        a[x]=n%2;
        n=n/2;
        x++;
        k--;
    }
    for(int i=z-1;i>=0;i--){
        cout<<a[i];
    }
}


/**
* printing the output of the varable length characters codes
*/
void printnode(struct Node *nd,int p[],int ptr){
    
    if(nd->str!="infinity"){
        for(int i=0; i<ptr; i++){
            cout<<p[i];
        }
        totalvariablebits = totalvariablebits + (nd->freq*ptr);
        cout<<"\t"<<nd->str<<endl;
    }
    
    if(nd->left != NULL){
        p[ptr] = 0;
        printnode(nd->left, p, ptr+1);
    }
    
    if(nd->right != NULL){
        p[ptr] = 1;
        printnode(nd->right, p, ptr+1);
    }
    
    
}


/**
* parsing the characters in the first line of the csv file
*/
int parse_char (string s, string p[])
{
  stringstream ss (s);
  string line[20];
  string name[2];
  string token;
  int i = 0;

  while (getline (ss, token, ','))
    {
      line[i] = token;
	  p[i]=line[i];
      i++;
    }
	return i;

}

/**
* parsing the frequencies of the characters and insert into array
*/

void parse_num (string s, int p[])
{
  stringstream ss (s);
  string line[20];
  string name[2];
  string token;
  int i = 0;

  while (getline (ss, token, ','))
    {
      line[i] = token;
	  p[i]= atoi(line[i].c_str());
      i++;
    }
}


int main(int argc, char *argv[])
{
	string s = argv[1];
	string c[20];
	int fre[20];
	ifstream myfile (s.c_str ());
	string str;
	getline (myfile, str);
	int n1 = parse_char(str, c);							//parsing the characters letters
	n = n1;
	c[0]=" "+c[0];
	getline (myfile, str);
	parse_num(str,fre);										//parsing the characters frequencies
	myfile.close();
    
    cout<<"Fixed length coding"<<endl;
    
    int bits = numberofbits(n1);							 //finds the number of bits needed for the fixed length coding
    int totalfixedbits = 0 ;
    
	//calculating the fixed length codes
    for(int i =0; i<n1; i++){
        binaryconverter(i,bits);
        totalfixedbits = totalfixedbits + (fre[i]*bits);
        cout<<"\t"<<c[i];
        cout<<endl;
    }
    
    cout<<"Total Fixed Length Bits = "<<totalfixedbits<<endl<<endl;
    
    for(int i=0; i<n1; i++){
        e[i].a = c[i];
        e[i].f = fre[i];
        e[i].n = NULL;
    }
	

    sort();

    
     
    for(int i=0; n>1; i++){
        struct elements temp1;
        struct elements temp2;
        struct Node *nd;
        nd = new Node();
        nd->left = new Node();
        nd->right = new Node();
        temp1 = e[0];
        temp2 = e[1];
        mindelete();
        nd->str = "infinity" ;											//assigning the infinity word as a node string if the node not a leaf node
        nd->freq = temp1.f + temp2.f;
		
		//check the node string is infnity or a original character to insert into right node
        if(temp1.a=="infinity"){
            nd->left = temp1.n;
        }else{
            nd->left->str = temp1.a;
            nd->left->freq = temp1.f;
        }
		//check the node string is infnity or a original character to insert into right node
        if(temp2.a=="infinity"){
            nd->right= temp2.n;
        }else{
            nd->right->str = temp2.a;
            nd->right->freq = temp2.f;
        }
        insert(nd->str,nd->freq,nd);									//inserting the new node after combining the two nodes
        
    }
    
    int p[10];
    int point=0;
    cout<<"Variable length coding"<<endl;
    printnode(e[0].n,p,point);
    
    cout<<"Total Variable Length Bits = "<<totalvariablebits<<endl;

    return 0;
}





