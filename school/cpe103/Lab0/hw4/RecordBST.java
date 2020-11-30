//Program by Jared Spadaro
//CPE103 with Professor Buckalew
//11/16/2013

public class RecordBST {

   //inner class node
   private class Node {
      private ItemRecord item;
      private Node left;
      private Node right;
      //constructor 
      private Node (ItemRecord x) {
         item = x;
         left = null;
         right = null;
      }
   }

   private Node root;
   //constructor
   public RecordBST () {
      root = null;
   }

   //method to add items to tree (this is a slightly modified version of the method we wrote in class)
   public void insert (ItemRecord x) {
      if(root==null) root = new Node (x);   
      else {
         Node p = root;
         while(p!=null) {
            if(x.word().compareTo(p.item.word())<0) {   
               if(p.left==null) {
                  p.left = new Node (x); break;
               }
               else p = p.left;
            }
            else {
               if(p.right==null) {
                  p.right = new Node (x); break;
               }
               else p = p.right;
            }
         }
      }
      return;
   }


   //method which checks to see if word can be found in the BST
   //NOTE: was unable to fix bug where plurals/gerunds weren't recognized if they 
   //were a certain way down in the BST (if they were near the top, it worked)
   public boolean find (ItemRecord r) {
      if(root==null) return false;   
      Node p = root;
      String Word = r.word();   //set Word to the ItemRecord's word
      while(p!=null) {
         String dictWord = p.item.word();          //set dictWord to the current dictionary word
         String gerund = dictWord.concat("ing");   //set gerund to dWord plus "ing"
         String plural =  dictWord.concat("s");    //set plural to dWord plus "s"
         String plural2 = dictWord.concat("es");   //set plural2 to dWord plus "es"
         //Check to see if the word or any of its variations matches the word in question
         if(dictWord.compareTo(Word)==0 || gerund.compareTo(Word)==0 || plural.compareTo(Word)==0 || plural2.compareTo(Word)==0) {
            r.setWord(dictWord);   //If they are equal, set ItemRecord's word to the dWord
            return true;        //And return true because the word has been found
         }
         //The words are not equal, so see which way we should proceed down the tree
         //(I kept thinking that this part was the source of my bug, but if that were the case,
         //then why would the problem only arise for plurals/gerunds? *sigh*)
         else if(dictWord.compareTo(Word)>0) {
            p = p.left;
         }
         else {
            p = p.right;
         }        
      }
      return false;
   }













}










