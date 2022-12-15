/*  Author: Tomas Koci
    Date: 30.10.2022
    Name: IZP_Project_01
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 101
#define TooManyContacts -1
#define Toolong -2

const char Options[][5] = {{'0', '+'}, {'1'}, {'2', 'a', 'b', 'c'}, {'3', 'd', 'e', 'f'}, {'4', 'g', 'h', 'i'}, {'5', 'j', 'k', 'l'}, {'6', 'm', 'n', 'o'}, {'7', 'p', 'q', 'r', 's'}, {'8', 't', 'u', 'v'}, {'9', 'w', 'x', 'y', 'z'}};

typedef struct
{
    char name[MAXLEN];
    char phoneNumber[MAXLEN];
    bool print; // param determining whether the Contact is supposed to be printed
} Tkontakt;
/*getting a line from stdin and returning number of chars*/
int CustomGets(char str[], int maxlen)
{
    int c;
    int index = 0;
    while (((c = getchar()) != EOF) && (c != '\n'))
    {
        str[index] = c;
        if (c == '\r')
        {
            getchar();
            break;
        }
        if (index >= maxlen - 1)
        {
            return Toolong;
        }
        index++;
    }

    str[index] = '\0';

    if (c == EOF)
    {
        return EOF;
    }

    return 0;
}
// loads contacts and returns the number of them
int loadContacts(Tkontakt arr[])
{
    int len = 0;
    int err = 0;

    while ((err = CustomGets(arr[len].name, 100)) != EOF)
    {
        if (err == Toolong)
        {
            return Toolong;
        }

        err = CustomGets(arr[len].phoneNumber, 100);

        if (err == Toolong)
        {
            return Toolong;
        }
        if (err == EOF)
        {
            break;
        }

        arr[len].print = false;

        len++;
        if (len > 42) // bigger than the memory allocated for it
        {

            return TooManyContacts;
        }
    }
    return len;
}

void printContacts(Tkontakt arr[], int len)
{
    int counter = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i].print)
        {
            printf("%s, %s \n", arr[i].name, arr[i].phoneNumber);
            counter++;
        }
    }
    if (counter == 0)
    {
        printf("Not found \n");
    }
}

void toLowerAllContacts(Tkontakt arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        while (arr[i].name[j] != 0)
        {
            arr[i].name[j] = tolower(arr[i].name[j]);
            j++;
        }
    }
}

/*returns value of the index where the char was found in case it wasn't found returns -1*/
int searchCharInStringFrom(char value[], char searched, int from)
{
    for (int i = from; value[i] != '\0'; i++)
    {
        if (value[i] == searched)
        {
            // value[i] = toupper(value[i]); // just for checking we are finding right chars
            return i;
        }
    }
    return -1;
}

/*Just because normal atoi returns value of whole rest of the string same thing does strtol*/
int getCharVal(char val)
{
    return atoi(&val);
}
/*Func looking for substring in name only rule => characters have to be in same order*/
bool searchStringInName(char value[], char searched[])
{
    int from = 0;
    bool valid;
    for (int i = 0; searched[i] != '\0'; i++)
    {
        char currSearch;
        valid = false;

        int j = 1;
        while ((currSearch = Options[getCharVal(searched[i])][j]) != '\0') // for all options of the number
        {
            if ((from = searchCharInStringFrom(value, currSearch, from)) != -1) // if that currSearch is in (contact's name = value)
            {
                valid = true;
                from++;
                break;
            }

            else
            {
                from = 0;
            }
            j++;
        }
        if (!valid) // if we did not found any occurece of all the options of the number in the name
        {
            return false;
        }
    }
    return valid;
}

bool searchInNameNeighboring(char value[], char searched[])
{
    int first = 0;  // index of char from searhced found in value
    int second = 0; // index of char from searhced found in value
    bool consequent = false;
    for (int i = 0; searched[i] != '\0'; i++)
    {

        for (int j = 0; Options[getCharVal(searched[i])][j] != '\0' && !consequent; j++) // for all options of values of searhced
        {
            char sChar; // option of second char
            if (!consequent)
            {
                sChar = Options[getCharVal(searched[i])][j];
                first = searchCharInStringFrom(value, sChar, first);
            }
            if (searched[i + 1] == '\0' && first != -1)
            {
                return true;
            }
            while (first != -1 && !consequent)
            {
                first = searchCharInStringFrom(value, sChar, first + 1);
                if (first != -1)
                {
                    for (int k = 0; Options[getCharVal(searched[i + 1])][k] != '\0' && !consequent; k++) // for all options of seccond char
                    {
                        char s2Char = Options[getCharVal(searched[i + 1])][k];
                        while (!consequent && ((second = searchCharInStringFrom(value, s2Char, second + 1)) != -1)) // all occurences of second char
                        {
                            if (first + 1 == second && second != -1)
                            {
                                consequent = true;
                                first = second;
                                sChar = s2Char;
                            }
                        }
                    }
                }
            }
            if (!consequent)
            {
                first = 0;
                i = 0;
            }
        }

        if (!consequent)
        {
            return false;
        }
    }
    return consequent;
}

bool searchStringInPhoneNumber(char value[], char searched[])
{
    int from = 0;
    for (int i = 0; searched[i] != '\0'; i++)
    {
        if ((from = searchCharInStringFrom(value, searched[i], from)) != -1)
        {
            from++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool searchInPhoneNumberNeighboring(char value[], char searched[])
{
    int first = 0;  // index of char from searhced found in value
    int second = 0; // index of char from searhced found in value
    bool consequent = false;
    if (value[0] != '+')
    {
        first = searchCharInStringFrom(value, searched[0], first);
    }
    if (first == -1) // if there is not the first char in
    {
        return false;
    }
    else if (searched[1] == '\0') // we found all searched chars => it's only 1
    {
        return true;
    }
    for (int i = 1; searched[i] != '\0'; i++)
    {
        second = searchCharInStringFrom(value, searched[i], first + 1);
        if (second == -1)
        {
            consequent = false;
            break;
        }
        else if (second == first + 1)
        {
            first = second;
            consequent = true;
        }
        else
        {
            consequent = false;
            first = second;
            i--;
        }
        if (searched[i + 1] == '\0')
        {
            return true;
        }
    }
    return consequent;
}
/* Void function changing Contact's .print param based on the searched[] value*/
void searchInArr(Tkontakt arr[], int len, char searched[], bool needForNeighboring)
{
    if (!needForNeighboring)
    {
        for (int i = 0; i < len; i++)
        {
            if (searchStringInName(arr[i].name, searched) || searchStringInPhoneNumber(arr[i].phoneNumber, searched))
            {
                arr[i].print = true;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if ((searchInNameNeighboring(arr[i].name, searched)) || (searchInPhoneNumberNeighboring(arr[i].phoneNumber, searched)))
            {
                arr[i].print = true;
            }
        }
    }
}

// Checks arg if there are only numbers inside
bool checkArg(char arr[])
{
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (!(arr[i] >= '0' && arr[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    // Load Contacts and make them lower
    Tkontakt arr[42];
    int len;
    len = loadContacts(arr);

    // Checking for the length of arr
    if (len == Toolong)
    {
        printf("Some shinanigens happened when getting your data\n");
        return -100;
    }
    if (len == TooManyContacts)
    {
        fprintf(stderr, "You assigned too many contacts\n");
        return -100;
    }

    toLowerAllContacts(arr, len);

    // check if there are arguments(there's always the path therefore "<=1")
    if (argc <= 1)
    {
        for (int i = 0; i <= len; i++)
        {
            arr[i].print = true;
        }

        printContacts(arr, len);
    }

    else if (argc >= 4)
    {
        fprintf(stderr, "Too many arguments \n");
        return -100;
    }

    else if (strcmp(argv[1], "-s") == 0)
    {
        if (!checkArg(argv[2]))
        {
            fprintf(stderr, "Your search input is invalid \n");
            return -100;
        }
        char *searched = argv[2];
        //  printf("%d", getCharVal(searched[1]));
        searchInArr(arr, len, searched, false);
        printContacts(arr, len);
    }
    else
    {
        if (!checkArg(argv[1]))
        {
            fprintf(stderr, "Your search input is invalid \n");
            return -100;
        }
        char *searched = argv[1];
        searchInArr(arr, len, searched, true);
        printContacts(arr, len);
    }

    return 0;
}
