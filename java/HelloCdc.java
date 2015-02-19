 import java.awt.*;

 public class HelloCdc extends Frame  {

	 public HelloCdc() {
		 super("Draw string");
		 setSize(900, 400);
		 show();
	 }

	 public void paint(Graphics g) {
		Font defaultFont20 = new Font(null, Font.PLAIN, 20);
		g.setFont(defaultFont20);
		FontMetrics metrics = Toolkit.getDefaultToolkit().getFontMetrics(defaultFont20);
		System.out.println("-------------------------------");
		System.out.println("ascent: " + metrics.getAscent());
		System.out.println("descent: " + metrics.getDescent());
		System.out.println("height: " + metrics.getHeight());
		System.out.println("leading: " + metrics.getLeading());
		String str = "AáàãçÇ\"jgZM";
		System.out.println("width: " + metrics.stringWidth(str) + "\n");

		g.setColor(Color.blue);
		g.fillRect(0, 0, 400, 165);

		int x = 50;
		int y = 50;
		int w = metrics.stringWidth(str);
		int h = metrics.getHeight();

		g.setColor(Color.pink);
		g.drawLine(0, 0, x, y);

		g.setColor(Color.white);
		g.drawString(str, x, y);

		//baseline
		g.setColor(Color.yellow);
		g.drawLine(x, y, x + w, y);

		int yy = y - metrics.getAscent();
		g.setColor(Color.green);
		g.drawLine(x, yy, x + w, yy);

		yy = y + metrics.getDescent();
		g.setColor(Color.red);
		g.drawLine(x, yy, x + w, yy);

		/*
		///
		Font defaultFont10 = new Font(null, Font.PLAIN, 10);
		g.setFont(defaultFont10);
		metrics = Toolkit.getDefaultToolkit().getFontMetrics(defaultFont10);

		System.out.println("ascent: " + metrics.getAscent());
		System.out.println("descent: " + metrics.getDescent());
		System.out.println("height: " + metrics.getHeight());
		System.out.println("leading: " + metrics.getLeading());
		System.out.println("width: " + metrics.stringWidth(str));
		System.out.println("-------------------------------");

		x = 50;
		y = 100;
		g.setColor(Color.white);
		g.drawString(str, x, y);

                //baseline
		g.setColor(Color.yellow);
		g.drawLine(x, y, x + w, y);

		yy = y - metrics.getAscent();
		g.setColor(Color.green);
		g.drawLine(x, yy, x + w, yy);

		yy = y + metrics.getDescent();
		g.setColor(Color.red);
		g.drawLine(x, yy, x + w, yy);
		*/
	 }

	 public static void main( String args[] ) {
		HelloCdc app = new HelloCdc();
		app.repaint();
	 }
 }

