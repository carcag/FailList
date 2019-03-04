#include "main.h"

int printFailure(failures f)
{
    printf("\n\t\t{\n\t\t\t0x%04X,\n\t\t\t%s,\n\t\t\t0x%04X,\n\t\t\t%d,\n\t\t\t%s,\n\t\t\t%d\n\t\t},", f.ID_FAILURE, f.DATETIME, f.ID_COMPONENT, f.LEVEL_CRITICITY, f.COMMENT, f.COMMENT_SIZE);
    return (0);
}

int printFailureMan(failuresMan f)
{
    printf("\n\t\t{\n\t\t\t0x%s,\n\t\t\t%s,\n\t\t\t0x%s,\n\t\t\t%d,\n\t\t\t%s,\n\t\t\t%d\n\t\t},", f.ID_FAILURE, f.DATETIME, f.ID_COMPONENT, f.LEVEL_CRITICITY, f.COMMENT, f.COMMENT_SIZE);
    return (0);
}

void cleanBuffer(char commandBuffer[], int size)
{
  int it = 0;

  while (it < size)
  {
    commandBuffer[it] = '\0';
    it++;
  }
}

int getRandoms(int lower, int upper)
{
    return ((rand() % (upper - lower + 1)) + lower);
}

int generateFailures(failures *failuresList, int numberOfFailures)
{
    int iterator = 0;
    const unsigned int ID_FAILURES_LIST[17] = {
        0x1000,
        0x1001,
        0x1002,
        0x1003,
        0x1004,
        0x1005,
        0x1006,
        0x1007,
        0x1008,
        0x1009,
        0x100A,
        0x100B,
        0x100C,
        0x100D,
        0x100E,
        0x100F,
        0x1010
    };
    const unsigned int ID_COMPONENT_LIST[14] = {
        0x2000,
        0x2001,
        0x2002,
        0x2003,
        0x2004,
        0x2005,
        0x2006,
        0x2007,
        0x2008,
        0x2009,
        0x200A,
        0x200B,
        0x200C,
        0x200D
    };
    char *comment = "No comment";
    size_t commentSize = sizeof(char) * strlen(comment);
    while (iterator < numberOfFailures)
    {
        int randomNumber = 0;
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = gmtime(&rawtime);

        strftime (buffer,80,"%Y/%m/%d - %H:%M:%S",timeinfo);

        randomNumber = getRandoms(0, 16);
        failuresList[iterator].ID_FAILURE = ID_FAILURES_LIST[randomNumber];

        strcpy(failuresList[iterator].DATETIME, buffer);

        randomNumber = getRandoms(0, 13);
        failuresList[iterator].ID_COMPONENT = ID_COMPONENT_LIST[randomNumber];

        randomNumber = getRandoms(0, 10);
        failuresList[iterator].LEVEL_CRITICITY = randomNumber;

        strcpy(failuresList[iterator].COMMENT, comment);

        failuresList[iterator].COMMENT_SIZE = commentSize;


        printFailure(failuresList[iterator]);
        iterator++;
    }
    return(0);
}

int autoGeneration(char commandBuffer[])
{
    char ID_PLANE[9][10] = {
        "F-GCQE",
        "UR-AZO",
        "RA-48852",
        "F-GGZB",
        "UR-HEI",
        "RA-14588",
        "F-GLEC",
        "UR-SIE",
        "RA-19833"
    };

    unsigned int TYPE_PLANE[11] = {
        0x0140,
        0x014A,
        0x015E,
        0x017C,
        0x0190,
        0x0127,
        0x02E1,
        0x02EB,
        0x02FF,
        0x0309,
        0x0313
    };
    int numberOfFailures = 0;
    failures failuresList[100];
    char ch;

    printf("\n\nPlease type the number of failure(s) that you want to generate :\n");
    fgets(commandBuffer, 127, stdin);

    numberOfFailures = atoi(commandBuffer);


    printf("{\n\tId_plane : %s,", ID_PLANE[getRandoms(0, 8)]);
    printf("\n\tType_plane: 0x%04X,", TYPE_PLANE[getRandoms(0, 10)]);
    printf("\n\tNb_failures: %d,", numberOfFailures);
    if (numberOfFailures >= 100)
        numberOfFailures = 99;
    printf("\n\tfailures: [");
    generateFailures(failuresList, numberOfFailures);
    printf("\n\t]\n}");
    return (0);
}

int deleten(char tab[], int size)
{
    int i = 0;

    while (i < size)
    {
        if (tab[i] == '\n')
            tab[i] = '\0';
        i++;
    }

    return (0);
}

failuresMan getUserFailures(int numberOfFailures, int iterator)
{
  failuresMan f;
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];
  time(&rawtime);
  timeinfo = gmtime(&rawtime);
  char commandBuffer[128];
  char ch;

  printf("Enter the id of the failure %d\n", iterator +1);
  while ((ch = getchar()) != '\n' && ch != EOF);
  cleanBuffer(commandBuffer, 128);
  fgets(commandBuffer, 127, stdin);
  deleten(commandBuffer, 15);
  strncpy(f.ID_FAILURE, commandBuffer, 7);
  strftime (buffer,80,"%Y/%m/%d - %H:%M:%S",timeinfo);
  strncpy(f.DATETIME, buffer, 80);
  printf("Enter the id of the component affected by the failure %d\n", iterator +1);
  fgets(commandBuffer, 127, stdin);
  deleten(commandBuffer, 15);
  strncpy(f.ID_COMPONENT, commandBuffer, 127);
  printf("Enter the level of criticity of the failure %d (between 1 & 10)\n", iterator +1);
  fgets(commandBuffer, 127, stdin);
  deleten(commandBuffer, 15);
  f.LEVEL_CRITICITY = atoi(commandBuffer);
  printf("Enter a comment to describe the failure %d\n", iterator+1);
  fgets(commandBuffer, 127, stdin);
  deleten(commandBuffer, 15);
  strncpy(f.COMMENT, commandBuffer, 127);
  f.COMMENT_SIZE = strlen(f.COMMENT) * sizeof(char);
  return (f);
}

int manualGeneration(char commandBuffer[])
{
    int numberOfFailures = 0;
    int iterator = 0;
    char ID_PLANE[15];
    char TYPE_PLANE[5];
    failuresMan failuresListMan[4];
    char ch;

    printf("How many failures do you want to generate ? (1 - 3)\n");
    fgets(commandBuffer, 127, stdin);
    numberOfFailures = atoi(commandBuffer);
    if (numberOfFailures < 4 && numberOfFailures > 0)
    {
        printf("Enter the id of the plane: \n");
        fgets(commandBuffer, 15, stdin);
        deleten(commandBuffer, 15);
        strncpy(ID_PLANE, commandBuffer, 15);
        printf("\nEnter the type of the plane (in hexa, without the prefix 0x)\n");
        fgets(commandBuffer, 5, stdin);
        deleten(commandBuffer, 5);
        strncpy(TYPE_PLANE, commandBuffer, 5);
        while (iterator < numberOfFailures)
        {
            failuresListMan[iterator] = getUserFailures(numberOfFailures, iterator);

            iterator++;
        }
        printf("{\n\tId_plane : %s,", ID_PLANE);
        printf("\n\tType_plane: 0x%s,", TYPE_PLANE);
        printf("\n\tNb_failures: %d,", numberOfFailures);
        printf("\n\tfailures: [");
        iterator = 0;
        while (iterator < numberOfFailures)
        {
          printFailureMan(failuresListMan[iterator]);
          iterator++;
        }
        printf("\n\t]\n}");
    }
    else
        printf("ERROR\n");
        return(0);
}

int main()
{
    char commandBuffer[128];
    char ch;

    srand(time(0));

    printf("Type :\n1- To use the automatic failure(s) generation\n2- To use the manual failure(s) generation (1 to 3 errors)\n");
    fgets(commandBuffer, 127, stdin);

    if(strncmp(commandBuffer, "1", 1) == 0)
        autoGeneration(commandBuffer);
    else if(strncmp(commandBuffer, "2", 1) == 0)
        manualGeneration(commandBuffer);

    return 0;
}
