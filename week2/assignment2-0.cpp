#include <iostream>
#include <cstdio>   // For printf function
using namespace std;

int main() {
    // Sample variables to display
    int integer_value = 42;
    float float_value = 3.14159265f;
    double double_value = 3.14159265;
    char char_value = 'X';
    const char* string_value = "Hello, World!";

    printf("Format Specifier Practice\n");
    printf("------------------------\n\n");

    // Integer formatting
    printf("Integer (%%d): %d\n", integer_value);                  // %d displays signed decimal integer
    printf("Integer (%%5d): %5d\n", integer_value);               // %5d reserves 5 character spaces, right-aligned
    printf("Integer (%%-5d): %-5d (left-aligned)\n", integer_value); // %-5d left-aligns the number in 5 spaces
    printf("Integer (%%#x): %#x (hex with 0x)\n", integer_value); // %#x prints hex with 0x prefix
    printf("Integer (%%#o): %#o (octal with 0)\n", integer_value); // %#o prints octal with 0 prefix

    // Float formatting
    printf("\nFloat (%%f): %f\n", float_value);               // %f prints float with 6 decimal places by default
    printf("Float (%%.2f): %.2f\n", float_value);             // %.2f limits to 2 decimal places
    printf("Float (%%8.2f): %8.2f\n", float_value);           // %8.2f uses width 8 and 2 decimals, right-aligned
    printf("Float (%%-8.2f): %-8.2f (left-aligned)\n", float_value); // %-8.2f left-aligned in 8 spaces

    // Double formatting
    printf("\nDouble (%%e): %e\n", double_value);             // %e prints in scientific notation
    printf("Double (%%.3g): %.3g\n", double_value);           // %g chooses between %f or %e depending on the value, with 3 significant digits

    // Character formatting
    printf("\nCharacter (%%c): %c\n", char_value);            // %c prints a single character

    // String formatting
    printf("String (%%s): %s\n", string_value);               // %s prints a C-style string
    printf("String (%%10s): %10s\n", string_value);           // %10s reserves 10 spaces, right-aligned
    printf("String (%%-10s): %-10s (left-aligned)\n", string_value); // %-10s left-aligns string in 10 spaces
    printf("String (%%.3s): %.3s (limit length)\n", string_value);   // %.3s prints only first 3 characters

    return 0;
}