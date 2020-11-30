 

public class Stack implements Cloneable
{
   // This array is used to store the items in the stack.

   private Object[] data;

   // This is an index indicating the location of the top item in the stack.

   private int TOS;

   // The following specifies the size of the array in the default constructor.

   private static final int DEFAULT_SIZE = 20;

   // The following specifies the maximum number of items on the stack that
   // will be included in the toString method.
 
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

   public static class Error extends RuntimeException {
     public Error (String message) {
       super(message);
     }
   }

   // The height of a stack is the number of items it contains. Note that these
   // items are in data[0]..data[TOS].  So the number of items is TOS+1.

   public int height() 
   {
      return TOS+1;
   }

   // This method is used just for our lab activities to report the size of the
   // underlying data array.  It would not be included in a real stack class,
   // since the user should be unaware of the array nature of the implementation.

   public int capacity() 
   {
      return data.length;
   }
   
   public Object clone()
   {
      // Fill in the details.  The clone must have the same capacity, height,
      // and data values (in the correct order) as the object being cloned.
      // Do not waste execution time by copying irrelevant objects in the data
      // array.
      Stack theClone = new Stack(this.capacity());
      int i;
      for (i=0;i<this.height();i++) {
         theClone.data[i] = this.data[i];
      }
      theClone.TOS = this.TOS;
      return theClone;
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
      Stack stk = (Stack)x;
      if(stk.height()!=this.height()) 
         return false;
      int i;
      if(stk.TOS!=this.TOS) return false;
      for(i=0;i<TOS;i++) {
         if(stk.data[i] != this.data[i]) {
            return false;
         }
      }
      return true;

      // Fill in the remaining details.
   }

   public void push(Object item)
   {
      if(this.height()==this.capacity()) {
        int i;
        Object[] temp;
        temp = new Object[this.capacity() * 2];
        for (i=0;i<this.height();i++) {
          temp[i] = data[i];
        }
        data = temp;
      }
      if(item.getClass()!=this.getClass()) {
        data[TOS+1] = item;
        TOS++;
      }
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
      // Fill in the details as required on the assignment sheet.
      if(TOS==-1) throw new Error("Stack contains no items.");
      TOS--;
      return data[TOS+1];
   }

   public Object peek()
   {
      // Fill in the details as required on the assignment sheet.
      if(TOS==-1) throw new Error ("Stack contains no items.");
      return data[TOS];
   }

}



