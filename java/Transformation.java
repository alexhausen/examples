import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.StringWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.Charset;
import java.util.Scanner;

import javax.net.ssl.SSLException;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

class Transformation {

  public static void main(String args[]) {

    try {

      DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
      dbf.setNamespaceAware(true);
      DocumentBuilder db = dbf.newDocumentBuilder();
      Scanner s = new Scanner(new FileInputStream(new File(args[0])), "ISO-8859-1").useDelimiter("\\A");
      String rawDocument = s.hasNext() ? s.next() : "";
/*
      ByteArrayInputStream byteStream = new ByteArrayInputStream(rawDocument.getBytes(Charset.forName("ISO-8859-1")));
      Document document = db.parse(byteStream);
      Transformer transformer = TransformerFactory.newInstance().newTransformer();
      StreamResult result = new StreamResult(new StringWriter());
      DOMSource source = new DOMSource(document);
      transformer.transform(source, result);
      String xmlString = result.getWriter().toString();
      System.out.println(xmlString);
*/
    } catch (Exception e) {
      e.printStackTrace();
    }

  }

}
