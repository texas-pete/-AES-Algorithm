#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<unsigned int> cipherTextVector; //Vector variable used later in code 

string vigenere(string str, string key){  //code to encrypt via vigenere algorithm
    string cipherText;
    for(int i = 0; i < str.size(); i++)
    {
	int x = (str[i] + key[i]) %26;
        x +='A';
        cipherText.push_back(x);
    }
   return cipherText;
}

string generateKey(string str, string key){ //code to generate key that is equal in length to plain text 
    int x = key.size();
    for(int i = 0; ; i++)
    {
        if(x== i)
            i=0;
        if(key.size() == str.size())
            break;
        key.push_back(key[i]);
    
    }
    return key;
}

void stringToVector(string str){  //function to turn string into unsigned int vector 
    unsigned int index;
    for(unsigned int i=0; i< str.size(); i++)
    {
        if(!(str[i] >= 'A' && str[i] <= 'Z'))
        {
        
        }
        else{
            index = str[i];
            cipherTextVector.push_back(index); 
        }
    }
}


bool parity(unsigned int n){ //function to get parity of asci letter 
    bool parity = 0;
    while(n)
    {
        parity != parity;
        n = n & (n-1);
    }
    return parity;
}


int main(){

    string plainText, key; 

    ifstream myfile, myfile2;
    string fileLocation, fileLocation2;



    cout << "Type in input file please: " << endl;


    //get file location from user 
    getline(cin, fileLocation);


    //open the file 
    myfile.open(fileLocation);

    //ensure file opens 
    while(myfile.fail()){
        cout << "File at location " << fileLocation << " failed to open, try again: " << endl;
        getline(cin,fileLocation);
        myfile.open(fileLocation);
    }

    //extract file data 
    getline(myfile, plainText);
    myfile >> plainText;

  //replace punctuation with spaces in string
   for(auto &c : plainText)
   {
        if(ispunct(c))
        {
          c=' ';
        }
   }


   //delete spaces in string
   for(auto &c : plainText){
	if(isspace(c))
	{
	  c='\0';
	}
   }


 cout << "Type in key file please: " << endl;


    //get file location from user
    getline(cin, fileLocation2);


    //open the file
    myfile2.open(fileLocation2);

    //ensure file opens
    while(myfile2.fail()){
        cout << "File at location " << fileLocation2 << " failed to open, try again: " << endl;
        getline(cin,fileLocation2);
        myfile2.open(fileLocation2);
    }

    //extract file data
    getline(myfile2, key);
    myfile2 >> key;

  //replace punctuation with spaces in string
   for(auto &c : key)
   {
        if(ispunct(c))
        {
          c=' ';
        }
   }


   //delete spaces in string
   for(auto &c : key)
   {
        if(isspace(c))
        {
          c='\0';
        }
   }

 string output;

 string newkey = generateKey(plainText, key);

 string cipherText = vigenere(plainText, newkey);

 cout << "Type the name of the file you wish to output to: ";
 cin >> output;


ofstream myfile3(output.c_str());

 cout << "Preprocessing: " << plainText << endl;
 myfile3 << "Preprocessing: " << plainText << endl;
 cout << "Substitution: " << cipherText << endl;
 myfile3 << "Substitution: " << cipherText << endl;




//Pad the last block of text, if necessary 
 string strA = "A";

 while(cipherText.length() % 16 != 0)
 {
 	cipherText.append(strA);
 }
 

string cipherText3 = cipherText;


stringToVector(cipherText);

//Print the padded information in the correct format
cout << endl; 
cout << "Padding: " << endl; 
myfile3 << endl << "Padding: " << endl;
 for(int i = 0; i < cipherText.size(); i++)
 {
	if(i%4 == 0)
		cout << '\n';
	if(i%16 == 0)
		cout << '\n';

	cout << cipherText[i]; 
    myfile3 << cipherText[i];
 }

 cout << endl; 


 int rowIndex = 1;
 for(int i = 0; i< cipherTextVector.size(); i++)
 {
     if(rowIndex == 1){  //if in row 1
         rowIndex++;
         i+=3;          //move to next row 
     }
     else if(rowIndex == 2){ //if in row 2
        int temp1 = cipherTextVector[i];
        int temp2 = cipherTextVector[i+1];
        int temp3 = cipherTextVector[i+2];
        int temp4 = cipherTextVector[i+3];
                                                //Rotate the value indexes 
        cipherTextVector[i] = temp2;
        cipherTextVector[i+1] = temp3;
        cipherTextVector[i+2] = temp4;
        cipherTextVector[i+3] = temp1; 

        rowIndex++;
        i+=3;

     }
     else if(rowIndex == 3){ //if in row 3
        int temp1 = cipherTextVector[i];
        int temp2 = cipherTextVector[i+1];
        int temp3 = cipherTextVector[i+2];
        int temp4 = cipherTextVector[i+3];
                                                //Rotate the value indexes 
        cipherTextVector[i] = temp3;
        cipherTextVector[i+1] = temp4;
        cipherTextVector[i+2] = temp1;
        cipherTextVector[i+3] = temp2; 

        rowIndex++;
        i+=3;

     }
     else { //if in row 4
        int temp1 = cipherTextVector[i];
        int temp2 = cipherTextVector[i+1];
        int temp3 = cipherTextVector[i+2];
        int temp4 = cipherTextVector[i+3];
                                                //Rotate the value indexes 
        cipherTextVector[i] = temp4;
        cipherTextVector[i+1] = temp1;
        cipherTextVector[i+2] = temp2;
        cipherTextVector[i+3] = temp3; 

        i+=3;
        rowIndex = 1;
     }



 }

//Print the shifted/padded information in the correct format
 
 cout << endl; 
 cout << "ShiftRows: " << endl;
 myfile3 << endl << "ShiftRows: " << endl; 
 
 for(int i = 0; i < cipherTextVector.size(); i++)
 {
	if(i%4 == 0)
		cout << '\n';
	if(i%16 == 0)
		cout << '\n';

	cout << (char)cipherTextVector[i];
    myfile3 << (char)cipherTextVector[i]; 
 }

for(int i = 0; i < cipherTextVector.size(); i++)
{
    int temp = parity(cipherTextVector[i]); //temp is a 0 or a 1 depending on the parity of the current character

    if(temp == 1){ //if the number has odd parity, set significant bit to 1
        int x;
        x = x + 128;
        cipherTextVector[i] = x;
    }  
}

//Print values in hex
cout << endl; 
cout <<"Parity Bit: " << endl; 
myfile3 << endl << "Parity Bit: " << endl;

for(int i = 0; i < cipherTextVector.size(); i++)
 {
	if(i%4 == 0)
		cout << '\n';
	if(i%16 == 0)
		cout << '\n';

	cout << hex << cipherTextVector[i] << " ";
    myfile3 << hex << cipherTextVector[i] << " ";
 }

cout << endl; 

}
