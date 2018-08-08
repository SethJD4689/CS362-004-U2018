import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import static org.junit.Assert.assertEquals;

import java.util.Collection;
import java.util.Random;
import java.util.Arrays;

/**
 * Tests a URL, scheme specific, with the following test rules:
 *
 * - Scheme must end with ":"
 * - Scheme must begin with a letter
 * - Scheme must only include letters, number, "+", ".", and "-"
 * - Scheme must not be null
 * - Scheme has no length limits
 */
@RunWith(Parameterized.class)
public class ProgrammingSchemeTest {

    private static UrlValidator validator;
    private static URL url;
    private static final String SCHEME = "http:";

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(SCHEME, "//www.test.com", "", "", "",
                true, true, true, true, true );
    }

    @Parameter(0)
    public String scheme;

    @Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Scheme - {0}, Expected = {1}")
    public static Collection<Object[]> schemeMutations() {

        Object[][] data = new Object[9][2];

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // Include a number in the Scheme (TRUE)
        data[0][0] = SCHEME.substring(0, SCHEME.length() - 3) + random.nextInt(10) + ":";
        data[0][1] = true;

        // Make scheme upper case (TRUE)
        data[1][0] = SCHEME.toUpperCase();
        data[1][1] = true;

        // Make scheme lower case (TRUE)
        data[2][0] = SCHEME.toLowerCase();
        data[2][1] = true;

        // Add all valid non-alphanumeric characters to scheme (TRUE)
        data[3][0] = SCHEME.substring(0, SCHEME.length() - 3) + "+" + "." + "-" + ":";
        data[3][1] = true;

        // Begin scheme with a number (FALSE)
        data[4][0] = random.nextInt(10) + SCHEME;
        data[4][1] = false;

        // Scheme has no colon (FALSE)
        data[5][0] = SCHEME.substring(0, SCHEME.length() - 3) + "";
        data[5][1] = false;

        // Scheme has no forward slashed (FALSE)
        data[5][0] = SCHEME.substring(0, SCHEME.length() - 2);
        data[5][1] = false;

        // Scheme is null (FALSE)
        data[6][0] = "";
        data[6][1] = false;

        // Scheme contains invalid characters
        data[7][0] = SCHEME.substring(0, SCHEME.length() - 1) + "!@#$%^&*():";
        data[7][1] = false;

        // Build a large string with only valid characters
        final int CAPACITY = 10000;
        StringBuilder largeString = new StringBuilder(CAPACITY);
        final String validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890+.-";

        for(int i = 0; i < CAPACITY - 1; i++){
            largeString.append(validCharacters.charAt(random.nextInt(validCharacters.length())));
        }

        largeString.append(":");

        // Large Scheme Length (TRUE)
        data[8][0] = largeString.toString();
        data[8][1] = true;

        return Arrays.asList(data);
    }

    @Test
    public void testScheme(){

        url.setScheme(scheme, isValid);
        System.out.println(url.getURL());
        System.out.println(url.isURLValid());
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

    }
}
