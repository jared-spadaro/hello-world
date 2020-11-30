

public class Student extends Person {

    private String major;
    private int year;

    public Student (String name, int id, String address, String major, int year) {
        super(name,id,address);
        this.major = major;
        this.year = year;
    }

    public String toString () {
        return super.toString() + "/nMajor: " + major + "/nYear: " + year;
    }



}
