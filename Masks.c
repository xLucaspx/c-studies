#include <stdio.h>

#define SUNDAY    0x01 // 0000 0001
#define MONDAY    0x02 // 0000 0010
#define TUESDAY   0x04 // 0000 0100
#define WEDNESDAY 0x08 // 0000 1000
#define THURSDAY  0x10 // 0001 0000
#define FRIDAY    0x20 // 0010 0000
#define SATURDAY  0x40 // 0100 0000

void printAsByte(char availability) {
	printf("(");
	for (int i = 0; i < 8; i++) {
		// !!: the first one negates the value, returning 0 or 1;
		// the second one then turns the value into it's 0 or 1 equivalent
		printf("%d", !!((availability << i) & 0x80));
		if (i == 3) printf(" ");
	}
	printf(")\n");
}

/**
 * prints the available weekdays.
 *
 * @param availability represents a persons availability in a week; the MSB is ignored, the bit
 * immediately to the right represents saturday, and so on, until the LSB, which represents sunday.
 * 0 = unavailable, 1 = available.
 */
void printAvailableDays(char availability) {
	int printed = 0;
	printf("[ ");

	if (availability & SUNDAY) {
		printf("Sunday");
		printed = 1;
	}
	if (availability & MONDAY) {
		if (printed) printf(", ");
		printf("Monday");
		printed = 1;
	}
	if (availability & TUESDAY) {
		if (printed) printf(", ");
		printf("Tuesday");
		printed = 1;
	}
	if (availability & WEDNESDAY) {
		if (printed) printf(", ");
		printf("Wednesday");
		printed = 1;
	}
	if (availability & THURSDAY) {
		if (printed) printf(", ");
		printf("Thursday");
		printed = 1;
	}
	if (availability & FRIDAY) {
		if (printed) printf(", ");
		printf("Friday");
		printed = 1;
	}
	if (availability & SATURDAY) {
		if (printed) printf(", ");
		printf("Saturday");
		printed = 1;
	}

	printf(" ]\n");
}

int main() {
	/**
	 * We may frequently need to isolate or manipulate specific bits from a collection of bits.
	 * A mask is a bit pattern built to be used with bitwise operators to accomplish that.
	 *
	 * E.g.: we can use a char to represent weekdays; chars have 8 bits, so we'll ignore the MSB
	 * (most significant bit) and use the resulting bits to represent a persons availability
	 * (1 = available, 0 = not available).
	 *
	 * | 0 | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
	 * | ` | S | F | T | W | T | M | S |
	 * | ` | A | R | H | E | U | O | U |
	 * | ` | T | I | U | D | E | N | N |
	 *
	 * Using the masks defined above and bitwise operators, we can verify and manipulate these values.
	 * E.g.:
	 *
	 * - add tuesday | - remove friday | - check for wednesday |  - check for monday
	 *   0010 0010   |   0010 0110     |   0000 0110           |    0000 0110
	 * | 0000 0100   | & 1101 1111     | & 0000 1000           |  & 0000 0010
	 *   =========   |   =========     |   =========           |    =========
	 *   0010 0110   |   0000 0110     |   0000 0000           |    0000 0010
	 *         *           *                    *                          *
	 */

	printf("\navailability:\n");
	char availability = 0x22; // 0010 0010
	printAsByte(availability);
	printAvailableDays(availability);

	printf("\nadding tuesday:\n");
	availability |= TUESDAY;
	printAsByte(availability);
	printAvailableDays(availability);

	printf("\nremoving friday:\n");
	availability &= ~FRIDAY;
	printAsByte(availability);
	printAvailableDays(availability);

	return 0;
}
