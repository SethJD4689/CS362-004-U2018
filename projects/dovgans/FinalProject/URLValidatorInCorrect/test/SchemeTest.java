import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.List;
import java.util.Random;
import java.util.Arrays;

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
public class SchemeTest {

    private UrlValidator validator;
    private URL url;

    public static final String BASE_SCHEME = "http:";

    public final static URLPart SCHEMES[] = {

            new URLPart(BASE_SCHEME, true),
            new URLPart("ht7:", true),                           // Include a number in the Scheme
            new URLPart(BASE_SCHEME.toUpperCase(), true),             // Make scheme upper case
            new URLPart(BASE_SCHEME.toLowerCase(), true),             // Make scheme lower case
            new URLPart("HttP:", true),                          // Mix of upper and lower case
            new URLPart("http" + "+" + "." + "-" + ":", true),   // Add all valid non-alphanumeric characters to scheme
            new URLPart("6http:", false),                        // Begin scheme with a number
            new URLPart("http", false),                          // Scheme has no colon
            new URLPart("", false),                              // Scheme is null
            new URLPart("http" + "!@#$%^&*():", false),          // Scheme contains invalid characters
            new URLPart(buildLargeScheme(), true)                     // Large Scheme Length
    };

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(BASE_SCHEME, AuthorityTest.BASE_AUTHORITY, PortTest.BASE_PORT,
                PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true, true, true );
    }

    @After
    public void teardown(){

        validator = null;
        url = null;
        scheme = null;
    }

    @Parameterized.Parameter
    public URLPart scheme;

    @Parameterized.Parameters(name= "{index}: Scheme - {0}")
    public static List<URLPart> schemeMutations() {

        return Arrays.asList(SCHEMES);
    }

    @Test
    public void testScheme(){

        url.setScheme(scheme.getPart(), scheme.isValid());

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        } catch(AssertionError e){

            System.out.println("FAILED SCHEME: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED SCHEME: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;
        }
    }

    private static String buildLargeScheme(){

        Random random = new Random();
        random.setSeed(System.nanoTime());

        final String VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz" +
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890+.-";

        final int CAPACITY = 100;
        StringBuilder largeScheme = new StringBuilder(CAPACITY);

        // Build a large string with only valid characters
        for(int i = 0; i < CAPACITY - 1; i++){
            largeScheme.append(VALID_CHARACTERS.charAt(random.nextInt(VALID_CHARACTERS.length())));
        }

        // Ensure proper format
        largeScheme.append(":");
        largeScheme.insert(0, "a");

        return largeScheme.toString();
    }
}
