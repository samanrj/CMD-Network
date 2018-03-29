#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


// Prints community members' data. If all=1 then prints everything, else pronts only name, year, birth place.
void print_all(Member* head, int all)	
{
	int cnt=1;
	while(head)
	{
		if(all)
			printf("\nMember #%d:\n\t- nickname: %s;\n\t- name: %s %s;\n\t- date of bith: %d.%d.%d;\n\t- place of birth: %s;\n\t- inviter: %s.\n", cnt++, 
				head->person.nickname,
				head->person.givenname,
				head->person.familyname,
				head->person.birthdate.day,
				head->person.birthdate.month,
				head->person.birthdate.year,
				head->person.birthplace,
				head->person.inviter);
		else
			printf("\nMember #%d:\n\t- name: %s %s;\n\t- year of bith: %d;\n\t- place of birth: %s.\n", cnt++, 
				head->person.givenname,
				head->person.familyname,
				head->person.birthdate.year,
				head->person.birthplace);

		head=head->next;
	}
	if(cnt==1)
		printf("There are no members in the community\n");
}

// Frees memory to avoid memory leakage
void free_memory(Member** head)	
{
	while(*head)
	{
		Member* current = (*head)->next;
		free(*head);
		*head = current;
	}
}

// Inserting the data of a new member into the community
void insert_new_member(Member** head, Person* newperson)
{
	Member* p = (Member*)malloc(sizeof(Member));
	p->person.birthdate = newperson->birthdate;
	strcpy(p->person.birthplace, newperson->birthplace);
	strcpy(p->person.familyname, newperson->familyname);
	strcpy(p->person.givenname, newperson->givenname);
	strcpy(p->person.inviter, newperson->inviter);
	strcpy(p->person.nickname, newperson->nickname);
	p->next = *head;
	*head = p;
}

// Deleting a member from the community by the given nickname
int delete_member(Member** head, char* nickname)
{
	Member* cur = *head;
	int cnt = 0;
	if(!cur)	// No members in the community
		return 0;
	while(cur!=NULL && cur->next != NULL)
	{
		if(strcmp(cur->next->person.nickname, nickname)==0)
		{
			Member* temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
			cnt++;
		}
		cur = cur->next;
	}
	if(strcmp((*head)->person.nickname, nickname)==0)
	{
		Member* temp = (*head);
		(*head) = (*head)->next;
		free(temp);
		cnt++;
	}
	return cnt;
}

// Saving the community members
int save(Member* head)
{
	FILE* fp = NULL;
	int cnt = 0;
	fp = fopen("facebook.bin", "wb");
	if(!fp)
	{
		printf("Unable to create file. Save operation aborted.");
		return -1;
	}
	while(head)
	{
		fwrite(&head->person, sizeof(Person),1,fp);
		head = head->next;
		cnt++;
	}
	fclose(fp);
	return cnt;
}

// Loading the community members
int load(Member** head)
{
	FILE* fp = NULL;
	Person p;
	int cnt = 0;
	fp = fopen("facebook.bin", "rb");
	if(!fp)
	{
		printf("Unable to open file. Load operation aborted.");
		return -1;
	}
	while(fread(&p, sizeof(Person), 1, fp) == 1)
	{
		insert_new_member(head, &p);
		cnt++;
	}
	fclose(fp);
	return cnt;
}

// Searching the data of a member (members) given by his nickname
Member* search_by_nickname(Member* head, char* nickname)
{
	Member* results = NULL;
	while(head)
	{
		if(strcmp(head->person.nickname, nickname)==0)
			insert_new_member(&results, &head->person); 
		head = head->next;
	}
	return results;
}

// Searching the data of a member (members) given by his family name
Member* search_by_familyname(Member* head, char* familyname)
{
	Member* results = NULL;
	while(head)
	{
		if(strcmp(head->person.familyname, familyname)==0)
			insert_new_member(&results, &head->person); 
		head = head->next;
	}
	return results;
}

// Searching all the members who were invited by the same person with the given nickname
Member* search_by_inviter(Member* head, char* inviter)
{
	Member* results = NULL;
	while(head)
	{
		if(strcmp(head->person.inviter, inviter)==0)
			insert_new_member(&results, &head->person); 
		head = head->next;
	}
	return results;
}