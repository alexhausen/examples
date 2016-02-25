public class StringTest {

  public static void main(String[] args) {

    String x = "xyz";
    x.toUpperCase();
    String y = x.replace('Y', 'y');
    y = y + "abc";
    System.out.println(y);
  }

}
