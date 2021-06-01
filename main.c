#include "drb.h"
#include <string.h>
#define MAX 50
#define STMAX 69
#define schoolName "NIELIT"
#define DATABASEFILENAME ".StudentRawData.txt"
#define SESSION_FILENAME ".SessionLog.txt"
#define NULL_TXT "(null)"
int opt = -1;
/* Session Related Timing */
FILE *sessionsFile = NULL;
char *getDateTimeNow()
{
    time_t currentTime;
    char *currentTimeInString;
    currentTime = time(NULL);
    currentTimeInString = ctime(&currentTime);
    currentTimeInString[strlen(currentTimeInString) - 1] = '\0';
    return currentTimeInString;
}
/* DataBase Initialize */
FILE *dataBase = NULL;
void createFileTXT(char filename[])
{
    FILE *_tmpFILE = NULL;
    _tmpFILE = fopen(filename, "w");
    fclose(_tmpFILE);
}
int addNullFile(char filename[])
{
    FILE *_tmpFILE = NULL;
    _tmpFILE = fopen(filename, "w");
    fprintf(_tmpFILE, NULL_TXT);
    fclose(_tmpFILE);
    _tmpFILE = fopen(filename, "r");
    char _tempString[STMAX];
    if (strcmp(fgets(_tempString, STMAX, _tmpFILE), NULL_TXT) == 0)
        return 1;
    else
        return 0;
    fclose(_tmpFILE);
}
int checkFileTXT(char filename[])
{
    FILE *_tmpFILE = NULL;
    _tmpFILE = fopen(filename, "r");
    if (_tmpFILE == 0)
        return 0;
    fclose(_tmpFILE);
    return 1;
}
int checkSESSIONContents(char filename[])
{
    FILE *_tmpFILE = NULL;
    _tmpFILE = fopen(filename, "r");
    int fileChar = getc(_tmpFILE);
    char keyChar;
    while (fileChar != EOF)
    {
        if (fileChar != EOF)
            keyChar = fileChar;
        fileChar = getc(_tmpFILE);
    }
    fclose(_tmpFILE);
    _tmpFILE = NULL;
    if (keyChar == '-')
    {
        _tmpFILE = fopen(filename, "a");
        fprintf(_tmpFILE, " [ Unexpected Application ShutDown ]");
        fclose(_tmpFILE);
        return 1;
    }
    else
        return 0;
}

int intLen(long int data)
{
    if (data == 0)
        return data;
    return 1 + intLen(data /= 10);
}
void inpText(char textDP[], char mainArr[])
{
    printf("%s", textDP);
    for (int i = 0; i < 50; i++)
    {
        scanf("%c", &mainArr[i]);
        if (mainArr[i] == 10)
        {
            mainArr[i] = '\0';
            break;
        }
    }
}
void regexPhoneNumber(char dpText[], long int *phoneNumber)
{
L8:
    printf("%s", dpText);
    scanf("%ld", phoneNumber);
    if (intLen(*phoneNumber) > 10)
    {
        printf("Phone Number can only be upto 10 Digits\n");
        goto L8;
    }
}
void textTransform(char data[], int choice)
{
    /* 1 - LowerCase , 2 - UpperCase*/
    switch (choice)
    {
    case 1:
        for (int i = 0; data[i] != '\0'; i++)
        {
            if (data[i] >= 65 && data[i] <= 90)
                data[i] += 32; // LowerCase
        }
        break;
    case 2:
        for (int i = 0; data[i] != '\0'; i++)
        {
            if (data[i] >= 97 && data[i] <= 122)
                data[i] -= 32; // UpperCase
        }
        break;
    default:
        break;
    }
}
void CapitalizeText(char data[])
{
    if (data[0] >= 97 && data[0] < 123)
        data[0] -= 32;
    for (int i = 1; data[i] != '\0'; i++)
    {
        if (data[i] == 32)
        {
            if (data[i + 1] >= 97 && data[i + 1] < 123)
                data[i + 1] -= 32;
        }
    }
}

typedef struct r_Student
{
    char name[MAX];
    int rollno;
    long int phNo;
} student;

void internalAppendStu(student data[], int dataCount)
{
    scanf("%c", &data[dataCount].name[0]);
    inpText("Enter Student Name : ", data[dataCount].name);
    CapitalizeText(data[dataCount].name);

L7:
    printf("Enter Roll Number (Unique Number): ");
    scanf("%d", &data[dataCount].rollno);
    if (intLen(data[dataCount].rollno) > 5)
    {
        printf("Roll Number can only be upto 5 Digits\n");
        goto L7;
    }
    for (int i = 0; i < dataCount; i++)
    {
        if (data[i].rollno == data[dataCount].rollno)
        {
            printf("Roll Number already exists. Try again\n");
            goto L7;
        }
    }

    regexPhoneNumber("Enter Phone Number : ", &data[dataCount].phNo);
}

void AddMultipleStudents(student data[], int *dataCount)
{
    system("clear");
    printf("> %s Dashboard / AddStudent / Insert Multiple Students\n\n", schoolName);
    int insertNum = 0;
    printf("0. Go Back\n");
    printf("Enter the number of students to insert (remaining %d): ", STMAX - *dataCount);
    scanf("%d", &insertNum);
    if (insertNum == 0)
        return;
    for (int i = 0; i < insertNum; i++)
    {
        printf("\n%d.\n", i + 1);
        internalAppendStu(data, *dataCount);
        (*dataCount)++;
        printf("\n");
    }
}

void AppendStudents(student data[], int *dataCount)
{
    int appendSelect = 0;
    system("clear");
    printf("> %s Dashboard / AddStudent / Append Students\n\n", schoolName);
    printf("Remaining Students Left %d \n\n", STMAX - *dataCount);
    printf("0. Go Back\n1. Append\n\n->");
    scanf("%d", &appendSelect);
    if (appendSelect == 0)
        return;
    internalAppendStu(data, *dataCount);
    (*dataCount)++;
    printf("\n");
}

void InsertStudents(student data[], int *dataCount)
{
    int inpIndex = 0, numInsert = 0, _tempRoll = 0;
    char _tempName[STMAX];
    system("clear");
    printf("> %s Dashboard / AddStudent / Insert Students\n\n", schoolName);
    if (*dataCount <= 1)
    {
        AppendStudents(data, dataCount);
        return;
    }
    printf("Remaining Students Left %d \n\n", STMAX - *dataCount);
    printf("Enter the number of students to Insert : ");
    scanf("%d", &numInsert);
    while (numInsert != 0)
    {
    L6:
        printf("\nEnter the index number where you want to insert (%d,%d) : ", 0, *dataCount);
        scanf("%d", &inpIndex);
        if (inpIndex > *dataCount)
        {
            printf("Invalid index number. Please try again in a range of (%d,%d)\n\n", 0, *dataCount);
            goto L6;
        }
        for (int i = *dataCount; i >= inpIndex; i--)
            data[i + 1] = data[i];
        (*dataCount)++;
        /* Insertion Started */
        scanf("%c", &_tempName[0]);
        inpText("Enter Student Name : ", _tempName);
    L15:
        printf("Enter Roll Number (Unique Number): ");
        scanf("%d", &_tempRoll);
        if (intLen(data[inpIndex].rollno) > 5)
        {
            printf("Roll Number can only be upto 5 Digits\n");
            goto L15;
        }
        for (int i = 0; i < *dataCount; i++)
        {
            if (_tempRoll == data[i].rollno)
            {
                printf("Roll Number already exists. Try again\n");
                goto L15;
            }
        }
        data[inpIndex].rollno = _tempRoll;
        strcpy(data[inpIndex].name, _tempName);
        if (data[inpIndex].name[0] >= 97 && data[inpIndex].name[0] <= 122)
            data[inpIndex].name[0] -= 32;
        regexPhoneNumber("Enter Phone Number : ", &data[inpIndex].phNo);
        /* Insertion Ended */
        numInsert--;
    }
}

void AddStudent(student data[], int *dataCount)
{
L3:
    system("clear");
    printf("> %s Dashboard / AddStudent\n\n", schoolName);
    printf("\nPlease Select your option :\n");
    printf("0. Back\n1. Add Multiple Students\n2. Append Student\n3. Insert Student");
    printf("\n\n-> ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 0:
        return;
        break;
    case 1:
        AddMultipleStudents(data, dataCount);
        break;
    case 2:
        AppendStudents(data, dataCount);
        break;
    case 3:
        InsertStudents(data, dataCount);
        break;
    default:
        break;
    }
    opt = -1;
    goto L3;
}

void ShowAllStudents(student data[], int dataCount, int shwChoice)
{
    //shwChoice is used two diffrent functionality [Show All Students (0), Show Selected Students (1)]
    int stShowNum = 0, stShowNumMAX = 0;
L10:
    system("clear");
    printf("> %s Dashboard / Show Students / ", schoolName);
    if (shwChoice)
        printf("No.of Students ");
    else
        printf("All Students");
    printf("\n\n");
    printf("Total No.of Students are %d\n", dataCount);
    if (dataCount <= 0)
        shwChoice = 0;
L5:
    if (shwChoice)
    {
        printf("Enter the range to show students (%d-%d) : ", 1, dataCount);
        scanf("%d%d", &stShowNum, &stShowNumMAX);
        if (stShowNum == 0 || stShowNumMAX == 0)
            return;
    }
    else
    {
        stShowNum = 1;
        stShowNumMAX = dataCount;
    }
    if (stShowNum < 1 || stShowNumMAX > dataCount)
    {
        printf("We Don't have Enough Data (Enter in the range of %d - %d)\n", 1, dataCount);
        goto L5;
    }
    printf("\nName\t\tRollNo\tPhoneNumber");
    printf("\n-------------------------------------");
    if (dataCount > 0)
    {
        for (int i = stShowNum - 1; i < stShowNumMAX; i++)
        {
            char dpName[STMAX];
            if (strlen(data[i].name) > 6)
            {
                int j = 0;
                for (; j < 6; j++)
                {
                    dpName[j] = data[i].name[j];
                }
                dpName[j++] = '_';
                dpName[j] = '\0';
            }
            else
            {
                strcpy(dpName, data[i].name);
            }
            printf("\n%s\t\t%d   \t%ld", dpName, data[i].rollno, data[i].phNo);
        }
        printf("\n\n(* _ is used when the name consist of 6 or more letters.)");
    }
    else
    {
        printf("\nThere are no Students Data (NULL)\n");
    }
    printf("\n\n0. Back\n");
    if (shwChoice)
    {
        printf("1. Redo\n");
    }
    printf("-> ");
    scanf("%d", &opt);
    if (opt)
        goto L10;
}

void ShowStudent(student data[], int dataCount)
{
L4:
    system("clear");
    printf("> %s Dashboard / Show Students\n\n", schoolName);
    printf("\nPlease Select your option :\n");
    printf("0. Back\n1. Show All %d Students\n2. Show No.of Students\n", dataCount);
    printf("\n\n-> ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 0:
        return;
        break;
    case 1:
        ShowAllStudents(data, dataCount, 0);
        break;
    case 2:
        ShowAllStudents(data, dataCount, 1);
        break;
    default:
        break;
    }
    opt = -1;
    goto L4;
}

void UpdateProfile(student data[], int dataCount)
{
    system("clear");
    printf("> %s Dashboard / Update Students Details\n\n", schoolName);
    if (dataCount <= 0)
    {
        printf("\nThere are no Students. \nStudent Data is required for Update Function\n");
    }
    printf("\nPlease Select your option :\n");
    printf("0. Back");
    if (dataCount > 0)
    {
        printf("\n1. Update by Roll No.");
    }
    printf("\n\n-> ");
    scanf("%d", &opt);
    if (opt == 1 && dataCount > 0)
    {
        int inpRollSearch = 0, srchCounter = 0;
    L9:
        printf("\nEnter the Roll Number to update details : ");
        scanf("%d", &inpRollSearch);
        for (int i = 0; i < dataCount; i++)
        {
            if (data[i].rollno == inpRollSearch)
            {
                srchCounter = 1;
                printf("\nOld Details\n---------\nName : %s\nRoll Number* : %d\nPhone Number : %ld", data[i].name, data[i].rollno, data[i].phNo);
                printf("\n\nNew Details\n---------\n");
                scanf("%c", &data[i].name[0]);
                printf("Enter Student New Name : ");
                inpText("", data[i].name);
                CapitalizeText(data[i].name);
                regexPhoneNumber("Enter the New Phone Number : ", &data[i].phNo);
                break;
            }
        }
        if (srchCounter == 0)
        {
            printf("Roll Number not found. Try again \n");
            goto L9;
        }
    }
}

void searchByName(student data[], int dataCount)
{
    char inpName[STMAX], _tempName[STMAX];
    int _minLen = 0, srchRES;
L14:
    system("clear");
    printf("> %s Dashboard / Search Students / Search by Name\n\n", schoolName);
    scanf("%c", &inpName[0]);
    inpText("\nEnter the Name you want to search :  ", inpName);
    textTransform(inpName, 1); // LowerCase
    printf("\nSearch results \n-----------------");
    srchRES = 0;
    for (int i = 0; i < dataCount; i++)
    {
        strcpy(_tempName, data[i].name);
        textTransform(_tempName, 1);
        _minLen = strlen(inpName) < strlen(_tempName) ? strlen(inpName) : strlen(_tempName);
        inpName[_minLen] = '\0';
        _tempName[_minLen] = '\0';
        if (strcmp(inpName, _tempName) == 0)
        {
            srchRES = 1;
            printf("\nName : %s\nRoll Number (KEY): %d\nPhone Number : %ld\n", data[i].name, data[i].rollno, data[i].phNo);
        }
    }
    if (srchRES == 0)
    {
        printf("\nNo Students found (NULL)");
    }
    printf("\n\n0. Back\n1. Search Again");
    printf("\n\n-> ");
    scanf("%d", &opt);
    if (opt)
        goto L14;
}

void searchByRoll(student data[], int dataCount)
{
    int inpRollSearch = 0, srchCounter;
L11:
    system("clear");
    printf("> %s Dashboard / Search Students / Search by Roll Number\n\n", schoolName);
    srchCounter = 0;
    printf("\nEnter the Roll Number to search student : ");
    scanf("%d", &inpRollSearch);
    for (int i = 0; i < dataCount; i++)
    {
        if (data[i].rollno == inpRollSearch)
        {
            srchCounter = 1;
            printf("\nSearch Details\n---------\n");
            printf("Name : %s\nRoll Number* : %d\nPhone Number : %ld", data[i].name, data[i].rollno, data[i].phNo);
            break;
        }
    }
    if (srchCounter == 0)
    {
        printf("Roll Number not found. Try again");
    }
    printf("\n\n0. Back\n1. Search Again");
    printf("\n\n-> ");
    scanf("%d", &opt);
    if (opt == 1)
        goto L11;
}

void searchByPhNo(student data[], int dataCount)
{
    int inpPhNo = 0, srchCounter;
L16:
    system("clear");
    printf("> %s Dashboard / Search Students / Search by Phone Number\n\n", schoolName);
    srchCounter = 0;
    printf("\nEnter the Phone Number to search student : ");
    scanf("%d", &inpPhNo);

    for (int i = 0; i < dataCount; i++)
    {
        if (data[i].phNo == inpPhNo)
        {
            srchCounter = 1;
            printf("\nSearch Details\n---------\n");
            printf("Name : %s\nRoll Number* : %d\nPhone Number : %ld", data[i].name, data[i].rollno, data[i].phNo);
            break;
        }
    }
    if (srchCounter == 0)
    {
        printf("Phone Number not found. Try again");
    }
    printf("\n\n0. Back\n1. Search Again");
    printf("\n\n-> ");
    scanf("%d", &opt);
    if (opt == 1)
        goto L16;
}

void SearchStudent(student data[], int dataCount)
{
L13:
    system("clear");
    printf("> %s Dashboard / Search Students\n\n", schoolName);
    printf("\nPlease Select your option :\n");
    printf("0. Back\n1. Search by Name\n2. Search by Roll Number\n3. Search by Phone Number");
    printf("\n\n-> ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 0:
        return;
    case 1:
        searchByName(data, dataCount);
        break;
    case 2:
        searchByRoll(data, dataCount);
        break;
    case 3:
        searchByPhNo(data, dataCount);
        break;
    default:
        break;
    }
    goto L13;
}

void DeleteStudent(student data[], int *dataCount)
{
    int _option = 0, _getIndex;
    char _tempName[STMAX];
L17:
    _getIndex = -1;
    system("clear");
    printf("> %s Dashboard / Delete Student\n\n", schoolName);
    printf("\nPlease Select your option :\n");
    printf("0. Back\n1. Delete By Roll Number\n2. Delete All Students");
    printf("\n\n-> ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 0:
        return;
    case 1:
        printf("\nEnter the Roll Number to Delete : ");
        scanf("%d", &_option);
        for (int i = 0; i < *dataCount; i++)
        {
            if (data[i].rollno == _option)
            {
                _getIndex = i;
                strcpy(_tempName, data[i].name);
                break;
            }
        }
        if (_getIndex < 0)
        {
            printf("\nRoll Number Doesn't Exist.\n");
            goto L18;
        }
        for (int i = _getIndex; i < (*dataCount) - 1; i++)
            data[i] = data[i + 1];
        (*dataCount)--;
        printf("\n%s has been kicked out of this school.\n", _tempName);
        break;
    case 2:
        if (*dataCount <= 0)
        {
            printf("\nNo Students to Delete.");
            break;
        }
        else
        {
            for (int i = 0; i < *dataCount; i++)
            {
                strcpy(data[i].name, "\0");
                data[i].phNo = 0;
                data[i].rollno = 0;
            }
            *dataCount = 0;
        }
        break;
    default:
        printf("\nInvalid Option Selected..\nPress 1 to Try again");
        printf("\n\n-> ");
        scanf("%d", &_option);
        if (_option == 1)
            goto L17;
        else
            return;
        break;
    }
L18:
    printf("\n0. Go Back\n1. Delete Again");
    printf("\n\n-> ");
    scanf("%d", &_option);
    if (_option)
        goto L17;
}

void showSessionLogs()
{
    char showLogString;
L19:
    sessionsFile = fopen(SESSION_FILENAME, "r");
    system("clear");
    printf("> %s Dashboard / Sessions Logs\n\n", schoolName);
    printf("\n[ Logged In ] - [ Logged Out ]\
            \n-------------------------------\n\n");
    int fileChar = getc(sessionsFile);
    while (fileChar != EOF)
    {
        putchar(fileChar);
        fileChar = getc(sessionsFile);
    }
    fclose(sessionsFile);
    printf(" Until Log Out\n");
    printf("\nPlease Select your option :\n");
    printf("0. Back\n1. Refresh\n2. Delete All Logs");
    printf("\n\n-> ");
    scanf("%d", &opt);
    if (opt == 0)
        return;
    if (opt == 2)
    {
        sessionsFile = fopen(SESSION_FILENAME, "w");
        fprintf(sessionsFile, " ");
        fclose(sessionsFile);
    }
    goto L19;
}

int initializeDataBase(student data[])
{

    dataBase = fopen(DATABASEFILENAME, "r");
    char currentLine[STMAX];
    int stCount = 0;
    fscanf(dataBase, "%s", currentLine);
    if (strcmp(currentLine, NULL_TXT) == 0)
        return stCount;
    while (strcmp(currentLine, "]") != 0)
    {
        fscanf(dataBase, "%s", data[stCount].name);
        for (int sC = 0; data[stCount].name[sC] != '\0'; sC++)
        {
            if (data[stCount].name[sC] == '%')
                data[stCount].name[sC] = ' ';
        }
        fscanf(dataBase, "%d %ld", &data[stCount].rollno, &data[stCount].phNo);
        stCount++;
        fscanf(dataBase, "%s", currentLine);
    }
    fclose(dataBase);
    return stCount;
}
void updateDataBase(student data[], int dataCount)
{
    dataBase = fopen(DATABASEFILENAME, "w");
    if (dataCount <= 0)
    {
        fprintf(dataBase, NULL_TXT);
        return;
    }
    fprintf(dataBase, "[");
    for (int ct = 0; ct < dataCount; ct++)
    {
        for (int strCT = 0; data[ct].name[strCT] != '\0'; strCT++)
        {
            if (data[ct].name[strCT] == ' ')
                data[ct].name[strCT] = '%';
        }
        fprintf(dataBase, "\n%s %d %ld", data[ct].name, data[ct].rollno, data[ct].phNo);
        if (ct != (dataCount - 1))
            fprintf(dataBase, " _");
    }
    fprintf(dataBase, "\n]");
}

void d_program()
{
    student stData[STMAX];
    int stDataCount = 0;
    int option = 0;
    char DBPass[STMAX];

    /* Database Defination */
    if (!checkFileTXT(DATABASEFILENAME))
    {
        printf("Error 404 : Database Not Found..");
        printf("\n\nWould you like to create the Database ?\n0. No\n1. Yes\n\n-> ");
        scanf("%d", &option);
        if (option == 1)
        {
            createFileTXT(DATABASEFILENAME);
            addNullFile(DATABASEFILENAME);
        }
        else
            return;
    }
    stDataCount = initializeDataBase(stData);
    option = 0;
    /* Session Initialize */
L_CheckSESSION:
    if (!checkFileTXT(SESSION_FILENAME))
        createFileTXT(SESSION_FILENAME);
    sessionsFile = fopen(SESSION_FILENAME, "r");
    if (fgetc(sessionsFile) == ' ')
    {
        remove(SESSION_FILENAME);
        goto L_CheckSESSION;
    }
    fclose(sessionsFile);
    sessionsFile = fopen(SESSION_FILENAME, "a");
    if (checkSESSIONContents(SESSION_FILENAME))
        fprintf(sessionsFile, "\n");
    fprintf(sessionsFile, "[ %s ] -", getDateTimeNow());
    fclose(sessionsFile);
L1:
    system("clear");
    printf("Welcome to %s.\n~~~~~~~~~~~~~~~~~~~~~~~~\n", schoolName);
    printf("[Session Started : %s]\n", getDateTimeNow());
    printf("\nPlease Select your option :\n");
    printf("1. Add Student\n2. Show Studednt\n3. Update Profile\n");
    printf("4. Search Student\n5. Delete Student\n6. Show Session Logs\n0. Logout");
    printf("\n\n-> ");
    scanf("%d", &option);
    switch (option)
    {
    case 0:
        goto L2;
        break;
    case 1:
        AddStudent(stData, &stDataCount);
        break;
    case 2:
        ShowStudent(stData, stDataCount);
        break;
    case 3:
        UpdateProfile(stData, stDataCount);
        break;
    case 4:
        SearchStudent(stData, stDataCount);
        break;
    case 5:
        DeleteStudent(stData, &stDataCount);
        break;
    case 6:
        showSessionLogs(stData, &stDataCount);
        break;
    default:
        goto L1;
        break;
    }
    goto L1;
L2:
    updateDataBase(stData, stDataCount);
    printf("\n\n-----------------\nSession Ended !");
    sessionsFile = fopen(SESSION_FILENAME, "r");
    if (fgetc(sessionsFile) != ' ')
    {
        FILE *_SSFile = NULL;
        _SSFile = fopen(SESSION_FILENAME, "a");
        fprintf(_SSFile, " [ %s ]\n", getDateTimeNow());
        fclose(_SSFile);
    }
    fclose(sessionsFile);
}
