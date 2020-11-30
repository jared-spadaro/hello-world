import java.util.*;
import java.io.*;

/****
 * Test CSC 102 Quiz 3.  See the code comments for details of each test case.
 */
public class SolarSystemTest {

    private static int totalPoints = 100;
    private static int summedPoints = 0;

    public static void main(String args[]) {

        // Test 1: Construct a Planet with the default constructor and confirm
        //         its value using toString.
        Planet p = new Planet();
        test(1, 5, p.toString(),
            "Name: null, Mass: 0.0, Diameter: 0.0, Day: 0.0, Moons: 0");
        
        // Test 2: Construct a Planet with the initializing constructor and
        //         confirm its value using toString.
        p = new Planet("Earth", 1, 12760, 1, 1);
        test(2, 5, p.toString(),
            "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1");

        // Test 3: Construct a solar system and confirm its number of planets
        //         is 0.
        SolarSystem ss = new SolarSystem();
        test(3, 5, ss.numPlanets(), 0);

        // Test 4: Confirm that toString on an empty solar system is the empty
        //         string.
        test(4, 5, ss.toString(), "");

        // Test 5: Add a planet and confirm that number of planets is 1.
        ss.add(p);
        test(5, 5, ss.numPlanets(), 1);

        // Test 6: Confirm that SolarSystem.toString works as expected.  Note
        //         that SolarSystem.toString ends with a newline character.
        test(6, 5, ss.toString(),
            "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1\n");

        // Test 7: Confirm that planet named "Earth" can be found in the solar
        //         system.  Use the Planet.getName() method.
        p = ss.find("Earth");
        test(7, 5, p.getName(), "Earth");

        // Test 8: Confirm that planet named "Mars" can NOT be found in the
        //         solar system.
        p = ss.find("Mars");
        test(8, 5, p == null, true);

        // Tests 9 and 10: Add two more planets and confirm size is 3 and
        //         toString works as expected
        ss.add(new Planet("Mars", 0.107, 6787.0, 1.025, 2));
        ss.add(new Planet("Jupiter", 318.0, 428400.0, 0.408, 50));
        test(9, 5, ss.numPlanets(), 3);
        test(10, 5, ss.toString(), threePlanetSolarSystem);

        // Test 11: Confirm that adding duplicate named planet does nothing.
        ss.add(new Planet("Mars", 0, 0, 0, 0));
        test(11, 5, ss.numPlanets(), 3);

        // Test 12: Confirm that removing a planet reduces size by 1.
        ss.remove("Mars");
        test(12, 5, ss.numPlanets(), 2);

        // Test 13: Confirm that removing a non-existent a planet does
        //          nothing.
        ss.remove("Mars");
        test(13, 5, ss.numPlanets(), 2);

        // Tests 14 and 15: Create a new solar system and read from the file
        //         planets.txt.  Confirm that number of planets and toString
        //         values are as expected.
        ss = new SolarSystem();
        ss.readFromFile("planets.txt");
        test(14, 5, ss.numPlanets(), 9);
        test(15, 5, ss.toString(), fullSolarSystem);

        // Test 16: Write to the file planets.out and confirm that it has the
        //         same contents as planets.txt.
        ss.writeToFile("planets.out");
        diff(16, 10, "planets.txt", "planets.out");

        // Test 17: Confirm that sortByName works as expected.
        ss.sortByName();
        test(17, 5, ss.toString(), sortedSolarSystem);

        // Test 18: Confirm that sortByMass works as expected;
        ss.sortByMass();
        test(18, 10, ss.toString(), sortedByMassSolarSystem);


        System.out.println("\n\nTotal Points: " + totalPoints + "/100");

    }

    /**
     * Test that the given string value equals the expected value.
     */
    private static void test(int testNumber, int points,
            String value, String expected) {
        if (! value.equals(expected)) {
            System.out.println("\nFOR TEST " + testNumber +
                "\n    expected: \"" + expected + "\"" +
                "\n         got: \"" + value + "\"" +
                "\n    -" + points + " points\n");
            totalPoints -= points;
        }
        else summedPoints += points;
    }

    /**
     * Test that the given int value equals the expected value.
     */
    private static void test(int testNumber, int points,
            int value, int expected) {
        if (value != expected) {
            System.out.println("\nFOR TEST " + testNumber +
                "\n    expected: " + expected +
                "\n         got: " + value +
                "\n    -" + points + " points\n");
            totalPoints -= points;
        }
        else summedPoints += points;
    }

    /**
     * Test that the given boolean value equals the expected value.
     */
    private static void test(int testNumber, int points,
            boolean value, boolean expected) {
        if (value != expected) {
            System.out.println("\nFOR TEST " + testNumber +
                "\n    expected: " + expected +
                "\n         got: " + value +
                "\n    -" + points + " points\n");
            totalPoints -= points;
        }
        else summedPoints += points;
    }


    /**
     * Test that the given two files are the same using UNIX diff.
     */
    static void diff(int testNumber, int points, String file1, String file2) {
        String diffResults;
        try {
            Process proc = Runtime.getRuntime().exec(
                "diff " + file1 + " " + file2);
            diffResults = getDiffOutput(new Scanner(proc.getInputStream()));
        }
        catch (FileNotFoundException fnfe) {
            System.out.println(fnfe);
            return;
        }
        catch (IOException ioe) {
            System.out.println(ioe);
            return;
        }

        if (!diffResults.equals("")) {
            System.out.println("\nFOR TEST " + testNumber +
                "\n    expected: " + "no file differences from UNIX diff" +
                "\n         got this:\n" + diffResults + "\n" +
                "\n    -" + points + " points\n");
            totalPoints -= points;
        }
        else summedPoints += points;
    }

    /**
     * Return what was sent to stdout by diff.
     */
    static String getDiffOutput(Scanner scan) {
        String output = "";
        while (scan.hasNext()) {
            output += scan.nextLine() + "\n";
        }
        return output;
    }

    // String values of expected outputs:

    static String threePlanetSolarSystem = 
     "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1\n" +
     "Name: Mars, Mass: 0.107, Diameter: 6787.0, Day: 1.025, Moons: 2\n" +
     "Name: Jupiter, Mass: 318.0, Diameter: 428400.0, Day: 0.408, Moons: 50\n";

    static String fullSolarSystem = 
     "Name: Mercury, Mass: 0.055, Diameter: 4878.0, Day: 58.6, Moons: 0\n" +
     "Name: Venus, Mass: 0.815, Diameter: 12194.0, Day: 241.0, Moons: 0\n" +
     "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1\n" +
     "Name: Mars, Mass: 0.107, Diameter: 6787.0, Day: 1.025, Moons: 2\n" +
     "Name: Jupiter, Mass: 318.0, Diameter: 428400.0, Day: 0.408, Moons: 50\n" +
     "Name: Saturn, Mass: 38.0, Diameter: 74900.0, Day: 0.4375, Moons: 53\n" +
     "Name: Uranus, Mass: 14.0, Diameter: 51120.6, Day: 1.333, Moons: 27\n" +
     "Name: Neptune, Mass: 17.0, Diameter: 49530.0, Day: 1.263, Moons: 13\n" +
     "Name: Pluto, Mass: 0.0066, Diameter: 2301.2, Day: 6.4, Moons: 3\n";

    static String sortedSolarSystem = 
     "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1\n" +
     "Name: Jupiter, Mass: 318.0, Diameter: 428400.0, Day: 0.408, Moons: 50\n" +
     "Name: Mars, Mass: 0.107, Diameter: 6787.0, Day: 1.025, Moons: 2\n" +
     "Name: Mercury, Mass: 0.055, Diameter: 4878.0, Day: 58.6, Moons: 0\n" +
     "Name: Neptune, Mass: 17.0, Diameter: 49530.0, Day: 1.263, Moons: 13\n" +
     "Name: Pluto, Mass: 0.0066, Diameter: 2301.2, Day: 6.4, Moons: 3\n" +
     "Name: Saturn, Mass: 38.0, Diameter: 74900.0, Day: 0.4375, Moons: 53\n" +
     "Name: Uranus, Mass: 14.0, Diameter: 51120.6, Day: 1.333, Moons: 27\n" +
     "Name: Venus, Mass: 0.815, Diameter: 12194.0, Day: 241.0, Moons: 0\n";

    static String sortedByMassSolarSystem = 
     "Name: Pluto, Mass: 0.0066, Diameter: 2301.2, Day: 6.4, Moons: 3\n" +
     "Name: Mercury, Mass: 0.055, Diameter: 4878.0, Day: 58.6, Moons: 0\n" +
     "Name: Mars, Mass: 0.107, Diameter: 6787.0, Day: 1.025, Moons: 2\n" +
     "Name: Venus, Mass: 0.815, Diameter: 12194.0, Day: 241.0, Moons: 0\n" +
     "Name: Earth, Mass: 1.0, Diameter: 12760.0, Day: 1.0, Moons: 1\n" +
     "Name: Uranus, Mass: 14.0, Diameter: 51120.6, Day: 1.333, Moons: 27\n" +
     "Name: Neptune, Mass: 17.0, Diameter: 49530.0, Day: 1.263, Moons: 13\n" +
     "Name: Saturn, Mass: 38.0, Diameter: 74900.0, Day: 0.4375, Moons: 53\n" +
     "Name: Jupiter, Mass: 318.0, Diameter: 428400.0, Day: 0.408, Moons: 50\n";

}

