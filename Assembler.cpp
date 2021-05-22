#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <math.h>
#include <vector>
using namespace std;
//----------------------------------------Global declarations------------------------------------------------------------------

string C_Instructions[44] = {"0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D", "D&A", "D|A", "M", "!M", "-M", "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M", "NULL", "M", "D", "MD", "A", "AM", "AD", "AMD", "NULL", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
string C_Values[44] = {"101010", "111111", "111010", "001100", "110000", "001101", "110001", "001111", "110011", "011111", "110111", "001110", "110010", "000010", "010011", "000111", "000000", "010101", "110000", "110001", "110011", "110111", "110010", "000010", "010011", "000111", "000000", "010101", "000", "001", "010", "011", "100", "101", "100", "111", "000", "001", "010", "011", "100", "101", "110", "111"};
string Table_23[23] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};
string Values_23[23] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "0", "1", "2", "3", "4", "16384", "24576"};
int Variables = 16;
std::vector<string> myvector;
std::vector<int> my2ndvector;

static int TotalLines = 0;

//-------------------------------converting decimal into binary using recursion-------------------------------------------------

string decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];
    stringstream num;
    // counter for binary array
    int i = 0;
    while (n > 0)
    {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        num << binaryNum[j];
    string ret;
    num >> ret;
    return ret;
}
//----------------------------------------removing spaces function------------------------------------------------------------

string RemoveSpace(string s)
{
    string str = "";                                    //initialize the empty string
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ' && s[i] != '\t')
            str.push_back(s[i]);                        //If the code contains any spaces or tab characters they will be removed
    }
    return str;
}

//------------------------------------------C_Code------------------------------------------
string C_Code(string s)
{
    string out7Bits;                                    //C-inst consist of 7 bits
    for (int i = 0; i <= 17; i++)
    {
        if (s == C_Instructions[i])                     //this for loop will check if the computation have 1st number 0
        {
            return out7Bits = "1110" + C_Values[i];     //if found value then simply concatinate 6bits with 4 extra bits
        }
    }
    for (int i = 18; i <= 27; i++)                      //this for loop will check if the computation have 1st number 1
    {
        if (s == C_Instructions[i])
        {
            return out7Bits = "1111" + C_Values[i];     //found value add 4 extra bits containig 1 op code
        }
    }
    return "Error! computation is not in the table";    //if comp is not in the range 0-27 then it is not valid
}
//----------------------------------------------Dest_Code----------------------------------------
string D_Code(string s)
{
    string out3Bits;                                    //output is 3 bits
    for (int i = 28; i <= 35; i++)                      //if dest variable value is present then
    {                                                   //simply assign out3Bits varibale that value
        if (s == C_Instructions[i])
        {
            return out3Bits = C_Values[i];
        }
    }
    return "Error! Destiation is not in the table";     //if dest is not in the range 28-35 then it is not valid
}
//------------------------------------------------Jump code----------------------------------------------
string J_Code(string s)
{
    string out3Bits;                                    //jump has 3 bits
    for (int i = 36; i <= 44; i++)                      // check if jump variable has value in this array
    {
        if (s == C_Instructions[i])
        {
            return out3Bits = C_Values[i];              //if it is present then simple store its equivalent value in
        }                                               //the variable out3bits and return
    }
    return "Error! Jump is not in the table";           //if jump is not in the range 36-44 then it is not valid
}

//---------------------------A-instruction function for converting into binary------------------------

string functionForA(string s)                           //this function used the recursive func to
{                                                       //convert the decimal into binary and then
    long number;
    int result;                                         //it completes total 16 bit code and return it
    string Bit_16, output16bit;
    number = stoi(s);                                   //converting string to int number
    Bit_16 = decToBinary(number);                       //converting decimal to binary
                                                        //convert the int to string
    //completing 16bits:
    if (Bit_16.length() < 16)                           //let assume if binary of 2 is 10 then this if condition
    {                                                   //will completes the 16bit code by adding 16-2 zeros
        int count = 16 - Bit_16.length();
        string chArray;
        chArray = '0';
        for (int i = 0; i < count - 1; i++)             //adding zeros 16-binary.size() times
        {
            chArray = chArray + '0';
        }
        output16bit = chArray + Bit_16;
    }
    return output16bit;
}

//------------------------------//C-instruction function ⚡------------------------------------

string functionForC(string s)
{
    string comp, dest, jump, Bits_16;
    //checking what is present and what is not in instruction:
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<destination 🏠>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    string delimeter_d = "=";
    int check_d = s.find(delimeter_d);                      //if = is present then there is destination
    if (check_d != -1)                                      //if true then there is destination and we have to filter its value
    {
        dest = s.substr(0, s.find(delimeter_d));            //if dest present then it must be from 0 to =
    }
    else
    {
        dest = "NULL";                                      //if = not present then simply store null in dest
    }

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  jump  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    string delimeter_j = ";";                               //if there is ; then there is jump condition present
    int check_j = s.find(delimeter_j);                      //finding the ; from string s
    if (check_j != -1)                                      //if present int check_j should be -1
    {
        jump = s.substr(s.find(delimeter_j) + 1, s.find(delimeter_j) + 3); //filtering from
    }                                                                      // after the ; till next 3 ch because all jump statements are of legnth 3
    else
    {
        jump = "NULL";                                      //if no ; then simply store null in jump variable
    }

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< computation 🤸‍♂️ >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    if (check_j != -1)                                      //there is no delimeter in computation part because it can never be null
    {
        if (check_d != -1)                                  //if jump and dest is present then the comp is from after = till ;
        {
            comp = s.substr(dest.size() + 1, s.find(delimeter_j) - 2);
        }
        else
        {
            comp = s.substr(0, s.find(delimeter_j));        //if jump present and dest not then filter from 0 to ;
        }
    }
    else if (check_d != -1)                                 //if jump is not present and dest is present then filter
    {                                                       //from after = to till end or sixe of string
        comp = s.substr(dest.size() + 1, s.size());
    }
    //  << "destination is " << dest << endl;
    //cout << "computation is " << comp << endl;
    //cout << "jmp is " << jump << endl;
    Bits_16 = C_Code(comp);                                 //C_code retunrs the 10 bits string with 1 bit opcode and 6 for computation 3 are allways 1
    Bits_16 = Bits_16 + D_Code(dest);                       //concatinate the 10 bits with the 3 bits of dest
    Bits_16 = Bits_16 + J_Code(jump);                       //concatinate the 13 bits with 3 bits of jump
    return Bits_16;                                         //return the 16 bits number which we can write into file later on
}

//-----------------------------------------------main func()-----------------------------------------------------

int main()
{
    string filename;
    cout << "Enter the File name : ";                   //open the appropriate file
    cin >> filename;
    filename = filename.substr(0, filename.find('.'));  //if you enter test.asm this instruction filter it to test
    string hack;
    hack = filename + ".hack";                          //filtered test+.hack makes test.hack
    //cout << hack << endl << filename;
                                                        //reading the asm file 👍
    fstream assemblyFile, outputFile;                   //.asm and hack files
    assemblyFile.open(filename + ".asm", ios::in);
    outputFile.open(hack, ios::out);
    while (!assemblyFile.eof())                         //will run till end of file
    {
        char ch;                                        //character by character data to char ch 
        assemblyFile >> ch;
        //for ( instructions
        if (ch == '(')                                  //this is 1st parsing if () occurs it simply add it to vector
         {
            string temp;
            getline(assemblyFile, temp);
            temp = RemoveSpace(temp);                   //RemoveSpace func removes all spaces
            temp = temp.substr(0, temp.size() - 1);
            myvector.push_back(temp);                   //pushing to vectot

            //for lines
            my2ndvector.push_back(TotalLines);          //This vector is int vector storing line numbers
        }
        else if (ch == '/')
        {
            string str;
            getline(assemblyFile, str);                 //if comment occurs it simply ignore the whole line
        }
        else if (ch == '@')
        {                                               //if @ occurs it simply count line and add 1
            string str;
            getline(assemblyFile, str);
            TotalLines++;
        }
        else
        {
            string str;                                //else means if it is a C instruction just count the line
            getline(assemblyFile, str);
            TotalLines++;
        }
        //cout << "OOppa =>" << TotalLines << endl;     
    }
    assemblyFile.close();                               //close the file and again open it
    //opening again
    assemblyFile.open(filename + ".asm", ios::in);      //now open it again
    if (!assemblyFile || !outputFile)
    {
        cout << "Files are not present";                //throws an error if file opening failed
    }
    else
    {
        while (!assemblyFile.eof())                     //it runs till end of file
        {
            char ch;                                    //initialixing single character
            //For A instruction
            assemblyFile >> ch;                         //data is going character by character into ch variable
            if (ch == '@')                              //this if condition checks wheter it is A ins or not as all A instructions starts with @
            {
                string line, output16bit, delimeter_A;
                string temp;
                int tempint;
                //checking if it is predefined symbol or not 👍
                getline(assemblyFile, line);
                line = RemoveSpace(line);             //after getting the whole number as string we used  RemoveSpace func for removing spaces
                delimeter_A = "/";                    //This delimeter will help in finding the inline comments
                int check_A = line.find(delimeter_A); //checking if inline comments present or not
                if (check_A != -1)                    //true if there is any inline cmnt
                {
                    line = line.substr(0, line.find(delimeter_A)); //line var stores the string from 0 to '/' where the comment begins
                }
                for (int i = 0; i <= 23; i++)       //start loop 23 times so it checks whether the @ after string is in table or not
                {
                    if (line == Table_23[i])
                    {
                        temp = Values_23[i];
                        line = temp;
                        goto LABEL;                 //if found simply goto label i can also copy paste the label code and return but i'm lazy,  
                    }
                }
                //if not in table then check if it is number
                if (line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9')
                {
                    goto LABEL;                    //if a number occurs after @ just goto label , i can also copy paste the code and return but i am lazyyyyyyyyy.      
                }

                for (int i = 0; i < myvector.size(); i++)
                {
                    if (line == myvector[i])        //now if it is not in table and not a number then check if it is in vector (symbol)
                    {
                        tempint = my2ndvector[i];
                        stringstream ss;
                        ss << tempint;
                        ss >> temp;
                        line = temp;
                        goto LABEL;               // //if found simply goto label i can also copy paste the label code and return but i'm lazy  
                    }
                }

                //symbols
                myvector.push_back(line);
                my2ndvector.push_back(Variables);
                line = to_string(Variables);
                Variables++;
            LABEL:
                output16bit = functionForA(line);                   //FuncForA function Converts the decimal code into binary and returns a 16bits string

                                                                    //storing 16 bits answer into output file:
                outputFile << output16bit << endl;                  //writing the A instruction 's code into file
                TotalLines++;
            }
            //For comments ⚓ and ( conditions
            else if (ch == '/' || ch == '(')
            {
                string comment;
                getline(assemblyFile, comment);                     //if line starts from '/' which we know is a comment we store the whole line into a trash variable
            }
            //For C instruction ✈️
            else if (ch != '/' && ch != '@' && ch != '(')           //if ch is not @ and / then the instruction is C-inst
            {

                string line, output16bit, delimeter_C, temp;
                delimeter_C = "/";                                  //checking for inline comments
                getline(assemblyFile, line);
                line = RemoveSpace(line);                           //removing the spaces by RemoveSpace func
                int check_C = line.find(delimeter_C);
                if (check_C != -1)                                  //if int value of check_C is -1 this means that inline comment occurs
                {
                    line = line.substr(0, line.find(delimeter_C)); //storing from 0 to '/' (from where comment begins)
                    line = ch + line;                              //adding ch to line becoz the first character which was not @ and / was stored in ch variable and we want it
                }
                else
                {
                    line = ch + line;                             //adding ch to line becoz the first character which was not @ and / was stored in ch variable and we want it
                }
                output16bit = functionForC(line);                //FuncforC function will convert the C inst to its equivalant code hence giving a 16bit output
                                                                 //storing 16bits to the file ;
                outputFile << output16bit << endl;               //wtiting data to file
                TotalLines++;
            }
        }

        outputFile.close();   //closing the files
        assemblyFile.close(); //closing the files
    }
    return 0;
}
