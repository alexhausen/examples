import java.awt.*;

public class MyLabel extends Component {

	private String text;

	MyLabel(int x, int y, String text) {
		this.text = text;
		setBounds(x, y, 10, 10);
		setVisible(true);
	}

	public void paint(Graphics g) {
		Font font20 = new Font(null, Font.PLAIN, 20);
		FontMetrics metrics = getFontMetrics(font20);
		int w = metrics.stringWidth(text);
		int h = metrics.getHeight();
		int x = getLocation().x;
		int y = getLocation().y;

		g.setColor(Color.white);
		g.fillRect(x, y, 100, 50);
		g.setFont(font20);
		g.setColor(Color.black);
		g.drawString(text, x, y);

		System.out.println("MyLabel.paint (" +x + "," + y + "," + w + "," + h + ") " + text);
	}

	public static void main( String args[] ) {
		Frame f = new Frame();
		f.setSize(640, 480);
		f.setTitle("Label test");
	        f.setVisible(true);
		f.setLayout(new FlowLayout());

		Component lbl1 = new MyLabel(50, 10, "label 1");
		f.add(lbl1);

		f.repaint();
	}
}
