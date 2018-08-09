import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertEquals;

/**
 * Tests a URL, port specific, with the following test rules:
 *
 * - Port Range - 0 to 65535
 * - Port must be preceded by ":"
 * - Port can be null
 */
@RunWith(Parameterized.class)
public class PortTest {

    private UrlValidator validator;
    private URL url;

    public static final String BASE_PORT = "";                      // Null Value

    public static final URLPart PORTS[] = {

            new URLPart(BASE_PORT, true),
            new URLPart(":0", true),                    // Lower Limit
            new URLPart(":65535", true),                // Upper Limit
            new URLPart(":-1", false),                  // Below Limit
            new URLPart(":655536", false),              // Above Limit
            new URLPart(":", true),                     // No Port #
            new URLPart("12345", false),                // No Colon
            new URLPart("abc", false),                  // Invalid Characters
            new URLPart(":" + Long.MAX_VALUE, false),   // Above Integer Limit
    };

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(SchemeTest.BASE_SCHEME, AuthorityTest.BASE_AUTHORITY,
                BASE_PORT, PathTest.BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true,
                true, true );
    }

    @After
    public void teardown(){

        validator = null;
        url = null;
        port = null;
    }

    @Parameterized.Parameter
    public URLPart port;

    @Parameterized.Parameters(name= "Port Test {0}")
    public static List<URLPart> portMutations() {

        return Arrays.asList(PORTS);
    }

    @Test
    public void testPort(){

        url.setPort(port.getPart(), port.isValid());
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}

