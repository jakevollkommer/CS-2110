/**
 * CS 2110 Spring 2017 HW2
 * Part 2 - Coding with bases
 *
 * @author Jake Vollkommer
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString and
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int num = 0;
        for (int i = 0; i < binary.length(); i++) {
            if (binary.charAt(i) == 49) {
                num = num + (1 << (binary.length() - i - 1));
            }
        }

        return num;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     */
    public static int decimalStringToInt(String decimal)
    {
        int num = 0;
        int bitValue = 1;
        for (int i = decimal.length() - 1; i >= 0; i--) {
            int value = decimal.charAt(i) - 48;
            num = num + (value * bitValue);
            bitValue = bitValue * 10;
        }
        return num;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int num = 0;
        for (int i = 0; i < hex.length(); i++) {
            int value = hex.charAt(i);
            if (value < 58) {
                value = value - 48;
            } else {
                value = value - 55;
            }
            int shiftAmount = (hex.length() - i - 1);
            shiftAmount = shiftAmount << 2;
            num = num + (value << shiftAmount);
        }
        return num;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     */
    public static String intToBinaryString(int binary)
    {
        if (binary == 0) {
            return "0";
        }
        String binaryString = "";
        int i = 0;
        while (binary > 0) {
            if ((binary & (1 << i)) != 0) {
                binaryString = "1" + binaryString;
                binary = binary - (1 << i);
            } else {
                binaryString = "0" + binaryString;
            }
            i++;
        }
        return binaryString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     */
    public static String intToHexString(int hex)
    {
        String hexString = "";
        int num = 0;
        int shifted = 1;
        while (shifted > 0) {
            shifted = (hex >> 4);
            num = hex - (shifted << 4);
            num = (num < 10) ? num + 48 : num + 55;
            hexString = ((char) num) + hexString;
            hex = shifted;
        }
        return hexString;
    }
}
