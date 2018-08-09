import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import static org.junit.Assert.assertFalse;

/**
 * Tests the IsValid class for complete coverage.
 */
public class IsValidTest {

    private UrlValidator validator;

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);
    }

    @After
    public void teardown(){

        validator = null;
    }

    @Test
    public void testNull(){

        try{
            assertFalse(validator.isValid(null));

        } catch(AssertionError e){

            System.out.println("FAILED NULL TEST: " + e.getMessage());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED NULL TEST: " + e.getMessage());
            throw e;
        }

    }

    @Test
    public void testURLPatternMatch(){

        try{
            assertFalse(validator.isValid("?#://?#\n"));

        } catch(AssertionError e){

            System.out.println("FAILED PATTERN MATCH: " + e.getMessage());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED PATTERN MATCH: " + e.getMessage());
            throw e;
        }
    }
}



