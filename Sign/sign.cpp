// Mikyla Wilfred mrw104

#include <iostream>
#include "sha256.h"
#include <iomanip>
#include <fstream>
#include "BigIntegerLibrary.hh"
#include <math.h>
#include <string.h>

using std::string;
using std::cout;
using std::endl;


BigInteger stringToBigInteger_mine(string postive_string){
    BigInteger x = 0;
    int length = postive_string.length();

    for (int i=0;i<length;i++) {
         x = x*10 + (int)postive_string[i];
    }
    return x;
}


int main(int argc, char *argv[])
{
char* files = "";
    if (argc == 2) files = argv[1];
else files = "";


if (argv[0] == "V" || argv[0] == "v"){

    if(files == "") files = "file.txt.signed";

    string x3;
    std::ifstream inFile3;
    inFile3.open(files);
    if (!inFile3) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    getline(inFile3, x3);
    string output1 = x3;
    BigInteger m2 = stringToBigInteger(output1);


    string file_string = "";
    while (inFile3 >> x3) {
        file_string += x3;
    }
    string file_string_ecrypt = sha256(file_string);
    BigInteger file_string_ecrypt_original = stringToBigInteger_mine(file_string_ecrypt);

    string x2;
    std::ifstream inFile2;
    inFile2.open("d_n.txt");
    if (!inFile2) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    getline(inFile2, x2);
    string file_string_d = x2;
    getline(inFile2, x2);
    string file_string_n = x2;

    BigUnsigned d = stringToBigUnsigned(file_string_d);
    BigUnsigned n = stringToBigUnsigned(file_string_n);
    BigInteger m = file_string_ecrypt_original;

    string x4;
    std::ifstream inFile4;
    inFile4.open("e_n.txt");
    if (!inFile4) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    getline(inFile4, x4);
    string file_string_e = x4;
    BigUnsigned e = stringToBigUnsigned(file_string_e);
    // Double checks
    BigUnsigned original = modexp(modexp(m, d ,n), e ,n) ;

    if (m2 == original) {cout << "This data is authentic.";}
    else  {cout << "This data is modified.";}

} else {

     if(files == "") files = "file.txt";

    //read in the file
    string x;
    std::ifstream inFile;

    inFile.open(files);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string file_string = "";

    while (inFile >> x) {
        file_string += x;
    }

    string output1 = sha256(file_string);

    //read in key
    string x2;
    std::ifstream inFile2;
    inFile2.open("d_n.txt");
    if (!inFile2) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string file_string_d = "";
    string file_string_n = "";
    getline(inFile2, x2);
    file_string_d = x2;

    getline(inFile2, x2);
    file_string_n = x2;

    BigUnsigned d = stringToBigUnsigned(file_string_d);
    BigUnsigned n = stringToBigUnsigned(file_string_n);
    BigInteger m = stringToBigInteger_mine(output1);
//encrypt file
    BigUnsigned encrypted = modexp(m,d,n);

//save to a signed file
        std::ofstream myfile;
        char* ext =  files;
        std::string str(ext);
        str += ".signed";
        const char *cstr = str.c_str();
        myfile.open (cstr);
        myfile << encrypted << "\n";
        myfile << file_string;
        myfile.close();
}
    return 0;
}


