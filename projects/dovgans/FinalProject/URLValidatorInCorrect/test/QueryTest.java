import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.List;

/**
 * Tests a URL, query specific, with the following test rules:
 *
 *  - Query may be null
 *  - Query cannot contain whitespace
 *  - Query excepts all characters
 */
@RunWith(Parameterized.class)
public class QueryTest {

    private UrlValidator validator;
    private URL url;

    public final static String BASE_QUERY = "";                  // Null Value

    public final static URLPart QUERIES[] = {

            new URLPart(BASE_QUERY, true),
            new URLPart("?test=query", true),
            new URLPart("?test = query", false),    // White Space in middle
            new URLPart("\n?test=query", false),    // White Space in beginning
            new URLPart("?test=query\t", false),    // White Space at end
    };

    @Before
    public void setup(){

        validator = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS);

        url = new URL(SchemeTest.BASE_SCHEME, AuthorityTest.BASE_AUTHORITY,
                PortTest.BASE_PORT, PathTest.BASE_PATH, BASE_QUERY,
                true, true, true,
                true, true );
    }

    @After
    public void teardown(){

        validator = null;
        url = null;
        query = null;
    }

    @Parameterized.Parameter
    public URLPart query;

    @Parameterized.Parameters(name= "Query Test {0}")
    public static List<URLPart> queryMutations() {

        return Arrays.asList(QUERIES);
    }

    @Test
    public void testQuery(){

        url.setQuery(query.getPart(), query.isValid());

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        } catch(AssertionError e){

            System.out.println("FAILED QUERY: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;

        } catch(NullPointerException e){

            System.out.println("FAILED QUERY: " + e.getMessage() + ", URL - " + url.getURL());
            throw e;
        }
    }
}


