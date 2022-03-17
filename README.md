# CryptoGroupProject
Cryptography Group Project: Jacob Balin and Anthony Filippello

## **Prerequisites**
To run this program you will need the folloing:
- Have OpenSSL installed and functional on your machine
- Capability of compiling with g++
## **Compile**
To compile this program, please run the following command:
    ```
    g++ -o prog crypto.cpp -lssl -lcrypto
    ```

## **Run**
To do encryption run the following command:
    ```
    ./prog enc <your_key>
    ```

To do decryption run the following command:
    ```
    ./prog dec <your_key>
    ```
    
Note: replace the instances of <your_key> above with your 32 character key

## **Details**
- Your key must be exactly 32 characters long
- The same key that was used for encryption is necessary for decryption
- For decryption, you need a file that contains the cipherted which you will be asked for when running the program
- Running the encryption will create such a file named ctxt.txt
- Since the initialization vector does not need to be secret, we have it pre-set to 32 0's as that is what we found worked best through testing
## **Sources**
The resources we used to learn how to use OpenSSL and how to invoke OpenSSL libraries (in particular EVP) in out c++ program are as follows:
- OpenSSL: https://www.openssl.org/
- OpenSSL documentation: https://www.openssl.org/docs/man3.0/man7/crypto.html
- OpenSSL EVP: https://www.openssl.org/docs/man1.1.1/man7/evp.html
- OpenSSL WIKI EVP: https://wiki.openssl.org/index.php/EVP
