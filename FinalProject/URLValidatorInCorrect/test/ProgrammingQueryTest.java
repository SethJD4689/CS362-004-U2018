import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import java.util.Random;

/**
 * Tests a URL, query specific, with the following test rules:
 *
 *  - Query may be null
 *  - Query cannot contain whitespace
 *  - Query excepts all characters
 */
@RunWith(Parameterized.class)
public class ProgrammingQueryTest {

    private static UrlValidator validator;
    private static URL url;
    private static final String QUERY = "?test=query";

    @BeforeClass
    public static void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL("Http:", "//www.test.com", "", "", QUERY,
                true, true, true, true, true );
    }

    @Parameterized.Parameter(0)
    public String query;

    @Parameterized.Parameter(1)
    public boolean isValid;

    @Parameterized.Parameters(name= "{index}: Query - {0}, Expected = {1}")
    public static Collection<Object[]> queryMutations() {

        Object[][] data = new Object[4][2];

        Random random = new Random();
        random.setSeed(System.nanoTime());

        // Base Test
        data[0][0] = QUERY;
        data[0][1] = true;

        // Query with beginning whitespace
        data[1][0] = "\n" + QUERY;
        data[1][1] = false;

        // Query with middle whitespace
        data[2][0] = "?test = query";
        data[2][1] = false;

        // Query with end whitespace
        data[3][0] = QUERY + "\t";
        data[3][1] = false;

        return Arrays.asList(data);
    }

    @Test
    public void testQuery(){

        url.setQuery(query, isValid);
        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));
    }
}


