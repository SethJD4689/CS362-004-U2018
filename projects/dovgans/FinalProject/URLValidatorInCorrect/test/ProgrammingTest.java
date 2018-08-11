import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.Rule;
import org.junit.rules.ErrorCollector;
import static org.junit.Assert.assertEquals;

public class ProgrammingTest {

    private static UrlValidator validator;
    private static URL url;

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
        url = null;
    }

    @Test
    public void urlMutations() {

        int tests = SchemeTest.SCHEMES.length * AuthorityTest.AUTHORITIES.length * PortTest.PORTS.length
                * PathTest.PATHS.length * QueryTest.QUERIES.length;

        for(int s = 0; s < SchemeTest.SCHEMES.length && tests > 0; s++){

            for(int a = 0; a < AuthorityTest.AUTHORITIES.length && tests > 0; a++){

                for(int po = 0; po < PortTest.PORTS.length && tests > 0; po++){

                    for(int pa = 0; pa < PathTest.PATHS.length && tests > 0; pa++){

                        for(int q = 0; q < QueryTest.QUERIES.length && tests > 0; q++){

                            testUrl(s, a, po, pa, q);
                            tests --;
                        }
                    }
                }
            }
        }
    }

    @Rule
    public ErrorCollector collector = new ErrorCollector();

    private void testUrl(int sI, int aI, int poI, int paI, int qI){

        url = new URL();
        url.setScheme(SchemeTest.SCHEMES[sI].getPart(), SchemeTest.SCHEMES[sI].isValid());
        url.setAuthority(AuthorityTest.AUTHORITIES[aI].getPart(), AuthorityTest.AUTHORITIES[aI].isValid());
        url.setPort(PortTest.PORTS[poI].getPart(), PortTest.PORTS[poI].isValid());
        url.setPath(PathTest.PATHS[paI].getPart(), PathTest.PATHS[paI].isValid());
        url.setQuery(QueryTest.QUERIES[qI].getPart(), QueryTest.QUERIES[qI].isValid());

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        } catch(AssertionError e){

            System.out.println("FAILED URL: " + e.getMessage() + ", URL - " + url.getURL());
            collector.addError(e);
        }
    }
}


