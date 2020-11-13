import java.util.*;
import java.lang.*;
public class withoutString {
    public static String withoutStrings(String base, String remove) {
        ArrayList<Integer> locations = new ArrayList<Integer>();
        char baseChars[] = base.toCharArray();
        int j = 0;
        int numRemoves = 0;
        String originalBase = base;
        while (base.toLowerCase().contains(remove.toLowerCase())) {
            //save location of substring
            locations.add(base.toLowerCase().indexOf(remove.toLowerCase()) + (numRemoves * remove.length()));
            base = base.toLowerCase().replaceFirst(remove.toLowerCase(), "");
            numRemoves++;
        }
        for (int i = 0; i < locations.size(); i++) {
            System.out.println("location (" + i + ") --> " + locations.get(i));
        }
        int originalIndex = 0;
        int currIndex = 0;
        char newBase[] = base.toCharArray();
        while (currIndex < base.length()) {
            /*System.out.println("curr Index --> " + currIndex + 
            ", originalIndex --> " + originalIndex + 
            ", location --> " + (!locations.isEmpty() ? locations.get(0) : " "));*/
            //if before first removed string
            if (!locations.isEmpty() && originalIndex < locations.get(0)) {
                if (Character.isUpperCase(baseChars[originalIndex])) {
                newBase[currIndex] = Character.toUpperCase(newBase[currIndex]);
                }
            }
            //compensate for removed string
            else if (!locations.isEmpty() && originalIndex == locations.get(0)) {
                originalIndex += remove.length(); //skip past removed chars
                locations.remove(0);
                if (Character.isUpperCase(baseChars[originalIndex])) {
                    newBase[currIndex] = Character.toUpperCase(newBase[currIndex]);
                }
            }
            originalIndex++; //10
            currIndex++; //6
        }
        return new String(newBase);
    }

    public static void main(String args[]) {
        System.out.println(withoutStrings("This is a FISH", "IS"));
    }
}