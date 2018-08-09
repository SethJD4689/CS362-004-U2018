import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import java.util.Random;

/**
 * Tests a URL, port specific, with the following test rules:
 *
 * - Port Range - 0 to 65535
 * - Port must be preceded by ":"
 * - Port can be null
 */
@RunWith(Parameterized.class)
public class ProgrammingPortTest {

    private static UrlValidator validator;
    private static URL url;

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL("http:", "//www.test.com", "", "", "",
                true, true, true, true, true );
    }

    @Parameterized.Parameter(0)
    public String port;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Port - {0}, Expected = {1}")
    public static Collection<Object[]> portMutations() {

        Object[][] data = new Object[9][2];

        final int LOWER_LIMIT = 0;
        final int UPPER_LIMIT = 65535;
        final String PRECURSOR = ":";

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // Port Lower Limit
        data[0][0] = PRECURSOR + LOWER_LIMIT;
        data[0][1] = true;

        // Port Upper Limit
        data[1][0] = PRECURSOR + UPPER_LIMIT;
        data[1][1] = true;

        // Port below limit
        data[2][0] = PRECURSOR + (LOWER_LIMIT - 1);
        data[2][1] = false;

        // Port above limit
        data[3][0] = PRECURSOR + (UPPER_LIMIT + 1);
        data[3][1] = false;

        // No Port Number
        data[4][0] = PRECURSOR;
        data[4][1] = true;

        // No port
        data[5][0] = "";
        data[5][1] = true;

        // No preceded colon
        data[6][0] = random.nextInt(UPPER_LIMIT + 1) + "";
        data[6][1] = false;

        // Letters in port versus numbers
        data[7][0] = PRECURSOR + "abc";
        data[7][1] = false;

        // Port above Integer Limit
        data[8][0] = PRECURSOR + (Long.MAX_VALUE);
        data[8][1] = false;

        return Arrays.asList(data);
    }

    @Test
    public void testPort(){

        url.setPort(port, isValid);
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}

