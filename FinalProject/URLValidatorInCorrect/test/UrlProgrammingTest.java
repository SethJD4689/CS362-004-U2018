import org.junit.Before;
import org.junit.Test;

import java.util.Random;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class UrlProgrammingTest {

    private final boolean PRINT_TRUE = true;
    private final boolean PRINT_FALSE = true;

    private UrlValidator validator;
    private URL url;

    private Random random;

    // Scheme,  Domain Name or IP Address, port, path, query
    // Scheme must end with ":"
    // Scheme must begin with a letter
    // Scheme must only include letters, numbers, "+", ".", and "-"
    // Scheme must not be null
    // Scheme has no length limits
    // Port Range - 0 to 65535
    // Port must be preceded by ":"
    // Port can be null;
    // Domain Name / IP Address Range - 0.0.0.0 to 255.255.255.255
    // Domain Name must start with "//"
    // Domain Name Range - 0 to 63 characters per label
    // Domain Name Range - 127 labels total, separated by periods
    // Domain Name Range - 253 characters total including labels and periods
    // Domain Name Characters - letters (non-case sensitive), numbers and "-"
    // Domain Name must not start or end with a "-"
    // Domain Name must not be all numeric
    // Domain must not be null
    // Path may be null
    // Path must be preceded by "/"
    // Query must be preceded with a ?

    @Before
    public void setup() {

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);

        url = new URL("http:", "www.google.com", ":123", "/path", "",
                true, true, true, true, true );

        random = new Random();
        random.setSeed(System.nanoTime());
    }

    @Test
    public void testSchemeVariations(){

        String scheme = url.getScheme();

        // Include a number in the Scheme (TRUE)
        url.setScheme(scheme.substring(0, scheme.length() - 2)
                + random.nextInt(10) + ":", true);
        assertEquals("Test including numbers", validator.isValid(url.getURL()), url.isURLValid());

        // Make scheme upper case (TRUE)
        url.setScheme(scheme.toUpperCase(), true);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Make scheme lower case (TRUE)
        url.setScheme(scheme.toLowerCase(), true);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Add all valid non-alphanumeric characters to scheme (TRUE)
        url.setScheme(scheme.substring(0, scheme.length() - 2)
                + "+" + "." + "-" + ":", true);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Begin scheme with a number (FALSE)
        url.setScheme(random.nextInt(10) + scheme, false);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Scheme has no colon (FALSE)
        url.setScheme(scheme.substring(0, scheme.length() - 2), false);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Scheme is null (FALSE)
        url.setScheme("", false);
        assertEquals(validator.isValid(url.getURL()), url.isURLValid());

        // Reset Scheme
        url.setScheme(scheme, true);
    }

    //@Test
    public void testPortVariations(){

        int choice = 0;

        final int LOWER_LIMIT = 0;          // TRUE
        final int UPPER_LIMIT = 1;          // TRUE
        final int BELOW_LIMIT = 2;          // FALSE
        final int ABOVE_LIMIT = 3;          // FALSE
        final int NULL = 4;                 // TRUE
        final int NO_COLON = 5;             // FALSE

        do { // Test all possible port variations

            switch(choice){

                case(LOWER_LIMIT):

                    url.setPort(":" + "0", true);

                case(UPPER_LIMIT):

                    url.setPort(":" + "65535", true);

                case(BELOW_LIMIT):

                    url.setPort( ":" + "-1" , false);

                case(ABOVE_LIMIT):

                    url.setPort(":" + "65536", false);

                case(NULL):

                    url.setPort("", true);

                case(NO_COLON):

                    url.setPort("12345", false);

                default:
                    choice = 0;

            }

            assertEquals(validator.isValid(url.getURL()), url.isURLValid());

            choice++;

        } while (choice != 0);
    }
}

