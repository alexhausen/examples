import java.awt.*;

public class AwtFrame {
	public static void main(String [] args) {
		Frame f = new Frame("Title");
		f.setSize(300, 200);
		f.setBackground(Color.red);
		f.show(); 
		while (true) {}
	} 
}

