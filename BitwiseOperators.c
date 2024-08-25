#include <stdio.h>

int main() {
	/**
	 * AND	(&) - useful to turn selected bits off (0)
	 * OR		(|) - useful to turn selected bits on (1)
	 * XOR	(^) - useful to inverse selected bits
	 * NOT	(~) - useful to inverse all bits
	 *
	 * SHIFT-LEFT		(<<) - shifts n bits left (multiplies by 2 n times)
	 * SHIFT-RIGHT	(>>) - shifts n bits right (divides by 2 n times)
	 */

	int n1 = 42;
	int n2 = 101;

	printf("\nchecking if a number is even or odd using '& 1':\n");
	printf("%d is %s\n", n1, (n1 & 1) ? "odd" : "even");
	printf("%d is %s\n", n2, (n2 & 1) ? "odd" : "even");

	printf("\nusing XOR to swap variables:\n");
	printf("some compilers optimize variable swap this way\n");
	printf("before swap:	{ n1: %d, n2: %d }\n", n1, n2);
	n1 ^= n2;
	n2 ^= n1;
	n1 ^= n2;
	printf("after swap:	{ n1: %d, n2: %d }\n", n1, n2);

	printf("\neach shift-left multiplies the number by 2:\n");
	int shift = 2;
	printf("%d << %d = %d\n", n2, shift, n2 << shift);

	printf("\neach shift-right divides the number by 2:\n");
	shift = 1;
	printf("%d >> %d = %d\n", n1, shift, n1 >> shift);

	/**
	 * We can use that to extract colors from RGB
	 * Consider an RGB color in the format 0x009dda;
	 * - To extract red, we shift 16 bits right		(>> 16);
	 * - To extract green, we shift 8 bits right	(>> 8);
	 * - To extract blue, we don't need to shift.
	 * Finally, whe clear our result with '& 0xFF'
	 */
	int rgb = 0x009dda;
	printf("\nextracting colors from RGB using shift and '&'\n");
	printf("RGB: 0x%06x\n", rgb);

	int r = (rgb >> 16) & 0xff;
	int g = (rgb >> 8) & 0xff;
	int b = rgb & 0xff;

	printf("R = %02x (%d)\n", r, r);
	printf("G = %02x (%d)\n", g, g);
	printf("B = %02x (%d)\n", b, b);

	// another possible way (leves you with the same number of bits)
	// int red = rgb & 0xff0000;
	// int green = rgb & 0xff00;
	// int blue = rgb & 0xff;

	return 0;
}
