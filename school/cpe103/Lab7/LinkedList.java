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

   // Default Constructor

   public LinkedList()
   {
      first = null;
      last = null;
   }

   // Insert the given object at the beginning of the list.

   public void addFirst(Object item)
   {
      // Supply details as in the assignment description
      Node node = new Node(item);
      if (last == null) last = node;
      node.next = first;
      node.prev = null;
      if (first != null) first.prev = node;
      first = node;
   }

   // Insert the given object at the end of the list.

   public void addLast(Object item)
   {
      // Supply details as in the assignment description
      Node node = new Node(item);
      if (first == null) first = node;
      node.next = null;
      node.prev = last;
      if (last != null) last.next = node;
      last = node;
   }

   // Return the number of items in the list

   public int length()
   {
      // Supply details as in the assignment description
      if (first == null) return 0; 
      Node node = first;
      int len = 1;
	   while (node.next != null) 
	   {
		   len++;
		   node = node.next;
	   }
      return len;
   }

   // Determine if the list contains no items

   public boolean isEmpty()
   {
      // Supply details as in the assignment description
      if (first == null) return true;
      else return false;
   }

   // (Virtually) remove all items from the list

   public void clear()
   {
      first = null;
      last = null;
   }

   // Determine if the list contains the given item

   public boolean contains(Object item)
   {
      // Supply details as in the assignment description
      if (first == null) return false;
      Node node = first;
	   while (node != null) 
	   {
		   if (node.item.equals(item)) return true;
		   node = node.next;
	   }
      return false;
   }

   // Remove first item on the list and return it
   
   public Object removeFirst()
   {
      // Supply details as in the assignment description
      if (first == null) throw new Error("no first item");
      Node node = first;
      first = node.next;
	   if (first == null) last = null;
	   else first.prev = null;
	   return node.item;
   }

   // Remove last item on the list and return it
   
   public Object removeLast()
   {
      // Supply details as in the assignment description
	   if (last == null) throw new Error("no last item");
	   Node node = last;
	   last = node.prev;
	   if (last == null) first = null;
	   else last.next = null;
	   return node.item;
   }
   
   // Determine if two LinkedLists are equal
      
   public boolean equals(Object obj)
   {
      // Supply details as in the assignment description
	   if (this == obj)
		   return true;
	   if (obj == null)
		   return false;
	   if (getClass() != obj.getClass())
		   return false;
	   LinkedList other = (LinkedList)obj;
	   if (other.length() != this.length()) return false;
	   Node thisPtr = first;
	   Node otherPtr = other.first;
	   for (int i=0; i<this.length(); i++) 
	   {
		   if (!(thisPtr.item.equals(otherPtr.item))) return false;
		   thisPtr = thisPtr.next;
		   otherPtr = otherPtr.next;
	   }
      return true;
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

	public boolean remove(Object obj) 
	{
		Node node = first;
		if (first == null) return false;
		while (node != null) 
		{
			if (node.item.equals(obj)) 
			{
				if (node == first) 
				{
					removeFirst();
					return true;
				}
				else if (node == last) 
				{
					removeLast();
					return true;
				}
				else 
				{ // neither first nor last
					node.prev.next = node.next;
					node.next.prev = node.prev;
					return true;
				}
			}
			node = node.next;
		}
		return false;
	}

	public Itr iterator() 
	{
		return new Itr();
	}

	public class Itr implements Iterator 
	{
		private Node current;
		public Itr() 
		{
			current = first;
		}

		public Object next() 
		{
			if (current != null) 
			{
				Object obj = current.item;
				current = current.next;
				return obj;
			}
			throw new Error("iterator error");
		}

		public boolean hasNext() 
		{
			if (current != null) return true;
			else return false;
		}
		public void remove(){}
	}

	public Object clone()
	{
		LinkedList list = new LinkedList();
		Node oldPtr = this.first;
		while (oldPtr != null) 
		{
			list.addLast(oldPtr.item);
			oldPtr = oldPtr.next;
		}
		return list;
	}


   public static class Error extends RuntimeException
   {
      public Error(String message)
      {
         super(message);
      }
   }
}


