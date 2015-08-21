
import java.util.regex.*;

class Regex {

  public static void main(String[] args) {

    final String s = "<style><![CDATA[\n" +
    "body{\n" + 
    "  resolution:720x480;\n" +
    "  display-aspect-ratio:16v9;\n" +
    "  background-color-index:0;\n" +
    "  used-key-list:basic data-button;\n" +
    "  clut:url(000.clt);\n";

    Pattern p = Pattern.compile(".*clut:url\\((.*)\\).*");
    Matcher m = p.matcher(s);
    if (m.find()) {
      System.out.println(m.group(1));
    }
  }
}
