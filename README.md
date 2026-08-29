 About

This project is a simple implementation of the RC4 stream cipher in C++.

The program is designed to encrypt the contents of `file.txt` and write the encrypted data back to the same file. A separate decryptor program can then restore the original contents when the correct key is entered.

Files

encryptor.cpp – Encrypts file.txt using RC4.
decryptor.cpp – Decrypts file.txt and restores the original content.

How It Works

The program follows the main steps of the RC4 algorithm:

1. Read file.txt in binary mode.
2. Store the file contents in memory.
3. Ask the user to enter an encryption key.
4. Generate the RC4 keystream using KSA and PRGA.
5. XOR the file data with the keystream.
6. Write the encrypted data back to file.txt.
7. Use the decryptor with the same key to restore the original file.

The decryptor also checks whether the entered key is correct before restoring the file.

 How to Run

Place file.txt in the same folder as the program.

Run the encryptor:

The contents of file.txt will become encrypted binary data.

Then run the decryptor:


If the correct key is entered, the original contents of file.txt will be restored.

 Note

This project was created for a cybersecurity learning assignment to understand the RC4 stream cipher, file handling, key usage, and encryption/decryption processes.

RC4 is an old and insecure cipher and should not be used for protecting sensitive information in real-world applications.
