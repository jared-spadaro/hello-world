import java.util.*;
import java.lang.*;
public class Decompress {
    public static String decompress(String input) {
        int multiplier = 0, i = 0, multiplierLoc, openLoc, closeLoc, multiplierStart, 
        multiplierEnd, lastBracket, currentBracket;
        char[] inputChars = input.toCharArray();
        String outputStr = "", innerStr = "", multiplierStr = "";
        //any char encountered before a multiplier is just printed back
        while (i < inputChars.length && !Character.isDigit(inputChars[i])) {
            outputStr += String.valueOf(inputChars[i++]);
        }
        if (i == inputChars.length) return outputStr; 
        //parse the multiplier (arbitary length integer)
        multiplierStart = i;
        multiplierEnd = i+1;
        while (Character.isDigit(inputChars[++i])) multiplierEnd++;
        for (i = multiplierStart; i < multiplierEnd; i++) {
            multiplierStr += String.valueOf(inputChars[i]);
        }
        multiplier = Integer.parseInt(multiplierStr);

        openLoc = input.indexOf("[");
        closeLoc = input.indexOf("]");
        innerStr = input.substring(openLoc+1, closeLoc);
        
        //base case
        if (!innerStr.contains("[")) {
            for (i = 0; i < multiplier; i++) {
                outputStr += innerStr;
            }
            return outputStr + decompress(input.substring(closeLoc+1));
        }
        
        //find outermost remaining closing bracket and recurse
        lastBracket = currentBracket = input.indexOf("]");
        while (input.indexOf("]", lastBracket+1) != -1) {
            currentBracket = input.indexOf("]", lastBracket+1);
            lastBracket = currentBracket;
        }
        for (i = 0; i < multiplier; i++) {
            outputStr += decompress(input.substring(openLoc+1, currentBracket)); 
        }
        return outputStr;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter string to decompress: ");
        String input = sc.nextLine();
        System.out.println(decompress(input));
    }
}