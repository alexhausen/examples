import java.util.Vector;

class Gen {
	public static Vector<Integer> x = new Vector<Integer>();

	public static void main(String [] args) {
		Gen.x.add(new Integer(1));
		System.out.println("x" + Gen.x.elementAt(0).toString());
	}

}
