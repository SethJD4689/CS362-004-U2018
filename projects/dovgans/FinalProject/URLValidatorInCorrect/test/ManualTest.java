import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

/**
 * Tests various URL manually.
 */
@RunWith(Parameterized.class)
public class ManualTest {

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
    }

    @Parameterized.Parameter(0)
    public String url;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "[{index}] Expected: {1}, URL: {0}")
    public static Collection<Object[]> portMutations() {

        Object[][] data = new Object[10][2];

        data[0][0] = "http://www.google.com";
        data[0][1] = true;

        data[1][0] = "ftp://go.com:65535/$23";
        data[1][1] = true;

        data[2][0] = "h3t://go.au:0/test1/file";
        data[2][1] = true;

        data[3][0] = "HTTP://www.google.com";
        data[3][1] = true;

        data[4][0] = "file://";
        data[4][1] = true;

        data[5][0] = "http://.";
        data[5][1] = false;

        data[6][0] = "http://go.a1a";
        data[6][1] = false;

        data[7][0] = "http://1.2.3.4/../";
        data[7][1] = false;

        data[8][0] = "http://www.google.com:65a/t123";
        data[8][1] = false;

        data[9][0] = "http://www.google.com:80/#";
        data[9][1] = false;

        return Arrays.asList(data);
    }

    @Test
    public void testURL(){

        try{

            assertEquals(isValid, validator.isValid(url));

        } catch(AssertionError e){

            System.out.println("FAILED AUTHORITY: " + e.getMessage() + ", URL - " + url);
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED AUTHORITY: " + e.getMessage() + ", URL - " + url);
            throw e;
        }
    }
}

