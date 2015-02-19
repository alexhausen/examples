import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.Panel;
import java.awt.Toolkit;
 
 
 
public class t extends Component {
 
    private String subtitle;
    private Image diagram;
    private int x;
    private int y;
    private Button exit;
 
    public t(String subtitle, Image diagram, int x, int y) {
        this.subtitle = subtitle;
        this.diagram = diagram;
        System.out.println(diagram.getSource());
        this.x = x;
        this.y = y;
        System.out.println("Constructor::this.x::" + this.x);
        System.out.println("Constructor::this.y::" + this.y);
    }
 
    public t() {
        // TODO Auto-generated constructor stub
    }
 
    public  void paint(Graphics g) {
         
         
 
        boolean textFits = false;
        Font f = g.getFont();
        FontMetrics fm = g.getFontMetrics();
        System.err.println("=======>START Paint");
 
        if (diagram != null) {
            System.out.println("diagram !=null");
            int diagramHeight = diagram.getHeight(this);
            int diagramWidth = diagram.getWidth(this);
 
            System.out.println("rectangle != null");
            g.setColor(Color.GREEN);
            g.fillRect(this.x, this.y, diagramWidth, diagramHeight + 20);
            g.setColor(Color.BLACK);
 
            while (!textFits) {
 
                if (fm.getHeight() <= 20
                        && fm.stringWidth(subtitle) <= diagramWidth) {
                    System.out.println("text fits");
                    g.drawString(subtitle, this.x, this.y + diagramHeight + 20);
                    textFits = true;
 
                } else {
                    System.out.println("text doesnt fit");
                    g.setFont(f = new Font( f.getName(),
                                            f.getStyle(),
                                            f.getSize() - 1));
                    fm = g.getFontMetrics();
 
                }
 
            }
            //System.out.println("DiagramWidth::" + diagramWidth);
            //System.out.println("DiagramHeight::" + diagramHeight);
            System.out.println("Drawing image at" + this.x+","+ this.y);
            g.drawImage(this.diagram, this.x, this.y, this);
             
        }
        System.err.println("=======>END Paint");
 
    }
 
    public static void main(String[] args) {
 
        MediaTracker mt = new MediaTracker(new t());
        Image a = Toolkit.getDefaultToolkit().getImage("Currency_A.png");
        Image b = Toolkit.getDefaultToolkit().getImage("Games.png");
        Image c = Toolkit.getDefaultToolkit().getImage("Currency_H.png");
 
        try {
            mt.addImage(a, 0);
            mt.addImage(b, 1);
            mt.addImage(c, 2);
            mt.waitForAll();
 
        } catch (Exception e) {
            e.printStackTrace();
        }
 
         
        Frame f = new Frame();
     
        f.setSize(400, 400);
        f.setTitle("FontMetrics test");
         
        t object1 = new t("g.drawRect()", a, 0,0);
        t object2 = new t("Another random subtitle", b,100,100);
        t object3 = new t("This text will fit", c, 200, 200);
 
         
        f.add(object1);
        f.add(object2);
        f.add(object3);
        f.setVisible(true);
        f.repaint();
        System.out.println("COMPLENGTH:"+f.getComponents().length);
         
         
    }
 
}
