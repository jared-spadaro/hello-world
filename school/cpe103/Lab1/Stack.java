import java.util.Iterator;

public class Stack implements Cloneable
{
   // This array is used to store the items in the stack.

   private Object[] data;

   // This is an index indicating the location of the top item in the stack.

   private int TOS;

   // The following specifies the size of the array in the default constructor.

   private static final int DEFAULT_SIZE = 20;

   public static final int TOP_TO_BOTTOM = 0;
   public static final int BOTTOM_TO_TOP = 1;

   // The following specifies the maximum number of items on the stack that will
   // be included in the toString method.
 
   private static int printLimit = 20;

   // This constructor creates an empty stack using the default array size.

   public Stack()
   {
      data = new Object[DEFAULT_SIZE];  
      TOS = -1;
   }

   // This constructor creates an empty stack using a user-supplied array size.

   public Stack(int initSize)
   {
      if (initSize <=1)
         initSize = DEFAULT_SIZE;
      data = new Object[initSize];  
      TOS = -1;
   }

   // The height of a stack is the number of items it contains. Note that these
   // items are in data[0]..data[TOS].  So the number of items is TOS+1.

   public int height() 
   {
      return TOS+1;
   }

   // This method is used just for our lab activities to report the size of the
   // underlying data array.

   public int capacity() 
   {
      return data.length;
   }
   
   // Create an exact copy of the invoking object

   public Object clone()
   {
      Stack s = new Stack(data.length);
      s.TOS = TOS;
      for(int i=0;i<=TOS;++i)
         s.data[i] = data[i];
      return s;
   }

   public boolean equals(Object x)
   {
      // The following tests are common to all implementations of "equals"
      // in this course, regardless of the class to which it applies.

      if (this == x)
         return true;
      if (x == null)
         return false;
      if (getClass() != x.getClass())
         return false;

      Stack s = (Stack) x;
      if (TOS != s.TOS)
         return false;
      for(int i=0;i<=TOS;++i)
         if (!data[i].equals(s.data[i]))
            return false;
      return true;
   }

   // Add a new item to the top of the stack.  Resize the underlying array if
   // necessary.

   public void push(Object item)
   {
      if (TOS == data.length-1)
      {
         Object[] temp = new Object[(int)(1.5*data.length)];
         for(int i=0;i<data.length;++i)
            temp[i] = data[i];
         data = temp;
      }
      data[++TOS] = item;
   }

   // This method allows the client to control the number of stack items
   // that will be included in the toString method.

   public static void setPrintLimit(int limit)
   {
      if (limit >= 1)
         printLimit = limit;
   }

   // This method produces a string of the form {item1,item2,...} where item1 
   // is the top of the stack. The number of items included is the smaller of 
   // the number of items in the stack and the value of printLimit. The "..."
   // is shown only if there are stack items that were not included.  

   public String toString()
   {
      int limit = Math.min(height(),printLimit);
      String answer = "{";
      for(int i=0;i<limit;++i)
      {
         answer = answer + data[TOS-i];
         if (i != limit-1)
            answer = answer + ",";
      }
      if (height() > limit)
         answer = answer + ",...";
      return answer + "}";
   }
   
   public Object pop()
   {
      if(TOS==-1) throw new Error("Stack contains no items.");
      TOS--;
      return data[TOS+1]; 
   }

   public Object peek()
   {
      if(TOS==-1) throw new Error ("Stack contains no items.");
      return data[TOS];
   }

   // Begin Part II

   // Nested exception class for reporting all errors that occur in Stack methods

   public static class Error extends RuntimeException
   {
      public Error(String message)
      {
         super(message);
      }
   }

        
   public boolean contains(Object item)
   {
     int i;
     for(i=0;i<height();i++) {
       if(item.equals(data[i])) return true;
     }
     return false; 
   }

   public boolean isEmpty()
   {
     if(TOS==-1) return true;
     else return false;  
   }

   public void clear()
   {
     TOS = -1;
   }
  
   public ITR iterator () {
     return new ITR();
   }

   public ITR iterator (int order) {
     return new ITR(order);
   }

   private class ITR implements Iterator {
     int current;
     int order;
     
     public ITR () {
       current = TOS;
       int order = TOP_TO_BOTTOM;
     }

     public ITR (int order) {
       if(order==TOP_TO_BOTTOM) current = TOS;
       else current = 0;
     }
 
     public boolean hasNext () {
       if(order==TOP_TO_BOTTOM) return (current!=-1);
       else return (current!=TOS+1);
     }
   
     public Object next () {
       if(order==TOP_TO_BOTTOM) {
         if(current==-1) throw new Error ("End of list reached.");
         Object temp = data[current];
         current--;
         return temp;
       }
       else {
         if(current==TOS+1) throw new Error ("End of list reached.");
         Object temp = data[current]; 
         current++;
         return temp;
       }
     }

     public void remove () {
       throw new UnsupportedOperationException();
     }
  }
       
     

}



