/* 
	ASSUMPTIONS MADE DURING PROJECT WORK

1) Only one unique nickname is allowed in the community. There cannot be two community members with the same nickname.
   However, there is no validation for nicknames.
2) There is no validation for inviters. Any inviter's nickname is accepted, even not existing one.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h>
#include "List.h"

// Function declarations
void ask_person_and_insert(Member**);
void ask_nickname_search_print(Member*);
void ask_familyname_search_print(Member*);
void ask_nickname_and_delete(Member**);
void ask_inviter_search_print(Member*);
void anykey();


int main()
{
	int selector;			// User's choice in the menu
	int counter;			// Counter of loaded (saved) members
	Member* members = NULL;	// The linked list with members
	while(1)
	{
		system("cls");		// Clear the console
		// MENU
		printf("Homework task for Saman Rajaei. FACEBOOK.\n\n");
		printf("(1) LOAD community from file\n");
		printf("(2) SAVE community to file\n");
		printf("(3) INSERT a new community member\n");
		printf("(4) SEARCH member by nickname\n");
		printf("(5) SEARCH member(s) by family name\n");
		printf("(6) DELETE member by nickname\n");
		printf("(7) LIST all memebers invited by a member with the given nickname\n");
		printf("(8) LIST all members of the community\n");
		printf("(9) QUIT\n\n");

		do selector = _getch();		// Waits for a preseed key
		while (!(selector >= '1' && selector <= '9'));

		switch (selector)
		{
		case '1' :		// Loading the community members
			free_memory(&members);
			if((counter=load(&members))>0)
				printf("Loaded successfully %d community members.", counter);
			else
				printf("The file is empty or not existing. There is nothing to load.", counter);
			break;
		case '2' :		// Saving the community members
			if((counter=save(members))>0)
				printf("Saved successfully %d community members.", counter);
			else
				printf("The community is empty. There is nothing to save.", counter);
			break;
		case '3' :		// Inserting the data of a new member into the community
			ask_person_and_insert(&members);
			break;
		case '4':		// Searching the data of a member (members) given by his family name
			ask_nickname_search_print(members);
			break;
		case '5':		// Searching the data of a member (members) given by his nickname
			ask_familyname_search_print(members);
			break;
		case '6':		// Deleting a member from the community by the given nickname
			ask_nickname_and_delete(&members);
			break;
		case '7':		// Listing all the members who were invited by the same person with the given nickname
			ask_inviter_search_print(members);
			break;
		case '8':		// List all the members of the community (name, year and place of birth)
			print_all(members, 0);		
			break;
		case '9':		// Quiting the application and freeing the memory
			free_memory(&members);
			return 0;
		default: 
			printf("Invalid option: %d\n", selector);
			break;
		}
		anykey();	// Waits for a key pressed
	}
	return 0;
}


void ask_person_and_insert(Member** head)
{
	Person p;
	printf("Please, enter data for a new member.\n");
	printf("1) Nickname: ");
	scanf("%s", p.nickname);
	printf("2) Family name: ");
	scanf("%s", p.familyname);
	printf("3) Given name(s): ");
	scanf("%s", p.givenname);
	printf("4) Date of birth in dd.mm.yyyy format: ");
	scanf("%d.%d.%d", &p.birthdate.day, &p.birthdate.month, &p.birthdate.year);
	printf("5) Place of birth: ");
	scanf("%s", p.birthplace);
	printf("6) Nickname of the inviter: ");
	scanf("%s", p.inviter);
	insert_new_member(head, &p);
}

void ask_nickname_search_print(Member* head)
{
	Person p;
	Member* result;
	printf("Please, enter nickname to search for.\nNote that nickname is unique in the community.\n");
	printf("Nickname: ");
	scanf("%s", p.nickname);
	result = search_by_nickname(head, p.nickname);
	printf("Search results:\n");
	if(!result)
		printf("\tNo such member found!");
	else
		print_all(result, 1);
}

void ask_familyname_search_print(Member* head)
{
	Person p;
	Member* result;
	printf("Please, enter family name to search for.\nNote that there can be multiple members with the same family name.\n");
	printf("Family name: ");
	scanf("%s", p.familyname);
	result = search_by_familyname(head, p.familyname);
	printf("Search results:\n");
	if(!result)
		printf("\tNo members found!");
	else
		print_all(result, 1);
}

void ask_nickname_and_delete(Member** head)
{
	Person p;
	printf("Please, enter nickname to delete.\nNote that nickname is unique in the community.\n");
	printf("Nickname: ");
	scanf("%s", p.nickname);
	if(delete_member(head, p.nickname)>0)
		printf("One community member deleted successfully.");
	else
		printf("Community member not found with the given nickname.");
}

void ask_inviter_search_print(Member* head)
{
	Person p;
	Member* result;
	printf("Please, enter inviter's nickname to search for.\nNote that there can be multiple members invited by the same person.\n");
	printf("Inviter: ");
	scanf("%s", p.inviter);
	result = search_by_inviter(head, p.inviter);
	printf("Search results:\n");
	if(!result)
		printf("\tNo members found!");
	else
		print_all(result, 1);

}

// Waits for a key pressed
void anykey()
{
	printf("\nPress any key to return to main menu . . .");
	_getch();
}
