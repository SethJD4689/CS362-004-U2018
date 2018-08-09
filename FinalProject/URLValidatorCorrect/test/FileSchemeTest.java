import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;

import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertEquals;

/**
 * Tests a URL, scheme specific, with the following test rules:
 *
 * - Scheme must end with ":"
 * - Scheme must begin with a letter
 * - Scheme must only include letters, number, "+", ".", and "-"
 * - Scheme capitalization is
 * - Scheme must not be null
 * - Scheme has no length limits
 */
@RunWith(Parameterized.class)
public class FileSchemeTest {

    private UrlValidator validator;
    private static final String SCHEME = "file:";
    private static final String AUTHORITY = "//www.test.com";
    private static final String PORT = "";
    private static final String PATH = "";
    private static final String QUERY = "";

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
        url = null;
    }

    @Parameter
    public static URL url;

    @Parameterized.Parameters(name= "{index}: Scheme - {0}")
    public static List<Object> schemeMutations() {

        Object[] data = new Object[3];

        // Test base case (TRUE)
        data[0] = new URL(SCHEME, AUTHORITY, PORT, PATH, QUERY,
                true, true, true, true, true);

        // Test null authority with file scheme (TRUE)
        data[1] = new URL(SCHEME, "//", PORT, PATH, QUERY,
                true, true, true, true, true);

        // Test authority with colon (FALSE)
        data[2] = new URL(SCHEME, "//:", PORT, PATH, QUERY,
                true, false, true, true, true);

        return Arrays.asList(data);
    }

    @Test
    public void testScheme(){

        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}

