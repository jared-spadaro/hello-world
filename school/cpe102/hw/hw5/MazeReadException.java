import java.io.IOException;

public class MazeReadException extends IOException {

    private String line;
	private int lineNum;
	
	/**
	 * MazeReadException constructor.
	 * @param message for exception to print
	 * @param the line which created the exception
	 * @param the line number which created the exception
	 */
	public MazeReadException (String message, String line, int lineNum) {
	    super(message);
		this.line = line;
		this.lineNum = lineNum;
	}
	
	public String getLine () {
	    return line;
	}
	
	public int getLineNum () {
	    return lineNum;
	}

}