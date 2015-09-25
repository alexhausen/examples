
import java.nio.charset.Charset;

public class CharsetTest {

  public static void main(String[] args) {
    boolean supported = false;
    String charset = args[0];
    try {
      supported = Charset.isSupported(charset);
    } catch (Exception e) {
      e.printStackTrace();
    }
    System.out.println("Charset '" + charset + "' supported? " + supported);
  }

}
