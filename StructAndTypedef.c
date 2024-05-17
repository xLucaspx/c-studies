#include <stdio.h>

// we can use structs to create new types, grouping variables that are used together
struct contact {
	char name[20];
	char phone[20];
};

// we can use typedef to create an alias to the struct
typedef struct contact CONTACT;

int main() {
	// struct contact c;
	CONTACT c;

	// acessing variables inside the struct:
	sprintf(c.name, "John Doe");
	sprintf(c.phone, "555 321 05 07");
	
	printf("Contact: %s\nPhone: %s\n", c.name, c.phone);
	
	return 0;
}

