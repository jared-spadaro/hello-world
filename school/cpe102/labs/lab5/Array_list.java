import java.util.ArrayList;

public class Array_list {
    
	private ArrayList<Integer> integers = new ArrayList<Integer>();
    private ArrayList<Double> doubles = new ArrayList<Double>();
    private ArrayList<Boolean> booleans = new ArrayList<Boolean>();
    private ArrayList<String> strings = new ArrayList<String>();

    Array_list() {
	    this.integers = integers;
		this.doubles = doubles;
		this.booleans = booleans;
		this.strings = strings;
	}
	
	
	
	
	
	//Get methods
	public ArrayList<Integer> get_integers () {
	    return this.integers;
	}
	
	public ArrayList<Double> get_doubles () {
	    return this.doubles;
	}
	
	public ArrayList<Boolean> get_booleans () {
	    return this.booleans;
	}
	
	public ArrayList<String> get_strings () {
	    return this.strings;
	}

    //Add methods
    private void add (int x) {
        integers.add(x);
    }

    private void add (double y) {  
        doubles.add(y);
    }
	
	private void add (boolean a) {
	    booleans.add(a);
	}
	
	private void add (String s) {
	    strings.add(s);
	}
	
	public int minimumInt () {      //Finds minimum integer from list
	    if(integers.size()==0) {
		    return 0;
	    }
	    int min = integers.get(0);
	    for(int i:integers) {
		    if (integers.get(i)<min) {
			    min = integers.get(i);
		    }
		}
		return min;
	}
	
	double averageDouble () {         //Finds average of doubles in list
	    if(doubles.size()==0) {
		    return 0;
        }
		int i;
	    double average=0;
		for(i=0;i<doubles.size();i++) {
		    average = average + doubles.get(i);
		}
		average = average / doubles.size();
		return average;
	}
	
	int numberofTrues () {                   //Finds number of trues in list
	    int i;
		int numTrues=0;
		for(i=0;i<booleans.size();i++) {
		    if(booleans.get(i) == true) {
			    numTrues++;
			}
		}
		return numTrues;
	}
	
	int numberofStrings () {              //Finds number of strings in list
	    return strings.size();
	}
	
	
	
	
		
	
	
		
}
