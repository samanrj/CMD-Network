#include "Person.h"

typedef struct m	// Structure for storing members of the community
{
	Person person;
	struct m* next;
} Member;

void print_all(Member*, int);
void free_memory(Member**);
void insert_new_member(Member**, Person*);
int delete_member(Member**, char*);
int save(Member*);
int load(Member**);
Member* search_by_nickname(Member*, char*);
Member* search_by_familyname(Member*, char*);
Member* search_by_inviter(Member*, char*);
