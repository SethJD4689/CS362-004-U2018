import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.List;

/**
 * Tests a URL, path specific, with the following test rules:
 *
 *  - Path may be null
 *  - Path must be preceded by "/" or "//"
 *  - Path cannot start with "/../" or contain "/.."
 *  - Path must contain only alphanumeric and "~ ! @ $ % & * = + , . _ ;"
 */
@RunWith(Parameterized.class)
public class PathTest {

    private UrlValidator validator;
    private URL url;

    private static final String VALID_CHARACTERS = "abcdefghijklmnopqrstuvwxyz" +
            "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@$%&*=+,._;";

    public static final String BASE_PATH = "";                       // Null

    public static final URLPart PATHS[] = {

            new URLPart(BASE_PATH, true),
            new URLPart("//Path/test", true),           // Valid Path
            new URLPart("//Path/test^{}<>", false),     // Invalid Characters
            new URLPart("Path/test", false),            // Not preceded by "//"
            new URLPart("/Path/test", true),            // Preceded by "/"
            new URLPart("/../Path/test", false),        // Invalid Starting Characters "/../"
            new URLPart("/..", false),                  // Invalid Path "/.."
            new URLPart("//test/path" + VALID_CHARACTERS, true)  // All valid Characters
    };

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(SchemeTest.BASE_SCHEME, AuthorityTest.BASE_AUTHORITY,
                PortTest.BASE_PORT, BASE_PATH, QueryTest.BASE_QUERY,
                true, true, true,
                true, true );
    }

    @After
    public void teardown(){

        validator = null;
        url = null;
        path = null;
    }

    @Parameterized.Parameter
    public URLPart path;

    @Parameterized.Parameters(name= "Path Test {0}")
    public static List<URLPart> pathMutations() {

        return Arrays.asList(PATHS);
    }

    @Test
    public void testPath(){

        url.setPath(path.getPart(), path.isValid());

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        } catch(AssertionError e){

            System.out.println("FAILED PATH: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED PATH: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;
        }
    }
}

