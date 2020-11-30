

public class Faculty extends Person {

    private String department;

    public Faculty (String name, int id, String address, String department) {
        super(name,id,address);
        this.department = department;
    }

    

    public String toString () {
        return super.toString() + "/nDeparment: " + department;
    }




}
        
        
