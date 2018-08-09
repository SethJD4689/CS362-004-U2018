import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

@RunWith(Parameterized.class)
public class URLTest {

    private UrlValidator validator;
    private URL url;

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
        urlIndex = null;
    }

    @Parameterized.Parameter
    public int[] urlIndex;

    @Parameterized.Parameters
    public static Collection<int[]> urlMutations() {

        int tests = SchemeTest.SCHEMES.length * AuthorityTest.AUTHORITIES.length * PortTest.PORTS.length
                * PathTest.PATHS.length * QueryTest.QUERIES.length;

        int[][] indices = new int[tests][5];

        URLPart[] schemes = SchemeTest.SCHEMES;
        URLPart[] authorities = AuthorityTest.AUTHORITIES;
        URLPart[] ports = PortTest.PORTS;
        URLPart[] paths = PathTest.PATHS;
        URLPart[] queries = QueryTest.QUERIES;

        for(int s = 0; s < schemes.length && tests > 0; s++){

            for(int a = 0; a < authorities.length && tests > 0; a++){

                for(int po = 0; po < ports.length && tests > 0; po++){

                    for(int pa = 0; pa < paths.length && tests > 0; pa++){

                        for(int q = 0; q < queries.length && tests > 0; q++){

                            indices[tests - 1][0] = s;
                            indices[tests - 1][1] = a;
                            indices[tests - 1][2] = po;
                            indices[tests - 1][3] = pa;
                            indices[tests - 1][4] = q;
                            tests --;
                        }
                    }
                }
            }
        }

        return Arrays.asList(indices);
    }

    @Test
    public void testUrl(){

        url = new URL();
        url.setScheme(SchemeTest.SCHEMES[urlIndex[0]].getPart(), SchemeTest.SCHEMES[urlIndex[0]].isValid());
        url.setAuthority(AuthorityTest.AUTHORITIES[urlIndex[1]].getPart(), AuthorityTest.AUTHORITIES[urlIndex[1]].isValid());
        url.setPort(PortTest.PORTS[urlIndex[2]].getPart(), PortTest.PORTS[urlIndex[2]].isValid());
        url.setPath(PathTest.PATHS[urlIndex[3]].getPart(), PathTest.PATHS[urlIndex[3]].isValid());
        url.setQuery(QueryTest.QUERIES[urlIndex[4]].getPart(), QueryTest.QUERIES[urlIndex[4]].isValid());

        assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        try{

            assertEquals(url.isURLValid(), validator.isValid(url.getURL()));

        }catch(AssertionError e){

            System.out.println("FAILED: Expected - " + url.isURLValid()
                    + ", URL - " + url.getURL());

            throw e;
        }

        url = null;
    }
}


