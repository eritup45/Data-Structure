#basic
This program can store the data from the file or user, and store into the structure. The following is the type of the structure:
    struct data
    {
	char name[100],output[1024];
        int index;
    }
    #index is the index which the next name should insert, and it should not exceed the lenth of name.
    #name is for storing the name, and the maximun of the name could only be store in 100 characters.
    #output is for storing the string which is a combination of name. The maximun of the output could only be store in 1024 characters..
    #The program only can store 1000 data.

#function
There are four options which the user can choose:
    input "1": read the data from file whose name is "data.csv"
    input "2": user input the data for each name and index
    input "3": user input the pattern, and the program pop the pattern from the main string
    input "0": exit the program

#user mode
If the user choose the "2" of the option, the user can input "Enter" to finish input data when the user input the name.

When the user choose the "3" of the option, this program will use the KMP algorithm to pop the pattern from the main string. The program will output lps which is the failure function of the pattern, and output the string after removing the pattern.
