// Program 3: Visual Sort
// By Jared Spadaro
// CPE103 with Professor Buckalew

import java.awt.*;
import java.applet.Applet;
import javax.swing.*;
import java.awt.event.*;
import java.util.*;

public class SortDriver extends Applet {
   
   private int array[];  // array to be sorted
   private int limit = 1000;  // size of array to be sorted - you may have to make
                              // this bigger for faster sorts
  
   //these are constants for use when loading array
   private static final int RANDOM = 0;
   private static final int ORDERED = 1;
   private static final int REVERSE = 2;

   private int largestNum; // need to know for color scaling purposes in paint()

   // flag to tell paint() whether to paint a single location or the whole array
   private enum PaintType {ALL, SINGLE};
   private PaintType doPaint = PaintType.ALL;

   private int index = -1;  // index of single array location to be painted

   //this listener object responds to button events
   private ButtonActionListener buttonListener;
   
   //button to start the sort
   private JButton startSort;
   
   // the picture of the sort will appear on this canvas
   private SortCanvas picture;
   private final int pictureWidth = 1001;  // size of the sort bar
   private final int pictureHeight = 50;

   // put buttons and canvas on this panel
   private JPanel sortPanel;

   // put radio buttons on this panel
   private JPanel radioPanel;
   private JPanel arrayPanel;
   private JPanel colorPanel;

   // declarations for some more GUI elements
   private JLabel label; // a non-interactive text field
   private JLabel colorLabel; //label for color radio buttons
   private JRadioButton r1, r2, r3, r4; // radio buttons
   private JRadioButton random,ordered,reverse; //radio buttons for array type selection
   private JRadioButton blue,green,red,purple; //radio buttons for color selection
   private ButtonGroup rButtons;
   private ButtonGroup arrayType;
   private ButtonGroup arrayColor;
   private JTextField rText; // you can type text into this field
     
   public void init() {

      buttonListener = new ButtonActionListener();

      array = new int[limit];
      // load the array (see below for array initialization methods)
      randomArray();

      // set up the window
      sortPanel = new JPanel();
      sortPanel.setLayout(new BoxLayout(sortPanel, BoxLayout.Y_AXIS));
      
      // first place the sort bar on top
      picture = new SortCanvas();
      sortPanel.add(picture);
      
      // now place a button
      startSort = new JButton("Start");
      // the listener is triggered when the button is clicked
      startSort.addActionListener(buttonListener);
      sortPanel.add(startSort);

      // here's some more code that you may find useful
      // they're all wide because of the BoxLayout:Y-AXIS

      label = new JLabel("Welcome to VisualSort 3.0! Hit start and be amazed!"); 
      label.setHorizontalAlignment(JLabel.CENTER);
      label.setHorizontalTextPosition(JLabel.CENTER);
      sortPanel.add(label);

      // text field with room for 20 characters
      rText = new JTextField("Enter size of array here", 20);
      rText.setHorizontalAlignment(JTextField.CENTER);
      rText.addActionListener(buttonListener); 
      sortPanel.add(rText);

      // put these buttons in their own panel
      radioPanel = new JPanel();
      radioPanel.setLayout(new BoxLayout(radioPanel, BoxLayout.X_AXIS));
      
      // radio buttons for selection of the sort
      r1 = new JRadioButton("BubbleSort", true); // true sets this button by default
      r1.addActionListener(buttonListener);
      radioPanel.add(r1);

      r2 = new JRadioButton("InsertionSort", false); 
      r2.addActionListener(buttonListener);
      radioPanel.add(r2);

      r3 = new JRadioButton("MergeSort", false); 
      r3.addActionListener(buttonListener);
      radioPanel.add(r3);

      r4 = new JRadioButton("QuickSort", false); 
      r4.addActionListener(buttonListener);
      radioPanel.add(r4);
   
      // radio buttons have to be added to a ButtonGroup to work
      rButtons = new ButtonGroup(); 
      rButtons.add(r1);
      rButtons.add(r2);
      rButtons.add(r3);
      rButtons.add(r4);

      // now add the radio panel to the sort panel
      sortPanel.add(radioPanel);

     
/************Initialize panel for array type selection************/
      arrayPanel = new JPanel();
      arrayPanel.setLayout(new BoxLayout(arrayPanel, BoxLayout.X_AXIS));
      // radio buttons
      random = new JRadioButton("Random", true); // true sets this button by default
      random.addActionListener(buttonListener);
      arrayPanel.add(random);

      ordered = new JRadioButton("Ordered", false); 
      ordered.addActionListener(buttonListener);
      arrayPanel.add(ordered);

      reverse = new JRadioButton("Reverse", false); 
      reverse.addActionListener(buttonListener);
      arrayPanel.add(reverse);
   
      // radio buttons have to be added to a ButtonGroup to work
      arrayType = new ButtonGroup(); 
      arrayType.add(random);
      arrayType.add(ordered);
      arrayType.add(reverse);

      sortPanel.add(arrayPanel);

/***********Initialize panel for color selection*************/
      colorLabel = new JLabel ("Pick a color!");
      sortPanel.add(colorLabel);

      colorPanel = new JPanel();
      colorPanel.setLayout(new BoxLayout(colorPanel, BoxLayout.X_AXIS));
      // radio buttons
      blue = new JRadioButton("Blue", false); // true sets this button by default
      blue.addActionListener(buttonListener);
      colorPanel.add(blue);

      red = new JRadioButton("Red", false); 
      red.addActionListener(buttonListener);
      colorPanel.add(red);

      green = new JRadioButton("Green", true); 
      green.addActionListener(buttonListener);
      colorPanel.add(green);
   
      purple = new JRadioButton("Purple", false); 
      purple.addActionListener(buttonListener);
      colorPanel.add(purple);

      // radio buttons have to be added to a ButtonGroup to work
      arrayColor = new ButtonGroup(); 
      arrayColor.add(blue);
      arrayColor.add(red);
      arrayColor.add(green);
      arrayColor.add(purple);

      sortPanel.add(colorPanel);

      // add the panel to the window
      add(sortPanel);
      
      picture.paint(picture.getGraphics());
   }
       
   
   // this object is triggered whenever a button is clicked
   private class ButtonActionListener implements ActionListener {
      public void actionPerformed(ActionEvent event) {
          
         // find out which button was clicked 
         Object source = event.getSource();
         
         // start sort button was clicked
         if (source == startSort) {
            //check to see which sort is selected, then perform that sort
            if(r1.isSelected()==true) {
              doBubblesort();
            }
            else if(r2.isSelected()==true) {
              doInsertionSort(array);
            }
            else if(r3.isSelected()==true) {
              doMergeSort(0,array.length-1);
            }
            else {
              doQuickSort(0,array.length-1);
            }
         }
         //if the "random" radio button is clicked, repaint the bar with a random array 
         if (source == random) {
           initArray(limit,RANDOM);
         }
         //if the "ordered" radio button is clicked, repaint the bar with an ordered array
         if (source == ordered) {
           initArray(limit,ORDERED);
         }
         //if the "reverse" radio button is clicked, repaint the bar with a reverse array
         if (source == reverse) {
           initArray(limit,REVERSE);
         }
         //if a color button is clicked, repaint the bar with the specified color
         if (source == blue || source == red || source == green || source == purple) {
           doPaint = PaintType.ALL;
           picture.paint(picture.getGraphics());
         }

         // called when user hits return in text field
         if (source == rText) {
            limit = Integer.parseInt(rText.getText());
            //if the random radio button is selected, repaint bar with random array and new limit
            if(random.isSelected()==true) initArray(limit,RANDOM);
            //if the ordered radio button is selected, repaint the bar with an ordered array and new limit
            else if(ordered.isSelected()==true) initArray(limit,ORDERED);
            //if the reverse radio button is selected, repaint the bar with a reverse array and new limit
            else initArray(limit,REVERSE);
         }
      }    
   }

/**********************************************BUBBLE SORT********************************************************/

   private void doBubblesort() {
      int temp;

      // this is just bubblesort
      for (int i=0; i<limit-1; i++) {
         for (int j=0; j<limit-1-i; j++) {
            if (array[j]>array[j+1]) {
               temp = array[j]; array[j] = array[j+1]; array[j+1] = temp;
                  
               // redraw only locations j and j+1
               doPaint = PaintType.SINGLE;  // try changing this to ALL and see what happens
               index = j; 
               picture.paint(picture.getGraphics());
               index = j+1; 
               picture.paint(picture.getGraphics());
            }
         }
      }
   }

/***********************************************INSERTION SORT*********************************************************/

   public void doInsertionSort (int[] array) {
     int i,j,temp;                   
     for(i=1;i<array.length;i++) {            //for each element 
       int position = linearSearch(array,i);  //position where the element is to be inserted
       if(position!=i) {                      //make sure that a shift is needed
         temp = array[i];         
         for(j=i;j>position;j--) {            //run loop from position of current element to its insertion spot
           array[j] = array[j-1];             //shift elements to the left
           doPaint = PaintType.SINGLE;
           index = j-1;
           picture.paint(picture.getGraphics());
           index = j;
           picture.paint(picture.getGraphics());       
         }
         array[position] = temp;              //insert element 
       }
     }
   }
   
  //Linear Search Method
  public int linearSearch (int[] array, int begin) {
    for(int i=begin-1;i>=0;i--) {                   //from current element to beginning of list
      if (array[i]<=array[begin]) return i+1;       //if x[i] is less than current element, we want to insert after x[i]. so return i+1
    }                                                 
    return 0;                                       //if loop makes it to end, element must be smallest. so return 0 
  }

/******************************************************MERGE SORT**************************************************************/


  //mergeSort method, called when start button is clicked
  public void doMergeSort (int begin, int end) {
    if(end-begin>=1) {                //As long as there is at least one element
      int mid = (begin+end)/2;
      doMergeSort(begin,mid);
      doMergeSort(mid+1,end);
      merge(begin,end); 
    }
    doPaint = PaintType.SINGLE;  
    //Paint only if there is more than 20 elements (greatly reduces number of calls)    
    if(end-begin+1>20) {          
      for(int i=begin;i<=end;i++) {
        index = i;
        picture.paint(picture.getGraphics());
      }
    }
  }
   
  //this merge method is very similar to the one we wrote in lab 
  private void merge(int begin, int end) { 
     int j = 0;
     int mid = (begin+end)/2;
     int[] temp = new int[end-begin+1];
     int leftMarker = begin;
     int leftEnd = mid;
     int rightMarker = mid+1;
     int rightEnd = end;
     int tempMarker = 0;
     while((leftMarker<=leftEnd)&&(rightMarker<=rightEnd)) {
       if(array[leftMarker]<=array[rightMarker]) {
         temp[tempMarker] = array[leftMarker];
         leftMarker++;
         tempMarker++;
       }
       else {
         temp[tempMarker] = array[rightMarker];
         rightMarker++;
         tempMarker++;
       }
     }
     while(leftMarker<=leftEnd) {
       temp[tempMarker] = array[leftMarker];
       leftMarker++;
       tempMarker++;
     }
     while(rightMarker<=rightEnd) {
       temp[tempMarker] = array[rightMarker];
       rightMarker++;
       tempMarker++;
     }
     for(int i=begin;i<=end;i++) {
       array[i] = temp[j];
       j++;
     }
  }


/***********************************************QUICK SORT*********************************************************/
  
   //quickSort method, called when start button is clicked
   private void doQuickSort(int first,int last)  
   {
      int size = last-first+1;
      if (size <= 20)
         binaryInsertionSort(array,first,last);
      else {
         int p = partition(array,first,last);
         doQuickSort(first,p-1); 
         doQuickSort(p+1,last);
         doPaint = PaintType.SINGLE;
         //Only paint if size > 20 (otherwise binary insertion sort is used and no painting is done)
         for(int i=first;i<=last;i++) {
           index = i;
           picture.paint(picture.getGraphics());
         }
      }
   }

   //this method was pulled from Lab 4
   private int partition(int[] data,int first,int last)
   {
      int left = first+1;
      int right = last;
      int temp;
      while(true)
      {
         while(left<=right && data[left]<=data[first])
            ++left;
         while(right>=left && data[first]<data[right])
            --right;
         if (left > right)
            break;
         temp = data[left];
         data[left] = data[right];
         data[right] = temp;
         ++left;
         --right;
      } 
      temp = data[first];
      data[first] = data[right];
      data[right] = temp;
      return right;
   }

   //this method was pulled from Lab 4
   private static void binaryInsertionSort(int[] data,int first,int last)
   {
      for(int i=first+1;i<=last;++i)
      {
         int target = binarySearch(data,data[i],first,i-1);
         if (target != i)
         {
            int temp = data[i];
            for(int j=i;j>target;--j)
               data[j] = data[j-1];
            data[target] = temp;
         }
      }
   }
  
   //this method was pulled from Lab 4
   private static int binarySearch(int[] data,int x,int first,int last)
   {
      int middle = 0;
      while(first<=last)
      {
         middle = (first+last)/2;
         if (x<data[middle])
            last = middle - 1;
         else if (x>data[middle])
            first = middle + 1;
         else
            return middle + 1;  
      }
      if (x>data[middle])
         return middle + 1;
      else
         return middle;
   }

/*********************************************END SORT METHODS**************************************************/

/***************************************BEGIN ARRAY INITIALIZATION**********************************************/
      
   //this method initializes array 
   public void initArray (int size, int type) {
      array = new int[size];
      if(type==RANDOM) randomArray();
      else if(type==ORDERED) orderedArray();
      else reverseArray();
      //repaint the entire color bar after the array has been initialized
      doPaint = PaintType.ALL;
      picture.paint(picture.getGraphics());
   }

  //this method loads a random array
  public void randomArray () {
     largestNum = array[0] = (int) (Math.random()*1000000.0);
     for (int i=1; i<limit; i++) {
       array[i] = (int) (Math.random()*1000000.0);
       // also keep track of the largest so that we can scale by it in paint()
       if (array[i] > largestNum) largestNum = array[i]; 
     }
  }
  
  //this method loads an ordered array
  public void orderedArray () {
     for(int i=0;i<limit;i++) {
       array[i] = i;
     }
     largestNum = array[limit-1];
  }
 
  //this method loads a reverse array
  public void reverseArray () {
     int j=0;
     for(int i=limit-1;i>=0;i--) {
       array[j] = i;
       j++;
     }
     largestNum = array[0];
  }

/****************************************END ARRAY INITIALIZATION************************************/
    
   class SortCanvas extends Canvas {
      // this class paints the sort bar 
       
      SortCanvas() {
         setSize(pictureWidth, pictureHeight);
         setBackground(Color.white);
      }
       
      public void paint(Graphics g) {
         
         if (doPaint == PaintType.ALL) {
            // paint whole array - this takes time so it shouldn't be done too frequently
            setBackground(Color.white);
            g.setColor(Color.white);
            g.fillRect(0, 0, pictureWidth, pictureHeight);
            
            for (int i=0; i<limit; i++) {
               // the larger the number, the brighter green it is
               // green is between 0.0 and 1.0
               // divide by the largest number to get a value between 0 and 1
               float green = (float)(array[i]/(float)largestNum);

               // clamp if necessary - it shouldn't be
               if (green<0f) green = 0f;
               if (green>1f) green = 1f;
               
               //MY CODE HERE
               //check to see which color is selected, then set color to that
               if(red.isSelected()) g.setColor(new Color(green, 0.0f, 0.0f)); 
               else if(blue.isSelected()) g.setColor(new Color(0.0f,0.0f,green)); 
               else if(purple.isSelected()) g.setColor(new Color(green,0.0f,green));
               else g.setColor(new Color(0.0f,green,0.0f));
               
               // array location 0 is painted at left; 
               //array location limit-1 is painted to right
               //this is a single vertical line in the bar
               g.drawLine((int)(i*pictureWidth/limit), 0, 
                          (int)(i*pictureWidth/limit), pictureHeight);
            }
         }
         else {
            // just paint one location on the bar
            float green = (float)(array[index]/(float)largestNum);
            if (green<0f) green = 0f;
            if (green>1f) green = 1f;
            
            //MY CODE HERE
            //check to see which color is selected, then set color to that
            if(red.isSelected()) g.setColor(new Color(green, 0.0f, 0.0f)); 
            else if(blue.isSelected()) g.setColor(new Color(0.0f,0.0f,green)); 
            else if(purple.isSelected()) g.setColor(new Color(green,0.0f,green));
            else g.setColor(new Color(0.0f,green,0.0f));

            g.drawLine((int)(index*pictureWidth/limit), 0, 
                       (int)(index*pictureWidth/limit), pictureHeight);
         }   
      }
   }
}