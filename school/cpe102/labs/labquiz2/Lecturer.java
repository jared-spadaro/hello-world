

public class Lecturer extends Faculty {

    private int level;

    public Lecturer (String name, int id, String address, String department, int level) {
        super(name,id,address,department);
        this.level = level;
    }

    public String toString () {
        return super.toString() + "/nLevel: " + level;
    }



}
