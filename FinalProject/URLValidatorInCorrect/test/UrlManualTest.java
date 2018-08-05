import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;

public class UrlManualTest {

    private UrlValidator validator;

    @Before
    public void setUp() {

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_ALL_SCHEMES);
    }


    @Test
    public void manualTests(){

        assertFalse("Hello World", validator.isValid("sjdhfaskjdhfaklsh"));
        assertFalse(validator.isValid("aqweoiruqwoeiru"));

    }
}
