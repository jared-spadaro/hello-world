import java.util.Iterator;

public class Lab1B
{
   private static int passed = 0;
   private static int failed = 0;
   private static int totalPoints = 0;

   public static void main(String[] args) 
   {  
      try  // Used to catch unexpected exceptions and report partial grade
      {
      System.out.println();
      System.out.println("BEGIN TESTING: Number in parentheses represents the point value");
      System.out.println("of the test case.");
      System.out.println();

      Stack s = new Stack(10);
      int i;
      boolean caught;

      for(i=1;i<=10;++i)
         s.push(new Integer(i));
      System.out.println("Initial contents of stack: " + s);
      Stack s2 = (Stack) s.clone();
      i = 10;
      while(!s.isEmpty())
      {
         System.out.println("Popped " + s.pop() + " Stack now is " + s);
         if (s.height() != --i)
         {
            reportTest("1",1,false);
            i = -1;
            break;
         }
      }
      if (i != -1)
         reportTest("1",1,true);

      s = new Stack(); 
      try
      {
         s.pop();
         caught = false;
      }
      catch (Stack.Error e)
      {
         caught = true;
      }
      reportTest("2",1,caught==true);

      try
      {
         s.peek();
         caught = false;
      }
      catch (Stack.Error e)
      {
         caught = true;
      }
      reportTest("3",1,caught==true);
       
      s = (Stack) s2.clone();
      for(i=10;i>0;--i)
      {
         if (((Integer)s.peek()).intValue() != i)
         {
            reportTest("4",1,false);
            i = -1;
         }
         else
            s.pop();
      }
      if (i != -1)
         reportTest("4",1,true);

      s = (Stack) s2.clone();
      s.clear();
      reportTest("5",1,s.height()==0&&s.isEmpty()&&s.capacity()==s2.capacity());

      s.push(new Integer(0));
      s.pop();
      reportTest("6",1,!s.contains(new Integer(0)));

      s = (Stack) s2.clone();
      for(i=1;i<=10;++i)
      {
         if (!s.contains(new Integer(i)))
         {
            reportTest("7",1,false);
            i = 0;
            break;
         }
      }
      if (i != 0)
         reportTest("7",1,true);

      s = new Stack();
      for(i=1;i<=15;++i)
         if (i%3==0)
            s.push(new Integer(i));
         else if (i%3==1)
            s.push(new Float(i));
         else
            s.push(new String("\""+i+"\""));
      System.out.println("Heterogeneous stack");
      System.out.println("   " + s);

      int failures = 0;
      for(i=1;i<=15;++i)
         if (i%3==0)
         {
            if (!s.contains(new Integer(i)))
               ++failures;
         }
         else if (i%3==1)
         {
            if (!s.contains(new Float(i)))
               ++failures;
         }
         else
         {
            if (!s.contains(new String("\""+i+"\"")))
               ++failures;
         }
      reportTest("8",1,failures==0);


      s = new Stack(1);
      s2 = new Stack(1);
      s.push(new Integer(1));
      s2.push(new Integer(1));
      s.pop();
      reportTest("9",1,!s.equals(s2));

      s = new Stack();
      s2 = new Stack();

      for(i=1;i<=4;++i)
      {
         s2.push(new Integer(i));
         s.push(s2.clone());
      }
      System.out.println("A stack of stacks of Integers");
      System.out.println("   " + s);
      s2 = new Stack();
      reportTest("10",1,!s.contains(s2));
      s2.push(new Integer(1));
      reportTest("11",1,s.contains(s2));
      reportTest("12",1,!s.contains(new Integer(1)));
      Integer x = new Integer(1);
      reportTest("13",1,!s2.equals(x));

      s = new Stack();
      s2 = new Stack();
      s.push(new Integer(1));
      s.pop();
      reportTest("14",1,s.equals(s2));
      reportTest("14A",1,s2.equals(s));

      s = new Stack();
      s2 = new Stack();
      s.push(new Integer(1));
      s.pop();
      s2.push(new Integer(1));
      reportTest("15",1,!s.equals(s2));
      reportTest("15A",1,!s2.equals(s));
      s = new Stack();
      s.push(new Integer(1));
      reportTest("16",1,s.peek().equals(s.peek()));
      
      s = new Stack();
      for(i=1;i<=10;++i)
         s.push(new Integer(i));
      Iterator it = s.iterator();
      i = 10;
      boolean failed = false;
      while(it.hasNext() && !failed)
      {
         x = (Integer) it.next();
         if (!x.equals(new Integer(i)))
            failed = true;
         --i;
      }
      reportTest("Traditional",1,!failed);

      // ********************************************************************
      // You may want to comment out the rest of this method until you
      // finish the first part of the assignment.

      it = s.iterator(Stack.TOP_TO_BOTTOM);
      i = 10;
      failed = false;
      while(it.hasNext() && !failed)
      {
         x = (Integer) it.next();
         if (!x.equals(new Integer(i)))
            failed = true;
         --i;
      }
      reportTest("TOP_TO_BOTTOM",1,!failed);

      it = s.iterator(Stack.BOTTOM_TO_TOP);
      i = 1;
      failed = false;
      while(it.hasNext() && !failed)
      {
         x = (Integer) it.next();
         if (!x.equals(new Integer(i)))
            failed = true;
         ++i;
      }
      reportTest("BOTTOM_TO_TOP",1,!failed);

      // End of commented-out part
      // ********************************************************************


      }  // End of wrapping try block for all of main

      catch (Exception e)
      {
         System.out.println();
         System.out.println(
            "ERROR: Testing is being aborted due to the following unexpected exception.");
       
         // NOTE: The following information is written to System.err and will not be
         // seen if Standard.out is piped to more.

         e.printStackTrace();
         System.out.println();
         System.out.println("INCOMPLETE GRADE");
         System.out.println("   Points Passed.......... " + passed);
         System.exit(1);
      }
      printSummary();
   }
   
   private static void reportTest(String testID,int weight,boolean passedTest)
   {
      totalPoints += weight;
      if (passedTest)
      {
         passed += weight;
         System.out.println("Passed test case " + testID + " (" + weight + ")");
      }
      else
      {
         failed += weight;
         System.out.println("FAILED test case " + testID + " (" + weight + ")");
      }
   }

   private static void printSummary()
   {
      double pct = 100.0*passed/totalPoints;
      int points = (int)Math.round(pct/100.0*25);

      System.out.println();
      System.out.println("TESTING SUMMARY");
      System.out.println("   Total Points...... " + totalPoints);
      System.out.println("   Passed............ " + passed);
      System.out.println("   Failed............ " + failed);
      System.out.println("   Grade............. " + Math.round(pct) + "% = " + 
                                                    points + "/25");
   }
}
