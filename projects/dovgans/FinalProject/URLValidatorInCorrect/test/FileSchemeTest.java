import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import static org.junit.Assert.assertEquals;

import java.util.List;
import java.util.Arrays;

/**
 * Tests file scheme specific rules.
 */
@RunWith(Parameterized.class)
public class FileSchemeTest {

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
        url = null;
    }

    @Parameter
    public static URL url;

    @Parameterized.Parameters(name= "{index}: Scheme - {0}")
    public static List<Object> schemeMutations() {

        final String SCHEME = "file:";

        Object[] data = new Object[3];

        // Test base case (TRUE)
        data[0] = new URL(SCHEME, AuthorityTest.BASE_AUTHORITY, PortTest.BASE_PORT, PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true, true, true);

        // Test null authority with file scheme (TRUE)
        data[1] = new URL(SCHEME, "//", PortTest.BASE_PORT, PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true, true, true);

        // Test authority with colon (FALSE)
        data[2] = new URL(SCHEME, "//:", PortTest.BASE_PORT, PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, false, true, true, true);

        return Arrays.asList(data);
    }

    @Test
    public void testScheme(){

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        } catch(AssertionError e){

            System.out.println("FAILED FILE SCHEME: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED FILE SCHEME: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;
        }
    }
}

