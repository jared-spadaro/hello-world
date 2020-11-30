import java.util.Scanner;

public interface DelimitedTextIO {

    String toText (char delimiter);
	
	void toObject (Scanner input);
	
}