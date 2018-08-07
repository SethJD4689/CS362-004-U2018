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
 * Tests a URL, domain specific, with the following test rules:
 *
 * - Domain Name / IP Address Range - 0.0.0.0 to 255.255.255.255
 * - Domain Name must start with "//"
 * - Domain Name Range - 0 to 63 characters per label
 * - Domain Name Range - 127 labels total, separated by periods
 * - Domain Name Range - 253 characters total including labels and periods
 * - Domain Name Characters - letters (non-case sensitive), numbers and "-"
 * - Domain Name must not start or end with a "-"
 * - Domain Name must not be all numeric
 * - Domain must not be null
 */
@RunWith(Parameterized.class)
public class ProgrammingAuthorityTest {

    private static UrlValidator validator;
    private static URL url;
    private static final String AUTHORITY = "www.test.com";

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL("ftp://", AUTHORITY, ":80", "/test1", "?action=view",
                true, true, true, true, true );
    }

    @Parameterized.Parameter(0)
    public String authority;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Authority - {0}, Expected = {1}")
    public static Collection<Object[]> authorityMutations() {

        Object[][] data = new Object[7][2];

        final int LOWER_LIMIT = 0;
        final int UPPER_LIMIT = 255;

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // IP Address Lower Limit
        data[0][0] = LOWER_LIMIT + "." + LOWER_LIMIT + "." + LOWER_LIMIT + "." + LOWER_LIMIT;
        data[0][1] = true;

        // IP Address Upper Limit
        data[1][0] = UPPER_LIMIT + "." + UPPER_LIMIT + "." + UPPER_LIMIT + "." + UPPER_LIMIT;
        data[1][1] = true;

        // IP Address below limit
        data[2][0] = (LOWER_LIMIT - 1) + "." + LOWER_LIMIT + "." + LOWER_LIMIT + "." + LOWER_LIMIT;
        data[2][1] = false;

        // IP Address above limit
        data[3][0] = (UPPER_LIMIT + 1) + "." + UPPER_LIMIT + "." + UPPER_LIMIT + "." + UPPER_LIMIT;
        data[3][1] = false;

        // Short IP Address
        data[4][0] = "172.5.3";
        data[4][1] = false;

        // Long IP Address
        data[5][0] = "172.5.3.189.4";
        data[5][1] = false;

        // No forward slashes
        data[6][0] = AUTHORITY.substring(2, AUTHORITY.length());
        data[6][1] = true;

        return Arrays.asList(data);
    }

    @Test
    public void testAuthority(){

        url.setPort(authority, isValid);
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}
