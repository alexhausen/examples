
public class Replace {

static public void main(String[] args) {

  String s = "a<![CDATA[b]]>c";
  String out = s.replace("<![CDATA[", "*-").replace("]]>", "-*");


  System.out.println(out);
}

}
