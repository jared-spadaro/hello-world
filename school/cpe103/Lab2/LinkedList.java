import java.io.*;
import java.util.Iterator;

public class LinkedList implements Cloneable
{

   private class Node
   {
      private Object item;
      private Node next;
      private Node prev;

      private Node(Object x)
      {
         item = x;
         next = null;
         prev = null;
      }
   }

   // Self explanatory instance variables

   private Node first;
   private Node last;
   private int length = 0;

   // Default Constructor

   public LinkedList()
   {
      first = null;
      last = null;
   }

   // Insert the given object at the beginning of the list.

   public void addFirst(Object item)
   {
      Node n = new Node(item);
      if(first==null) {
        first = n;
        last = n;
      }
      else if(first.next==null) {
        n.next = first;
	last.prev = n;
        first = n;
      }
      else {
        n.next = first;
        first.prev = n;
        first = n;
      }
      length++;
   }

   // Insert the given object at the end of the list.

   public void addLast(Object item)
   {
      Node n = new Node(item);
      if(first==null) {
        first = n;
        last = n;
      }
      else if(first.next==null) {
        n.prev = first;
		first.next = n;
		last = n;
      }
      else {
        n.prev = last;
		last.next = n;
        last = n;
      }
	  length++;
      
   }

   // Return the number of items in the list

   public int length()
   {
      return length;
   }

   // Determine if the list contains no items

   public boolean isEmpty()
   {
      if(first==null) return true;
      else return false;
   }

   // (Virtually) remove all items from the list

   public void clear()
   {
      first = null;
      last = null;
      length = 0;
   }

   // Determine if the list contains the given item

   public boolean contains(Object item)
   {
      Node current = new Node(null);
	  if(first==null) return false;
      current = first;
      while(current!=null) {
        if(current.item.equals(item)) return true;
        current = current.next;
      }
      return false;
   }

   // Remove first item on the list and return it
   
   public Object removeFirst()
   {
      Object o;
      if(first==null) throw new Error("List is empty");
      else if(first.next==null) {
	o = first.item;
        first = null;
	last = null;
      }
      else {
        o = first.item;
	first = first.next;
        first.prev = null;
      }
      length--;
      return o;
   }

   // Remove last item on the list and return it
   
   public Object removeLast()
   {
      Object o;
      if(last==null) throw new Error("Linked List is empty");
	  else if (last.prev==null) {
	    o = last.item;
            last = null;
            first = null;
      }
	  else {
	    o = last.item;
	    last = last.prev;
	    last.next = null;
      }
     length--;
      return o;
   }

  public boolean remove (Object o) {
    if(first==null) return false;  //Linked List is empty
    else if(first.next==null) {  //Linked List has one item
      if(first.item.equals(o)) {
       first = null;
       last = null;
       length--;
       return true;
      }
      else return false;
    }
    else {  //Linked List has 2 or more items
      Node current = first.next;
      //int i;
      if(first.item.equals(o)) {      //Item occurs in first
        first = first.next;
        first.prev = null;
        length--;
        return true;
      }

      else { 
        int i=1;                        //Item occurs somewhere in between
        while(i<length()) {      //Run from 2nd link to 2nd-to-last link
          if(current.item.equals(o)) {

            if(i==length()-1) {
              removeLast();
              return true;
            }
            else {
              current.prev.next = current.next;
              current.next.prev = current.prev;
              length--;
              current = null;
              return true;
          }
          //i++;
          //current = current.next;
        }i++;
         current = current.next;}
        return false;
      }

    }
  }

  public Object clone () {
    LinkedList theClone = new LinkedList();
    Node p = this.first;
    while(p!=null) {
      theClone.addLast(p.item);
      p = p.next;
    }
    return theClone;
  }
          
      
      
   
   // Determine if two LinkedLists are equal
      
   public boolean equals(Object o)
   {
      if(o==null) return false;
      if(!(o instanceof LinkedList)) return false;
      LinkedList list = (LinkedList) o;
      if(list.length()!=this.length()) return false;
      Node p = this.first;
      Node q = list.first;
      while(p!=null) {
        if(!(p.item.equals(q.item))) return false;
        p=p.next;
        q=q.next;
      }
      return true;
   }

   public Iterator iterator () {
     return new ITR();
   }

   private class ITR implements Iterator {
     
     public Node current;
     
     public ITR() {
       current = first;
     }
     
     public boolean hasNext () {
       return (current!=null);
     }
     
     public Object next () {
       if(current==null) throw new Error ("End of list reached.");
       Object temp = current.item;
       current = current.next;
       return temp;
     }

     public void remove () {
       throw new UnsupportedOperationException();
     }

   }

   // **********************************************************************

   // FOR THE PURPOSES OF THIS LAB, YOU DON'T NEED TO SPEND TIME READING THE
   // REST OF THIS FILE.  HOWEVER, YOU SHOULD DO SO LATER ON YOUR OWN TIME.

   // The following specifies the maximum number of items in the list that
   // will be included in the toString method.
 
   private static int printLimit = 20;

   // This method allows the client to control the number of list items
   // that will be included in the toString method.

   public static void setPrintLimit(int limit)
   {
      if (limit >= 1)
         printLimit = limit;
   }

   // This method produces a string of the form {item1,item2,...} where item1 
   // is the first item in the list. The number of items included is the smaller 
   // of the number of items in the list and the value of printLimit. The "..."
   // is shown only if there are list items that were not included.  

   public String toString()
   {
      String answer = "{";
      int ctr = 0;
      for(Node curr=first;curr!=null;curr=curr.next)
      {
         answer = answer + curr.item;
         ++ctr;
         if (curr.next != null)
            if (ctr == printLimit)
               return answer + ",...}";
            else
               answer = answer + ",";
      }
      return answer + "}";
   }

   public static class Error extends RuntimeException
   {
      public Error(String message)
      {
         super(message);
      }
   }
}


