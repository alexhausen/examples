package pkg;

import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

public class KlassTest {

  @Test
  public void method1ReturnsTrue() {
    assertTrue(Klass.method1());
  }

  @Test
  public void method2ReturnsFalse() {
    assertFalse(Klass.method2());
  }

}
