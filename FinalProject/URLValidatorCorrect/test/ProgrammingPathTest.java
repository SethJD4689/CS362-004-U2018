import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;
import java.util.Random;

import static org.junit.Assert.assertEquals;

/**
 * Tests a URL, path specific, with the following test rules:
 *
 *  - Path may be null
 *  - Path must be preceded by "/" or "//"
 *  - Path cannot start with "/../" or contain "/.."
 *  - Path must contain only alphanumeric and "~ ! @ $ % & * = + , . _ ;"
 */
@RunWith(Parameterized.class)
public class ProgrammingPathTest {

    private static UrlValidator validator;
    private static URL url;
    private static final String PATH = "//test/path";

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL("Http:", "//www.test.com", "", PATH, "",
                true, true, true, true, true );
    }

    @Parameterized.Parameter(0)
    public String path;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Path - {0}, Expected = {1}")
    public static Collection<Object[]> schemeMutations() {

        final String VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz" +
                "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@$%&*=+,._;";

        Object[][] data = new Object[8][2];

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // Base Test
        data[0][0] = PATH;
        data[0][1] = true;

        // Includes invalid characters
        data[1][0] = PATH + "^{}<>";
        data[1][1] = false;

        // Null
        data[2][0] = "";
        data[2][1] = true;

        // Not preceded by valid "//"
        data[3][0] = PATH.substring(2, PATH.length());
        data[3][1] = false;

        // Preceded by valid "/"
        data[4][0] = PATH.substring(1, PATH.length());
        data[4][1] = true;

        // Invalid Starting characters
        data[5][0] = "/../" + PATH.substring(2, PATH.length());
        data[5][1] = false;

        // Invalid string in path
        data[6][0] = "/..";
        data[6][1] = false;

        // Includes valid characters
        data[7][0] = PATH + "/" + VALID_CHARACTERS;
        data[7][1] = true;

        return Arrays.asList(data);
    }

    @Test
    public void testPath(){

        url.setPath(path, isValid);
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}

