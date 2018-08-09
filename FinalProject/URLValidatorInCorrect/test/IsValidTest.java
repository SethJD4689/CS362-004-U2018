import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

import java.util.Arrays;
import java.util.Collection;
import java.util.Random;

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



