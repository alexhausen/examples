
public class IntShift {

  public static void main(String[] args) {

    Integer hi = 1;
    Integer low = 2;

    long l = ((long)hi << 31) | (long)low;

    System.out.println("l = " + l);
    //2147483650
  }
}