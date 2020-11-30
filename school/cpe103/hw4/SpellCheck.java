//Program by Jared Spadaro
//CPE103 with Professor Buckalew
//11/16/2013

import java.io.*;
import java.util.*;

public class SpellCheck {

   //instance variables
   public RecordBST dictionary;
   public ArrayList<ItemRecord> foundWords;     //words that were found in the dictionary
   public ArrayList<ItemRecord> notFoundWords;  //words that were not found in the dictionary
   public ArrayList<ItemRecord> fixedWords;     //words which had spelling corrected

   //method to read in the dictionary file (unsortedWords.txt)
   public void scanDictionary (String filename) {
      dictionary = new RecordBST();
      try {
         File unsortedWords = new File (filename);   
         Scanner s = new Scanner (unsortedWords);
         while(s.hasNext()) {
            String str = s.next();   //set str to the next word in the scanner
            str = str.toLowerCase();  //set str to all lower case (makes compare methods easier to deal with)
            ItemRecord ir = new ItemRecord(str);  //construct new itemrecord with str
            dictionary.insert(ir);   //add itemrecord to the dictionary
         }
      }
      catch (FileNotFoundException e) {
         System.out.println ("Error: file not found");
      }
   }  


   //method to scan a file to see which words are in the dictionary
   public void scanForWords (String filename) {
      File file = new File (filename);
      try {
         Scanner s = new Scanner (file);
         //initialize arraylists
         foundWords = new ArrayList<ItemRecord>();
         notFoundWords = new ArrayList<ItemRecord>();
         while(s.hasNext()) {
            boolean found = false; //flag to see if the word has already been seen
            String str = s.next(); //set str to the next word in the scanner
            str = str.toLowerCase(); 
            ItemRecord ir = new ItemRecord(str);  //construct new itemrecord with str
            if(dictionary.find(ir)) {  //call find method to see if word is in dictionary
               //this loop checks to see if the found word has previously been found
               for(int i=0;i<foundWords.size();i++) {
                  //if the word has already been found
                  if(ir.word().compareTo(foundWords.get(i).word())==0) {
                     found = true;  
                     foundWords.get(i).addTally(); //add to the word's tally but do not add it to arraylist
                  }
               }
               if(found==false) { //if the word has not been found
                  foundWords.add(ir); //add it to the arraylist
                  foundWords.get(foundWords.size()-1).addTally(); //add to its tally
               }
            }
            else {
               notFoundWords.add(ir);  //if the word was not in the dictionary, then add it to this list
            }
         }
         doBubblesort(foundWords);  //sort the found words
         doBubblesort(notFoundWords);  //sort the words that were not found as well
         //some formatting here 
         System.out.println("The file " + filename + " contained the following words:");
         //print out all the found words and their tally's
         for(int i=0;i<foundWords.size();i++) {
            System.out.println(foundWords.get(i).word() + " " + foundWords.get(i).tally());
         }
      }
      catch (FileNotFoundException e) {
         System.out.println ("Error: file not found");
      }
   }

   //method for checking the non-dictionary words for spelling corrections
   public void checkSpelling () {
      //some formatting here
      System.out.println("These words were not found: ");
      //for each word
      for(int i=0;i<notFoundWords.size();i++) {
         String str = notFoundWords.get(i).word();  //set str to current word
         System.out.print(str + "   possible spellings:  ");
         char[] c = str.toCharArray();  //convert str to an array of characters
         //for each character in the string
         for(int j=0;j<c.length-1;j++) {
            c = str.toCharArray();  //reset the character array 
            //these lines are swapping each set of adjacent letters
            char temp = c[j];  
            c[j] = c[j+1];
            c[j+1] = temp;
            String string = String.copyValueOf(c); //convert back to string
            ItemRecord ir = new ItemRecord (string);
            //check to see if the new string is in the dictionary
            if(dictionary.find(ir)) {
                System.out.print(string);
            }
               
         }
         System.out.println(" ");  //formatting
      }
   }   

 
   //this is just a modified version of bubblesort from the previous assignment
   private void doBubblesort(ArrayList<ItemRecord> a) {
      ItemRecord temp;
      for (int i=0; i<a.size()-1; i++) {
         for (int j=0; j<a.size()-1-i; j++) {
            if (a.get(j).word().compareTo(a.get(j+1).word())>0) {
               temp = a.get(j); 
               a.set(j,a.get(j+1));
               a.set(j+1,temp);
            }
         }
      }
   }
 

   //run the program
   public static void main (String[] args) {
      SpellCheck sc = new SpellCheck();
      sc.scanDictionary("unsortedWords.txt");
      sc.scanForWords(args[0]); //filename comes from first cmdline argument
      sc.checkSpelling();
   }
}
