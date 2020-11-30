import java.util.Properties;

public class SystemProperties
{
   public static void main(String[] args) throws Exception
   {
      System.out.println("\nThe following \"Properties\" are predefined " +
         "and are guaranteed to have a value on\nevery Java client.  " +
         "There are others.\n");
      System.out.println("Version number of the Java system: " + 
                                System.getProperty("java.version"));
      System.out.println("Vendor specific string:            " + 
                                System.getProperty("java.vendor"));
      System.out.println("Vendor URL:                        " + 
                                System.getProperty("java.vendor.url"));
      System.out.println("Java installation directory:       " + 
                                System.getProperty("java.home"));
      System.out.println("Java class version number:         " + 
                                System.getProperty("java.class.version"));
      System.out.println("Java classpath:                    " + 
                                System.getProperty("java.class.path"));
      System.out.println("Operating System Name:             " + 
                                System.getProperty("os.name"));
      System.out.println("Operating System Architecture:     " + 
                                System.getProperty("os.arch"));
      System.out.println("Operating System Version:          " + 
                                System.getProperty("os.version"));
      System.out.println("File separator:                    " + 
                                System.getProperty("file.separator"));
      System.out.println("Path separator:                    " + 
                                System.getProperty("path.separator"));
      System.out.println("User account name:                 " + 
                                System.getProperty("user.name"));
      System.out.println("User home directory:               " + 
                                System.getProperty("user.home"));
      System.out.println("User's current working directory:  " + 
                                System.getProperty("user.dir"));
      System.out.println("Default installed extensions path: " + 
                                System.getProperty("java.ext.dirs"));
      String compiler = System.getProperty("java.compiler");
      if (compiler == null)
         System.out.println("Java-to-native-code compilation not supported");
      else
         System.out.println("Java JIT compiler:                 " + 
                                System.getProperty("java.compiler"));
      System.out.println("Bootstrap class path:              " + 
                                System.getProperty("sun.boot.class.path"));
   }
}


