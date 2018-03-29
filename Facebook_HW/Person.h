// Structure for storing the date
typedef struct d
{
	int day;
	int month;
	int year;
} Date;

// Structure for storing the person data
typedef struct p
{
	char nickname[20];
	char familyname[40];
	char givenname[40];
	Date birthdate;
	char birthplace[20];
	char inviter[20];
} Person;

