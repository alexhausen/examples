//File test

import java.io.File;
import java.io.IOException;

class FileOps {
public static void main(String[] args) {

	File f1 = new File("file1.txt");
	System.out.println("f1: " + f1 + ", " + f1.length() + ", " + f1.exists() + ", " + !f1.isAbsolute());
	System.out.println("f2 parent: " + f1.getParent() + ", " + (f1.getParent() == null));
	System.out.println("f1 abs: " + f1.getAbsolutePath());
	try {
		System.out.println("f1 canonical: " + f1.getCanonicalPath() + ", " + (f1.getCanonicalPath().equals("/home/likewise-open/CERTI/alh/file1.txt")));
	} catch (IOException e) {
		e.printStackTrace();
	}

	File f2 = new File("/home/likewise-open/CERTI/../CERTI/alh/file2.txt");
	System.out.println("\nf2: " + f2 + ", " + f2.length() + ", " + f2.exists() + ", " + f2.isAbsolute());
	System.out.println("f2 parent: " + f2.getParent() + ", "+ (f2.getParent().equals("/home/likewise-open/CERTI/../CERTI/alh")));
	System.out.println("f2 abs: " + f2.getAbsolutePath());
	try {
		System.out.println("f2 canonical: " + f2.getCanonicalPath() + ", " + (f2.getCanonicalPath().equals("/home/likewise-open/CERTI/alh/file2.txt")));
	} catch (IOException e) {
		e.printStackTrace();
	}

//*/
	System.out.println("PASSED");
}

}

