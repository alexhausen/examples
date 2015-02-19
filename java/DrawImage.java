import java.awt.*;

class CanvasImage extends Component {
	public void paint(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		Image img = Toolkit.getDefaultToolkit().getImage("image.jpg");
		g2.drawImage(img, 0, 0, 500, 500, this);
		g2.finalize();
	}
}

public class DrawImage {
	public static void main(String[] args) {
		Frame f = new Frame();
		f.setSize(500, 500);
		f.add(new CanvasImage());
		f.setVisible(true);
	}

}
