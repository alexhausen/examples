package package2;

public final class Class2 {
  
  private package1.Class1 c = new package1.Class1();

  public static void main(String[] args) {
    Class2 c2 = new Class2();
    c2.c.var1 = true;
    Sytem.out.println("******** Class2 main **********");
  }
}
