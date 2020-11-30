//Program by Jared Spadaro
//CPE103 with Professor Buckalew
//11/16/2013

public class ItemRecord {

   //instance variables
   private String word;
   private int tally;

   //constructor
   public ItemRecord (String x) {
      word = x;
      tally = 0;
   }

   //get method for word
   public String word () {
      return word;
   }

   //set method for word (used in find method)
   public void setWord (String newWord) {
      word = newWord;
   }

   //get method for tally
   public int tally () {
      return tally;
   }

   //method to increment tally
   public void addTally () {
      tally++;
   }

}