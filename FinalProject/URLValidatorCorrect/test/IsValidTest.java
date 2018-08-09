import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertFalse;

/**
 * Tests the IsValid Class:
 *
 *  - Query may be null
 *  - Query cannot contain whitespace
 *  - Query excepts all characters
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

        assertFalse(validator.isValid(null));
    }

    @Test
    public void testURLPatternMatch(){

        assertFalse(validator.isValid("?#://?#\n"));
    }
}



