# 42_get_next_line
42 school get_next_line project

### Description
Need to make a function that reads next line from the file. At the first function call - need to return the first line, at the second call - the second line and etc. Functions to use : 
 * open - to open file and get the file descriptor
 * read - to read the fixed count of characters from file
 * close - to close file and file descriptor

### Realization
The main idea of the get-next-line realization is using the linked lists. After the reading of the text from the file we are need to create a new node of the linked list and save the readed data there.
The file is read until the \n character is encountered in the read data. After that, we collect all the characters from the list up to \n into a string and return them as the result of the function. Also, if we have a remainder after \n in the last node of the list, we need to store it in a static variable (for the next function call).

### Testing
  * [gnlTester](https://github.com/Tripouille/gnlTester) - to test project by test cases
  * [wallgrine](https://github.com/opsec-infosec/42-ValgrindContainer) - to check the memory leaks
