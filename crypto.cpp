#include <iostream>
#include <stdio.h>
#include <openssl/evp.h>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Crypto {
    private: 
        // stores the input key
        string key;

        // stores the iv
        // since iv need not be secret in CBC mode, we set it here to what we found worked best in testing
        string iv = "0000000000000000000000000000000";

        // stores input ctxt from file for use when decrypting
        string givenCtxt;

        // holds the ptxt to be encrypted
        string ptxt;

         // holds the ctxt created when encrypting
        unsigned char *ctxt;

        // hold the sized of the genrated ptxt or ctxt
        unsigned char *newPtxt;

        // holds the leght of the ptxt and the ctxt respecitvely
        int p, c;

    public:
        // handle encryption
        void enc(){
            // alocate 1kb for the cihpertext
            ctxt = (unsigned char *)malloc(1024 * sizeof(char));

            // set up encryption context
            EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();

            // initialize the context to use camellia cbc encryption with the given key and iv
            EVP_EncryptInit_ex(context, EVP_camellia_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

            // encrypt the ptxt and store in ctxt up to the length of ptxt, store length of ctxt in c
            EVP_EncryptUpdate(context, ctxt, &c, (unsigned char*)ptxt.c_str(), strlen((char *)ptxt.c_str()));

            // since padding is enabled by default, account for it in the ctxt in the case where ptxt is not exactly a multiple of block length
            EVP_EncryptFinal_ex(context, ctxt + c, &c);

            // free the context
            EVP_CIPHER_CTX_free(context);

            // notify user that ctxt file will be created
            cout << "Ciphertext file created as ctxt.txt" << endl;

            // create a ctxt.txt file and save ctxt to it
            ofstream ctxtFile("ctxt.txt");
            ctxtFile << ctxt;
            ctxtFile.close();
        }

        // handle decryption
        void dec(){
            // allocate space to hold the decrypted plaintext
            newPtxt = (unsigned char *)malloc(1024 * sizeof(char));

            // create a context for the decryption
            EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();

            // initiallize the camellia algorithm in the context for decryption
            EVP_DecryptInit_ex(context, EVP_camellia_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());
            
            // decrypt the ctxt and store in ptxt up to the length of ctxt and save the length of this decrypted ptxt in p
            EVP_DecryptUpdate(context, newPtxt, &p, (unsigned char*)givenCtxt.c_str(), strlen((char *)givenCtxt.c_str()));

            // account for padding / original ptxt not being a multiple of blocklength
            EVP_DecryptFinal(context, newPtxt  + p, &p);

            // free the context
            EVP_CIPHER_CTX_free(context);

            // diplay the decrypted plaintext
            cout << "Decrypted plaintext: " << newPtxt << endl;
        }

        // set the key value of the object
        void setKey(string k) {
            key = k;
        }

        // set the input plaintext of the object
        void setPtxt(string p){
            ptxt = p;
        }

        // set the input ciphertext of the object
        void setCtxt(string c){
            givenCtxt = c;
        }

};

int main(int argc, char* argv[]){

    // get mode of program either encryption or decryption (enc or dec) from command line
    string mode = argv[1];

    // get key from command line
    string key = argv[2]; 

    // strings for holding input ptxt, input ctxt (from file), and the name of the ctxt file
    string ptxt, ctxt, ctxtFileName;

    // create the program object
    Crypto cryptoObj;

    // check that the key is the correct length
    if(key.length() != 32){
        cout << "Error: key needs to be exacly 32 characters." << endl;
        return -1;
    }

    // set the key of the obj to the input key from command line
    cryptoObj.setKey(key);

    // check for mode and act accordingly
    // for encryption
    if(mode == "enc" || mode == "encrypt"){
        // ask user for message to encrypt
        cout << "Input message to encrypt: ";
        getline(cin, ptxt);

        // give the message to the object and encrypt
        cryptoObj.setPtxt(ptxt);
        cryptoObj.enc();
    }

    // for decryption
    else if(mode == "dec" || mode == "decrypt"){
        // ask user for the name of the file containing the ctxt
        cout << "Enter ciphertext file name: ";
        getline(cin, ctxtFileName);

        // read the ctxt in from the file
        ifstream ctxtFile(ctxtFileName);
        getline(ctxtFile, ctxt);

        // pass the ctxt to the object and decrypt
        cryptoObj.setCtxt(ctxt);
        cryptoObj.dec();
    }

    // for invalid mode input
    else{
        cout << "Error: Invalid mode detected." << endl;
        return -1;
    }

    return 0;
}