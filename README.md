# CryptoGroupProject
### Cryptography Group Project: Jacob Balin and Anthony Filippello
Demo video: https://oregonstate.zoom.us/rec/share/oFlEDzslsyYGbXlXTqmYjps0-mFsMDikOHszfJTUUSw2oMFlGf4MApoDb7gJrVQY.59cA9k2dDbLa8a6f?startTime=1647495179000 (Passcode: 3?.SKr@t)

## **Prerequisites**
To run this program you will need the folloing:
- Have OpenSSL installed and functional on your machine
- Capability of compiling with g++
- Linux is recomended
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
    
Note: replace the instances of <your_key> above with your 32 character key. I each case, follow the prompts from the program.

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
- Camellia: https://en.wikipedia.org/wiki/Camellia_(cipher)
- Feistel cipher: https://en.wikipedia.org/wiki/Feistel_cipher

## **Write up**
For this project we used OpenSSL to perform camellia encryption and decryption. In particular we used camellia with a 256 bit key. Becuase camellia is a Feistel cipher, and becuse we are using 256 bit keys, that means that the encryption is a 24 round Feistel cipher, meaning our encryption program is CCA secure. We are assuming that both parties (Alice and Bob) have the key ahead of time. When Alice runs the encryption function of our program, she is given a text file containing the ciphertext. She can then send that ciphertext to Bob however she likes (email, discord, etc.). Now that Bob has the ciphert text file, he can run the decryption function of our program to decrypt the ciphertex. Importantly, the only information being transfered over a network is the ciphertext file. That means that the only information Eve has access to is the ciphertext file. And since the encryption schemeis CCA secure, then Alice and Bob have successfully communicated securely. Thus, our encryption and decryption program is provably secure.

Thanks for a fantastic class and a fantastic term!
