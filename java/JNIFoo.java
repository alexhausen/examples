//https://blogs.oracle.com/moonocean/entry/a_simple_example_of_jni
//alh@ccd-7835l:~/ProjectsLocal/jvm/mika/Mika/trunk/release/pc/bin$ export LD_LIBRARY_PATH=~/ProjectsRemote/misc/poc/java
//alh@ccd-7835l:~/ProjectsLocal/jvm/mika/Mika/trunk/release/pc/bin$ ./mika -Djava.library.path=~/ProjectsRemote/misc/poc/java -cp ~/ProjectsRemote/misc/poc/java JNIFoo
//java -Djava.library.path=. JNIFoo

public class JNIFoo {    
    public native String nativeFoo();    

    public static native void f(int[] v);

    static {
        System.loadLibrary("foo");
    }        

    public static void print2() {
        System.out.println("static print2");
    }

    public void print () {
        String str = nativeFoo();
        System.out.println(str);
    }
    
    public static void main(String[] args) {
        (new JNIFoo()).print();
        print2();
	f(new int[]{0, 1, 2, 3, 4, 5});
    }
}
